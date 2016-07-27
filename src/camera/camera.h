#ifndef CAMERA_H_
#define CAMERA_H_

#include "../world/global.h"

class Camera {
public:
	VECTOR3D eye,lookAt;
	float plane;

	Camera();
	Camera(VECTOR3D e,VECTOR3D d,float n);
	~Camera();

	void renderWorld(FrameBuffer* fb,int width,int height);
};


#endif /* CAMERA_H_ */
