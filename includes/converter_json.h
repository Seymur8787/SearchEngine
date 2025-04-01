#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>  // Подключаем JSON-библиотеку

class ConverterJSON {
public:
    ConverterJSON(); // Добавляем конструктор

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    nlohmann::json config; // Добавляем приватное поле для хранения конфигурации
};

#endif // CONVERTER_JSON_H
