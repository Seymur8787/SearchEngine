cmake_minimum_required(VERSION 3.16)

# Название проекта
project(Search-ENGINE VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Устанавливаем директорию для бинарников (опционально для VS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Подключаем FetchContent для зависимостей
include(FetchContent)
#find_package(fmt CONFIG REQUIRED)

# JSON for Modern C++
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


# GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Подключаем поддиректории с логикой и тестами
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(Search-ENGINE PRIVATE nlohmann_json::nlohmann_json)

# Включаем тестирование
enable_testing()
