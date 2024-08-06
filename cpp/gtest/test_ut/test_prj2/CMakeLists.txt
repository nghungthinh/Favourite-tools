# Get the directory name
get_filename_component(TEST_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Add the executable for test_prj2
add_executable(${TEST_NAME} test_prj2.cpp ${TEST_PRJ1})

# Link the executable with gtest
target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES})

# Add the test
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
