#include "rayCast.h"
#include "../world/global.h"

RayCast::RayCast():Tracer() {

}

RayCast::RayCast(const RayCast& rhs):Tracer(rhs) {

}

RayCast* RayCast::clone() {
	return new RayCast(*this);
}

RayCast::~RayCast() {

}

COLOR3D RayCast::traceRay(Ray* ray,int depth) {
	if(depth>world->maxDepth)
		return COLOR3D(0,0,0);
	ShadeRec* sr=new ShadeRec();
	world->hitObjects(ray,sr);
	if(sr->isHit) {
		sr->depth=depth;
		sr->ray=ray->clone();
		COLOR3D lo=sr->material->shade(sr);
		delete sr;
		return lo;
	} else {
		delete sr;
		return COLOR3D(0.5,0.7,0.8);
//		return COLOR3D(0,0,0);
	}
}

