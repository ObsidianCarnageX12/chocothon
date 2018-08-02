file(GLOB C_FILES "*.c")

add_executable(main ${C_FILES})

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cseries)
