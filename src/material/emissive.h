#ifndef EMISSIVE_H_
#define EMISSIVE_H_

#include "material.h"

class Emissive: public Material {
public:
	float ls;
	COLOR3D ce;

	Emissive();
	Emissive(const Emissive& rhs);
	virtual Emissive* clone();
	virtual ~Emissive();

	virtual COLOR3D shade(ShadeRec* sr);
	virtual COLOR3D getLe();
};

#endif /* EMISSIVE_H_ */
