#include "Object3D.h"
class Plane: public Object3D{

public:
	Plane(Vec3f &normal, float d, Vec3f &color);
	bool intersect(const Ray &,Hit &,float);
};