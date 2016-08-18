#ifndef RAYCAST_H_
#define RAYCAST_H_

#include "tracer.h"

class RayCast: public Tracer {
public:
	RayCast();
	RayCast(const RayCast& rhs);
	virtual RayCast* clone();
	virtual ~RayCast();

	virtual COLOR3D traceRay(Ray* ray,int depth);
};

#endif /* RAYCAST_H_ */
