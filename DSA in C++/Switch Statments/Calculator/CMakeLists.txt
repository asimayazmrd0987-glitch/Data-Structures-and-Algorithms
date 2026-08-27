cmake_minimum_required(VERSION 3.16)

project(CppCalculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(CppCalculator
    main.cpp
    calculatorwindow.cpp
    calculatorwindow.h
)

target_link_libraries(CppCalculator PRIVATE Qt6::Widgets)