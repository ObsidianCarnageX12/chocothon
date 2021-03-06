/*
DEVICES.C
Sunday, December 5, 1993 2:48:44 PM

Tuesday, December 7, 1993 11:12:25 PM
	changed to be Jason compatible, open/close doors, and nixed gratuitous enum.
Tuesday, January 4, 1994 10:36:08 AM
	opening doors can wake monsters.
Sunday, September 18, 1994 6:23:04 PM  (alain)
	much of control panel code has been rewritten. no longer use composite sides,
	but a flag in the side data structure. some control panels work over time (refueling)
	and there are on/off textures associated with each control panel. and sounds.
Friday, June 9, 1995 11:43:37 AM  (Jason')
	destroy-able switches.
Wednesday, June 21, 1995 8:31:57 AM  (Jason)
	tag switches.
*/

#include "cseries.h"

#include "map.h"
#include "monsters.h"
#include "interface.h"
#include "player.h"
#include "platforms.h"
#include "game_sound.h"
#include "computer_interface.h"
//#include "music.h"
#include "lightsource.h"
#include "game_window.h"
#include "items.h"

#ifdef mpwc
#pragma segment marathon
#endif

/* ---------- constants */

#define OXYGEN_RECHARGE_FREQUENCY 0
#define ENERGY_RECHARGE_FREQUENCY 0

#define MAXIMUM_ACTIVATION_RANGE (3*WORLD_ONE)
#define MAXIMUM_PLATFORM_ACTIVATION_RANGE (3*WORLD_ONE)
#define MAXIMUM_CONTROL_ACTIVATION_RANGE (WORLD_ONE+WORLD_ONE_HALF)
#define OBJECT_RADIUS 50

#define MINIMUM_RESAVE_TICKS (2*TICKS_PER_SECOND)

enum
{
	_target_is_platform,
	_target_is_control_panel
};

/* ---------- structures */

enum // control panel sounds
{
	_activating_sound,
	_deactivating_sound,
	_unusuable_sound,

	NUMBER_OF_CONTROL_PANEL_SOUNDS
};

struct control_panel_definition
{
	short panel_class;
	word flags;

	short collection;
	short active_shape, inactive_shape;

	short sounds[NUMBER_OF_CONTROL_PANEL_SOUNDS];
	fixed sound_frequency;

	short item;
};

/* ---------- globals */

#define NUMBER_OF_CONTROL_PANEL_DEFINITIONS (sizeof(control_panel_definitions)/sizeof(struct control_panel_definition))
static struct control_panel_definition control_panel_definitions[]=
{
	// _collection_walls1
	{_panel_is_oxygen_refuel, 0, _collection_walls1, 2, 3, {_snd_oxygen_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_shield_refuel, 0, _collection_walls1, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_double_shield_refuel, 0, _collection_walls1, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/8, NONE},
	{_panel_is_tag_switch, 0, _collection_walls1, 0, 1, {_snd_chip_insertion, NONE, NONE}, FIXED_ONE, _i_uplink_chip},
	{_panel_is_light_switch, 0, _collection_walls1, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_platform_switch, 0, _collection_walls1, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls1, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_pattern_buffer, 0, _collection_walls1, 4, 4, {_snd_pattern_buffer, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_computer_terminal, 0, _collection_walls1, 4, 4, {NONE, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls1, 1, 0, {_snd_destroy_control_panel, NONE, NONE}, FIXED_ONE, NONE},

	// _collection_walls2
	{_panel_is_shield_refuel, 0, _collection_walls2, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_double_shield_refuel, 0, _collection_walls2, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/8, NONE},
	{_panel_is_triple_shield_refuel, 0, _collection_walls2, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/4, NONE},
	{_panel_is_light_switch, 0, _collection_walls2, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_platform_switch, 0, _collection_walls2, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls2, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_pattern_buffer, 0, _collection_walls2, 4, 4, {_snd_pattern_buffer, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_computer_terminal, 0, _collection_walls2, 4, 4, {NONE, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_oxygen_refuel, 0, _collection_walls2, 2, 3, {_snd_oxygen_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls2, 0, 1, {_snd_chip_insertion, NONE, NONE}, FIXED_ONE, _i_uplink_chip},
	{_panel_is_tag_switch, 0, _collection_walls2, 1, 0, {_snd_destroy_control_panel, NONE, NONE}, FIXED_ONE, NONE},

	// _collection_walls3
	{_panel_is_shield_refuel, 0, _collection_walls3, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_double_shield_refuel, 0, _collection_walls3, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/8, NONE},
	{_panel_is_triple_shield_refuel, 0, _collection_walls3, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/4, NONE},
	{_panel_is_light_switch, 0, _collection_walls3, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_platform_switch, 0, _collection_walls3, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls3, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_pattern_buffer, 0, _collection_walls3, 4, 4, {_snd_pattern_buffer, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_computer_terminal, 0, _collection_walls3, 4, 4, {NONE, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_oxygen_refuel, 0, _collection_walls3, 2, 3, {_snd_oxygen_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls3, 0, 1, {_snd_chip_insertion, NONE, NONE}, FIXED_ONE, _i_uplink_chip},
	{_panel_is_tag_switch, 0, _collection_walls3, 1, 0, {_snd_destroy_control_panel, NONE, NONE}, FIXED_ONE, NONE},

	// _collection_walls5
	{_panel_is_shield_refuel, 0, _collection_walls5, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_double_shield_refuel, 0, _collection_walls5, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/8, NONE},
	{_panel_is_triple_shield_refuel, 0, _collection_walls5, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/4, NONE},
	{_panel_is_light_switch, 0, _collection_walls5, 0, 1, {_snd_pfhor_switch_on, _snd_pfhor_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_platform_switch, 0, _collection_walls5, 0, 1, {_snd_pfhor_switch_on, _snd_pfhor_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls5, 0, 1, {_snd_pfhor_switch_on, _snd_pfhor_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_pattern_buffer, 0, _collection_walls5, 4, 4, {_snd_pattern_buffer, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_computer_terminal, 0, _collection_walls5, 4, 4, {NONE, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_oxygen_refuel, 0, _collection_walls5, 2, 3, {_snd_oxygen_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls5, 0, 1, {_snd_chip_insertion, NONE, NONE}, FIXED_ONE, _i_uplink_chip},
	{_panel_is_tag_switch, 0, _collection_walls5, 1, 0, {_snd_destroy_control_panel, NONE, NONE}, FIXED_ONE, NONE},

	// _collection_walls4
	{_panel_is_shield_refuel, 0, _collection_walls4, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_double_shield_refuel, 0, _collection_walls4, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/8, NONE},
	{_panel_is_triple_shield_refuel, 0, _collection_walls4, 2, 3, {_snd_energy_refuel, NONE, NONE}, FIXED_ONE+FIXED_ONE/4, NONE},
	{_panel_is_light_switch, 0, _collection_walls4, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_platform_switch, 0, _collection_walls4, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls4, 0, 1, {_snd_switch_on, _snd_switch_off, _snd_cant_toggle_switch}, FIXED_ONE, NONE},
	{_panel_is_pattern_buffer, 0, _collection_walls4, 4, 4, {_snd_pattern_buffer, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_computer_terminal, 0, _collection_walls4, 4, 4, {NONE, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_oxygen_refuel, 0, _collection_walls4, 2, 3, {_snd_oxygen_refuel, NONE, NONE}, FIXED_ONE, NONE},
	{_panel_is_tag_switch, 0, _collection_walls4, 0, 1, {_snd_chip_insertion, NONE, NONE}, FIXED_ONE, _i_uplink_chip},
	{_panel_is_tag_switch, 0, _collection_walls4, 1, 0, {_snd_destroy_control_panel, NONE, NONE}, FIXED_ONE, NONE},
};

/* ------------ private prototypes */

#ifdef DEBUG
struct control_panel_definition *get_control_panel_definition(short control_panel_type);
#else
#define get_control_panel_definition(i) (control_panel_definitions+(i))
#endif

static short find_action_key_target(short player_index, world_distance range, short *target_type);
static boolean line_side_has_control_panel(short line_index, short polygon_index, short *side_index_with_panel);
static void	change_panel_state(short player_index, short panel_side_index);
static void set_control_panel_texture(struct side_data *side);

static boolean line_is_within_range(short monster_index, short line_index, world_distance range);

static boolean switch_can_be_toggled(short line_index, boolean player_hit);

static void play_control_panel_sound(short side_index, short sound_index);

static boolean get_recharge_status(short side_index);

/* ---------- code */

/* set the initial states of all switches based on the objects they control */
void initialize_control_panels_for_level(
	void)
{
	short side_index;
	struct side_data *side;

	for (side_index= 0, side= map_sides; side_index<dynamic_world->side_count; ++side, ++side_index)
	{
		if (SIDE_IS_CONTROL_PANEL(side))
		{
			struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);
			boolean status= FALSE;

			switch (definition->panel_class)
			{
				case _panel_is_tag_switch:
					status= GET_CONTROL_PANEL_STATUS(side);
					// use default position
					break;

				case _panel_is_light_switch:
					status= get_light_status(side->control_panel_permutation);
					break;

				case _panel_is_platform_switch:
					if (platform_is_on(get_polygon_data(side->control_panel_permutation)->permutation)) status= TRUE;
					break;
			}

			SET_CONTROL_PANEL_STATUS(side, status);
			set_control_panel_texture(side);
		}
	}

	return;
}

void update_control_panels(
	void)
{
	short player_index;
	struct player_data *player;

	for (player_index= 0, player= players; player_index<dynamic_world->player_count; ++player_index, ++player)
	{
		short side_index;

		if ((side_index= player->control_panel_side_index)!=NONE)
		{
			struct side_data *side= get_side_data(player->control_panel_side_index);
			struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);
			boolean still_in_use= FALSE;

			if (player->variables.direction == player->variables.last_direction &&
				player->variables.last_position.x == player->variables.position.x &&
				player->variables.last_position.y == player->variables.position.y &&
				player->variables.last_position.z == player->variables.position.z)
			{
				switch (definition->panel_class)
				{
					case _panel_is_oxygen_refuel:
						if (!(dynamic_world->tick_count&OXYGEN_RECHARGE_FREQUENCY))
						{
							if (player->suit_oxygen<PLAYER_MAXIMUM_SUIT_OXYGEN)
							{
								player->suit_oxygen+= TICKS_PER_SECOND;
								mark_oxygen_display_as_dirty();
								still_in_use= TRUE;
							}
						}
						break;

					case _panel_is_shield_refuel:
					case _panel_is_double_shield_refuel:
					case _panel_is_triple_shield_refuel:
						if (!(dynamic_world->tick_count&ENERGY_RECHARGE_FREQUENCY))
						{
							short maximum, rate;

							switch (definition->panel_class)
							{
								case _panel_is_shield_refuel: maximum= PLAYER_MAXIMUM_SUIT_ENERGY, rate= 1; break;
								case _panel_is_double_shield_refuel: maximum= 2*PLAYER_MAXIMUM_SUIT_ENERGY, rate= 2; break;
								case _panel_is_triple_shield_refuel: maximum= 3*PLAYER_MAXIMUM_SUIT_ENERGY, rate= 3; break;
								default: halt();
							}
							if (player->suit_energy<maximum)
							{
								player->suit_energy= CEILING(player->suit_energy+rate, maximum);
								mark_shield_display_as_dirty();
								still_in_use= TRUE;
							}
						}
						break;

					default:
						halt();
				}
			}

			if (still_in_use)
			{
				set_control_panel_texture(side);
				play_control_panel_sound(side_index, _activating_sound);
			}
			else
			{
				change_panel_state(player_index, side_index);
				stop_sound(NONE, definition->sounds[_activating_sound]);
			}
		}
	}

	return;
}

void update_action_key(
	short player_index,
	boolean triggered)
{
	short               object_index;
	short               minimum_distance= 0;
	short               target_type;
	struct player_data  *player= get_player_data(player_index);

	if(triggered)
	{
		object_index= find_action_key_target(player_index, MAXIMUM_ACTIVATION_RANGE, &target_type);

		if(object_index != NONE)
		{
			switch(target_type)
			{
				case _target_is_platform:
					player_touch_platform_state(player_index, object_index);
					break;
				case _target_is_control_panel:
					change_panel_state(player_index, object_index);
					break;

				default:
					vhalt(csprintf(temporary, "%d is not a valid target type", target_type));
					break;
			}
		}
	}
}

boolean untoggled_repair_switches_on_level(
	void)
{
	short side_index;
	struct side_data *side;
	boolean untoggled_switch= FALSE;

	for (side_index= 0, side= map_sides; side_index<dynamic_world->side_count && !untoggled_switch; ++side_index, ++side)
	{
		if (SIDE_IS_CONTROL_PANEL(side) && SIDE_IS_REPAIR_SWITCH(side))
		{
			struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

			switch (definition->panel_class)
			{
				case _panel_is_platform_switch:
					untoggled_switch= platform_is_at_initial_state(get_polygon_data(side->control_panel_permutation)->permutation) ? TRUE : FALSE;
					break;

				default:
					untoggled_switch= GET_CONTROL_PANEL_STATUS(side) ? FALSE : TRUE;
					break;
			}
		}
	}

	return untoggled_switch;
}

void assume_correct_switch_position(
	short switch_type, /* platform or light */
	short permutation, /* platform or light index */
	boolean new_state)
{
	short side_index;
	struct side_data *side;

	for (side_index= 0, side= map_sides; side_index<dynamic_world->side_count; ++side_index, ++side)
	{
		if (SIDE_IS_CONTROL_PANEL(side) && side->control_panel_permutation==permutation)
		{
			struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

			if (switch_type==definition->panel_class)
			{
				play_control_panel_sound(side_index, new_state ? _activating_sound : _deactivating_sound);
				SET_CONTROL_PANEL_STATUS(side, new_state);
				set_control_panel_texture(side);
			}
		}
	}

	return;
}

void try_and_toggle_control_panel(
	short polygon_index,
	short line_index)
{
	struct polygon_data *polygon= get_polygon_data(polygon_index);
	struct line_data *line= get_line_data(line_index);
	short side_index= find_adjacent_side(polygon_index, line_index);

	if (side_index!=NONE)
	{
		struct side_data *side= get_side_data(side_index);

		if (SIDE_IS_CONTROL_PANEL(side))
		{
			if (switch_can_be_toggled(side_index, FALSE))
			{
				boolean make_sound, state= GET_CONTROL_PANEL_STATUS(side);
				struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

				switch (definition->panel_class)
				{
					case _panel_is_tag_switch:
						state= !state;
						make_sound= set_tagged_light_statuses(side->control_panel_permutation, state);
						if (try_and_change_tagged_platform_states(side->control_panel_permutation, state)) make_sound= TRUE;
						if (!side->control_panel_permutation) make_sound= TRUE;
						if (make_sound)
						{
							SET_CONTROL_PANEL_STATUS(side, state);
							set_control_panel_texture(side);
						}
						break;
					case _panel_is_light_switch:
						state= !state;
						make_sound= set_light_status(side->control_panel_permutation, state);
						break;
					case _panel_is_platform_switch:
						state= !state;
						make_sound= try_and_change_platform_state(get_polygon_data(side->control_panel_permutation)->permutation, state);
						break;
				}

				if (make_sound)
				{
					play_control_panel_sound(side_index, state ? _activating_sound : _deactivating_sound);
				}
			}
		}
	}

	return;
}

/* ---------- these functions are all used in Vulcan */
boolean shape_is_control_panel(
	shape_descriptor texture)
{
	boolean is_control_panel= FALSE;
	short index;

	for(index= 0; index<NUMBER_OF_CONTROL_PANEL_DEFINITIONS; ++index)
	{
		struct control_panel_definition *definition= get_control_panel_definition(index);

		if(texture==BUILD_DESCRIPTOR(definition->collection, definition->active_shape) ||
			texture==BUILD_DESCRIPTOR(definition->collection, definition->inactive_shape))
		{
			is_control_panel= TRUE;
			break;
		}
	}

	return is_control_panel;
}

short get_panel_class(
	short panel_type)
{
	struct control_panel_definition *definition= get_control_panel_definition(panel_type);

	return definition->panel_class;
}

//---------- changed 9.18.95
#if 0
boolean control_panel_type_valid_for_texture(
	shape_descriptor shape,
	short control_panel_type)
{
	boolean valid= FALSE;
	short index;

	for(index= 0; index<NUMBER_OF_CONTROL_PANEL_DEFINITIONS; ++index)
	{
		struct control_panel_definition *definition= get_control_panel_definition(index);

		if(GET_DESCRIPTOR_COLLECTION(shape)==definition->collection)
		{
			if((GET_DESCRIPTOR_SHAPE(shape)==definition->active_shape) ||
				(GET_DESCRIPTOR_SHAPE(shape)==definition->inactive_shape))
			{
				if(control_panel_type==definition->panel_class)
				{
					valid= TRUE;
				}
			}
		}
	}

	return valid;
}
#endif
//---------- changed 9.18.95
boolean control_panel_type_valid_for_texture(
	shape_descriptor shape,
	short control_panel_type)
{
	struct control_panel_definition *definition= get_control_panel_definition(control_panel_type);
	boolean valid= FALSE;

	if(GET_DESCRIPTOR_COLLECTION(shape)==definition->collection)
	{
		if((GET_DESCRIPTOR_SHAPE(shape)==definition->active_shape) ||
			(GET_DESCRIPTOR_SHAPE(shape)==definition->inactive_shape))
		{
			valid= TRUE;
		}
	}

	return valid;
}

//------------------

/* ---------- private code */

static short find_action_key_target(
	short player_index,
	world_distance range,
	short *target_type)
{
	struct player_data *player= get_player_data(player_index);
	short current_polygon= player->camera_polygon_index;
	world_point2d destination;
	boolean done= FALSE;
	short itemhit, line_index;
	struct polygon_data *polygon;

	/* Should we use this one, the physics one, or the object one? */
	ray_to_line_segment((world_point2d *) &player->location, &destination, player->facing, range);

//	dprintf("#%d(#%d,#%d) --> (#%d,#%d) (#%d along #%d)", current_polygon, player->location.x, player->location.y, destination.x, destination.y, range, player->facing);

	itemhit= NONE;
	while (!done)
	{
		line_index= find_line_crossed_leaving_polygon(current_polygon, (world_point2d *) &player->location, &destination);

		if (line_index==NONE)
		{
			done= TRUE;
		}
		else
		{
			struct line_data *line;
			short original_polygon;

			line= get_line_data(line_index);
			original_polygon= current_polygon;
			current_polygon= find_adjacent_polygon(current_polygon, line_index);

//			dprintf("leaving polygon #%d through line #%d to polygon #%d", original_polygon, line_index, current_polygon);

			if (current_polygon!=NONE)
			{
				polygon= get_polygon_data(current_polygon);

				/* We hit a platform */
				if (polygon->type==_polygon_is_platform && line_is_within_range(player->monster_index, line_index, MAXIMUM_PLATFORM_ACTIVATION_RANGE) &&
					platform_is_legal_player_target(polygon->permutation))
				{
//					dprintf("found platform #%d in %p", polygon->permutation, polygon);
					itemhit= polygon->permutation;
					*target_type= _target_is_platform;
					done= TRUE;
				}
			}
			else
			{
				done= TRUE;
			}

			/* Slammed a wall */
			if (line_is_within_range(player->monster_index, line_index, MAXIMUM_CONTROL_ACTIVATION_RANGE))
			{
				if (line_side_has_control_panel(line_index, original_polygon, &itemhit))
				{
					if (switch_can_be_toggled(itemhit, TRUE))
					{
						*target_type= _target_is_control_panel;
						done= TRUE;
					}
					else
					{
						itemhit= NONE;
					}
				}
			}
		}
	}

	return itemhit;
}

static boolean line_is_within_range(
	short monster_index,
	short line_index,
	world_distance range)
{
	world_point3d monster_origin= get_object_data(get_monster_data(monster_index)->object_index)->location;
	world_point3d line_origin;
	world_distance radius, height;
	world_distance dx, dy, dz;

	calculate_line_midpoint(line_index, &line_origin);
	get_monster_dimensions(monster_index, &radius, &height);
	monster_origin.z+= height>>1;

	dx= monster_origin.x-line_origin.x;
	dy= monster_origin.y-line_origin.y;
	dz= 2*(monster_origin.z-line_origin.z); /* dz is weighted */

	return isqrt(dx*dx + dy*dy + dz*dz)<range ? TRUE : FALSE;
}

static boolean line_side_has_control_panel(
	short line_index,
	short polygon_index,
	short *side_index_with_panel)
{
	short             side_index = NONE;
	boolean           has_panel = FALSE;
	struct line_data  *line = get_line_data(line_index);
	struct side_data  *side = NULL;

	if (line->clockwise_polygon_owner==polygon_index)
	{
		side_index = line->clockwise_polygon_side_index;
		if (side_index != NONE)
		{
			side = get_side_data(side_index);
		}
	}
	else
	{
		assert(line->counterclockwise_polygon_owner==polygon_index);
		side_index = line->counterclockwise_polygon_side_index;
		if (side_index != NONE)
		{
			side= get_side_data(side_index);
		}
	}

	if (side != NULL && SIDE_IS_CONTROL_PANEL(side))
	{
		*side_index_with_panel = side_index;
		has_panel = TRUE;
	}

	return has_panel;
}

static void	change_panel_state(
	short player_index,
	short panel_side_index)
{
	short state, make_sound= FALSE;
	struct side_data *side= get_side_data(panel_side_index);
	struct player_data *player= get_player_data(player_index);
	struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

	state= GET_CONTROL_PANEL_STATUS(side);

	/* Do the right thing, based on the panel type.. */
	switch (definition->panel_class)
	{
		case _panel_is_oxygen_refuel:
		case _panel_is_shield_refuel:
		case _panel_is_double_shield_refuel:
		case _panel_is_triple_shield_refuel:
#ifndef VULCAN
			player->control_panel_side_index= player->control_panel_side_index==panel_side_index ? NONE : panel_side_index;
			state= get_recharge_status(panel_side_index);
			SET_CONTROL_PANEL_STATUS(side, state);
			if (!state) set_control_panel_texture(side);
#endif
			break;
		case _panel_is_computer_terminal:
#ifndef VULCAN
			if (get_game_state()==_game_in_progress && !PLAYER_HAS_CHEATED(player) && !PLAYER_HAS_MAP_OPEN(player))
			{
				/* this will handle changing levels, if necessary (i.e., if we’re finished) */
				enter_computer_interface(player_index, side->control_panel_permutation, calculate_level_completion_state());
			}
#endif
			break;
		case _panel_is_tag_switch:
			if (definition->item==NONE || (!state && try_and_subtract_player_item(player_index, definition->item)))
			{
				state= !state;
				make_sound= set_tagged_light_statuses(side->control_panel_permutation, state);
				if (try_and_change_tagged_platform_states(side->control_panel_permutation, state)) make_sound= TRUE;
				if (!side->control_panel_permutation) make_sound= TRUE;
				if (make_sound)
				{
					SET_CONTROL_PANEL_STATUS(side, state);
					set_control_panel_texture(side);
				}
			}
			break;
		case _panel_is_light_switch:
			state= !state;
			make_sound= set_light_status(side->control_panel_permutation, state);
			break;
		case _panel_is_platform_switch:
			state= !state;
			make_sound= try_and_change_platform_state(get_polygon_data(side->control_panel_permutation)->permutation, state);
			break;
		case _panel_is_pattern_buffer:
#ifndef VULCAN
			if (dynamic_world->tick_count-player->ticks_at_last_successful_save>MINIMUM_RESAVE_TICKS &&
				player_controlling_game() && !PLAYER_HAS_CHEATED(local_player) && !game_is_networked)
			{
				play_control_panel_sound(panel_side_index, _activating_sound);
//				fade_out_background_music(30);

				/* Assume a successful save- prevents vidding of the save game key.. */
				player->ticks_at_last_successful_save= dynamic_world->tick_count;
				if (!save_game())
				{
					// AMR 3/12/97 vidding happens with InputSprocket with this here
					//player->ticks_at_last_successful_save= 0;
				}
//				fade_in_background_music(30);
			}
#endif
			break;

		default:
			halt();
	}

	if (make_sound)
	{
		play_control_panel_sound(panel_side_index, state ? _activating_sound : _deactivating_sound);
	}

	return;
}

static void set_control_panel_texture(
	struct side_data *side)
{
	struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

	side->primary_texture.texture= BUILD_DESCRIPTOR(definition->collection,
		GET_CONTROL_PANEL_STATUS(side) ? definition->active_shape : definition->inactive_shape);

	return;
}

#ifdef DEBUG
static struct control_panel_definition *get_control_panel_definition(
	short control_panel_type)
{
	assert(control_panel_type>=0 && control_panel_type<NUMBER_OF_CONTROL_PANEL_DEFINITIONS);

	return control_panel_definitions + control_panel_type;
}
#endif

static boolean switch_can_be_toggled(
	short side_index,
	boolean player_hit)
{
	boolean valid_toggle= TRUE;
	struct side_data *side= get_side_data(side_index);
	struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

	if (side->flags&_side_is_lighted_switch)
	{
		valid_toggle= get_light_intensity(side->primary_lightsource_index)>(3*FIXED_ONE/4) ? TRUE : FALSE;
	}

	if (definition->item!=NONE && !player_hit) valid_toggle= FALSE;
	if (player_hit && (side->flags&_side_switch_can_only_be_hit_by_projectiles)) valid_toggle= FALSE;

	if (valid_toggle && (side->flags&_side_switch_can_be_destroyed))
	{
		// destroy switch
		SET_SIDE_CONTROL_PANEL(side, FALSE);
	}

	if (!valid_toggle && player_hit) play_control_panel_sound(side_index, _unusuable_sound);

	return valid_toggle;
}

static void play_control_panel_sound(
	short side_index,
	short sound_index)
{
	struct side_data *side= get_side_data(side_index);
	struct control_panel_definition *definition= get_control_panel_definition(side->control_panel_type);

	assert(sound_index>=0 && sound_index<NUMBER_OF_CONTROL_PANEL_SOUNDS);

	_play_side_sound(side_index, definition->sounds[sound_index], definition->sound_frequency);

	return;
}

static boolean get_recharge_status(
	short side_index)
{
	short player_index;
	boolean status= FALSE;

	for (player_index= 0; player_index<dynamic_world->player_count; ++player_index)
	{
		struct player_data *player= get_player_data(player_index);

		if (player->control_panel_side_index==side_index) status= TRUE;
	}

	return status;
}
