#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "hit.h"
#include "vectors.h"
#include "ray.h"

class Object3D
{
public:
	//Constructor por defecto
	Object3D(){}

	//Destructor por defecto
	~Object3D(){}

	//metodo abstracto
	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

	//variable de instancia
protected:
	Vec3f _color;
};
#endif
