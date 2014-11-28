#include "Object3D.h"

class Triangle:public Object3D{

public:
	Triangle(){}
	Triangle(Vec3f &a,Vec3f &b,Vec3f &c,Vec3f &color){
		_vertex0=a;
		_vertex1=b;
		_vertex2=c;
		_color=color;
		Vec3f::Cross3(_n,(b-a),(c-a));
	}
	bool intersect(const Ray &r, Hit &h, float tmin){
		Vec3f e=r.getOrigin();
		Vec3f d=r.getDirection();
		Vec3f a=_vertex0;
		Vec3f b=_vertex1;
		Vec3f c=_vertex2;
		float A= Matrix().determ3x3(a[0]-b[0],a[1]-b[1],a[2]-b[2],
			a[0]-c[0],a[1]-c[1],a[2]-c[2],d[0],d[1],d[2]);
		float t= Matrix().determ3x3(a[0]-b[0],a[1]-b[1],a[2]-b[2],
			a[0]-c[0],a[1]-c[1],a[2]-c[2],e[0],e[1],e[2])/A;
		if(t>tmin)return false;
		float gamma= Matrix().determ3x3(a[0]-b[0],a[1]-b[1],a[2]-b[2],
			a[0]-e[0],a[1]-e[1],a[2]-e[2],d[0],d[1],d[2])/A;
		if(gamma<0 || gamma>1)return false;
		float beta= Matrix().determ3x3(a[0]-e[0],a[1]-e[1],a[2]-e[2],
			a[0]-c[0],a[1]-c[1],a[2]-c[2],d[0],d[1],d[2])/A;
		if(beta<0 || beta>1-gamma)return false;
		if(h.getT()>t){
			h.set(t,_color,_n);
		}
	}

private:
	Vec3f _vertex0;
	Vec3f _vertex1;
	Vec3f _vertex2;
	Vec3f _color;
	Vec3f _n;

};