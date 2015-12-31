#include "CircleImplementation.h"
#include <stdio.h>


CircleImplementation::CircleImplementation()
{
}


CircleImplementation::~CircleImplementation()
{
}

const char* CircleImplementation::GetShapeName() const
{
	return "Circle";
}

void CircleImplementation::DrawShape() const
{
	printf("            XXXX       \n");
	printf("          XXX  XXX     \n");
	printf("        XXX      XXX   \n");
	printf("       XX          XX  \n");
	printf("        XXX      XXX   \n");
	printf("          XXX  XXX     \n");
	printf("            XXXX       \n");
}