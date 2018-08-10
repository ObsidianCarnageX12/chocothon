#ifndef __SCREEN_CHOCOTHON_H
#define __SCREEN_CHOCOTHON_H

/*
 * screen_chocothon.h: Function prototypes that screen_drawing.c needs.
 */

void GetForeColor(RGBColor *color);
void GetBackColor(RGBColor *color);
void RGBBackColor(const RGBColor *color);
void RGBForeColor(const RGBColor *color);
void GetGWorld (CGrafPtr* port, GDHandle* gdh);
void SetGWorld (CGrafPtr port, GDHandle gdh);
void OffsetRect (Rect* r, short dh, short dv);
short TextWidth (const void * textBuf, short firstByte, short byteCount);
short CharWidth (CharParameter ch);
void BlockMove (const void* srcPtr, void* destPtr, Size byteCount);

typedef short TruncCode;
short TruncText(short width, Ptr textPtr, short * length, TruncCode truncWhere);

// For CopyBits 'mode' parameter
enum {
	srcCopy,
	srcOr,
	srcXor,
	srcBic,
	notSrcCopy,
	notSrcOr,
	notSrcXor,
	notSrcBic
};

void CopyBits (
	const BitMap *srcBits,
	const BitMap *dstBits,
	const Rect *srcRect,
	const Rect *dstRect,
	short mode,
	RgnHandle maskRgn
);

#endif // __SCREEN_CHOCOTHON_H
