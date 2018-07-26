cmake_minimum_required(VERSION 3.7)

project(chocothon)

file(GLOB chocothon_SRC "*.c")
file(GLOB chocothon_H "*.h")

add_executable(chocothon ${chocothon_SRC})
