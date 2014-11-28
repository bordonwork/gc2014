#include "Object3D.h"
class Transform: public Object3D{
public:
	Transform(Matrix &m, Object3D *o);
	bool intersect(const Ray &,Hit &h,float tmin);
};