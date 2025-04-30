#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "search_server.h"  // сюда попала структура RelativeIndex

class ConverterJSON {
public:
    ConverterJSON();

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void PutAnswers(const std::vector<std::vector<RelativeIndex>>& answers);

private:
    nlohmann::json config;
};

#endif // CONVERTER_JSON_H
