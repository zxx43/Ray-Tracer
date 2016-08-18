#ifndef MATTE_H_
#define MATTE_H_

#include "material.h"
#include "../brdf/lambertian.h"

class Matte: public Material {
public:
	Lambertian* diffuseBRDF;

	Matte();
	Matte(const Matte& rhs);
	virtual Matte* clone();
	virtual ~Matte();

	void setCd(COLOR3D cd);
	void setKd(float kd);
	virtual COLOR3D shade(ShadeRec* sr);
	COLOR3D directShade(ShadeRec* sr);
};

#endif /* MATTE_H_ */
