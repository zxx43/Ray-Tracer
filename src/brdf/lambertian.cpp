#include "lambertian.h"

Lambertian::Lambertian():BRDF() {
	kd=1.0;
	cd.r=0.0; cd.g=0.0; cd.b=0.0;
}

Lambertian::Lambertian(const Lambertian& lamb):BRDF(lamb) {
	kd=lamb.kd;
	cd=lamb.cd;
}

Lambertian* Lambertian::clone() {
	return new Lambertian(*this);
}

Lambertian::~Lambertian() {

}

COLOR3D Lambertian::f(ShadeRec* sr,const VECTOR3D& wo,VECTOR3D& wi,float& pdf) {
	VECTOR3D w=sr->hitNormal;
	w.Normalize();
	VECTOR3D up(0.0034,1.0,0.0071);
	VECTOR3D v=up.CrossProduct(w);
	v.Normalize();
	VECTOR3D u=v.CrossProduct(w);
	u.Normalize();

	VECTOR3D point=sampler->sampleHemisphere();
	wi=point.x*u+point.y*v+point.z*w;
	wi.Normalize();

	pdf=sr->hitNormal.DotProduct(wi)*M_1_PI;
//	pdf=M_1_PI;
	return (cd*kd*M_1_PI);
}

COLOR3D Lambertian::f(ShadeRec* sr,const VECTOR3D& wo,const VECTOR3D& wi) {
	return (cd*kd*M_1_PI);
}
