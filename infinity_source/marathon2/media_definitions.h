/*
MEDIA_DEFINITIONS.H
Sunday, March 26, 1995 11:09:26 PM  (Jason')
*/

/* ---------- structures */

struct media_definition
{
	short collection, shape, shape_count, shape_frequency;
	short transfer_mode;

	short damage_frequency; // mask&ticks
	struct damage_definition damage;

	short detonation_effects[NUMBER_OF_MEDIA_DETONATION_TYPES];
	short sounds[NUMBER_OF_MEDIA_SOUNDS];

	short submerged_fade_effect;
};

/* ---------- globals */

static struct media_definition media_definitions[NUMBER_OF_MEDIA_TYPES]=
{
	/* _media_water */
	{
		_collection_walls1, 19, 1, 0, /* collection, shape, shape_count, frequency */
		_xfer_normal, /* transfer mode */

		0, {NONE, 0, 0, 0, FIXED_ONE}, /* damage frequency and definition */

		{_effect_small_water_splash, _effect_medium_water_splash, _effect_large_water_splash, _effect_large_water_emergence}, /* small, medium, large detonation effects */
		{NONE, NONE, _snd_enter_water, _snd_exit_water,
			_snd_walking_in_water, _ambient_snd_water, _ambient_snd_under_media,
			_snd_enter_water, _snd_exit_water},

		_effect_under_water, /* submerged fade effect */
	},

	/* _media_lava */
	{
		_collection_walls2, 12, 1, 0, /* collection, shape, shape_count, frequency */
		_xfer_normal, /* transfer mode */

		0xf, {_damage_lava, _alien_damage, 16, 0, FIXED_ONE}, /* damage frequency and definition */

		{_effect_small_lava_splash, _effect_medium_lava_splash, _effect_large_lava_splash, _effect_large_lava_emergence}, /* small, medium, large detonation effects */
		{NONE, NONE, _snd_enter_lava, _snd_exit_lava,
			_snd_walking_in_lava, _ambient_snd_lava, _ambient_snd_under_media,
			_snd_enter_lava, _snd_exit_lava},

		_effect_under_lava, /* submerged fade effect */
	},

	/* _media_goo */
	{
		_collection_walls5, 5, 1, 0, /* collection, shape, shape_count, frequency */
		_xfer_normal, /* transfer mode */

		0x7, {_damage_goo, _alien_damage, 8, 0, FIXED_ONE}, /* damage frequency and definition */

		{_effect_small_goo_splash, _effect_medium_goo_splash, _effect_large_goo_splash, _effect_large_goo_emergence}, /* small, medium, large detonation effects */
		{NONE, NONE, _snd_enter_lava, _snd_exit_lava,
			_snd_walking_in_lava, _ambient_snd_goo, _ambient_snd_under_media,
			_snd_enter_lava, _snd_exit_lava},

		_effect_under_goo, /* submerged fade effect */
	},

	/* _media_sewage */
	{
		_collection_walls3, 13, 1, 0, /* collection, shape, shape_count, frequency */
		_xfer_normal, /* transfer mode */

		0, {NONE, 0, 0, 0, FIXED_ONE}, /* damage frequency and definition */

		{_effect_small_sewage_splash, _effect_medium_sewage_splash, _effect_large_sewage_splash, _effect_large_sewage_emergence}, /* small, medium, large detonation effects */
		{NONE, NONE, _snd_enter_sewage, _snd_exit_sewage,
			NONE, _ambient_snd_sewage, _ambient_snd_under_media,
			_snd_enter_sewage, _snd_exit_sewage},

		_effect_under_sewage, /* submerged fade effect */
	},

	/* _media_jjaro */
	{
		_collection_walls4, 13, 1, 0, /* collection, shape, shape_count, frequency */
		_xfer_normal, /* transfer mode */

		0, {NONE, 0, 0, 0, FIXED_ONE}, /* damage frequency and definition */

		{_effect_small_jjaro_splash, _effect_medium_jjaro_splash, _effect_large_jjaro_splash, _effect_large_jjaro_emergence}, /* small, medium, large detonation effects */
		{NONE, NONE, _snd_enter_sewage, _snd_exit_sewage,
			NONE, _ambient_snd_sewage, _ambient_snd_under_media,
			_snd_enter_sewage, _snd_exit_sewage},

		_effect_under_sewage, /* submerged fade effect */
	},
};
