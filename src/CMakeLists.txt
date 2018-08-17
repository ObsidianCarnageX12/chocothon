set(C_FILES
#	computer_interface.c
	crc.c
	devices.c
	effects.c
#	export_definitions.c
	fades.c
	files_chocothon.c
#	files_macintosh.c
#	find_files.c
#	flood_map.c
#	game_dialogs.c
#	game_errors.c
#	game_sound.c
#	game_wad.c
#	game_window.c
#	game_window_macintosh.c
#	images.c
#	import_definitions.c
#	interface.c
#	interface_macintosh.c
	items.c
#	keyboard_dialog.c
	lightsource.c
#	low_level_textures.c
	main.c
	map.c
	map_accessors.c
#	map_constructors.c
#	marathon2.c
	media.c
#	monsters.c
	motion_sensor.c
#	mouse.c
#	music.c
#	network.c
#	network_adsp.c
#	network_ddp.c
#	network_dialogs.c
#	network_games.c
#	network_lookup.c
#	network_microphone.c
#	network_modem.c
#	network_modem_protocol.c
#	network_names.c
#	network_speaker.c
#	network_stream.c
	overhead_map.c
#	overhead_map_macintosh.c
	pathfinding.c
	physics.c
#	physics_patches.c
	placement.c
	platforms.c
	player.c
#	preferences.c
#	preprocess_map_mac.c
#	progress.c
	projectiles.c
	render.c
	scenery.c
#	scottish_textures.c
#	screen.c
#	screen_drawing.c
#	serial_numbers.c
#	shapes.c
#	shapes_macintosh.c
#	shell.c
#	sound_macintosh.c
#	textures.c
#	valkyrie.c
#	vbl.c
#	vbl_macintosh.c
	wad.c
#	wad_macintosh.c
	wad_prefs.c
#	wad_prefs_macintosh.c
	weapons.c
	world.c
)

set(CMAKE_C_FLAGS "-Wall -Wpedantic")

# Set SUPPORT_DRAW_SPROCKET so the DrawSprocket code gets used instead of the older codepath
# TODO: remove this when the old codepaths are pruned, and the new ones rewritten.
add_compile_definitions(SUPPORT_DRAW_SPROCKET)

add_executable(main "${C_FILES}")

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cseries)
