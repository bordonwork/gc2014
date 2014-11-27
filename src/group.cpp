#include "group.h"

bool Group::intersect(const Ray &r, Hit &h, float tmin) {
	bool aux = false;
    for (int i = 0; i < _num_objetos; i++){
		if (_objetos3D[i]->intersect(r, h, tmin)){
			aux = true;
		}
    }
    return aux;
}

void Group::addObject(int index, Object3D *objeto3D ){
    _objetos3D[index] = objeto3D;
}