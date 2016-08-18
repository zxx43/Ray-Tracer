#include "multiJittered.h"

MultiJittered::MultiJittered():Sampler() {
	this->ex=1.0;
	genShuffledIndices();
	genSamples();
	mapSamples2Hemisphere(1.0);
}

MultiJittered::MultiJittered(int nSamples,int nSets):Sampler(nSamples,nSets) {
	this->ex=1.0;
	genShuffledIndices();
	genSamples();
	mapSamples2Hemisphere(1.0);
}

MultiJittered::MultiJittered(int nSamples,int nSets,float exp):Sampler(nSamples,nSets) {
	this->ex=exp;
	genShuffledIndices();
	genSamples();
	mapSamples2Hemisphere(this->ex);
}

MultiJittered::MultiJittered(const MultiJittered& rhs):Sampler(rhs) {

}

MultiJittered* MultiJittered::clone() {
	return new MultiJittered(*this);
}

MultiJittered::~MultiJittered() {

}

void MultiJittered::genSamples() {
	int n=(int)sqrtf((float)numSamples);
	float cellWidth=1.0/((float)numSamples);
	VECTOR2D point;
	for(int i=0;i<numSamples*numSets;i++)
		samples.push_back(point);

	for(int set=0;set<numSets;set++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				samples[i*n+j+set*numSamples].x=(i*n+j)*cellWidth+RandFloat(0,cellWidth);
				samples[i*n+j+set*numSamples].y=(j*n+i)*cellWidth+RandFloat(0,cellWidth);
			}
		}
	}

	for(int set=0;set<numSets;set++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				int k=RandInt(j,n-1);
				float t=samples[i*n+j+set*numSamples].x;
				samples[i*n+j+set*numSamples].x=samples[i*n+k+set*numSamples].x;
				samples[i*n+k+set*numSamples].x=t;
			}
		}
	}

	for(int set=0;set<numSets;set++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				int k=RandInt(j,n-1);
				float t=samples[j*n+i+set*numSamples].y;
				samples[j*n+i+set*numSamples].y=samples[k*n+i+set*numSamples].y;
				samples[k*n+i+set*numSamples].y=t;
			}
		}
	}
}

