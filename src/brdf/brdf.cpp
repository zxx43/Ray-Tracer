#include "brdf.h"

BRDF::BRDF() {
	sampler=NULL;
}

BRDF::BRDF(const BRDF& brdf) {
	if(brdf.sampler)
		sampler=brdf.sampler;
}

BRDF::~BRDF() {

}

void BRDF::setSampler(Sampler* s) {
	sampler=s;
}

COLOR3D BRDF::f(ShadeRec* sr,const VECTOR3D& wo,VECTOR3D& wi,float& pdf) {
	return COLOR3D(0.0,0.0,0.0);
}

COLOR3D BRDF::f(ShadeRec* sr,const VECTOR3D& wo,const VECTOR3D& wi) {
	return COLOR3D(0.0,0.0,0.0);
}

