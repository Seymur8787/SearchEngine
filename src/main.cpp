#include "inverted_index.h"
#include <iostream>
#include "converter_json.h"
#include "search_server.h"
#include <locale>


int main() {
    try {
        std::locale::global(std::locale("ru_RU.UTF-8")); // Более надёжный вариант
    }
    catch (const std::exception& e) {
        std::cerr << "Не удалось установить русскую локаль: " << e.what() << std::endl;
    }

    ConverterJSON jsonConverter;
    InvertedIndex index;

    index.UpdateDocumentBase(jsonConverter.GetTextDocuments());

    int responseLimit = jsonConverter.GetResponsesLimit();
    SearchServer searchServer(index, responseLimit);

    auto results = searchServer.search(jsonConverter.GetRequests());
    jsonConverter.PutAnswers(results);

    return 0;
}
