#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "light.h"
#include "../geometry/geometry.h"

class AreaLight: public Light {
public:
	Geometry* object;
	VECTOR3D samplePoint,sampleNormal,wo;

	AreaLight();
	AreaLight(const AreaLight& rhs);
	virtual AreaLight* clone();
	virtual ~AreaLight();

	void setObject(Geometry* obj);
	virtual VECTOR3D calWo(ShadeRec* sr);
	virtual COLOR3D l(ShadeRec* sr);
	virtual float g(ShadeRec* sr);
	virtual float pdf(ShadeRec* sr);
	virtual bool isInShadow(Ray* ray);
};

#endif /* AREALIGHT_H_ */
