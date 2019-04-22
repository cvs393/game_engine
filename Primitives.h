#pragma once

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>



class Primitives
{
	float positions[10];
public : 
	void ObjectPositions(float numOfObjects);
	Primitives(); 
	int sizeOf();

};

/*
class Cube 
{
public : 

	//constructor of cube object
	Cube();
};
*/
#endif