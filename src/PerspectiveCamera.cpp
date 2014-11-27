#include "camera.h"

	PerspectiveCamera::PerspectiveCamera(Vec3f& centro, Vec3f& direccion, Vec3f& vec_arriba, float angulo){

		_centro = centro;

		//Normalizamos el vector direccion antes de asignarlo
		direccion.Normalize();
		w = direccion;

		// El vector horizontal obtenemos a partir del vector vec_arriba y el vector direccion
		// Es la proyeccion del vector_arriba (up vector) en el plano de vista.
		// v = w x vec_arriba
		Vec3f::Cross3(v, w, vec_arriba); 
		v.Normalize(); 

		//Modificamos el vector vec_arriba para que sea ortonormal al vector direccion
		// u = v x n
		Vec3f::Cross3(u, v, w);
		u.Normalize();

		_angulo = angulo;  
	}

	Ray PerspectiveCamera::generateRay(Vec2f& point){
		// alfa = 1/tan(ang/2)
	    float alfa = 1.0/tan(_angulo/2.0);
		// 
	    Vec3f direccion = (v*point.x()) + (u*point.y()) + (w*alfa);
		direccion.Normalize();
	    return Ray(direccion, _centro);
	}
