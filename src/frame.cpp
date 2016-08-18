#include "frame.h"
#include "camera/camera.h"
#include "sampler/multiJittered.h"
#include "tracer/rayCast.h"
#include "geometry/rectangle.h"
#include "geometry/sphere.h"
#include "material/matte.h"
#include "material/emissive.h"
#include "light/areaLight.h"
#include <time.h>

Camera* camera;
int scrw=SCREEN_WIDTH,scrh=SCREEN_HEIGHT;
void draw() {
	clearScreen(frameBuffer,128,178,204);

	camera->renderWorld(frameBuffer,scrw,scrh);

	flush(frameBuffer);
}

MultiJittered* matSampler;
Matte *planeMat,*redMat,*greenMat,*sphereMat;
Emissive* emiMat;
void init() {
	SetRandSeed((unsigned int)time(0));
	int nSample=2500;
	matSampler=new MultiJittered(nSample,1024,1);

	emiMat=new Emissive();
	emiMat->ls=40.0;
	planeMat=new Matte();
	planeMat->diffuseBRDF->setSampler(matSampler);
	COLOR3D color(0.9,0.9,0.9);
	planeMat->setCd(color);
	planeMat->setKd(0.75);
	redMat=new Matte();
	redMat->diffuseBRDF->setSampler(matSampler);
	color.g=0.1; color.b=0.1;
	redMat->setCd(color);
	redMat->setKd(0.75);
	greenMat=new Matte();
	greenMat->diffuseBRDF->setSampler(matSampler);
	color.r=0.1; color.g=0.9; color.b=0.1;
	greenMat->setCd(color);
	greenMat->setKd(0.75);
	sphereMat=new Matte();
	sphereMat->diffuseBRDF->setSampler(matSampler);
	COLOR3D sphereColor(0.9,0.9,0.2);
	sphereMat->setCd(sphereColor);
	sphereMat->setKd(0.75);

	InitWorld();
	world->nSamples=nSample;
	world->maxDepth=5;
	RayCast* tracer=new RayCast();
	world->setTracer(tracer);
	delete tracer;

	VECTOR3D eye(0,-50,400),dir(0,0,-1);
	camera=new Camera(eye,dir,0);

	VECTOR3D pos(-50,250,0),va(0,0,-100),vb(100,0,0);

	Rect* lightRec=new Rect(pos,va,vb);
	lightRec->setMaterial(emiMat);
	lightRec->setSampler(matSampler);
	world->addObject(lightRec);

	AreaLight* light=new AreaLight();
	light->setObject(lightRec);
	world->addLight(light);

	pos.x=-200; pos.y=-200; pos.z=-200; va.z=350,vb.x=400;
	Rect* ground=new Rect(pos,va,vb);
	ground->setMaterial(planeMat);
	world->addObject(ground);

	pos.x=-200; pos.y=250; pos.z=150; va.z=-350,vb.x=400;
	Rect* top=new Rect(pos,va,vb);
	top->setMaterial(planeMat);
	world->addObject(top);

	pos.x=-200; pos.y=-200; pos.z=-200; va.x=400; va.y=0; va.z=0; vb.x=0; vb.y=450; vb.z=0;
	Rect* far=new Rect(pos,va,vb);
	far->setMaterial(planeMat);
	world->addObject(far);

	pos.x=-200; pos.y=-200; pos.z=150; va.x=0; va.y=0; va.z=-350; vb.x=0; vb.y=450; vb.z=0;
	Rect* left=new Rect(pos,va,vb);
	left->setMaterial(redMat);
	world->addObject(left);

	pos.x=200; pos.y=-200; pos.z=-200; va.x=0; va.y=0; va.z=350; vb.x=0; vb.y=450; vb.z=0;
	Rect* right=new Rect(pos,va,vb);
	right->setMaterial(greenMat);
	world->addObject(right);

	pos.x=100; pos.y=-150; pos.z=-50;
	Sphere* sphere=new Sphere(pos,50);
	sphere->setMaterial(sphereMat);
	world->addObject(sphere);
}

void release() {
	delete redMat;
	delete greenMat;
	delete planeMat;
	delete sphereMat;
	delete emiMat;
	delete matSampler;
	delete camera;
	ReleaseWorld();

	releaseFrameBuffer(&frameBuffer);
}

void resize(int width,int height) {
	releaseFrameBuffer(&frameBuffer);
	initFrameBuffer(&frameBuffer,width,height);

	scrw=width; scrh=height;
}
