#include "ray.h"

Ray::Ray() {
	ori.x=0; ori.y=0; ori.z=0;
	dir.x=0; dir.y=0; dir.z=1;
}

Ray::Ray(VECTOR3D o,VECTOR3D d) {
	ori.x=o.x; ori.y=o.y; ori.z=o.z;
	dir.x=d.x; dir.y=d.y; dir.z=d.z;
	dir.Normalize();
}

Ray::Ray(const Ray& ray) {
	ori.x=ray.ori.x; ori.y=ray.ori.y; ori.z=ray.ori.z;
	dir.x=ray.dir.x; dir.y=ray.dir.y; dir.z=ray.dir.z;
}

Ray* Ray::clone() {
	return new Ray(*this);
}

