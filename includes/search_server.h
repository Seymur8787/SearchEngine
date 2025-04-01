#pragma once
#include "inverted_index.h"
#include <vector>
#include <string>
#include <mutex>
#include <thread>

class SearchServer {
public:
    explicit SearchServer(InvertedIndex& idx) : _index(idx) {}

    std::vector<std::vector<std::pair<int, float>>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;
    std::mutex search_mutex;
};
