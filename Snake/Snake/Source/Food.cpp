#include "Food.h"
#include "Snake.h"

Food::Food(Pos pos)
{
	_pos = pos;

	int r = rand();
	if (r % 3 == 0)
	{
		_shape = "¡Ý";
	}
	else if (r % 3 == 1)
	{
		_shape = "¡Ü";
	}
	else
	{
		_shape = "¡Ù";
	}
}

void Food::printBody()
{
	Utility::printStringOnPos(_shape, _pos);
}