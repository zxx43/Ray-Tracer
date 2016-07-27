#ifndef WORLD_H_
#define WORLD_H_

#include "../header/header.h"
#include "../geometry/geometry.h"
#include "../light/light.h"
#include "../tracer/tracer.h"
#include <vector>

class World {
public:
	std::vector<Geometry*> objects;
	std::vector<Light*> lights;
	Tracer* tracer;
	int maxDepth,nSamples;

	World();
	~World();

	void setTracer(Tracer* trace);
	void addObject(Geometry* obj);
	void addLight(Light* light);
	void hitObjects(Ray* ray,ShadeRec* sr);
};

#endif /* WORLD_H_ */
