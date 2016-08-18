#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "../util/util.h"
#include <vector>

class Sampler {
public:
	std::vector<VECTOR2D> samples;
	std::vector<VECTOR2D> diskSamples;
	std::vector<VECTOR3D> hemisphereSamples;
	std::vector<VECTOR3D> sphereSamples;
	std::vector<int> shuffledIndices;
	unsigned long count;
	int jump;
	float ex;

	int numSamples;
	int numSets;

	Sampler();
	Sampler(int nSamples,int nSets);
	Sampler(const Sampler& sampler);
	virtual Sampler* clone()=0;
	virtual ~Sampler();

	virtual void genSamples()=0;
	void genShuffledIndices();
	void mapSamples2UnitDisk();
	void mapSamples2Hemisphere(const float exp);
	void mapSamples2Sphere();
	VECTOR2D sampleUnitSquare();
	VECTOR2D sampleUnitDisk();
	VECTOR3D sampleHemisphere();
	VECTOR3D sampleSphere();
};


#endif /* SAMPLER_H_ */
