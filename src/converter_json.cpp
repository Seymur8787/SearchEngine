#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "converter_json.h"

using json = nlohmann::json;

json ReadJSON(const std::string& filename) {
    std::ifstream file(filename);
    std::cout << filename << std::endl;
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    json j;
    file >> j;
    return j;
}

ConverterJSON::ConverterJSON() {
    try {
        config = ReadJSON("config.json");
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки config.json: " << e.what() << std::endl;
        config = json::object();
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
    if (!config.contains("max_responses")) {
        return 5;
    }
    return config["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests() {
    json requests = ReadJSON("requests.json");
    if (!requests.contains("requests")) {
        throw std::runtime_error("Ошибка: в requests.json отсутствует поле 'requests'");
    }
    return requests["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<RelativeIndex>>& answers) {
    json j;
    j["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string request_name = "request" + std::string(3 - std::to_string(i + 1).length(), '0') + std::to_string(i + 1);
        json request_result;

        if (answers[i].empty()) {
            request_result["result"] = "false";
        }
        else {
            request_result["result"] = "true";

            json relevance = json::array();
            for (const auto& ri : answers[i]) {
                relevance.push_back({
                    {"docid", ri.doc_id},
                    {"rank", std::round(ri.rank * 1000.0) / 1000.0}
                    });
            }

            request_result["relevance"] = relevance;
        }

        j["answers"][request_name] = request_result;
    }

    try {
        std::ofstream file("answers.json");
        if (!file.is_open()) {
            throw std::ios_base::failure("Не удалось открыть файл для записи. Возможно: нет прав, файл занят или диск переполнен.");
        }

        file << std::setw(4) << j;
        if (file.fail()) {
            throw std::ios_base::failure("Ошибка при записи в файл: возможно, закончилось место на диске.");
        }

        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "[Ошибка] Не удалось сохранить answers.json: " << e.what() << std::endl;
        // Можно выбросить дальше, если нужно:
        // throw;
    }
}
