cmake_minimum_required(VERSION 3.25)
project(LongFloat CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC
        src/LongFloat.cpp
)

enable_testing()

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE
        PROJECT_NAME=${PROJECT_NAME}
)

add_executable(${PROJECT_NAME}_PI tests/pi.cpp)
target_link_libraries(${PROJECT_NAME}_PI PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_PI PRIVATE include)

add_executable(${PROJECT_NAME}_tests tests/test.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)