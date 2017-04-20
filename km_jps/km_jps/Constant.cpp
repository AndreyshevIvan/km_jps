#include "Constant.h"

const std::map<size_t, std::pair<size_t, size_t>> Constant::WIN_POSITIONS =
{
	{ 0,{ 0, 0 } },
	{ 1,{ 1, 0 } },
	{ 2,{ 2, 0 } },
	{ 3,{ 3, 0 } },
	{ 4,{ 0, 1 } },
	{ 5,{ 1, 1 } },
	{ 6,{ 2, 1 } },
	{ 7,{ 3, 1 } },
	{ 8,{ 0, 2 } },
	{ 9,{ 1, 2 } },
	{ 10,{ 2, 2 } },
	{ 11,{ 3, 2 } },
	{ 12,{ 0, 3 } },
	{ 13,{ 1, 3 } },
	{ 14,{ 2, 3 } },
	{ 15,{ 3, 3 } }
};

const Matrix Constant::WIN_MATRIX =
{
	{ 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 8, 9, 10, 11 },
	{ 12, 13, 14, 15 }
};

const size_t Constant::WIN_MATRIX_HASH = 3350190892;
