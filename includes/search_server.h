#pragma once
#include "inverted_index.h"
#include <vector>
#include <string>
#include <thread>

struct RelativeIndex {
    int doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return doc_id == other.doc_id && rank == other.rank;
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx, int response_limit);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;
    int _response_limit;
};
