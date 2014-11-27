#ifndef _GROUP_H_
#define _GROUP_H_

#include "Object3D.h"

class Group:public Object3D
{
public:
	//Cosntructores
	Group(){};

	Group(int num_objetos){
		_num_objetos = num_objetos;
		_objetos3D = new Object3D*[_num_objetos];
	}
	
	//Destructor
	~Group(){
		for(int i = 0; i < _num_objetos; i++){
			delete _objetos3D[i];
		}
		if(_objetos3D != NULL)
			delete _objetos3D;
	}

	virtual bool intersect(const Ray &r , Hit &h , float tmin );
	
	void addObject( int index , Object3D *obj );

private:
	int _num_objetos;
	Object3D **_objetos3D;
};
#endif
