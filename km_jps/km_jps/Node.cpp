#include "Node.h"

CNode::CNode(const Matrix & matrix)
	: matrix(matrix)
{
}

CNode::CNode(Matrix && matrix)
{
	matrix = move(matrix);
}

CNode *CNode::GetFather() const
{
	return m_father;
}

void CNode::SetFather(CNode *father)
{
	m_father = father;
	m_depth = father->GetDepth() + 1;
}

size_t CNode::GetDepth() const
{
	return m_depth;
}

size_t CNode::GetHash() const
{
	return m_hash;
}

void CNode::SetHash(size_t value)
{
	m_hash = value;
}

Point CNode::GetZeroPos() const
{
	return m_zeroPos;
}

void CNode::SetZeroPos(const Point & value)
{
	m_zeroPos = value;
}

void CNode::SetZeroPos(Point && value)
{
	m_zeroPos = move(value);
}

size_t CNode::CalculateMatrixHash(const Matrix & matrix)
{
	size_t seed = 0;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		seed ^= boost::hash_range(matrix[i].begin(), matrix[i].end()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

size_t CNode::CalculateManhattanDistance(const Matrix & matrix)
{
	size_t result = 0;
	for (size_t y = 0; y < matrix.size(); ++y)
	{
		for (size_t x = 0; x < matrix[y].size(); ++x)
		{
			if (Constant::WIN_POSITIONS.at(matrix[y][x]).first > x)
			{
				result += Constant::WIN_POSITIONS.at(matrix[y][x]).first - x;
			}
			else
			{
				result += x - Constant::WIN_POSITIONS.at(matrix[y][x]).first;
			}
			if (Constant::WIN_POSITIONS.at(matrix[y][x]).second > y)
			{
				result += Constant::WIN_POSITIONS.at(matrix[y][x]).second - y;
			}
			else
			{
				result += y - Constant::WIN_POSITIONS.at(matrix[y][x]).second;
			}
		}
	}
	return result;
}

void CNode::CalculateZeroPos(const Matrix & matrix, Point & zeroPos)
{
	for (size_t y = 0; y < matrix.size(); ++y)
	{
		for (size_t x = 0; x < matrix[y].size(); ++x)
		{
			if (matrix[y][x] == 0)
			{
				zeroPos = Point(x, y);
				return;
			}
		}
	}
}

CNode *CNode::CreateNode(CNode *currentNode, int directionX, int directionY)
{
	Point & currentNodeZeroPos = currentNode->GetZeroPos();
	CNode *newNode = new CNode;
	newNode->SetZeroPos(Point(currentNodeZeroPos.x + directionX, currentNodeZeroPos.y + directionY));
	newNode->SetFather(currentNode);
	newNode->matrix = currentNode->matrix;
	swap(newNode->matrix[newNode->GetZeroPos().y][newNode->GetZeroPos().x], newNode->matrix[currentNodeZeroPos.y][currentNodeZeroPos.x]);
	newNode->SetHash(CNode::CalculateMatrixHash(newNode->matrix));
	return newNode;
}
