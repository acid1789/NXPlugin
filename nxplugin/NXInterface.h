#pragma once

typedef struct _NXInterfaceID
{
	unsigned int uuid[4];

	_NXInterfaceID() { uuid[0] = uuid[1] = uuid[2] = uuid[3] = 0; }
	_NXInterfaceID(unsigned int a, unsigned int b, unsigned int c, unsigned int d) { uuid[0] = a; uuid[1] = b; uuid[2] = c; uuid[3] = d; }

	bool IsZero() const { return (uuid[0] == 0 && uuid[1] == 0 && uuid[2] == 0 && uuid[3] == 0); }

	bool operator==(const _NXInterfaceID& other) const { return (uuid[0] == other.uuid[0] && uuid[1] == other.uuid[1] && uuid[2] == other.uuid[2] && uuid[3] == other.uuid[3]);
	}
} NXInterfaceID;

class NXInterface
{
public:
	NXInterface() {}
	virtual ~NXInterface() {}

	const NXInterfaceID& GetID() const { return _interfaceID; }

protected:
	NXInterfaceID _interfaceID;
};
