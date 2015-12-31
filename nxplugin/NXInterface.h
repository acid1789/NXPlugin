#pragma once

typedef struct _NXInterfaceID
{
	unsigned int uuid[4];

	_NXInterfaceID(unsigned int a, unsigned int b, unsigned int c, unsigned int d) { uuid[0] = a; uuid[1] = b; uuid[2] = c; uuid[3] = d; }

	bool IsZero() const { return (uuid[0] == 0 && uuid[1] == 0 && uuid[2] == 0 && uuid[3] == 0); }
} NXInterfaceID;

class NXInterface
{
public:
	NXInterface();
	virtual ~NXInterface();

};
