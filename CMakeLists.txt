cmake_minimum_required(VERSION 3.15)
project(Rational_Calculator)

set(CMAKE_CXX_STANDARD 20)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
add_executable(Rational_Calculator main.cpp classes/Fraction.h classes/Fraction.cpp classes/My_expression.cpp classes/My_expression.h classes/Math_element.h classes/Math_element.cpp)