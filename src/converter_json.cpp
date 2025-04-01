#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../includes/converter_json.h"

using json = nlohmann::json;

// Вспомогательная функция для чтения JSON
json ReadJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    json j;
    file >> j;
    return j;
}

// Конструктор класса, загружающий конфигурацию при создании объекта
ConverterJSON::ConverterJSON() {
    try {
        config = ReadJSON("config.json");
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки config.json: " << e.what() << std::endl;
        config = json::object(); // создаём пустой объект, чтобы не падало
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    if (!config.contains("files")) {
        throw std::runtime_error("Ошибка: в config.json отсутствует поле 'files'");
    }

    std::vector<std::string> files = config["files"];
    std::vector<std::string> documents;

    for (const auto& file : files) {
        std::ifstream doc(file);
        if (!doc.is_open()) {
            std::cerr << "Ошибка открытия файла: " << file << std::endl;
            continue;
        }
        std::string content((std::istreambuf_iterator<char>(doc)), std::istreambuf_iterator<char>());
        documents.push_back(content);
    }

    return documents;
}

int ConverterJSON::GetResponsesLimit() {
    if (!config.contains("config") || !config["config"].contains("max_responses")) {
        return 5; // Значение по умолчанию, если в config.json нет max_responses
    }
    return config["config"]["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests() {
    if (!config.contains("requests")) {
        throw std::runtime_error("Ошибка: в config.json отсутствует поле 'requests'");
    }
    return config["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json output;
    output["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string requestKey = "request" + std::to_string(i + 1);
        json requestResult;

        if (answers[i].empty()) {
            requestResult["result"] = "empty"; // Исправлено с "false" на "empty"
        }
        else {
            requestResult["result"] = "true";
            requestResult["relevance"] = json::array();
            for (const auto& [docID, rank] : answers[i]) {
                requestResult["relevance"].push_back({ {"doc_id", docID}, {"rank", rank} });
            }
        }

        output["answers"][requestKey] = requestResult;
    }

    std::ofstream outFile("answers.json");
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось записать файл answers.json");
    }
    outFile << output.dump(4);
}
