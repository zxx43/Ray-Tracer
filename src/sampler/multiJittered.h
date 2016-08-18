#ifndef MULTIJITTERED_H_
#define MULTIJITTERED_H_

#include "sampler.h"

class MultiJittered: public Sampler {
private:
	virtual void genSamples();
public:
	MultiJittered();
	MultiJittered(int nSamples,int nSets);
	MultiJittered(int nSamples,int nSets,float exp);
	MultiJittered(const MultiJittered& rhs);
	virtual MultiJittered* clone();
	virtual ~MultiJittered();
};

#endif /* MULTIJITTERED_H_ */
