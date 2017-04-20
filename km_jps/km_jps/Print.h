#pragma once
#include "stdafx.h"
#include "Node.h"

using namespace std;

class CPrint
{
public:
	CPrint(wostream & out)
		: m_out(out)
	{
		m_useFile = false;
	}

	CPrint(const string & outputFileName)
		: m_out(wcout)
	{
		m_outputFile.open(outputFileName);
		m_useFile = true;
	}

	void StatesToGoal(const map<size_t, vector<CNode*>> & nodesPriorityQueue, size_t & wayLength)
	{
		SimpleType(L"Ходы: ", "");
		wayLength = 0;
		PrintStatesToGoalRecursive(nodesPriorityQueue.begin()->second[0], nodesPriorityQueue.begin()->second[0]->matrix, wayLength);
		--wayLength;
	}

	void Steps(const map<size_t, vector<CNode*>> & nodesPriorityQueue, size_t & wayLength)
	{
		wayLength = 0;
		SimpleType(L"Путь: ", "");
		Print("[");
		PrintStepsRecursive(nodesPriorityQueue.begin()->second[0], nodesPriorityQueue.begin()->second[0]->matrix, Point(SIZE_MAX, SIZE_MAX), wayLength);
		Print("]");
		Print("\n");
	}

	void MemoryUsage()
	{
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		SimpleType(L"Пямять: ", pmc.WorkingSetSize / 1024 / 1024);
	}

	template<typename T>
	void SimpleType(const wstring & message, T simpleType)
	{
		Print(message);
		Print(simpleType);
		Print("\n");
	}

private:
	template<typename T>
	void Print(T arg)
	{
		if (m_useFile)
		{
			m_outputFile << arg;
		}
		else
		{
			m_out << arg;
		}
	}

	void PrintStepsRecursive(CNode *currentNode, const Matrix & matrix, const Point & fromZeroPos, size_t & wayLength)
	{
		if (currentNode->GetFather() != nullptr)
		{
			PrintStepsRecursive(currentNode->GetFather(), currentNode->GetFather()->matrix, currentNode->GetZeroPos(), wayLength);
		}
		if (fromZeroPos.x == SIZE_MAX && fromZeroPos.y == SIZE_MAX)
		{
			return;
		}
		++wayLength;
		if (currentNode->GetZeroPos().x > fromZeroPos.x)
		{
			Print("'left', ");
		}
		else if (currentNode->GetZeroPos().x < fromZeroPos.x)
		{
			Print("'right', ");
		}
		else if (currentNode->GetZeroPos().y > fromZeroPos.y)
		{
			Print("'up', ");
		}
		else if (currentNode->GetZeroPos().y < fromZeroPos.y)
		{
			Print("'down', ");
		}
	}

	void PrintStatesToGoalRecursive(CNode *currentNode, const Matrix & matrix, size_t & wayLength)
	{
		if (currentNode->GetFather() != nullptr)
		{
			PrintStatesToGoalRecursive(currentNode->GetFather(), currentNode->GetFather()->matrix, wayLength);
		}
		++wayLength;
		for (size_t y = 0; y < matrix.size(); ++y)
		{
			for (size_t x = 0; x < matrix[y].size(); ++x)
			{
				Print(matrix[y][x]);
				Print(" ");
			}
			Print("\n");
		}
		Print("\n");
	}

	wostream & m_out;
	wofstream m_outputFile;
	bool m_useFile = false;
};

