#ifndef SHADEREC_H_
#define SHADEREC_H_

class Material;

#include "../header/header.h"
#include "../ray/ray.h"

class ShadeRec {
public:
	bool isHit;
	float hitT;
	VECTOR3D hitPoint,hitNormal;
	Ray* ray;
	int depth;
	COLOR3D color;
	Material* material;

	ShadeRec();
	ShadeRec(const ShadeRec& rhs);
	~ShadeRec();
};

#endif /* SHADEREC_H_ */
