#ifndef GRAPHICLIB_H_
#define GRAPHICLIB_H_

#include "../header/header.h"

extern FrameBuffer* frameBuffer;
extern unsigned char* screenBits;

void initFrameBuffer(FrameBuffer** pfb,int width,int height);
void releaseFrameBuffer(FrameBuffer** pfb);
void clearScreen(FrameBuffer* fb,unsigned char red,unsigned char green,unsigned char blue);
void flush(FrameBuffer* fb);

void drawPixel(FrameBuffer* fb,int x,int y,
	unsigned char r,unsigned char g,unsigned char b);

#endif /* GRAPHICLIB_H_ */
