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
			float t_mayor_positivo=max(tmin,t_negativo);
			float t_mayor_negativo=max(tmin,t_negativo);
			t=(t_mayor_positivo!=tmin && t_mayor_negativo!=tmin)? 
				min(t_mayor_positivo,t_mayor_negativo): max(t_mayor_positivo,t_mayor_negativo);
		}
		if ( t >= tmin && t < h.getT()){
			//el vector normal en el punto de interseccion
			Vec3f n= ((r.getOrigin()+(ray_direccion*t))-_centro);
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
