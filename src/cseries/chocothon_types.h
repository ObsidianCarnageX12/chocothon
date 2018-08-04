#ifndef __CHOCOTHON_TYPES_H
#define __CHOCOTHON_TYPES_H

/*
 * chocothon_types.h: Defines various types the code expects in order to
 * compile
 */

#include <stdint.h>
#include <stdbool.h>

typedef short OSErr;

struct RGBColor {
	uint16_t red, green, blue;
};
typedef struct RGBColor RGBColor;

struct Rect {
	uint16_t top, left;
	uint16_t bottom, right;
};
typedef struct Rect Rect;

/* TODO: these are dummy typedefs to appease the compiler */
typedef void* Ptr;
typedef void* WindowPtr;
typedef struct{} EventRecord;
typedef void* GrafPtr;
typedef struct{} Point;
typedef struct{} ConstStr255Param;
typedef struct{} FSSpec;
typedef void* GDHandle;
typedef bool Boolean;
typedef void* VDSwitchInfoPtr;
typedef struct{} CSpecArray;
typedef void* CTabHandle;
typedef struct{} ModalFilterUPP;
typedef void* DialogPtr;
typedef void* dialog_header_proc_ptr;
typedef void* update_any_window_proc_ptr;
typedef void* suspend_resume_proc_ptr;
typedef void* MenuHandle;
typedef void* GWorldPtr;
typedef void* RgnHandle;

#endif // __CHOCOTHON_TYPES_H
