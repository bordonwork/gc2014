#include "camera.h"


OrthographicCamera::OrthographicCamera(Vec3f centro, Vec3f direccion, Vec3f vec_arriba, float tamano){
		_centro = centro;

		//Normalizamos el vector direccion antes de asignarlo
		direccion.Normalize();
		_direccion = direccion;

		//Modificamos el vector vec_arriba para que sea ortonormal al vector direccion
		//Aplicamos la formula u = u1 - (u1,u2)/|u1| . u1 para ortonormalizar
		Vec3f vec_ort = vec_arriba-direccion*(vec_arriba.Dot3(direccion)/direccion.Dot3(direccion));
		vec_ort.Normalize();
		_vec_arriba = vec_ort;

		//El vector horizontal obtenemos a partir del vector vec_arriba y el vector direccion
		//horizontal = vec_arriba x direccion
		Vec3f::Cross3(_horizontal, vec_arriba, direccion); 
		_horizontal.Normalize(); 

		_tamano = tamano;  
		_tMin = FLT_MIN;
}

Ray OrthographicCamera::generateRay(Vec2f point){ 

		//centro – tamaño x arriba – tamaño x horizontal -> centro + tamaño x arriba + arriba x horizontal
		//Para la coordenada x calculamos  (_horizontal . (x - 0.5) . tamano)
		//Para la coordenada y calculamos (_vec_arriba . (y - 0.5) . tamano)
		//Nuevo vector origen
		Vec3f origen = _centro+_horizontal*(point.x()-0.5)*_tamano+(_vec_arriba*_tamano)*(point.y()-0.5);
		Ray newRay(_direccion, origen);
		return newRay;
}
