# Указываем исходники
set(SOURCES
    main.cpp
    converter_json.cpp
    inverted_index.cpp
    search_server.cpp
)

# Добавляем исполняемый файл
add_executable(Search-ENGINE ${SOURCES})

# Указываем директории заголовков
target_include_directories(Search-ENGINE PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${json_SOURCE_DIR}/include    
)

# Подключаем библиотеки
target_link_libraries(Search-ENGINE PRIVATE nlohmann_json::nlohmann_json)
