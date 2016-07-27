#include "light.h"

Light::Light() {

}

Light::Light(const Light& rhs) {

}

Light::~Light() {

}

COLOR3D Light::l(ShadeRec* sr) {
	return COLOR3D(0,0,0);
}

float Light::g(ShadeRec* sr) {
	return 0.0;
}

float Light::pdf(ShadeRec* sr) {
	return 1.0;
}

bool Light::isInShadow(Ray* ray) {
	return true;
}

