#ifndef __SCREEN_CHOCOTHON_H
#define __SCREEN_CHOCOTHON_H

/*
 * screen_chocothon.h: Function prototypes that screen_drawing.c needs.
 */

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
