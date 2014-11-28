
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "scene_parser.h"
#include "image.h"
#include "hit.h"
#include "Object3D.h"
#include "Group.h"
#include "Sphere.h"
#include "vectors.h"
#include "ray.h"
#include "camera.h"
#include "light.h"


char* input_file = NULL; 
int   width = 100;
int   height = 100;
char* output_file = NULL;
float depth_min = 0;
float depth_max = 1;
char* depth_file = NULL;


/**
 * Interpreta los argumentos del programa
 *
 *  sample command lines:
 *  raycast -input input.txt -size 100 100 -output output.tga
 *  raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.tga
 *
 */
void parseArguments(int argc, char* argv[]) {

   // printf("Input %d\n", strcmp(argv[1],"-input"));
    for (int i = 1; i < argc; i++) {
        //if (0 == strcmp(argv[i],"-input")) 
		if (!strcmp(argv[i],"-input")){
            i++;
            assert (i < argc);
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++;
            assert (i < argc);
            width = atoi(argv[i]);
            i++;
            assert (i < argc);
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++;
            assert (i <= argc);
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++;
            assert (i < argc);
            depth_min = (float)atof(argv[i]);
            i++;
            assert (i < argc);
            depth_max = (float)atof(argv[i]);
            i++;
            assert (i <= argc);
            depth_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            printf(argv[0]);
			assert(0);
        }
    }
    //printf("First!!! %s", argv[1]);

}


int main(int argc, char* argv[]) {
	//char *argv1[] ={"raycast", "-input", "scene1_difuse_light.txt", "-size", "200", "200","-output", "scene2.tga"};
	//int argc1 =9;
    // Interpreta los argumentos del programa
    parseArguments(argc, argv);
	//Pasamos al parser el archivo de entrada
	SceneParser *escena = new SceneParser(input_file);
	//Creamos la imagen de salida con las medidas pasadas en consola
	Image *salida = new Image(width,height);
	//pintamos con el color de fondo indicado en el archivo de entrada
	salida->SetAllPixels(escena->getBackgroundColor());
	//Creamos la imagen qu
	Image  *profundidad = new Image(width,height);     
    Camera *camera = escena->getCamera();   
	Group  *objetos = escena->getGroup();
	Vec3f color = escena->getBackgroundColor();
	for(int y=0; y<height; y++)                 
	{
		for(int x=0; x<width; x++)
		{
			Vec2f point(x,y);
			//float u = 0 + (1-0)*(point.x() + 0.5)/float(width);
			//float v = 0 + (1-0)*(point.y() + 0.5)/float(height);
	
			point/=(float)width;
			//Generamos un rayo por cada pixel
			Ray rayo = camera->generateRay(point);
			//Inicializamos Hit con con t= FLT_MAX y el color de fondo
			Hit hit(FLT_MAX, color,Vec3f(0,0,0));
			//Verificamos si existe interseccion
			bool interseccion = objetos->intersect(rayo, hit,-100000);
			Light* luz= escena->getLight(0);
			Vec3f dir;
			Vec3f color_luz_r;
			Vec3f color_luz;
			luz->getIllumination(dir,dir,color_luz);
			Vec3f::Cross3(color_luz_r,escena->getAmbientLight(),color_luz);
			Vec3f _color= hit.getColor()+(color_luz-escena->getAmbientLight())*(0.5*dir.Dot3(hit.getNormal()));
			if(interseccion)salida->SetPixel(x,y,_color);
			else salida->SetPixel(x,y,color);
		    float t_aux = hit.getT();
			float l = depth_max-depth_min;
			//color entre 1.0 y 0.0 (blanco y negro)
			float color_pro = 1.0f-(t_aux-depth_min)/l;
			Vec3f color(color_pro,color_pro,color_pro);
			//profundidad del pixel
			profundidad->SetPixel(x,y,color);
		}
	}
	//Guardamos los archivos de salida dependiendo de los argumentos
	if(output_file != NULL){
		salida->SaveTGA(output_file);
	}
	if(depth_file != NULL){
		profundidad->SaveTGA(depth_file);
	}
    
    return 0;
}


