#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object3D.h"
class Sphere:public Object3D
{
public:
	//Constructores
	Sphere(){}

	Sphere(Vec3f centro, float radio, Vec3f color){
		_centro = centro;
		_radio = radio;
		_color = color;
	}

	//Destructor
	~Sphere(void){}

	virtual bool intersect(const Ray &r, Hit &h, float tmin){
		Vec3f ray_origen = r.getOrigin();
		Vec3f ray_direccion= r.getDirection();
		//Para el calculo de t utilizamos la funcion cuadratica de distancia. Interseccion de una linea con una esfera
		// A x^2 + B x + C = 0
		//Usamos la formula general para resolucion de ecuaciones de segundo grado
	    //t = (-b +- sqrt(b^2 - 4ac)) / 2a
		//En donde:
	    //a = ray_direccion x ray_direccion
	    //b = 2(ray_direccion x (ray_origen - centro))
	    //c = (ray_origen - centro) x (ray_origen - centro) - radio^2
		
		Vec3f ray_d = ray_origen-_centro;

		float a = ray_direccion.Dot3(ray_direccion);
		float b = 2*ray_direccion.Dot3(ray_d);
		float c = ray_d.Dot3(ray_d)-pow(_radio,2);

		float d = pow(b,2) - (4*a*c);
		float t;

		if(d < 0){
			
			return false;

		}
		else if (d == 0){

			t = (-1.0f * b)/(2.0f * a);

		} else {

			float raiz = sqrt(d);
			//valor de t con la parte positiva de la raiz
			float t_positivo = (-1.0f * b + raiz) / (2.0f * a);
			//valor de t con la parte negativa de la raiz
	    	float t_negativo = (-1.0f * b - raiz) / (2.0f * a);

	    	if (t_positivo < tmin && t_negativo < tmin){
	    		//si ambos valores son menores a tmin, asignamos a t el menor de ambos. Es decir, el que mas cercano a t
				t = min(t_positivo, t_negativo);
	    	} else {
				//Si ambos valores son mayores a tmin, asignamos a t el menor de ambos. Es decir, el que mas cercano a t
	    		t = (t_positivo < t_negativo)? t_positivo : t_negativo;
	    	}	
		}

		if ( t < tmin && t < h.getT()){
			//el vector normal en el punto de interseccion
			Vec3f n= ((_centro+(ray_direccion*t))-_centro)*2;
			n.Normalize();
			h.set(t, _color,n);
	    	return true;
	    }
        return false;

	}

private:
	Vec3f _centro;
	float _radio;
};
#endif
