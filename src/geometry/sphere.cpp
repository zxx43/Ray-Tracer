#include "sphere.h"

Sphere::Sphere():Geometry() {
	center.x=0; center.y=0; center.z=0; radius=1;
}

Sphere::Sphere(VECTOR3D c,float r):Geometry() {
	center=c; radius=r;
}

Sphere::Sphere(const Sphere& rhs):Geometry(rhs) {
	center=rhs.center; radius=rhs.radius;
}

Sphere* Sphere::clone() {
	return new Sphere(*this);
}

Sphere::~Sphere() {

}

const float kEpsilon=0.001;
bool Sphere::hit(Ray* ray,float& t,ShadeRec* sr) {
	float 		tmin;
	VECTOR3D	temp 	= ray->ori - center;
	float 		a 		= ray->dir.DotProduct(ray->dir);
	float 		b 		= 2.0 * temp.DotProduct(ray->dir);
	float 		c 		= temp.DotProduct(temp) - radius * radius;
	float 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;
	else {
		float e = sqrtf(disc);
		float denom = 2.0 * a;
		tmin = (-b - e) / denom;    // smaller root

		if (tmin > kEpsilon) {
			t = tmin;
//			sr->hitNormal = (temp + tmin * ray->dir) / radius;
			sr->hitPoint  = ray->ori + tmin * ray->dir;
			sr->hitNormal = getNormal(sr->hitPoint);
			return true;
		}

		tmin = (-b + e) / denom;    // larger root

		if (tmin > kEpsilon) {
			t = tmin;
//			sr->hitNormal = (temp + tmin * ray->dir) / radius;
			sr->hitPoint  = ray->ori + tmin * ray->dir;
			sr->hitNormal = getNormal(sr->hitPoint);
			return true;
		}
	}

	return false;
}

bool Sphere::shadowHit(Ray* ray,float& t) {
	float 		tmin;
	VECTOR3D	temp 	= ray->ori - center;
	float 		a 		= ray->dir.DotProduct(ray->dir);
	float 		b 		= 2.0 * temp.DotProduct(ray->dir);
	float 		c 		= temp.DotProduct(temp) - radius * radius;
	float 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;
	else {
		float e = sqrtf(disc);
		float denom = 2.0 * a;
		tmin = (-b - e) / denom;    // smaller root

		if (tmin > kEpsilon) {
			t = tmin;
			return true;
		}

		tmin = (-b + e) / denom;    // larger root

		if (tmin > kEpsilon) {
			t = tmin;
			return true;
		}
	}

	return false;
}

VECTOR3D Sphere::getNormal(VECTOR3D point) {
	VECTOR3D normal(point-center);
	normal.Normalize();
	return normal;
}

