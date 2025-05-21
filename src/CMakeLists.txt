# Указываем исходники для библиотеки
set(SOURCES
    converter_json.cpp
    inverted_index.cpp
    search_server.cpp
)

# Создаём статическую библиотеку
add_library(Search-ENGINELib STATIC ${SOURCES})

# Указываем заголовочные файлы
target_include_directories(Search-ENGINELib PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
    ${json_SOURCE_DIR}/include
)

# Подключаем JSON-библиотеку
target_link_libraries(Search-ENGINELib PUBLIC nlohmann_json::nlohmann_json)

# Создаём исполняемый файл с main.cpp
add_executable(Search-ENGINE main.cpp)

# Линкуем основную библиотеку к исполняемому файлу
target_link_libraries(Search-ENGINE PRIVATE Search-ENGINELib)
