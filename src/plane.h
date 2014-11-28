#include "Object3D.h"

class Plane:public Object3D {

public:
	//Constructores
	Plane() {}
	Plane(Vec3f& normal, float d, Vec3f& color) {
		normal.Normalize();
		_normal = normal;
		_d = d;
		_color=color;
	}
	//Destructor
	//~Plane() {}
	bool intersect(const Ray &ray, Hit &hit, float tmin) {
		// Ecuacion del plano
		// Ax + By + Cz + D = 0
		// Ecuacion explicita del rayo
		// R = Ro + Rd.t   siendo t>0
		// Reemplazando tenemos
		// A(Xo + Xd.t) + B(Yo + Yd.t) + C(Zo + Zd.t) + D = 0
		// Despejamos t
		// t = - (A.Xo + B.Yo + C.Zo + D) / (A.Xd + B.Yd + C.Zd)
		// Por lo tanto, expresando en notacion vectorial:  
		// t = - (N.Ro + D) / (N.Rd)
		// D = -d

		Vec3f Ro = ray.getOrigin();
		Vec3f Rd = ray.getDirection();
		Rd.Normalize();

		float D = -1.0 * _d;
		float numerador = _normal.Dot3(Ro) + D;
		float denominador = _normal.Dot3(Rd);


		//Si el denominador es igual a 0 no hay interseccion
		if ( denominador == 0) {
			return false;
		}

		float t = -1.0 *(numerador)/(denominador);

		if( t >= tmin && t < hit.getT()){
			hit.set(t, _color, _normal);
			return true;
		} else {
			return false;

		}

	}

protected:
	//Vector normal
	Vec3f _normal;
	//distancia del origen
	float _d;
	Vec3f _color;
};