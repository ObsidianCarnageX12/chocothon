#ifndef __CHOCOTHON_TYPES_H
#define __CHOCOTHON_TYPES_H

/*
 * chocothon_types.h: Copies of various definitions from the Mac headers that
 * the code originally linked against so we can get it to compile. Some of the
 * actual definitions are changed to suit our needs (e.g. int16_t instead of
 * Apple's SInt16 or 'unsigned short').
 */

#include <stdint.h>
#include <stdbool.h>

/* Generally useful types */
typedef char* Ptr;
typedef Ptr* Handle;

typedef int16_t OSErr;

typedef int32_t Fixed;

typedef bool Boolean;

/* QuickDraw types */
struct Point {
	int16_t v;
	int16_t h;
};
typedef struct Point Point;
typedef Point* PointPtr;

struct Rect {
	int16_t top;
	int16_t left;
	int16_t bottom;
	int16_t right;
};
typedef struct Rect Rect;
typedef Rect* RectPtr;

struct RGBColor {
	uint16_t red;
	uint16_t green;
	uint16_t blue;
};
typedef struct RGBColor RGBColor;
typedef RGBColor* RGBColorPtr;

struct BitMap {
	Ptr baseAddr;
	short rowBytes;
	Rect bounds;
};
typedef struct BitMap BitMap;
typedef BitMap * BitMapPtr;

struct Pattern {
	uint8_t pat[8];
};
typedef struct Pattern Pattern;
typedef Pattern* PatPtr;
typedef PatPtr* PatHandle;

typedef struct OpaqueRgnHandle* RgnHandle;

struct GrafPort {
	short         device;
	BitMap        portBits;
	Rect          portRect;
	RgnHandle     visRgn;
	RgnHandle     clipRgn;
	Pattern       bkPat;
	Pattern       fillPat;
	Point         pnLoc;
	Point         pnSize;
	short         pnMode;
	Pattern       pnPat;
	short         pnVis;
	short         txFont;
	StyleField    txFace;
	short         txMode;
	short         txSize;
	Fixed         spExtra;
	long          fgColor;
	long          bkColor;
	short         colrBit;
	short         patStretch;
	Handle        picSave;
	Handle        rgnSave;
	Handle        polySave;
	QDProcsPtr    grafProcs;
};
typedef struct GrafPort GrafPort;
typedef GrafPort * GrafPtr;

struct CGrafPort {
	short           device;
	PixMapHandle    portPixMap;
	short           portVersion;
	Handle          grafVars;
	short           chExtra;
	short           pnLocHFrac;
	Rect            portRect;
	RgnHandle       visRgn;
	RgnHandle       clipRgn;
	PixPatHandle    bkPixPat;
	RGBColor        rgbFgColor;
	RGBColor        rgbBkColor;
	Point           pnLoc;
	Point           pnSize;
	short           pnMode;
	PixPatHandle    pnPixPat;
	PixPatHandle    fillPixPat;
	short           pnVis;
	short           txFont;
	StyleField      txFace;
	short           txMode;
	short           txSize;
	Fixed           spExtra;
	long            fgColor;
	long            bkColor;
	short           colrBit;
	short           patStretch;
	Handle          picSave;
	Handle          rgnSave;
	Handle          polySave;
	CQDProcsPtr     grafProcs;
};

struct ColorTable {
	int32_t             ctSeed;
	short               ctFlags;
	short               ctSize;
	CSpecArray          ctTable;
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;

struct PixMap {
	Ptr baseAddr;
	short rowBytes;
	Rect bounds;
	short pmVersion;
	short packType;
	long packSize;
	Fixed hRes;
	Fixed vRes;
	short pixelType;
	short pixelSize;
	short cmpCount;
	short cmpSize;
	long planeBytes;
	CTabHandle pmTable;
	long pmReserved;
};
typedef struct PixMap PixMap;
typedef PixMap * PixMapPtr;
typedef PixMapPtr * PixMapHandle;

typedef CGrafPtr GWorldPtr;

// TODO: these are dummy typedefs to appease the compiler
typedef void* WindowPtr;
typedef struct{} EventRecord;
typedef struct{} ConstStr255Param;
typedef struct{} FSSpec;
typedef void* GDHandle;
typedef void* VDSwitchInfoPtr;
typedef struct{} CSpecArray;
typedef struct{} ModalFilterUPP;
typedef void* DialogPtr;
typedef void* dialog_header_proc_ptr;
typedef void* update_any_window_proc_ptr;
typedef void* suspend_resume_proc_ptr;
typedef void* MenuHandle;
typedef void* RgnHandle;

#endif // __CHOCOTHON_TYPES_H
