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
PerspectiveCamera::PerspectiveCamera(Vec3f& centro, Vec3f& direccion, Vec3f& vec_arriba, float angulo){

	_centro = centro;

	//Normalizamos el vector direccion antes de asignarlo
	direccion.Normalize();
	_direccion = direccion;

	// El vector horizontal obtenemos a partir del vector vec_arriba y el vector direccion
	// Es la proyeccion del vector_arriba (up vector) en el plano de vista.
	// horizontal = _direccion x vec_arriba
	Vec3f::Cross3(_horizontal, _direccion, vec_arriba); 
	_horizontal.Normalize(); 

	//Normalizamos el vector vec_arriba
	_up=vec_arriba;
	_up.Normalize();

	_angulo = angulo;  
}
Ray PerspectiveCamera::generateRay(Vec2f point){
	// alfa = 0.5/tan(ang/2)
	float alfa = 0.5/tan(_angulo/2.0);
	Vec3f origen=(_horizontal*(point.x()-0.5f)) + (_up*(point.y()-0.5f)) + (_direccion*alfa)+_centro;
	Vec3f direccion=origen-_centro;
	direccion.Normalize();
	return Ray(direccion, origen);
}