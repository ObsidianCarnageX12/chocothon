#ifndef __CHOCOTHON_TYPES_H
#define __CHOCOTHON_TYPES_H

/*
 * chocothon_types.h: Copies of various definitions from the Mac headers that
 * the code originally linked against so we can get it to compile. Some of the
 * actual definitions are changed for modernization reasons (e.g. int16_t
 * instead of Apple's SInt16 or 'unsigned short').
 */

#include <stdint.h>
#include <stdbool.h>

/* Generally useful types */
typedef char* Ptr;
typedef Ptr* Handle; // TODO: remove me and all other 'Handle' types
typedef long Size;

/********************************************************************************

    Base integer types for all target OS's and CPU's
    
        UInt8            8-bit unsigned integer 
        SInt8            8-bit signed integer
        UInt16          16-bit unsigned integer 
        SInt16          16-bit signed integer           
        UInt32          32-bit unsigned integer 
        SInt32          32-bit signed integer   
        UInt64          64-bit unsigned integer 
        SInt64          64-bit signed integer   

*********************************************************************************/
typedef uint8_t UInt8;
typedef int8_t SInt8;
typedef uint16_t UInt16;
typedef int16_t SInt16;
typedef uint32_t UInt32;
typedef int32_t SInt32;
typedef uint64_t UInt64;
typedef int64_t SInt64;

/********************************************************************************

    Higher level basic types

        OSErr                   16-bit result error code
        OSStatus                32-bit result error code

*********************************************************************************/
typedef int16_t OSErr;
typedef int32_t OSStatus;

/*******************************************************************************

    Base fixed point types 
    
        Fixed           16-bit signed integer plus 16-bit fraction
        UnsignedFixed   16-bit unsigned integer plus 16-bit fraction
        Fract           2-bit signed integer plus 30-bit fraction
        ShortFixed      8-bit signed integer plus 8-bit fraction
        
*******************************************************************************/
typedef int32_t                         Fixed;
typedef Fixed*                          FixedPtr;
typedef int32_t                         Fract;
typedef Fract*                          FractPtr;
typedef uint32_t                        UnsignedFixed;
typedef UnsignedFixed*                  UnsignedFixedPtr;
typedef int16_t                         ShortFixed;
typedef ShortFixed*                     ShortFixedPtr;

/********************************************************************************

    Boolean types and values

        Boolean         Mac OS historic type, sizeof(Boolean)==1
        bool            Defined in stdbool.h, ISO C/C++ standard type
        false           Now defined in stdbool.h
        true            Now defined in stdbool.h

*********************************************************************************/
typedef uint8_t Boolean;

/********************************************************************************

    Common Constants

        noErr                   OSErr: function performed properly - no error

*********************************************************************************/
enum {
  noErr                         = 0
};

/********************************************************************************

    String Types and Unicode Types

        UnicodeScalarValue,     A complete Unicode character in UTF-32 format, with
        UTF32Char               values from 0 through 0x10FFFF (excluding the surrogate
                                range 0xD800-0xDFFF and certain disallowed values).

        UniChar,                A 16-bit Unicode code value in the default UTF-16 format.
        UTF16Char               UnicodeScalarValues 0-0xFFFF are expressed in UTF-16
                                format using a single UTF16Char with the same value.
                                UnicodeScalarValues 0x10000-0x10FFFF are expressed in
                                UTF-16 format using a pair of UTF16Chars - one in the
                                high surrogate range (0xD800-0xDBFF) followed by one in
                                the low surrogate range (0xDC00-0xDFFF). All of the
                                characters defined in Unicode versions through 3.0 are
                                in the range 0-0xFFFF and can be expressed using a single
                                UTF16Char, thus the term "Unicode character" generally
                                refers to a UniChar = UTF16Char.

        UTF8Char                An 8-bit code value in UTF-8 format. UnicodeScalarValues
                                0-0x7F are expressed in UTF-8 format using one UTF8Char
                                with the same value. UnicodeScalarValues above 0x7F are
                                expressed in UTF-8 format using 2-4 UTF8Chars, all with
                                values in the range 0x80-0xF4 (UnicodeScalarValues
                                0x100-0xFFFF use two or three UTF8Chars,
                                UnicodeScalarValues 0x10000-0x10FFFF use four UTF8Chars).

        UniCharCount            A count of UTF-16 code values in an array or buffer.

        StrNNN                  Pascal string holding up to NNN bytes
        StringPtr               Pointer to a pascal string
        StringHandle            Pointer to a StringPtr
        ConstStringPtr          Pointer to a read-only pascal string
        ConstStrNNNParam        For function parameters only - means string is const

        CStringPtr              Pointer to a C string           (in C:  char*)
        ConstCStringPtr         Pointer to a read-only C string (in C:  const char*)

    Note: The length of a pascal string is stored as the first byte.
          A pascal string does not have a termination byte.
          A pascal string can hold at most 255 bytes of data.
          The first character in a pascal string is offset one byte from the start of the string.

          A C string is terminated with a byte of value zero.
          A C string has no length limitation.
          The first character in a C string is the zeroth byte of the string.


*********************************************************************************/
typedef UInt32                          UnicodeScalarValue;
typedef UInt32                          UTF32Char;
typedef UInt16                          UniChar;
typedef UInt16                          UTF16Char;
typedef UInt8                           UTF8Char;
typedef UniChar*                        UniCharPtr;
typedef unsigned long                   UniCharCount;
typedef UniCharCount*                   UniCharCountPtr;
typedef unsigned char                   Str255[256];
typedef unsigned char                   Str63[64];
typedef unsigned char                   Str32[33];
typedef unsigned char                   Str31[32];
typedef unsigned char                   Str27[28];
typedef unsigned char                   Str15[16];
/*
    The type Str32 is used in many AppleTalk based data structures.
    It holds up to 32 one byte chars.  The problem is that with the
    length byte it is 33 bytes long.  This can cause weird alignment
    problems in structures.  To fix this the type "Str32Field" has
    been created.  It should only be used to hold 32 chars, but
    it is 34 bytes long so that there are no alignment problems.
*/
typedef unsigned char                   Str32Field[34];
/*
    QuickTime 3.0:
    The type StrFileName is used to make MacOS structs work
    cross-platform.  For example FSSpec or SFReply previously
    contained a Str63 field.  They now contain a StrFileName
    field which is the same when targeting the MacOS but is
    a 256 char buffer for Win32 and unix, allowing them to
    contain long file names.
*/
typedef Str63                           StrFileName;
typedef unsigned char*                  StringPtr;
typedef StringPtr*                      StringHandle;
typedef const unsigned char*            ConstStringPtr;
typedef const unsigned char*            ConstStr255Param;
typedef const unsigned char*            ConstStr63Param;
typedef const unsigned char*            ConstStr32Param;
typedef const unsigned char*            ConstStr31Param;
typedef const unsigned char*            ConstStr27Param;
typedef const unsigned char*            ConstStr15Param;
typedef ConstStr63Param                 ConstStrFileNameParam;

/********************************************************************************

    Miscellaneous Carbon type definitions

*********************************************************************************/
struct FSSpec {
   short vRefNum;
   long parID;
   StrFileName name;
};
typedef struct FSSpec FSSpec;
typedef FSSpec* FSSpecPtr;

/********************************************************************************

    Quickdraw types
    TODO: these types should all eventually leave here; some should be deleted
    when no longer needed, and the useful ones should be moved to more appropriate
    header files.

*********************************************************************************/
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

struct FixedPoint {
	Fixed               x;
	Fixed               y;
};
typedef struct FixedPoint FixedPoint;
struct FixedRect {
	Fixed               left;
	Fixed               top;
	Fixed               right;
	Fixed               bottom;
};
typedef struct FixedRect FixedRect;

typedef short CharParameter;
enum {
	normal                        = 0,
	bold                          = 1,
	italic                        = 2,
	underline                     = 4,
	outline                       = 8,
	shadow                        = 0x10,
	condense                      = 0x20,
	extend                        = 0x40
};

typedef unsigned char                   Style;
typedef short                           StyleParameter;
typedef Style                           StyleField;

struct RGBColor {
	uint16_t red;
	uint16_t green;
	uint16_t blue;
};
typedef struct RGBColor RGBColor;
typedef RGBColor* RGBColorPtr;

struct ColorSpec {
	short               value;
	RGBColor            rgb;
};
typedef struct ColorSpec ColorSpec;
typedef ColorSpec* ColorSpecPtr;
typedef ColorSpec CSpecArray[1];

struct ColorTable {
	int32_t             ctSeed;
	short               ctFlags;
	short               ctSize;
	CSpecArray          ctTable;
};
typedef struct ColorTable ColorTable;
typedef ColorTable* CTabPtr;
typedef CTabPtr* CTabHandle;

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
typedef PixMap* PixMapPtr;
typedef PixMapPtr* PixMapHandle;

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

struct PixPat {
	short               patType;
	PixMapHandle        patMap;
	Handle              patData;
	Handle              patXData;
	short               patXValid;
	Handle              patXMap;
	Pattern             pat1Data;
};
typedef struct PixPat PixPat;
typedef PixPat* PixPatPtr;
typedef PixPatPtr* PixPatHandle;

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
//	QDProcsPtr    grafProcs;
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
//	CQDProcsPtr     grafProcs;
};
typedef struct CGrafPort CGrafPort;
typedef GrafPtr CGrafPtr;
typedef CGrafPtr GWorldPtr;
typedef short QDErr;
typedef unsigned long GWorldFlags;

struct CWindowRecord {
	CGrafPort port;
	SInt16 windowKind;
	Boolean visible;
	Boolean hilited;
	Boolean goAwayFlag;
	Boolean spareFlag;
	RgnHandle strucRgn;
	RgnHandle contRgn;
	RgnHandle updateRgn;
	Handle windowDefProc;
	Handle dataHandle;
//	StringHandle titleHandle;
	SInt16 titleWidth;
	Handle controlList;
//	CWindowPeek nextWindow;
//	PicHandle windowPic;
	SInt32 refCon;
};
typedef struct CWindowRecord CWindowRecord;
typedef CWindowRecord* WindowPtr;
typedef WindowPtr CWindowPtr;

typedef struct GDevice GDevice;
typedef GDevice *GDPtr, **GDHandle;
struct GDevice {
   short          gdRefNum;      /* reference number of screen driver */
   short          gdID;          /* reserved; set to 0 */
   short          gdType;        /* type of device--indexed or direct */
//   ITabHandle     gdITable;      /* handle to inverse table for Color
//                                    Manager */
   short          gdResPref;     /* preferred resolution */
//   SProcHndl      gdSearchProc;  /* handle to list of search functions */
//   CProcHndl      gdCompProc;    /* handle to list of complement functions */
   short          gdFlags;       /* graphics device flags */
   PixMapHandle   gdPMap;        /* handle to PixMap record for displayed
                                    image */
   long           gdRefCon;      /* reference value */
   GDHandle       gdNextGD;      /* handle to next graphics device */
   Rect           gdRect;        /* graphics device's boundary in global
                                    coordinates */
   long           gdMode;        /* graphics device's current mode */
   short          gdCCBytes;     /* width of expanded cursor data */
   short          gdCCDepth;     /* depth of expanded cursor data */
   Handle         gdCCXData;     /* handle to cursor's expanded data */
   Handle         gdCCXMask;     /* handle to cursor's expanded mask */
   long           gdReserved;    /* reserved for future use; must be 0 */
};

typedef struct VDSwitchInfoRec {
	unsigned short csMode;
	unsigned long csData;
	unsigned short csPage;
	void*	csBaseAddr;
	unsigned long csReserved;
} VDSwitchInfoRec;
typedef VDSwitchInfoRec* VDSwitchInfoPtr;

typedef UInt16                          EventKind;
typedef UInt16                          EventMask;
enum {
	nullEvent                     = 0,
	mouseDown                     = 1,
	mouseUp                       = 2,
	keyDown                       = 3,
	keyUp                         = 4,
	autoKey                       = 5,
	updateEvt                     = 6,
	diskEvt                       = 7,    /* Not sent in Carbon. See kEventClassVolume in CarbonEvents.h*/
	activateEvt                   = 8,
	osEvt                         = 15,
	kHighLevelEvent               = 23
};

enum {
	mDownMask                     = 1 << mouseDown, /* mouse button pressed*/
	mUpMask                       = 1 << mouseUp, /* mouse button released*/
	keyDownMask                   = 1 << keyDown, /* key pressed*/
	keyUpMask                     = 1 << keyUp, /* key released*/
	autoKeyMask                   = 1 << autoKey, /* key repeatedly held down*/
	updateMask                    = 1 << updateEvt, /* window needs updating*/
	diskMask                      = 1 << diskEvt, /* disk inserted*/
	activMask                     = 1 << activateEvt, /* activate/deactivate window*/
	highLevelEventMask            = 0x0400, /* high-level events (includes AppleEvents)*/
	osMask                        = 1 << osEvt, /* operating system events (suspend, resume)*/
	everyEvent                    = 0xFFFF /* all of the above*/
};

enum {
	charCodeMask                  = 0x000000FF,
	keyCodeMask                   = 0x0000FF00,
	adbAddrMask                   = 0x00FF0000,
	osEvtMessageMask              = (UInt32)0xFF000000
};

enum {
                                        /* OS event messages.  Event (sub)code is in the high byte of the message field.*/
	mouseMovedMessage             = 0x00FA,
	suspendResumeMessage          = 0x0001
};

enum {
	resumeFlag                    = 1     /* Bit 0 of message indicates resume vs suspend*/
};

typedef UInt16                          EventModifiers;
enum {
                                        /* modifiers */
	activeFlagBit                 = 0,    /* activate? (activateEvt and mouseDown)*/
	btnStateBit                   = 7,    /* state of button?*/
	cmdKeyBit                     = 8,    /* command key down?*/
	shiftKeyBit                   = 9,    /* shift key down?*/
	alphaLockBit                  = 10,   /* alpha lock down?*/
	optionKeyBit                  = 11,   /* option key down?*/
	controlKeyBit                 = 12,   /* control key down?*/
	rightShiftKeyBit              = 13,   /* right shift key down? Not supported on Mac OS X.*/
	rightOptionKeyBit             = 14,   /* right Option key down? Not supported on Mac OS X.*/
	rightControlKeyBit            = 15    /* right Control key down? Not supported on Mac OS X.*/
};

enum {
	activeFlag                    = 1 << activeFlagBit,
	btnState                      = 1 << btnStateBit,
	cmdKey                        = 1 << cmdKeyBit,
	shiftKey                      = 1 << shiftKeyBit,
	alphaLock                     = 1 << alphaLockBit,
	optionKey                     = 1 << optionKeyBit,
	controlKey                    = 1 << controlKeyBit,
	rightShiftKey                 = 1 << rightShiftKeyBit, /* Not supported on Mac OS X.*/
	rightOptionKey                = 1 << rightOptionKeyBit, /* Not supported on Mac OS X.*/
	rightControlKey               = 1 << rightControlKeyBit /* Not supported on Mac OS X.*/
};

struct EventRecord {
	EventKind what;
	UInt32 message;
	UInt32 when;
	Point where;
	EventModifiers modifiers;
};
typedef struct EventRecord EventRecord;

/*

    TODO: Remove these miscellaneous bogus typedefs

*/

typedef uint16_t DisplayIDType;
typedef void* ModalFilterUPP;
typedef void* DialogPtr;
typedef void* MenuHandle;

#endif // __CHOCOTHON_TYPES_H
