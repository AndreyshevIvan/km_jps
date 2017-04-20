#pragma once
#include "Point.h"
#include "Matrix.h"
#include "Constant.h"

using namespace std;

class CNode
{
public:
	CNode() = default;
	CNode(const Matrix & matrix);

	CNode(Matrix && matrix);

	CNode *GetFather() const;
	void SetFather(CNode *father);

	size_t GetDepth() const;

	size_t GetHash() const;
	void SetHash(size_t value);

	Point GetZeroPos() const;
	void SetZeroPos(const Point & value);
	void SetZeroPos(Point && value);

	static size_t CalculateMatrixHash(const Matrix & matrix);
	static size_t CalculateManhattanDistance(const Matrix & matrix);
	static void CalculateZeroPos(const Matrix & matrix, Point & zeroPos);
	static CNode *CreateNode(CNode *currentNode, int directionX, int directionY);

	Matrix matrix;

private:
	Point m_zeroPos = { 0, 0 };
	size_t m_hash = 0;
	CNode *m_father = nullptr;
	size_t m_depth = 0;
};

