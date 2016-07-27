#include "emissive.h"

Emissive::Emissive():Material() {
	ls=1.0;
	ce.r=1.0; ce.g=1.0; ce.b=1.0;
}

Emissive::Emissive(const Emissive& rhs):Material(rhs) {
	ls=rhs.ls;
	ce=rhs.ce;
}

Emissive* Emissive::clone() {
	return new Emissive(*this);
}

Emissive::~Emissive() {

}

COLOR3D Emissive::shade(ShadeRec* sr) {
	COLOR3D le=ce*ls;
	if(sr->depth==1)
		return COLOR3D(0,0,0);
	if(sr->hitNormal.DotProduct(-sr->ray->dir)<=0.0) {
		le.r=0.0; le.g=0.0; le.b=0.0;
	}
	return le;
}

COLOR3D Emissive::getLe() {
	return ce*ls;
}


