#include "camera.h"
#include "../util/util.h"
#include "../graphicLib/graphicLib.h"

Camera::Camera() {
	eye.x=0; eye.y=0; eye.z=-1;
	lookAt.x=0; lookAt.y=0; lookAt.z=1;
	plane=0;
}

Camera::Camera(VECTOR3D e,VECTOR3D d,float n) {
	eye=e;
	lookAt=d;
	plane=n;
}

Camera::~Camera() {

}

void Camera::renderWorld(FrameBuffer* fb,int width,int height) {
	VECTOR3D pix;
	pix.z=plane;
	COLOR3D color(0,0,0);
	int depth=0;
	int n=(int)sqrt(world->nSamples);
	Ray* ray=new Ray();
	ray->ori=eye;
	unsigned char pr=0,pg=0,pb=0;

	for(int r=0;r<height;r++) {
		for(int c=0;c<width;c++) {
			color.r=0; color.g=0; color.b=0;

			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++) {
					pix.x=c-0.5*width+(j+0.5)/n;
					pix.y=r-0.5*height+(i+0.5)/n;
					ray->dir=pix-ray->ori; ray->dir.Normalize();
					color+=world->tracer->traceRay(ray,depth);
				}
			}
			color/=world->nSamples;
			ClampColor(color.r,color.g,color.b);
			pr=(unsigned char)(color.r*255.0);
			pg=(unsigned char)(color.g*255.0);
			pb=(unsigned char)(color.b*255.0);
			drawPixel(fb,c,r,pr,pg,pb);
		}
	}
	delete ray;
}

