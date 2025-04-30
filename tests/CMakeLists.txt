# Создание исполняемого файла для тестов
add_executable(MyTest MyTest.cpp)

# Линкуем тесты с GoogleTest и основной библиотекой
target_link_libraries(MyTest gtest gtest_main Search-ENGINELib)

# Добавление теста для CTest
add_test(NAME MyTest COMMAND MyTest)
