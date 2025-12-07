cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(bigint-lab)

set(exe_name ${PROJECT_NAME})

set(test_name test_${PROJECT_NAME})

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(corelib OBJECT src/BigInt.cpp)

target_include_directories(corelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${exe_name} src/main.cpp)
target_link_libraries(${exe_name} corelib)

target_include_directories(${exe_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${test_name} tests/test_bigint.cpp)
target_link_libraries(${test_name} gtest_main corelib)

target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GoogleTest)

gtest_discover_tests(${test_name})
