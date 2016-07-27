#include "world.h"

World::World() {
	maxDepth=3;
	nSamples=1;
	tracer=NULL;
}

World::~World() {
	for(unsigned int i=0;i<objects.size();i++)
		delete objects[i];
	objects.clear();
	for(unsigned int i=0;i<lights.size();i++)
		delete lights[i];
	lights.clear();
	if(tracer) {
		delete tracer;
		tracer=NULL;
	}
}

void World::setTracer(Tracer* trace) {
	tracer=trace->clone();
}

void World::addObject(Geometry* obj) {
	objects.push_back(obj);
}

void World::addLight(Light* light) {
	lights.push_back(light);
}

void World::hitObjects(Ray* ray,ShadeRec* sr) {
	float t=0;
	float tmin=1000000.0;
	VECTOR3D normal,hitPoint;
	Material* material=NULL;
	for(unsigned int i=0;i<objects.size();i++) {
		if(objects[i]->hit(ray,t,sr)&&t<tmin) {
			sr->isHit=true;
			tmin=t;
			normal=sr->hitNormal;
			hitPoint=ray->ori+ray->dir*t;
			if(objects[i]->material)
				material=objects[i]->material;
		}
	}

	if(sr->isHit) {
		sr->hitT=tmin;
		sr->hitNormal=normal;
		sr->hitPoint=hitPoint;
		sr->material=material;
	}
}

