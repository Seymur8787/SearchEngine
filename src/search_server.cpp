#include "search_server.h"
#include <sstream>
#include <map>
#include <algorithm>
#include <thread>

SearchServer::SearchServer(InvertedIndex& idx, int response_limit)
    : _index(idx), _response_limit(response_limit) {
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> results(queries_input.size());
    std::vector<std::thread> threads;

    for (size_t i = 0; i < queries_input.size(); ++i) {
        threads.emplace_back([&, i]() {
            std::map<int, float> doc_relevance;
            std::istringstream stream(queries_input[i]);
            std::string word;

            // Step 1: Count total relevance per document
            while (stream >> word) {
                auto entries = _index.GetWordCount(word);
                for (const auto& entry : entries) {
                    doc_relevance[entry.doc_id] += static_cast<float>(entry.count);
                }
            }

            // Step 2: Find max relevance
            float max_rank = 0.0f;
            for (const auto& [doc_id, relevance] : doc_relevance) {
                if (relevance > max_rank) {
                    max_rank = relevance;
                }
            }

            // Step 3: Normalize relevance and collect results
            std::vector<RelativeIndex> sorted_results;
            for (const auto& [doc_id, relevance] : doc_relevance) {
                float normalized_rank = (max_rank == 0.0f) ? 0.0f : relevance / max_rank;
                sorted_results.push_back({ doc_id, normalized_rank });
            }

            // Step 4: Sort results by rank descending, then by doc_id ascending
            std::sort(sorted_results.begin(), sorted_results.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
                return (a.rank > b.rank) || (a.rank == b.rank && a.doc_id < b.doc_id);
                });

            // Step 5: Apply response limit
            if (sorted_results.size() > static_cast<size_t>(_response_limit)) {
                sorted_results.resize(_response_limit);
            }

            results[i] = std::move(sorted_results);
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return results;
}
