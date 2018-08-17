#file(GLOB C_FILES "*.c")

set(C_FILES
	crc.c
	main.c)

# Set SUPPORT_DRAW_SPROCKET so the DrawSprocket code gets used instead of the older codepath
add_compile_definitions(SUPPORT_DRAW_SPROCKET)

add_executable(main "${C_FILES}")

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cseries)
