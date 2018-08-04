file(GLOB C_FILES "*.c")


set(SOURCE_FILES crc.c files_chocothon.c)
add_executable(main "${SOURCE_FILES}")

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cseries)
