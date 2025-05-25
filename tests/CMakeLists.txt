# Указываем исходники, которые нужны для тестов
add_executable(MyTest
    MyTest.cpp
    ${CMAKE_SOURCE_DIR}/src/converter_json.cpp
    ${CMAKE_SOURCE_DIR}/src/inverted_index.cpp
    ${CMAKE_SOURCE_DIR}/src/search_server.cpp
)

# Подключаем заголовки
target_include_directories(MyTest PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
)

# Линкуем зависимости
target_link_libraries(MyTest PRIVATE
    gtest
    gtest_main
    nlohmann_json::nlohmann_json
)

# Добавляем в CTest
add_test(NAME MyTest COMMAND MyTest)
