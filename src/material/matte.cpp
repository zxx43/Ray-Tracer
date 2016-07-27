#include "matte.h"
#include "../world/global.h"

Matte::Matte():Material() {
	diffuseBRDF=new Lambertian();
}

Matte::Matte(const Matte& rhs):Material(rhs) {
	if(rhs.diffuseBRDF)
		diffuseBRDF=rhs.diffuseBRDF->clone();
}

Matte* Matte::clone() {
	return new Matte(*this);
}

Matte::~Matte() {
	if(diffuseBRDF) {
		delete diffuseBRDF;
		diffuseBRDF=NULL;
	}
}

void Matte::setCd(COLOR3D cd) {
	diffuseBRDF->cd=cd;
}

void Matte::setKd(float kd) {
	diffuseBRDF->kd=kd;
}

COLOR3D Matte::directShade(ShadeRec* sr) {
	COLOR3D lo(0,0,0);
	for(unsigned int i=0;i<world->lights.size();i++) {
		Light* light=world->lights[i];
		VECTOR3D wo=-sr->ray->dir;
		VECTOR3D wi=-light->calWo(sr);
		float nDotWi=sr->hitNormal.DotProduct(wi);
		if(nDotWi>0.0) {
			bool inShadow=false;
			Ray* shadowRay=new Ray(sr->hitPoint,wi);
			inShadow=light->isInShadow(shadowRay);
			delete shadowRay;

			if(!inShadow) {
				COLOR3D brdf=diffuseBRDF->f(sr,wo,wi);
				COLOR3D li=light->l(sr);
				float g=light->g(sr);
				float pdf=light->pdf(sr);
				lo+=brdf*li*g/pdf;
			}
		}
	}
	return lo;
}

COLOR3D Matte::shade(ShadeRec* sr) {
	COLOR3D dirLight(0,0,0),indirLight(0,0,0);
	if(sr->depth==0)
		dirLight+=directShade(sr);

	VECTOR3D wi;
	VECTOR3D wo=-sr->ray->dir;
	float pdf;
	COLOR3D brdf=diffuseBRDF->f(sr,wo,wi,pdf);

	float nDotWi=sr->hitNormal.DotProduct(wi);
	Ray* reflectRay=new Ray(sr->hitPoint,wi);
	COLOR3D li=world->tracer->traceRay(reflectRay,sr->depth+1);
	delete reflectRay;

	indirLight+=brdf*li*nDotWi/pdf;

	COLOR3D lo=dirLight+indirLight;
	return lo;
}

