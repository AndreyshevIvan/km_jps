#include "stdafx.h"
#include "Input.h"
#include "Constant.h"
#include "Node.h"
#include "Print.h"

using namespace std;

bool IsHashProcessed(size_t hash, set<size_t> & processedHashes)
{
	return processedHashes.find(hash) != processedHashes.end();
}

CNode *GetFirstNode(map<size_t, vector<CNode*>> & nodesPriorityQueue)
{
	CNode *result = nullptr;
	result = nodesPriorityQueue.begin()->second[nodesPriorityQueue.begin()->second.size() - 1];
	if (nodesPriorityQueue.begin()->second.size() == 1)
	{
		nodesPriorityQueue.erase(nodesPriorityQueue.begin());
	}
	else
	{
		nodesPriorityQueue.begin()->second.pop_back();
	}
	return result;
}

bool InsertNewNodeToQueueAndCheckIsItWin(CNode *currentNode, Point && newZeroPos, Matrix && newMatrix, size_t newManhattanDistance, size_t newHash, map<size_t, vector<CNode*>> & nodesPriorityQueue, size_t & totalNodeCount)
{
	++totalNodeCount;
	CNode *newNode = CNode::CreateNode(currentNode, move(newZeroPos), move(newMatrix), newHash, newManhattanDistance);
	nodesPriorityQueue[newNode->GetManhattanDistance() + currentNode->GetDepth()].push_back(newNode);
	return newNode->GetHash() == Constant::WIN_MATRIX_HASH;
}

bool ProcessQueue(map<size_t, vector<CNode*>> & nodesPriorityQueue, set<size_t> & processedHashes, size_t & totalNodeCount, bool & doesGoalReached)
{
	CNode *firstNode = GetFirstNode(nodesPriorityQueue);
	size_t smallestNewManhattanDistance = SIZE_MAX;
	vector<Point> newZeroPos;
	vector<Matrix> newMatrix;
	vector<size_t> newHash;

	Point & firstNodeZeroPos = firstNode->GetZeroPos();
	if (firstNodeZeroPos.y > 0)
	{
		Point newZeroPosTop = Point(firstNodeZeroPos.x, firstNodeZeroPos.y - 1);
		Matrix newMatrixTop = firstNode->matrix;
		swap(newMatrixTop[newZeroPosTop.y][newZeroPosTop.x], newMatrixTop[firstNodeZeroPos.y][firstNodeZeroPos.x]);
		size_t newManhattanDistance = CNode::CalculateManhattanDistance(newMatrixTop);
		size_t newHashTop = CNode::CalculateMatrixHash(newMatrixTop);
		if (!IsHashProcessed(newHashTop, processedHashes) && newManhattanDistance <= smallestNewManhattanDistance)
		{
			if (newManhattanDistance < smallestNewManhattanDistance)
			{
				newZeroPos.clear();
				newMatrix.clear();
				newHash.clear();
			}
			smallestNewManhattanDistance = newManhattanDistance;
			newZeroPos.push_back(move(newZeroPosTop));
			newMatrix.push_back(move(newMatrixTop));
			newHash.push_back(newHashTop);
		}
	}
	if (firstNodeZeroPos.x < firstNode->matrix.size() - 1)
	{
		Point newZeroPosRight = Point(firstNodeZeroPos.x + 1, firstNodeZeroPos.y);
		Matrix newMatrixRight = firstNode->matrix;
		swap(newMatrixRight[newZeroPosRight.y][newZeroPosRight.x], newMatrixRight[firstNodeZeroPos.y][firstNodeZeroPos.x]);
		size_t newManhattanDistance = CNode::CalculateManhattanDistance(newMatrixRight);
		size_t newHashRight = CNode::CalculateMatrixHash(newMatrixRight);
		if (!IsHashProcessed(newHashRight, processedHashes) && newManhattanDistance <= smallestNewManhattanDistance)
		{
			if (newManhattanDistance < smallestNewManhattanDistance)
			{
				newZeroPos.clear();
				newMatrix.clear();
				newHash.clear();
			}
			smallestNewManhattanDistance = newManhattanDistance;
			newZeroPos.push_back(move(newZeroPosRight));
			newMatrix.push_back(move(newMatrixRight));
			newHash.push_back(newHashRight);
		}
	}
	if (firstNodeZeroPos.y < firstNode->matrix.size() - 1)
	{
		Point newZeroPosBottom = Point(firstNodeZeroPos.x, firstNodeZeroPos.y + 1);
		Matrix newMatrixBottom = firstNode->matrix;
		swap(newMatrixBottom[newZeroPosBottom.y][newZeroPosBottom.x], newMatrixBottom[firstNodeZeroPos.y][firstNodeZeroPos.x]);
		size_t newManhattanDistance = CNode::CalculateManhattanDistance(newMatrixBottom);
		size_t newHashBottom = CNode::CalculateMatrixHash(newMatrixBottom);
		if (!IsHashProcessed(newHashBottom, processedHashes) && newManhattanDistance <= smallestNewManhattanDistance)
		{
			if (newManhattanDistance < smallestNewManhattanDistance)
			{
				newZeroPos.clear();
				newMatrix.clear();
				newHash.clear();
			}
			smallestNewManhattanDistance = newManhattanDistance;
			newZeroPos.push_back(move(newZeroPosBottom));
			newMatrix.push_back(move(newMatrixBottom));
			newHash.push_back(newHashBottom);
		}
	}
	if (firstNodeZeroPos.x > 0)
	{
		Point newZeroPosLeft = Point(firstNodeZeroPos.x - 1, firstNodeZeroPos.y);
		Matrix newMatrixLeft = firstNode->matrix;
		swap(newMatrixLeft[newZeroPosLeft.y][newZeroPosLeft.x], newMatrixLeft[firstNodeZeroPos.y][firstNodeZeroPos.x]);
		size_t newManhattanDistance = CNode::CalculateManhattanDistance(newMatrixLeft);
		size_t newHashLeft = CNode::CalculateMatrixHash(newMatrixLeft);
		if (!IsHashProcessed(newHashLeft, processedHashes) && newManhattanDistance <= smallestNewManhattanDistance)
		{
			if (newManhattanDistance < smallestNewManhattanDistance)
			{
				newZeroPos.clear();
				newMatrix.clear();
				newHash.clear();
			}
			smallestNewManhattanDistance = newManhattanDistance;
			newZeroPos.push_back(move(newZeroPosLeft));
			newMatrix.push_back(move(newMatrixLeft));
			newHash.push_back(newHashLeft);
		}
	}

	for (size_t i = 0; i < newZeroPos.size(); ++i)
	{
		if (InsertNewNodeToQueueAndCheckIsItWin(firstNode, move(newZeroPos[i]), move(newMatrix[i]), smallestNewManhattanDistance, newHash[i], nodesPriorityQueue, totalNodeCount))
		{
			doesGoalReached = true;
			return false;
		}
	}
	processedHashes.insert(firstNode->GetHash());
	if (nodesPriorityQueue.empty())
	{
		return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "rus");
	CInput input;

	Matrix startMatrix;
	input.ReadStartMatrix("input.txt", startMatrix);

	CNode *firstNode = new CNode(startMatrix);
	firstNode->SetHash(CNode::CalculateMatrixHash(firstNode->matrix));
	Point zeroPos(0, 0);
	CNode::CalculateZeroPos(firstNode->matrix, zeroPos);
	firstNode->SetZeroPos(move(zeroPos));
	firstNode->SetManhattanDistance(CNode::CalculateManhattanDistance(firstNode->matrix));

	set<size_t> processedHashes;
	map<size_t, vector<CNode*>> nodesPriorityQueue;

	size_t totalNodeCount = 0;
	nodesPriorityQueue[firstNode->GetManhattanDistance()].push_back(firstNode);

	bool doesGoalReached = false;
	boost::chrono::high_resolution_clock::time_point start = boost::chrono::high_resolution_clock::now();
	while (ProcessQueue(nodesPriorityQueue, processedHashes, totalNodeCount, doesGoalReached)) {}
	boost::chrono::high_resolution_clock::time_point end = boost::chrono::high_resolution_clock::now();
	boost::chrono::milliseconds duration = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start);

	CPrint Print(wcout);
	if (!doesGoalReached)
	{
		Print.SimpleType(L"Целевое состояние не достигнуто", "");
		return EXIT_FAILURE;
	}

	Print.SimpleType(L"Сгенерировано узлов: ", totalNodeCount);
	Print.SimpleType(L"Раскрыто узлов: ", processedHashes.size());
	Print.SimpleType(L"Время: ", duration.count());
	Print.MemoryUsage();

	size_t wayLength = 0;
	Print.Steps(nodesPriorityQueue, wayLength);
	Print.StatesToGoal(nodesPriorityQueue, wayLength);
	Print.SimpleType(L"Длина пути: ", wayLength);

	return EXIT_SUCCESS;
}