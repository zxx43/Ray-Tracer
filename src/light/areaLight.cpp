#include "areaLight.h"
#include "../world/global.h"

AreaLight::AreaLight():Light() {
	object=NULL;
}

AreaLight::AreaLight(const AreaLight& rhs):Light(rhs) {
	if(rhs.object)
		object=rhs.object;
}

AreaLight* AreaLight::clone() {
	return new AreaLight(*this);
}

AreaLight::~AreaLight() {

}

void AreaLight::setObject(Geometry* obj) {
	object=obj;
}

VECTOR3D AreaLight::calWo(ShadeRec* sr) {
	samplePoint=object->sample();
	sampleNormal=object->getNormal(samplePoint);
	wo=sr->hitPoint-samplePoint;
	wo.Normalize();
	return wo;
}

COLOR3D AreaLight::l(ShadeRec* sr) {
	float lnDotWo=sampleNormal.DotProduct(wo);
	if(lnDotWo>0.0)
		return object->material->getLe();
	return COLOR3D(0,0,0);
}

float AreaLight::g(ShadeRec* sr) {
	float lnDotWo=sampleNormal.DotProduct(wo);
	VECTOR3D wi=samplePoint-sr->hitPoint;
	float lengthSquare=wi.DotProduct(wi);
	wi.Normalize();
	float snDotWi=sr->hitNormal.DotProduct(wi);
	return lnDotWo*snDotWi/lengthSquare;
}

float AreaLight::pdf(ShadeRec* sr) {
	if(object)
		return object->pdf(sr);
	return 1.0;
}

bool AreaLight::isInShadow(Ray* ray) {
	float t=0.0;
	float ts=(samplePoint-ray->ori).DotProduct(ray->dir);
	for(unsigned int i=0;i<world->objects.size();i++) {
		if(world->objects[i]->shadowHit(ray,t)&&t<ts)
			return true;
	}
	return false;
}

