/*

Dummy routines for matrix transformations.

These are for you to write!

*/


#include <stdio.h>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>

#include "osuGraphics.h"
#include "lines.h"

//-------------------------------------------------

class Matr4X4 {
public:
	float x1y1;
	float x1y2;
	float x1y3;
	float x1y4;
	float x2y1;
	float x2y2;
	float x2y3;
	float x2y4;
	float x3y1;
	float x3y2;
	float x3y3;
	float x3y4;
	float x4y1;
	float x4y2;
	float x4y3;
	float x4y4;
	int size;
	Matr4X4() {
		x1y1 = 1;
		x1y2 = 0;
		x1y3 = 0;
		x1y4 = 0;
		x2y1 = 0;
		x2y2 = 1;
		x2y3 = 0;
		x2y4 = 0;
		x3y1 = 0;
		x3y2 = 0;
		x3y3 = 1;
		x3y4 = 0;
		x4y1 = 0;
		x4y2 = 0;
		x4y3 = 0;
		x4y4 = 1;
		size = 0;
	};
};

class Matr4X1 {
public:
	double x;
	double y;
	double z;
	double w;
	int size;
	Matr4X1() {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	};
	Matr4X1(float a, float b, float c, float d);
};

Matr4X1::Matr4X1(float a, float b, float c, float d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

int xy = 0;
float nearclip;
float farclip;
Matr4X1 endpoints[2];
Matr4X4 *matrix = new Matr4X4[32];

Matr4X4 orthmatrix;
Matr4X4 perspective;
Matr4X4 windowing_transform;

Matr4X4 *transformation = new Matr4X4[32];

Matr4X4 matrix_Multiply4x4(Matr4X4 left, Matr4X4 right) {
	Matr4X4 matrix1;
	matrix1.x1y1 = (left.x1y1 * right.x1y1) + (left.x2y1 * right.x1y2) + (left.x3y1 * right.x1y3) + (left.x4y1 * right.x1y4);
	matrix1.x2y1 = (left.x1y1 * right.x2y1) + (left.x2y1 * right.x2y2) + (left.x3y1 * right.x2y3) + (left.x4y1 * right.x2y4);
	matrix1.x3y1 = (left.x1y1 * right.x3y1) + (left.x2y1 * right.x3y2) + (left.x3y1 * right.x3y3) + (left.x4y1 * right.x3y4);
	matrix1.x4y1 = (left.x1y1 * right.x4y1) + (left.x2y1 * right.x4y2) + (left.x3y1 * right.x4y3) + (left.x4y1 * right.x4y4);

	matrix1.x1y2 = (left.x1y2 * right.x1y1) + (left.x2y2 * right.x1y2) + (left.x3y2 * right.x1y3) + (left.x4y2 * right.x1y4);
	matrix1.x2y2 = (left.x1y2 * right.x2y1) + (left.x2y2 * right.x2y2) + (left.x3y2 * right.x2y3) + (left.x4y2 * right.x2y4);
	matrix1.x3y2 = (left.x1y2 * right.x3y1) + (left.x2y2 * right.x3y2) + (left.x3y2 * right.x3y3) + (left.x4y2 * right.x3y4);
	matrix1.x4y2 = (left.x1y2 * right.x4y1) + (left.x2y2 * right.x4y2) + (left.x3y2 * right.x4y3) + (left.x4y2 * right.x4y4);


	matrix1.x1y3 = (left.x1y3 * right.x1y1) + (left.x2y3 * right.x1y2) + (left.x3y3 * right.x1y3) + (left.x4y3 * right.x1y4);
	matrix1.x2y3 = (left.x1y3 * right.x2y1) + (left.x2y3 * right.x2y2) + (left.x3y3 * right.x2y3) + (left.x4y3 * right.x2y4);
	matrix1.x3y3 = (left.x1y3 * right.x3y1) + (left.x2y3 * right.x3y2) + (left.x3y3 * right.x3y3) + (left.x4y3 * right.x3y4);
	matrix1.x4y3 = (left.x1y3 * right.x4y1) + (left.x2y3 * right.x4y2) + (left.x3y3 * right.x4y3) + (left.x4y3 * right.x4y4);

	matrix1.x1y4 = (left.x1y4 * right.x1y1) + (left.x2y4 * right.x1y2) + (left.x3y4 * right.x1y3) + (left.x4y4 * right.x1y4);
	matrix1.x2y4 = (left.x1y4 * right.x2y1) + (left.x2y4 * right.x2y2) + (left.x3y4 * right.x2y3) + (left.x4y4 * right.x2y4);
	matrix1.x3y4 = (left.x1y4 * right.x3y1) + (left.x2y4 * right.x3y2) + (left.x3y4 * right.x3y3) + (left.x4y4 * right.x3y4);
	matrix1.x4y4 = (left.x1y4 * right.x4y1) + (left.x2y4 * right.x4y2) + (left.x3y4 * right.x4y3) + (left.x4y4 * right.x4y4);

	return matrix1;
}

Matr4X1 matrix_Multiply4x1(Matr4X4 left, Matr4X1 right) {
	Matr4X1 matrix1;
	matrix1.x = (left.x1y1 * right.x) + (left.x2y1 * right.y) + (left.x3y1 * right.z) + (left.x4y1 * right.w);
	matrix1.y = (left.x1y2 * right.x) + (left.x2y2 * right.y) + (left.x3y2 * right.z) + (left.x4y2 * right.w);
	matrix1.z = (left.x1y3 * right.x) + (left.x2y3 * right.y) + (left.x3y3 * right.z) + (left.x4y3 * right.w);
	matrix1.w = (left.x1y4 * right.x) + (left.x2y4 * right.y) + (left.x3y4 * right.z) + (left.x4y4 * right.w);

	return matrix1;
}


void osuOrtho(double left, double right, double bottom, double top, double nearp,double farp)
{ 
	float m = 360.0f; //width of display window
	float n = 360.0f; //height of display window
	Matr4X4 matrix1 = Matr4X4(); //matrix maps (r-l)x(t-b) to 360x360
	Matr4X4 matrix2 = Matr4X4();
	Matr4X4 matrix3 = Matr4X4();

	windowing_transform.x1y1 = m / 2;
	windowing_transform.x1y2 = 0;
	windowing_transform.x1y3 = 0;
	windowing_transform.x1y4 = 0;
	windowing_transform.x2y1 = 0;
	windowing_transform.x2y2 = n / 2;
	windowing_transform.x2y3 = 0;
	windowing_transform.x2y4 = 0;
	windowing_transform.x3y1 = 0;
	windowing_transform.x3y2 = 0;
	windowing_transform.x3y3 = 1;
	windowing_transform.x3y4 = 0;
	windowing_transform.x4y1 = (m / 2.0f ) - 0.5f;
	windowing_transform.x4y2 = (n / 2.0f) - 0.5f;
	windowing_transform.x4y3 = 0;
	windowing_transform.x4y4 = 1;

	matrix2.x1y1 = (2.0f / (right - left));
	matrix2.x1y2 = 0;
	matrix2.x1y3 = 0;
	matrix2.x1y4 = 0;
	matrix2.x2y1 = 0;
	matrix2.x2y2 = (2.0f / (top - bottom));
	matrix2.x2y3 = 0;
	matrix2.x2y4 = 0;
	matrix2.x3y1 = 0;
	matrix2.x3y2 = 0;
	matrix2.x3y3 = -(2.0f / (farp - nearp));
	matrix2.x3y4 = 0;
	matrix2.x4y1 = 0;
	matrix2.x4y2 = 0;
	matrix2.x4y3 = 0;
	matrix2.x4y4 = 1;

	matrix3.x1y1 = 1;
	matrix3.x1y2 = 0;
	matrix3.x1y3 = 0;
	matrix3.x1y4 = 0;
	matrix3.x2y1 = 0;
	matrix3.x2y2 = 1;
	matrix3.x2y3 = 0;
	matrix3.x2y4 = 0;
	matrix3.x3y1 = 0;
	matrix3.x3y2 = 0;
	matrix3.x3y3 = 1;
	matrix3.x3y4 = 0;
	matrix3.x4y1 = -(left + right) / 2;
	matrix3.x4y2 = -(top + bottom) / 2;
	matrix3.x4y3 = -(nearp + farp) / 2;
	matrix3.x4y4 = 1;

	orthmatrix = matrix_Multiply4x4(matrix2, matrix3);
	///orthmatrix = matrix_Multiply4x4(matrix1, orthmatrix);
	nearclip = nearp;
	farclip = farp;

	/*
	perspective.x1y1 = (right - left);
	perspective.x1y2 = 0;
	perspective.x1y3 = 0;
	perspective.x1y4 = 0;
	perspective.x2y1 = 0;
	perspective.x2y2 = (top - bottom);
	perspective.x2y3 = 0;
	perspective.x2y4 = 0;	
	perspective.x3y1 = 0;
	perspective.x3y2 = 0;
	perspective.x3y3 = farp/(nearp-farp);
	perspective.x3y4 = -1;
	perspective.x4y1 = 0;
	perspective.x4y2 = 0;
	perspective.x4y3 = ((nearp * farp) / (nearp - farp));
	perspective.x4y4 = 0;

	*/
		
}
void osuPerspective(double fovy, double nearp, double farp) 
{  	

	Matr4X4 matrix1 = Matr4X4(); //matrix maps (r-l)x(t-b) to 360x360
	fovy = fovy / 2.0f;
	float c = cos(fovy * 3.14159 / 180);
	float s = sin(fovy * 3.14159 / 180);
	float h = c/s;
	perspective.x1y1 = h;
	perspective.x1y2 = 0;
	perspective.x1y3 = 0;	
	perspective.x1y4 = 0;
	perspective.x2y1 = 0;
	perspective.x2y2 = h;
	perspective.x2y3 = 0;
	perspective.x2y4 = 0;
	perspective.x3y1 = 0;
	perspective.x3y2 = 0;
	perspective.x3y3 = farp / (nearp - farp);
	perspective.x3y4 = -1;
	perspective.x4y1 = 0;
	perspective.x4y2 = 0;
	perspective.x4y3 = ((nearp * farp) / (nearp - farp));
	perspective.x4y4 = 0;
	/*
	matrix1.x1y1 = 360.0f / 2.0f;
	matrix1.x1y2 = 0;
	matrix1.x1y3 = 0;
	matrix1.x1y4 = 0;
	matrix1.x2y1 = 0;
	matrix1.x2y2 = 360.0f / 2.0f;
	matrix1.x2y3 = 0;
	matrix1.x2y4 = 0;
	matrix1.x3y1 = 0;
	matrix1.x3y2 = 0;
	matrix1.x3y3 = 1;
	matrix1.x3y4 = 0;
	matrix1.x4y1 = (360.0f / 2.0f) - 0.5f;
	matrix1.x4y2 = (360.0f / 2.0f) - 0.5f;
	matrix1.x4y3 = 0;
	matrix1.x4y4 = 1;
	perspective = matrix_Multiply4x4(matrix1, perspective);

	*/


	windowing_transform.x1y1 = 360.0f / 2.0f;
	windowing_transform.x1y2 = 0;
	windowing_transform.x1y3 = 0;
	windowing_transform.x1y4 = 0;
	windowing_transform.x2y1 = 0;
	windowing_transform.x2y2 = 360.0f / 2.0f;
	windowing_transform.x2y3 = 0;
	windowing_transform.x2y4 = 0;
	windowing_transform.x3y1 = 0;
	windowing_transform.x3y2 = 0;
	windowing_transform.x3y3 = 1;
	windowing_transform.x3y4 = 0;
	windowing_transform.x4y1 = (360.0f / 2.0f) - 0.5f;
	windowing_transform.x4y2 = (360.0f / 2.0f) - 0.5f;
	windowing_transform.x4y3 = 0;
	windowing_transform.x4y4 = 1;
	
	nearclip = nearp;
	farclip = farp;

}
void osuBegin(OSUDrawable mode)
{
}

void osuEnd()
{
}

void osuColor3f(double red, double green, double blue)
{
}

void osuVertex2f(double x, double y)
{
}



void osuVertex3f(double x, double y, double z)
{
	Matr4X1 temp;
	Matr4X1 temp2;

	Matr4X4 tempy;
	int size = matrix[0].size;
	Matr4X4 transform = matrix[size];

	
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.w = 1;
		//temp.x = temp.x / temp.w;
		//temp.y = temp.y / temp.w;
		//temp.z = temp.z / temp.w;
		//temp.w = temp.w / temp.w;
		temp = matrix_Multiply4x1(transform, temp);
		temp = matrix_Multiply4x1(perspective, temp);

		
	if (xy == 0) {
		endpoints[0] = temp;		
		xy++;
	}
	else if (xy == 1) {
		temp2 = endpoints[0];

		if (1 == near_far_clip(-100, 100, &temp.x, &temp.y, &temp.z, &temp2.x, &temp2.y, &temp2.z))
		{


			temp2 = matrix_Multiply4x1(orthmatrix, temp2);
			temp2 = matrix_Multiply4x1(windowing_transform, temp2);
			temp2.x = temp2.x / temp2.w;
			temp2.y = temp2.y / temp2.w;
			temp2.z = temp2.z / temp2.w;
			temp2.w = temp2.w / temp2.w;
			endpoints[0] = temp2;

			temp = matrix_Multiply4x1(orthmatrix, temp);
			temp = matrix_Multiply4x1(windowing_transform, temp);
			temp.x = temp.x / temp.w;
			temp.y = temp.y / temp.w;
			temp.z = temp.z / temp.w;
			temp.w = temp.w / temp.w;
			endpoints[1] = temp;

			draw_line((endpoints[0].x), (endpoints[0].y), (endpoints[1].x), (endpoints[1].y));
			xy = 0;
		}
		else {
			xy = 0;

		}
	}
}

void osuInitialize() 
{ 
}


void osuPushMatrix() 
{ 
	matrix[0].size = matrix[0].size + 1;
	int size = matrix[0].size;
	matrix[size] = matrix[size - 1];
}

void osuPopMatrix() 
{ 
	int size = matrix[0].size;
	matrix[size].x1y1 = 1;
	matrix[size].x1y2 = 0;
	matrix[size].x1y3 = 0;
	matrix[size].x1y4 = 0;
	matrix[size].x2y1 = 0;
	matrix[size].x2y2 = 1;
	matrix[size].x2y3 = 0;
	matrix[size].x2y4 = 0;
	matrix[size].x3y1 = 0;
	matrix[size].x3y2 = 0;
	matrix[size].x3y3 = 1;
	matrix[size].x3y4 = 0;
	matrix[size].x4y1 = 0;
	matrix[size].x4y2 = 0;
	matrix[size].x4y3 = 0;
	matrix[size].x4y4 = 1;
	matrix[0].size = matrix[0].size - 1;
}

void osuLoadIdentityMatrix()
{
}
void osuTranslate(double tx, double ty, double tz) 
{ 
	int size = matrix[0].size;

	Matr4X4 matrix1;


	matrix1.x1y1 = 1;
	matrix1.x2y1 = 0;
	matrix1.x3y1 = 0;
	matrix1.x4y1 = tx;

	matrix1.x1y2 = 0;
	matrix1.x2y2 = 1;
	matrix1.x3y2 = 0;
	matrix1.x4y2 = ty;

	matrix1.x1y3 = 0;
	matrix1.x2y3 = 0;
	matrix1.x3y3 = 1;
	matrix1.x4y3 = tz;

	matrix1.x1y4 = 0;
	matrix1.x2y4 = 0;
	matrix1.x3y4 = 0;
	matrix1.x4y4 = 1;
	matrix[size] = matrix_Multiply4x4(matrix[size], matrix1);
}

void osuScale(double sx, double sy, double sz) 
{ 
	int size = matrix[0].size;
	Matr4X4 matrix1;

	matrix1.x1y1 = sx;
	matrix1.x1y2 = 0;
	matrix1.x1y3 = 0;
	matrix1.x1y4 = 0;

	matrix1.x2y1 = 0;
	matrix1.x2y2 = sy;
	matrix1.x2y3 = 0;
	matrix1.x2y4 = 0;

	matrix1.x3y1 = 0;
	matrix1.x3y2 = 0;
	matrix1.x3y3 = sz;
	matrix1.x3y4 = 0;

	matrix1.x4y1 = 0;
	matrix1.x4y2 = 0;
	matrix1.x4y3 = 0;
	matrix1.x4y4 = 1;
	matrix[size] = matrix_Multiply4x4(matrix[size], matrix1);
}



void osuRotate(double angle, double ax, double ay, double az) { 

	int size = matrix[0].size;
	Matr4X4 matrix1;
	Matr4X4 matrix2;
	Matr4X4 matrix3;

	if (ax != 0) {
		matrix1.x1y1 = 1;
		matrix1.x1y2 = 0;
		matrix1.x1y3 = 0;
		matrix1.x1y4 = 0;

		matrix1.x2y1 = 0;
		matrix1.x2y2 = cos(angle * 3.14159 / 180);
		matrix1.x2y3 = -sin(angle * 3.14159 / 180) * ax;
		matrix1.x2y4 = 0;

		matrix1.x3y1 = 0;
		matrix1.x3y2 = sin(angle * 3.14159 / 180) * ax;
		matrix1.x3y3 = cos(angle * 3.14159 / 180);
		matrix1.x3y4 = 0;

		matrix1.x4y1 = 0;
		matrix1.x4y2 = 0;
		matrix1.x4y3 = 0;
		matrix1.x4y4 = 1;
	}
	if (ay != 0) {
		matrix2.x1y1 = cos(angle * 3.14159 / 180);
		matrix2.x1y2 = 0;
		matrix2.x1y3 = -sin(angle * 3.14159 / 180) * ay;
		matrix2.x1y4 = 0;

		matrix2.x2y1 = 0;
		matrix2.x2y2 = 1;
		matrix2.x2y3 = 0;
		matrix2.x2y4 = 0;

		matrix2.x3y1 = sin(angle * 3.14159 / 180) * ay;
		matrix2.x3y2 = 0;
		matrix2.x3y3 = cos(angle * 3.14159 / 180);
		matrix2.x3y4 = 0;

		matrix2.x4y1 = 0;
		matrix2.x4y2 = 0;
		matrix2.x4y3 = 0;
		matrix2.x4y4 = 1;
	}
	matrix2 = matrix_Multiply4x4(matrix2, matrix1);
	if (az != 0) {
		matrix3.x1y1 = cos(angle * 3.14159 / 180);
		matrix3.x1y2 = sin(angle * 3.14159 / 180) * az;
		matrix3.x1y3 = 0;
		matrix3.x1y4 = 0;

		matrix3.x2y1 = -sin(angle * 3.14159 / 180) * az;
		matrix3.x2y2 = cos(angle * 3.14159 / 180);
		matrix3.x2y3 = 0;
		matrix3.x2y4 = 0;

		matrix3.x3y1 = 0;
		matrix3.x3y2 = 0;
		matrix3.x3y3 = 1;
		matrix3.x3y4 = 0;

		matrix3.x4y1 = 0;
		matrix3.x4y2 = 0;
		matrix3.x4y3 = 0;
		matrix3.x4y4 = 1;
	}
	matrix3 = matrix_Multiply4x4(matrix3, matrix2);


	matrix[size] = matrix_Multiply4x4(matrix[size], matrix3);

}

void osuLookat(double from[3], double at[3], double up[3])
{
}

