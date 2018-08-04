#ifndef __SCREEN_CHOCOTHON_H
#define __SCREEN_CHOCOTHON_H

/*
 * screen_chocothon.h: Definitions of things that screen_drawing.c needs to
 * compile
 */

struct BitMap {
   Ptr baseAddr;
   short rowBytes;
   Rect bounds;
};
typedef struct BitMap BitMap;
typedef BitMap * BitMapPtr;

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

void GetForeColor(RGBColor *color);
void GetBackColor(RGBColor *color);
void RGBBackColor(const RGBColor *color);
void RGBForeColor(const RGBColor *color);
void CopyBits (
   const BitMap *srcBits,
   const BitMap *dstBits,
   const Rect *srcRect,
   const Rect *dstRect,
   short mode,
   RgnHandle maskRgn
);

#endif // __SCREEN_CHOCOTHON_H
