#include "inverted_index.h"
#include <iostream>
#include "converter_json.h"
#include "search_server.h"
#include <locale>

int main() {
    std::locale::global(std::locale("Rus"));

    ConverterJSON jsonConverter;
    InvertedIndex index;

    index.UpdateDocumentBase(jsonConverter.GetTextDocuments());

    int responseLimit = jsonConverter.GetResponsesLimit();
    SearchServer searchServer(index, responseLimit); // передаём лимит

    auto results = searchServer.search(jsonConverter.GetRequests());
    jsonConverter.PutAnswers(results);

    return 0;
}
