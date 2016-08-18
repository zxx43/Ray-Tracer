#ifndef BRDF_H_
#define BRDF_H_

#include "../header/header.h"
#include "../sampler/sampler.h"
#include "../shadeRec/shadeRec.h"

class BRDF {
public:
	Sampler* sampler;

	BRDF();
	BRDF(const BRDF& brdf);
	virtual BRDF* clone()=0;
	virtual ~BRDF();

	void setSampler(Sampler* s);
	virtual COLOR3D f(ShadeRec* sr,const VECTOR3D& wo,VECTOR3D& wi,float& pdf);
	virtual COLOR3D f(ShadeRec* sr,const VECTOR3D& wo,const VECTOR3D& wi);
};

#endif /* BRDF_H_ */
