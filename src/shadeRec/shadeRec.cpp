#include "shadeRec.h"
#include "../material/material.h"

ShadeRec::ShadeRec() {
	isHit=false;
	ray=NULL;
	depth=0;
	color.r=0.0; color.g=0.0; color.b=0.0;
	material=NULL;
}

ShadeRec::ShadeRec(const ShadeRec& rhs) {
	isHit=rhs.isHit;
	hitT=rhs.hitT;
	hitPoint=rhs.hitPoint;
	hitNormal=rhs.hitNormal;
	ray=new Ray(rhs.ray->ori,rhs.ray->dir);
	depth=rhs.depth;
	color=rhs.color;
	if(rhs.material)
		material=rhs.material;
}

ShadeRec::~ShadeRec() {
	if(ray) {
		delete ray;
		ray=NULL;
	}
}

