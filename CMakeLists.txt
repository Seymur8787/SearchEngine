# Минимальная версия CMake
cmake_minimum_required(VERSION 3.8)

# Название проекта
project(Search-ENGINE VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем FetchContent для зависимостей
include(FetchContent)

# Подключаем GoogleTest через FetchContent
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Подключаем JSON for Modern C++
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Устанавливаем линковку для всех конфигураций
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

# Добавляем поддиректории
add_subdirectory(src)
add_subdirectory(tests)

# Включаем тестирование
enable_testing()

# Устанавливаем директорию для исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/x64-release/Search-ENGINE)

# Устанавливаем рабочую директорию для отладчика в Visual Studio
set_target_properties(Search-ENGINE PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/data")
