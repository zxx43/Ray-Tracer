#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../shadeRec/shadeRec.h"
#include "../material/material.h"

class Geometry {
public:
	Material* material;

	Geometry();
	Geometry(const Geometry& rhs);
	virtual Geometry* clone()=0;
	virtual ~Geometry();

	virtual bool hit(Ray* ray,float& t,ShadeRec* sr)=0;
	virtual bool shadowHit(Ray* ray,float& t)=0;
	virtual float pdf(ShadeRec* sr);
	virtual VECTOR3D getNormal(VECTOR3D point);
	virtual VECTOR3D sample();
	virtual void setMaterial(Material* mat);
};

#endif /* GEOMETRY_H_ */
