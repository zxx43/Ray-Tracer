#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "brdf.h"

class Lambertian: public BRDF {
public:
	float kd;
	COLOR3D cd;

	Lambertian();
	Lambertian(const Lambertian& lamb);
	virtual Lambertian* clone();
	virtual ~Lambertian();

	virtual COLOR3D f(ShadeRec* sr,const VECTOR3D& wo,VECTOR3D& wi,float& pdf);
	virtual COLOR3D f(ShadeRec* sr,const VECTOR3D& wo,const VECTOR3D& wi);
};

#endif /* LAMBERTIAN_H_ */
