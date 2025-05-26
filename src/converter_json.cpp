#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>   // Для std::setw
#include <cmath>     // Для std::round
#include <nlohmann/json.hpp>
#include "converter_json.h"

using json = nlohmann::json;

// Чтение JSON из файла
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

// Конструктор
ConverterJSON::ConverterJSON() {
    try {
        config = ReadJSON("files/config.json");
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки config.json: " << e.what() << std::endl;
        config = json::object(); // Пустой объект
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> documents;

    try {
        if (!config.contains("files") || !config["files"].is_array()) {
            throw std::runtime_error("Ошибка: поле 'files' отсутствует или не является массивом");
        }

        std::vector<std::string> files = config["files"].get<std::vector<std::string>>();

        for (const auto& file : files) {
            std::ifstream doc(file);
            if (!doc.is_open()) {
                std::cerr << "Ошибка открытия файла: " << file << std::endl;
                continue;
            }
            std::string content((std::istreambuf_iterator<char>(doc)), std::istreambuf_iterator<char>());
            documents.push_back(content);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при получении документов: " << e.what() << std::endl;
    }

    return documents;
}


// Получение лимита ответов
int ConverterJSON::GetResponsesLimit() {
    if (!config.contains("max_responses")) {
        return 5;
    }
    return config["max_responses"].get<int>();
}

// Получение запросов
std::vector<std::string> ConverterJSON::GetRequests() {
    json requests = ReadJSON("files/requests.json");
    if (!requests.contains("requests")) {
        throw std::runtime_error("Ошибка: в requests.json отсутствует поле 'requests'");
    }
    return requests["requests"].get<std::vector<std::string>>();
}

// Сохранение ответов
void ConverterJSON::PutAnswers(const std::vector<std::vector<RelativeIndex>>& answers) {
    json j;
    j["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        // Формируем имя запроса: request001, request002 и т.д.
        char buffer[16];
        std::snprintf(buffer, sizeof(buffer), "request%03zu", i + 1);
        std::string request_name = buffer;

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
        std::ofstream file("files/answers.json");
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
    }
}
