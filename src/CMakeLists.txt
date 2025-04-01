# Указание всех исходных файлов
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Создаём библиотеку из исходников
add_library(Search-ENGINELib ${SOURCES})

# Подключаем заголовочные файлы
target_include_directories(Search-ENGINELib PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
    ${json_SOURCE_DIR}/single_include  # Подключаем JSON
)

# Создаём исполняемый файл из main.cpp
add_executable(Search-ENGINE main.cpp)

# Линкуем исполняемый файл с библиотекой
target_link_libraries(Search-ENGINE PRIVATE Search-ENGINELib)
