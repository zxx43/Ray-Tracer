#include "graphicLib.h"

FrameBuffer* frameBuffer=NULL;
unsigned char* screenBits=NULL;

void initFrameBuffer(FrameBuffer** pfb,int width,int height) {
	*pfb=(FrameBuffer*)malloc(sizeof(FrameBuffer));
	(*pfb)->width=width; (*pfb)->height=height;
	(*pfb)->colorBuffer=new unsigned char[width*height*3];
	memset((*pfb)->colorBuffer,0,sizeof(unsigned char)*width*height*3);
}
void releaseFrameBuffer(FrameBuffer** pfb) {
	if(*pfb==NULL)
		return;
	delete[] (*pfb)->colorBuffer;
	free(*pfb);
	*pfb=NULL;
}

void clearScreen(FrameBuffer* fb,unsigned char red,unsigned char green,unsigned char blue) {
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			fb->colorBuffer[index]=red;
			fb->colorBuffer[index+1]=green;
			fb->colorBuffer[index+2]=blue;
		}
	}
}
void flush(FrameBuffer* fb) {
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			unsigned char red=fb->colorBuffer[index];
			unsigned char green=fb->colorBuffer[index+1];
			unsigned char blue=fb->colorBuffer[index+2];
			screenBits[index]=blue;
			screenBits[index+1]=green;
			screenBits[index+2]=red;
		}
	}
}

void convertToScreen(int height,int& sx,int& sy) {
	sy=height-1-sy;
}
void drawPixel(FrameBuffer* fb,int x,int y,
		unsigned char r,unsigned char g,unsigned char b) {
	convertToScreen(fb->height,x,y);
	int index=(y*fb->width+x)*3;
	fb->colorBuffer[index]=r;
	fb->colorBuffer[index+1]=g;
	fb->colorBuffer[index+2]=b;
}
