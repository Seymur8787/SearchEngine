# Указываем исходники для основного приложения
set(SOURCES
    converter_json.cpp
    inverted_index.cpp
    search_server.cpp
    main.cpp
)

# Создаём исполняемый файл
add_executable(Search-ENGINE ${SOURCES})

# Подключаем заголовочные файлы
target_include_directories(Search-ENGINE PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${json_SOURCE_DIR}/include
)

# Подключаем внешние библиотеки
target_link_libraries(Search-ENGINE PRIVATE nlohmann_json::nlohmann_json)
