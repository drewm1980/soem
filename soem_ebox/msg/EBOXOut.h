#include <stdint.h>

struct EBOXOut
{
	bool trigger[2];
	bool digital[8];
	float analog[2];
	uint32_t timestamp;
	uint32_t encoder[2];
};
