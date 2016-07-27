#ifndef RAY_H_
#define RAY_H_

#include "../Maths/Maths.h"
#include "../header/constants.h"

class Ray {
public:
	VECTOR3D ori,dir;

	Ray();
	Ray(VECTOR3D o,VECTOR3D d);
	Ray(const Ray& ray);
	Ray* clone();
	~Ray() {};
};

#endif /* RAY_H_ */
