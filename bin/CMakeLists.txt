add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE argparser)
target_link_libraries(${PROJECT_NAME} PRIVATE sandpile)
target_link_libraries(${PROJECT_NAME} PRIVATE queue)