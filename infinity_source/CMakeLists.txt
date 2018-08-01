cmake_minimum_required(VERSION 3.7)

project(chocothon)

subdirs(cseries CSeriesInterfaces CSeriesLibraries marathon2)

find_package(SDL2 REQUIRED)


include_directories(
	${PROJECT_SOURCE_DIR}/cseries
	${PROJECT_SOURCE_DIR}/CSeriesInterfaces
	${PROJECT_SOURCE_DIR}/CSeriesLibraries
    ${PROJECT_SOURCE_DIR}/marathon2
    ${SDL2_INCLUDE_DIRS}
)
