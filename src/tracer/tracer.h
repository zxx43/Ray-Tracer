#ifndef TRACER_H_
#define TRACER_H_

#include "../ray/ray.h"
#include "../header/header.h"

class Tracer {
public:
	Tracer();
	Tracer(const Tracer& rhs);
	virtual Tracer* clone()=0;
	virtual ~Tracer();

	virtual COLOR3D traceRay(Ray* ray,int depth);
};

#endif /* TRACER_H_ */
