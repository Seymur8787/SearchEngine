cmake_minimum_required(VERSION 3.16)

# Название проекта
project(Search-ENGINE VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Директория для исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Подключаем FetchContent
include(FetchContent)

# Подключаем nlohmann/json
FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Подключаем GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Поддиректории с исходниками и тестами
add_subdirectory(src)
add_subdirectory(tests)

# Включаем тестирование
enable_testing()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/requests.json
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/requests.json COPYONLY)
