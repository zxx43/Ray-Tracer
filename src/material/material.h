#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../shadeRec/shadeRec.h"

class Material {
public:
	Material();
	Material(const Material& rhs);
	virtual Material* clone()=0;
	virtual ~Material();

	virtual COLOR3D shade(ShadeRec* sr);
	virtual COLOR3D getLe();
};

#endif /* MATERIAL_H_ */
