#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

struct Entry {
    int doc_id;
    int count;
};

class InvertedIndex {
public:
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);
    std::vector<Entry> GetWordCount(const std::string& word) const;

private:
    std::vector<std::string> docs;
    std::unordered_map<std::string, std::vector<Entry>> freq_dictionary;
    mutable std::mutex index_mutex;
};
