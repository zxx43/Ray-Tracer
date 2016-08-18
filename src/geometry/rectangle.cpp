#include "rectangle.h"

Rect::Rect():Geometry() {
	corner.x=-1; corner.y=0; corner.z=-1;
	va.x=0; va.y=0; va.z=2;
	vb.x=2; vb.y=0; vb.z=0;
	la=va.GetLength();
	lb=vb.GetLength();
	area=la*lb;
	invArea=1.0/area;
	normal=va.CrossProduct(vb);
	normal.Normalize();
	sampler=NULL;
}

Rect::Rect(VECTOR3D cor,VECTOR3D a,VECTOR3D b):Geometry() {
	corner=cor;
	va=a; vb=b;
	la=va.GetLength();
	lb=vb.GetLength();
	area=la*lb;
	invArea=1.0/area;
	normal=va.CrossProduct(vb);
	normal.Normalize();
	sampler=NULL;
}

Rect::Rect(const Rect& rhs):Geometry(rhs) {
	corner=rhs.corner;
	va=rhs.va; vb=rhs.vb;
	la=rhs.la; lb=rhs.lb;
	area=rhs.area;
	invArea=rhs.invArea;
	normal=rhs.normal;
	if(rhs.sampler)
		sampler=rhs.sampler;
}

Rect* Rect::clone() {
	return new Rect(*this);
}

Rect::~Rect() {

}

void Rect::setSampler(Sampler* s) {
	sampler=s;
}

VECTOR3D Rect::sample() {
	VECTOR2D samplePoint=sampler->sampleUnitSquare();
	return corner+samplePoint.x*va+samplePoint.y*vb;
}

VECTOR3D Rect::getNormal(VECTOR3D point) {
	return normal;
}

float Rect::pdf(ShadeRec* sr) {
	return invArea;
}

const float kEpsilon=0.001;
bool Rect::hit(Ray* ray,float& t,ShadeRec* sr) {
	float tmin = (corner - ray->ori).DotProduct(normal) / (ray->dir.DotProduct(normal));

	if (tmin <= kEpsilon)
		return false;

	VECTOR3D p = ray->ori + tmin * ray->dir;
	VECTOR3D d = p - corner;

	float dDotA = d.DotProduct(va);

	if (dDotA < 0.0 || dDotA > (la*la))
		return false;

	float dDotB = d.DotProduct(vb);

	if (dDotB < 0.0 || dDotB > (lb*lb))
		return false;

	t = tmin;
	sr->hitNormal = normal;
	sr->hitPoint  = p;

	return true;
}

bool Rect::shadowHit(Ray* ray,float& t) {
	float tmin = (corner - ray->ori).DotProduct(normal) / (ray->dir.DotProduct(normal));

	if (tmin <= kEpsilon)
		return false;

	VECTOR3D p = ray->ori + tmin * ray->dir;
	VECTOR3D d = p - corner;

	float dDotA = d.DotProduct(va);

	if (dDotA < 0.0 || dDotA > (la*la))
		return false;

	float dDotB = d.DotProduct(vb);

	if (dDotB < 0.0 || dDotB > (lb*lb))
		return false;

	t = tmin;

	return true;
}
