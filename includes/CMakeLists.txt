# Создание исполняемого файла для тестов
add_executable(MyTest MyTest.cpp)


# Линкуем тесты с GoogleTest, основной библиотекой и json
target_link_libraries(MyTest PRIVATE
    gtest
    gtest_main
    Search-ENGINELib
    nlohmann_json::nlohmann_json     
)

# Добавление теста для CTest
add_test(NAME MyTest COMMAND MyTest)
