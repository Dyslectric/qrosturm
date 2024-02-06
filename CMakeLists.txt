cmake_minimum_required(VERSION 3.27.2)
project(qrosturm VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_library(qrosturm src/qrosturm.cpp)
add_executable(qrosturm-test test/main.cpp)

include_directories(include)
target_link_libraries(qrosturm-test qrosturm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
