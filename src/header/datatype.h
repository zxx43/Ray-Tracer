#ifndef DATATYPE_H_
#define DATATYPE_H_

struct FrameBuffer {
	unsigned char* colorBuffer;
	int width,height;
};

class COLOR3D {
public:
	float r,g,b;
	COLOR3D() {r=0.0;g=0.0;b=0.0;}
	COLOR3D(float cr,float cg,float cb) {r=cr;g=cg;b=cb;}
	COLOR3D(const COLOR3D& rhs) {r=rhs.r;g=rhs.g;b=rhs.b;}
	COLOR3D& operator=(const COLOR3D& rhs) {r=rhs.r;g=rhs.g;b=rhs.b;return *this;}
	COLOR3D* clone() {return new COLOR3D(*this);}
	~COLOR3D() {}

	COLOR3D operator*(const float rhs) const {return COLOR3D(r*rhs,g*rhs,b*rhs);}
	COLOR3D operator/(const float rhs) const {return COLOR3D(r/rhs,g/rhs,b/rhs);}
	COLOR3D operator*(const COLOR3D& rhs) const {return COLOR3D(r*rhs.r,g*rhs.g,b*rhs.b);}
	COLOR3D operator+(const COLOR3D& rhs) const {return COLOR3D(r+rhs.r,g+rhs.g,b+rhs.b);}
	COLOR3D operator-(const COLOR3D& rhs) const {return COLOR3D(r-rhs.r,g-rhs.g,b-rhs.b);}
	COLOR3D& operator+=(const COLOR3D& rhs) {r+=rhs.r; g+=rhs.g; b+=rhs.b; return *this;}
	COLOR3D& operator/=(const float rhs) {r/=rhs; g/=rhs; b/=rhs; return *this;}
};

typedef void (*DrawCall)();

#endif /* DATATYPE_H_ */
