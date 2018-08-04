#ifndef __CHOCOTHON_TYPES_H
#define __CHOCOTHON_TYPES_H

/*
 * chocothon_types.h: Stubs of various types that the code expects to have
 */

#include <stdint.h>
#include <stdbool.h>

typedef short OSErr;
typedef struct s_RGBColor {
	uint16_t red, green, blue;
} RGBColor;

/* TODO: these are dummy typedefs to appease the compiler */
typedef void* WindowPtr;
typedef struct{} EventRecord;
typedef struct{} Rect;
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

#endif // __CHOCOTHON_TYPES_H
