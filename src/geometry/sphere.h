#ifndef SPHERE_H_
#define SPHERE_H_

#include "geometry.h"

class Sphere:public Geometry {
public:
	VECTOR3D center;
	float radius;

	Sphere();
	Sphere(VECTOR3D c,float r);
	Sphere(const Sphere& rhs);
	virtual Sphere* clone();
	virtual ~Sphere();

	virtual bool hit(Ray* ray,float& t,ShadeRec* sr);
	virtual bool shadowHit(Ray* ray,float& t);
	virtual VECTOR3D getNormal(VECTOR3D point);
};

#endif /* SPHERE_H_ */
