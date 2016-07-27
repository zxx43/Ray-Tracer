#include "geometry.h"

Geometry::Geometry() {
	material=NULL;
}

Geometry::Geometry(const Geometry& rhs) {
	if(rhs.material)
		material=rhs.material;
}

Geometry::~Geometry() {

}

float Geometry::pdf(ShadeRec* sr) {
	return 1.0;
}

VECTOR3D Geometry::getNormal(VECTOR3D point) {
	return VECTOR3D(0.0,0.0,1.0);
}

VECTOR3D Geometry::sample() {
	return VECTOR3D(0.0,0.0,0.0);
}

void Geometry::setMaterial(Material* mat) {
	material=mat;
}

