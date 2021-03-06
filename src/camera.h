#include "ray.h"

class Camera
{
public:
	//Constructor
	Camera(){}

	//Destructor
	~Camera(){}

	virtual Ray generateRay(Vec2f point)=0;
	virtual float getTMin()=0;

protected:
	float _tMin;
};
//Camara Ortografica
class OrthographicCamera:public Camera{

public:
	//Constructores
	OrthographicCamera(){}

	OrthographicCamera(Vec3f centro, Vec3f direccion, Vec3f vec_arriba, float tamano);

	//Destructor
	~OrthographicCamera(){}

	virtual Ray generateRay(Vec2f point);

	float getTMin(){
		return _tMin;
	}

private:
	Vec3f _centro;
	Vec3f _direccion;
	Vec3f _vec_arriba;
	float _tamano;
	Vec3f _horizontal;
};
//Camara Perspectiva
class PerspectiveCamera:public Camera {

public:
	//Constructor
	PerspectiveCamera(Vec3f& centro, Vec3f& direccion, Vec3f& vec_arriba, float angulo);

	//Destructor
	~PerspectiveCamera(){}

	virtual Ray generateRay(Vec2f point);

	float getTMin(){ 
		return _centro[2];
	}
private:
	Vec3f _centro;
	Vec3f _direccion;
	Vec3f _horizontal;
	Vec3f _up;
	float _angulo;
};