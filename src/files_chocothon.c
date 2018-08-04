/*

	macintosh_files.c
	Tuesday, August 29, 1995 3:18:54 PM- rdm created.

*/

#include "macintosh_cseries.h"
//#include <Aliases.h>
//#include <folders.h>

#include "portable_files.h"
#include "game_errors.h"
#include "tags.h" // for APPLICATION_CREATOR

/* --------------- code! */
FileError create_file(
	FileDesc *file,
	unsigned long file_type) /* Should be OSType, or extension for dos. */
{
	FileError err;
	return err;
}

fileref open_file_for_reading(
	FileDesc *file)
{
	fileref file_id;
	return file_id;
}

fileref open_file_for_writing(
	FileDesc *file)
{
	fileref file_id;
	return file_id;
}

void close_file(
	fileref refnum)
{
	OSErr error;
	return;
}

unsigned long get_fpos(
	fileref refnum)
{
	unsigned long position;
	return position;
}

FileError set_fpos(
	fileref refnum,
	unsigned long offset)
{
	OSErr err;
	return err;
}

FileError set_eof(
	fileref refnum,
	unsigned long offset)
{
	OSErr err;
	return err;
}

unsigned long get_file_length(
	fileref refnum)
{
	unsigned long file_length;
	return file_length;
}

FileError read_file(
	fileref refnum,
	unsigned long count,
	void *buffer)
{
	OSErr err;
	return err;
}

FileError write_file(
	fileref refnum,
	unsigned long count,
	void *buffer)
{
	OSErr err;
	return err;
}

FileError delete_file(
	FileDesc *file)
{
	FileError error;
	return error;
}

FileError find_preferences_location(
	FileDesc *file)
{
	FileError err;
	return err;
}

/* ------- miscellaneous routines */
FileError add_application_name_to_fsspec(
	FileDesc *file,
	char *pascal_name)
{
	FileError err;
	return err;
}

void get_application_filedesc( /* this is used to save files in the same directory */
	FileDesc *file)
{
	return;
}

FileError memory_error(
	void)
{
	FileError err;
	return err;
}
