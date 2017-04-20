#pragma once
#include "stdafx.h"
#include "Matrix.h"

using namespace std;

class CInput
{
public:
	bool ReadStartMatrix(const string & inputFileName, Matrix & matrix)
	{
		ifstream inputFile(inputFileName);
		bool result = false;
		SkipWhitespaces(inputFile);
		size_t elem;
		size_t counter = 0;
		matrix = Matrix(4, vector<size_t>());
		while (inputFile.peek() != '\n' && !inputFile.eof() && inputFile >> elem)
		{
			matrix[counter].push_back(elem);
			result = true;
			SkipWhitespaces(inputFile);
			if (matrix[counter].size() % 4 == 0)
			{
				++counter;
			}
		}
		return result;
	}
private:
	void SkipWhitespaces(ifstream & inputFile)
	{
		while (inputFile.peek() == ' ')
		{
			inputFile.get();
		}
	}
};

