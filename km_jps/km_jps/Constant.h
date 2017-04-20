#pragma once
#include "stdafx.h"
#include "Matrix.h"

class Constant
{
public:
	static const std::map<size_t, std::pair<size_t, size_t>> WIN_POSITIONS;
	static const Matrix WIN_MATRIX;
	static const size_t WIN_MATRIX_HASH;
};
