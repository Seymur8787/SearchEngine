#include "inverted_index.h"
#include <sstream>
#include <iostream>

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    std::lock_guard<std::mutex> lock(index_mutex);
    docs = input_docs;
    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::istringstream file(docs[doc_id]);
        std::string word;
        std::unordered_map<std::string, size_t> word_count;

        while (file >> word) {
            word_count[word]++;
        }

        for (const auto& [word, count] : word_count) {
            freq_dictionary[word].push_back({ static_cast<int>(doc_id), static_cast<int>(count) });
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    std::lock_guard<std::mutex> lock(index_mutex);
    auto it = freq_dictionary.find(word);
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    return {};
}
