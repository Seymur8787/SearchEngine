#include <gtest/gtest.h>
#include "../includes/converter_json.h"
#include "../includes/inverted_index.h"
#include "../includes/search_server.h"
#include <fstream>
// Тест для ConverterJSON
TEST(ConverterJSONTest, GetTextDocuments) {
    ConverterJSON converter;
    std::vector<std::string> files = converter.GetTextDocuments();
    ASSERT_FALSE(files.empty()); // Проверяем, что список документов не пуст
}

// Тест для InvertedIndex
TEST(InvertedIndexTest, IndexingWords) {
    InvertedIndex index;
    std::vector<std::string> docs = {
        "word1 word2 word3",
        "word2 word3 word4 word4"
    };
    index.UpdateDocumentBase(docs);

    auto result = index.GetWordCount("word2");
    ASSERT_EQ(result.size(), 2); // Ожидаем 2 документа с этим словом
    ASSERT_EQ(result[0].doc_id, 0);
    ASSERT_EQ(result[1].doc_id, 1);
    ASSERT_EQ(result[0].count, 1);
    ASSERT_EQ(result[1].count, 1);
}

// Тест для SearchServer
TEST(SearchServerTest, SearchQuery) {
    InvertedIndex index;
    index.UpdateDocumentBase({ "word1 word2", "word2 word3", "word3 word4" });

    int response_limit = 5;
    SearchServer server(index, response_limit);
    auto results = server.search({ "word2" });

    ASSERT_EQ(results.size(), 1); // Один запрос
    ASSERT_EQ(results[0].size(), 2); // "word2" встречается в 2 документах

    EXPECT_EQ(results[0][0].doc_id, 0);
    EXPECT_EQ(results[0][1].doc_id, 1);

    // Проверка нормализованных значений rank
    EXPECT_NEAR(results[0][0].rank, 1.0f, 0.01f); // Максимальный rank
    EXPECT_NEAR(results[0][1].rank, 1.0f, 0.01f); // Такой же счёт, тот же rank
}

TEST(ConverterJSONTest, GetTextDocuments) {
    ConverterJSON converter;
    std::vector<std::string> files = converter.GetTextDocuments();
    ASSERT_FALSE(files.empty()); // Проверяем, что список документов не пуст
}



// Главная функция GoogleTest
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
