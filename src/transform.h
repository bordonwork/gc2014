#include "Object3D.h"
class Transform: public Object3D{
public:
	Transform(Matrix &m, Object3D *o){
		_m=m;
		_o=0;
	}
	bool intersect(const Ray &,Hit &h,float tmin){
		return false;
	}
private:
	Matrix _m;
	Object3D* _o;
};