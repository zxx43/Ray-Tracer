#include "sampler.h"
#include <algorithm>

Sampler::Sampler() {
	numSamples=1;
	numSets=100;
	count=0;
	jump=0;
	ex=1;
	samples.reserve(numSamples*numSets);
}

Sampler::Sampler(int nSamples,int nSets) {
	numSamples=nSamples;
	numSets=nSets;
	count=0;
	jump=0;
	ex=1;
	samples.reserve(numSamples*numSets);
}

Sampler::Sampler(const Sampler& sampler) {
	numSamples=sampler.numSamples;
	numSets=sampler.numSets;
	count=sampler.count;
	jump=sampler.jump;
	ex=sampler.ex;
	samples.reserve(sampler.samples.size());
	unsigned int i=0;
	for(i=0;i<samples.size();i++)
		samples[i]=sampler.samples[i];
	shuffledIndices.reserve(sampler.shuffledIndices.size());
	for(i=0;i<shuffledIndices.size();i++)
		shuffledIndices[i]=sampler.shuffledIndices[i];
	diskSamples.reserve(sampler.diskSamples.size());
	for(i=0;i<diskSamples.size();i++)
		diskSamples[i]=sampler.diskSamples[i];
	hemisphereSamples.reserve(sampler.hemisphereSamples.size());
	for(i=0;i<hemisphereSamples.size();i++)
		hemisphereSamples[i]=sampler.hemisphereSamples[i];
	sphereSamples.reserve(sampler.sphereSamples.size());
	for(i=0;i<sphereSamples.size();i++)
		sphereSamples[i]=sampler.sphereSamples[i];
}

Sampler::~Sampler() {
	samples.clear();
	diskSamples.clear();
	hemisphereSamples.clear();
	sphereSamples.clear();
	shuffledIndices.clear();
}

void Sampler::genShuffledIndices() {
	shuffledIndices.reserve(numSamples*numSets);
	std::vector<int> indices;
	for(int i=0;i<numSamples;i++)
		indices.push_back(i);
	for(int i=0;i<numSets;i++) {
		std::random_shuffle(indices.begin(),indices.end());
		for(int j=0;j<numSamples;j++)
			shuffledIndices.push_back(indices[j]);
	}
	indices.clear();
}

void Sampler::mapSamples2UnitDisk() {
	int size = samples.size();
	float r, phi;		// polar coordinates
	VECTOR2D sp; 		// sample point on unit disk

	diskSamples.reserve(size);

	for (int j = 0; j < size; j++) {
		 // map sample point to [-1, 1] X [-1,1]

		sp.x = 2.0 * samples[j].x - 1.0;
		sp.y = 2.0 * samples[j].y - 1.0;

		if (sp.x > -sp.y) {			// sectors 1 and 2
			if (sp.x > sp.y) {		// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {					// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {						// sectors 3 and 4
			if (sp.x < sp.y) {		// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {					// sector 4
				r = -sp.y;
				if (sp.y != 0.0)	// avoid division by zero at origin
					phi = 6 - sp.x / sp.y;
				else
					phi  = 0.0;
			}
		}

		phi *= M_PI / 4.0;

		diskSamples[j].x = r * cos(phi);
		diskSamples[j].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

void Sampler::mapSamples2Hemisphere(const float exp) {
	int size = samples.size();
	hemisphereSamples.reserve(numSamples * numSets);

	for (int j = 0; j < size; j++) {
		float cos_phi = cos(2.0 * M_PI * samples[j].x);
		float sin_phi = sin(2.0 * M_PI * samples[j].x);
		float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
		float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		hemisphereSamples.push_back(VECTOR3D(pu, pv, pw));
	}
}

void Sampler::mapSamples2Sphere(void) {
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphereSamples.reserve(numSamples * numSets);

	for (int j = 0; j < numSamples * numSets; j++) {
		r1 	= samples[j].x;
    	r2 	= samples[j].y;
    	z 	= 1.0 - 2.0 * r1;
    	r 	= sqrt(1.0 - z * z);
    	phi = M_PI * 2 * r2;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
		sphereSamples.push_back(VECTOR3D(x, y, z));
	}
}

VECTOR2D Sampler::sampleUnitSquare() {
	if(count%numSamples==0)
		jump=(RandInt()%numSets)*numSamples;
	return samples[jump+shuffledIndices[jump+(count++)%numSamples]];
}

VECTOR2D Sampler::sampleUnitDisk() {
	if(count%numSamples==0)
		jump=(RandInt()%numSets)*numSamples;
	return diskSamples[jump+shuffledIndices[jump+(count++)%numSamples]];
}

VECTOR3D Sampler::sampleHemisphere() {
	if(count%numSamples==0)
		jump=(RandInt()%numSets)*numSamples;
	count++;
	int innerIndex=jump+count%numSamples;
	return hemisphereSamples[jump+shuffledIndices[innerIndex]];
}

VECTOR3D Sampler::sampleSphere() {
	if(count%numSamples==0)
		jump=(RandInt()%numSets)*numSamples;
	return sphereSamples[jump+shuffledIndices[jump+(count++)%numSamples]];
}

