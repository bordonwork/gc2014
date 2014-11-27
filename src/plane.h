#ifndef _PLANE_H_
#define _PLANE_H_

#include "Object3D.h"

class Plane: public Object3D {

public:
	//Constructores
	Plane() {}
	Plane( Vec3f& normal, float d, Vec3f& color);

	//Destructor
	~Plane() {}

	virtual bool intersect(Ray& r , Hit& h , float tmin)=0;

protected:
	//Vector normal
	Vec3f _normal;
	//distancia del origen
	float _d;

};

#endif
