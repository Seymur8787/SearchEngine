#include "../includes/search_server.h"
#include <algorithm>
#include <iostream>

std::vector<std::vector<std::pair<int, float>>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<std::pair<int, float>>> results(queries_input.size());
    std::vector<std::thread> threads;

    for (size_t i = 0; i < queries_input.size(); ++i) {
        threads.emplace_back([&, i]() {
            std::vector<std::pair<int, float>> search_result;
            auto word_count = _index.GetWordCount(queries_input[i]);

            for (const auto& entry : word_count) {
                search_result.emplace_back(entry.doc_id, static_cast<float>(entry.count));
            }

            std::sort(search_result.begin(), search_result.end(),
                [](const auto& a, const auto& b) {
                    return a.second > b.second;
                });

            results[i] = std::move(search_result);
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return results;
}
