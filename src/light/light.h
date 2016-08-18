#ifndef LIGHT_H_
#define LIGHT_H_

#include "../shadeRec/shadeRec.h"

class Light {
public:
	Light();
	Light(const Light& rhs);
	virtual Light* clone()=0;
	virtual ~Light();

	virtual VECTOR3D calWo(ShadeRec* sr)=0;
	virtual COLOR3D l(ShadeRec* sr);
	virtual float g(ShadeRec* sr);
	virtual float pdf(ShadeRec* sr);
	virtual bool isInShadow(Ray* ray);
};

#endif /* LIGHT_H_ */
