#include "SquareImplementation.h"
#include <stdio.h>



SquareImplementation::SquareImplementation()
{
}


SquareImplementation::~SquareImplementation()
{
}

const char* SquareImplementation::GetShapeName() const
{
	return "Square";
}

void SquareImplementation::DrawShape() const
{
	printf("  XXXXXXXXXX  \n");
	printf("  XX      XX  \n");
	printf("  XX      XX  \n");
	printf("  XX      XX  \n");
	printf("  XXXXXXXXXX  \n");
}

