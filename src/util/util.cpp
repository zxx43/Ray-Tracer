#include "util.h"

void ClampColor(float& r,float& g,float& b) {
	if(r<=1.0&&g<=1.0&&b<=1.0)
		return;
	float maxColor=r>g?r:g;
	if(b>maxColor)
		maxColor=b;
	r/=maxColor; g/=maxColor; b/=maxColor;
}

