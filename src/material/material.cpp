#include "material.h"

Material::Material() {

}

Material::Material(const Material& rhs) {

}

Material::~Material() {

}

COLOR3D Material::shade(ShadeRec* sr) {
	return COLOR3D(0.0,0.0,0.0);
}

COLOR3D Material::getLe() {
	return COLOR3D(0.0,0.0,0.0);
}

