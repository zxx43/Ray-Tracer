#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "geometry.h"
#include "../sampler/sampler.h"

class Rect: public Geometry {
public:
	VECTOR3D corner,va,vb,normal;
	float la,lb;
	float area,invArea;
	Sampler* sampler;

	Rect();
	Rect(VECTOR3D cor,VECTOR3D a,VECTOR3D b);
	Rect(const Rect& rhs);
	virtual Rect* clone();
	virtual ~Rect();

	void setSampler(Sampler* s);
	virtual VECTOR3D sample();
	virtual VECTOR3D getNormal(VECTOR3D point);
	virtual float pdf(ShadeRec* sr);
	virtual bool hit(Ray* ray,float& t,ShadeRec* sr);
	virtual bool shadowHit(Ray* ray,float& t);
};

#endif /* RECTANGLE_H_ */
