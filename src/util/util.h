#ifndef UTIL_H_
#define UTIL_H_

#include "../Maths/Maths.h"
#include <stdlib.h>

const float INV_RAND_MAX=1.0/(float)RAND_MAX;

inline void SetRandSeed(unsigned int seed) {
	srand(seed);
}

inline int RandInt() {
	return (int)rand();
}

inline float RandFloat() {
	return (float)RandInt()*INV_RAND_MAX;
}

inline float RandFloat(float min,float max) {
	return RandFloat()*(max-min)+min;
}

inline int RandInt(int min,int max) {
	return (int)RandFloat(0,max-min+1)+min;
}

void ClampColor(float& r,float& g,float& b);

#endif /* UTIL_H_ */
