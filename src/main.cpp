#include "../includes/inverted_index.h"
#include <iostream>
#include "../includes/converter_json.h"
#include "../includes/search_server.h"
#include <locale>

int main() {
    std::locale::global(std::locale(""));

    ConverterJSON jsonConverter;
    InvertedIndex index;
    SearchServer searchServer(index);

    index.UpdateDocumentBase(jsonConverter.GetTextDocuments());

    auto results = searchServer.search(jsonConverter.GetRequests());
    jsonConverter.PutAnswers(results);

    return 0;
}
//#include <iostream>
//#include <fstream>
//#include <stdexcept>
//#include <nlohmann/json.hpp>
//#include <filesystem>
//
//#include <iostream>
//#include <fstream>
//#include <stdexcept>
//#include <nlohmann/json.hpp>
//#include <filesystem>
//#include <vector>
//
//using json = nlohmann::json;
//namespace fs = std::filesystem;
//
//int main() {
//    // Define the path to the configuration file
//    std::string configPath = "data/config.json";
//
//    // Check if the file exists before opening it
//    if (!fs::exists(configPath)) {
//        throw std::runtime_error("Error: File " + configPath + " not found!");
//    }
//
//    // Open the JSON file
//    std::ifstream file(configPath);
//    if (!file) {
//        throw std::runtime_error("Error: Unable to open " + configPath);
//    }
//
//    // Read JSON content
//    json config;
//    try {
//        file >> config;
//    }
//    catch (const json::parse_error& e) {
//        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
//    }
//
//    // Validate that the "files" field exists and is an array
//    if (!config.contains("files") || !config["files"].is_array()) {
//        throw std::runtime_error("Error: 'files' field is missing or not an array in config.json");
//    }
//
//    // Read the file paths from the JSON safely
//    std::vector<std::string> files;
//    try {
//        files = config["files"].get<std::vector<std::string>>();
//    }
//    catch (const json::type_error& e) {
//        throw std::runtime_error("Error: 'files' field has an invalid format. " + std::string(e.what()));
//    }
//
//    // Debug output
//    std::cout << "File config.json loaded successfully!" << std::endl;
//    std::cout << "Number of files listed in 'files': " << files.size() << std::endl;
//
//    return 0;
//}
//
