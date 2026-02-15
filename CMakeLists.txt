cmake_minimum_required(VERSION 3.10)
project(ImageCpp VERSION 0.0.1 DESCRIPTION "ImageCpp" LANGUAGES CXX)
include(CTest)

if(BUILD_TESTING)
    add_executable(ImageTest ImageTest.cpp)
    add_executable(ImageCpp o.cpp
            ImageTest.cpp)
    target_link_libraries(ImageCpp PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(ImageTest)
endif()
