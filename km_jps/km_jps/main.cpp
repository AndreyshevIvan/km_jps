#include "stdafx.h"
#include "Input.h"
#include "Constant.h"
#include "Node.h"
#include "Print.h"

using namespace std;

bool IsHashProcessed(CNode *currentNode, set<size_t> & processedHashes)
{
	return processedHashes.find(currentNode->GetHash()) != processedHashes.end();
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

bool InsertNewNodeToQueueAndCheckIsItWin(CNode *curentNode, const Point & direction, map<size_t, vector<CNode*>> & nodesPriorityQueue, size_t & totalNodeCount)
{
	bool result = false;
	++totalNodeCount;
	CNode *newNode = CNode::CreateNode(curentNode, direction.x, direction.y);
	nodesPriorityQueue[CNode::CalculateManhattanDistance(newNode->matrix) + curentNode->GetDepth()].push_back(newNode);
	if (newNode->GetHash() == Constant::WIN_MATRIX_HASH)
	{
		result = true;
	}
	return result;
}

bool ProcessQueue(map<size_t, vector<CNode*>> & nodesPriorityQueue, set<size_t> & processedHashes, size_t & totalNodeCount, bool & doesGoalReached)
{
	CNode *firstNode = GetFirstNode(nodesPriorityQueue);

	if (!IsHashProcessed(firstNode, processedHashes))
	{
		Point & firstNodeZeroPos = firstNode->GetZeroPos();
		if (firstNodeZeroPos.y > 0)
		{
			if (InsertNewNodeToQueueAndCheckIsItWin(firstNode, Point(0, -1), nodesPriorityQueue, totalNodeCount))
			{
				doesGoalReached = true;
				return false;
			}
		}
		if (firstNodeZeroPos.x < firstNode->matrix.size() - 1)
		{
			if (InsertNewNodeToQueueAndCheckIsItWin(firstNode, Point(1, 0), nodesPriorityQueue, totalNodeCount))
			{
				doesGoalReached = true;
				return false;
			}
		}
		if (firstNodeZeroPos.y < firstNode->matrix.size() - 1)
		{
			if (InsertNewNodeToQueueAndCheckIsItWin(firstNode, Point(0, 1), nodesPriorityQueue, totalNodeCount))
			{
				doesGoalReached = true;
				return false;
			}
		}
		if (firstNodeZeroPos.x > 0)
		{
			if (InsertNewNodeToQueueAndCheckIsItWin(firstNode, Point(-1, 0), nodesPriorityQueue, totalNodeCount))
			{
				doesGoalReached = true;
				return false;
			}
		}
		processedHashes.insert(firstNode->GetHash());
	}
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

	set<size_t> processedHashes;
	map<size_t, vector<CNode*>> nodesPriorityQueue;

	size_t totalNodeCount = 0;
	nodesPriorityQueue[CNode::CalculateManhattanDistance(firstNode->matrix)].push_back(firstNode);

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