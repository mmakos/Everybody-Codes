cmake_minimum_required(VERSION 3.27)
project(everybody_codes)

set(CMAKE_CXX_STANDARD 26)

set(SOURCES src/main/cpp/utils/utils.cpp)
set(SOURCE_DIR src/main/cpp)

set(YEARS 2024)
set(QUESTS 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)

foreach (YEAR IN LISTS YEARS)
    foreach (QUEST IN LISTS QUESTS)
        set(TASK_EXECUTABLE "year${YEAR}quest${QUEST}")
        set(EXECUTABLE_SRC ${SOURCE_DIR}/year${YEAR}/quest${QUEST}.cpp)

        if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${EXECUTABLE_SRC})
            add_executable(${TASK_EXECUTABLE} ${EXECUTABLE_SRC} ${SOURCES})

            target_include_directories(${TASK_EXECUTABLE} PRIVATE src/main/cpp/utils)

            add_custom_command(
                    TARGET ${TASK_EXECUTABLE} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/input
                    ${CMAKE_BINARY_DIR}/input
            )
        endif ()
    endforeach ()
endforeach ()
