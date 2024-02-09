cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(TEST_SRC TagTests.cpp BaseComponentTest.cpp)

add_executable(tests ${TEST_SRC})

target_include_directories(tests PUBLIC lib/googletest-master/googletest/include)
target_include_directories(tests PUBLIC lib/googletest-master/googlemock/include)

target_link_libraries(tests gtest gtest_main core)
