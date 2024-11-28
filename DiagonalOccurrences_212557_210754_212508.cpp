#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <filesystem>
using namespace std;

// Function to check pattern occurrence
bool found(char** matrix, int matrixRows, int matrixCols, char** pattern, int patternDim, int startRow, int endRow, int startCol, int endCol) 
{
	int count = 0;

	for (int i = startRow; i < endRow; i++) 
	{
		for (int j = startCol; j < endCol; j++) 
		{
			if (matrix[i][j] == pattern[i - startRow][j - startCol]) 
			{
				count++;
			}
		}
	}

	return (count == patternDim * patternDim);
}

//Caller function that change the positions for diagonal checking
int count_occurrences(char** matrix, char** pattern, int patternDim, int matrixRows, int matrixCols)
{
	int occurrences = 0;
	for (int i = 0; i < matrixRows - patternDim + 1; i++)
	{
		for (int j = 0; j < matrixCols - patternDim + 1; j++) 
		{
			if (found(matrix, matrixRows, matrixCols, pattern, patternDim, i, i + patternDim, j, j + patternDim))
			{
				occurrences++;
			}
		}
	}
	return (occurrences > 1 ? occurrences : 0);
}

// Function to read the file in the specified format
void read_file(const string& filename, int& rows, int& cols, int& pattern_dim, int& result, char**& arr, char**& pattern)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		return;
	}
	string rd = "";
	string to_int = "";
	int i = 0;
	bool flag = true;
	while (!file.eof())
	{
		flag = true;
		getline(file, rd, '\n');

		if (rd[0] == 't')
		{
			to_int += rd[2];
			rows = atoi(to_int.c_str());
			to_int.clear();
			to_int += rd[4];
			cols = atoi(to_int.c_str());
			arr = new char* [rows];
			for (int i = 0; i < rows; i++)
				arr[i] = new char[cols];
		}
		else if (rd[0] != 't' && i < rows)
		{
			int k = 0;
			for (int j = 0; j < cols; j++)
			{
				if (arr != nullptr)
				{
					if (arr[i] != nullptr)
					{
						arr[i][j] = rd[k];
						flag = false;
					}
				}
				k += 2;
			}
			if (!flag)
				i++;
		}
		else if (rd != "" && !isdigit(rd[0]))
		{
			int len = sqrt(rd.length());
			pattern_dim = len;
			pattern = new char* [len];
			for (int i = 0; i < len; i++)
				pattern[i] = new char[len];
			int k = 0;
			for (int i = 0; i < len; i++)
			{
				for (int j = 0; j < len; j++)
					pattern[i][j] = rd[k++];
			}
		}
		else if (rd != "" && isdigit(rd[0]))
		{
			result = stoi(rd);
		}
	}
}

// Function to clear the dynamically allocated arrays
void clear_arrays(char**& arr, char**& pattern, int& rows,int& cols, int& pattern_dim,int& result)
{
	for (int i = 0; i < rows; ++i)
		delete[] arr[i];
	delete[] arr;

	for (int i = 0; i < pattern_dim; ++i)
		delete[] pattern[i];
	delete[] pattern;

	arr = nullptr;
	pattern = nullptr;
	rows = 0;
	cols = 0;
	pattern_dim = 0;
	result = 0;
}

// Main Function 
int main()
{
	int k = 0;
	string file = "";
	int rows = 0, cols = 0, pattern_dim = 0, result = 0;
	char** arr = nullptr;
	char** pattern = nullptr;
	while (k < 3)
	{
		if (k == 0)
		{
			file = "input.txt";
		}
		else if (k == 1)
		{
			file = "input2.txt";
		}
		else if(k == 2)
		{
			file = "input3.txt";
		}

		clear_arrays(arr, pattern, rows,cols, pattern_dim,result);
		read_file(file, rows, cols, pattern_dim, result, arr, pattern);
		cout << endl;
		cout << "********************" << endl;
		cout << "    TestCase-" <<  k+1  << endl;
		cout << "********************" << endl;
		cout << "Rows =  " << rows << endl;
		cout << "Columns = " << cols << endl;
		cout << "2D-Matrix : " << endl;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++) 
				cout << arr[i][j] << ',';
			cout << endl;
		}
		cout << "2D-Pattern Matrix : " << endl;
		for (int i = 0; i < pattern_dim; i++)
		{
			for (int j = 0; j < pattern_dim; j++)
				cout << pattern[i][j] << ',';
			cout << endl;
		}
		cout << "Expected Result = " << result << endl;
		int get = count_occurrences(arr, pattern, pattern_dim, rows, cols);
		cout << "Result = " << get << endl;
		if (get == result)
		{
			cout << "********************" << endl;
			cout << " Passed " << endl;
			cout << "********************" << endl;
		}
		else
		{
			cout << "********************" << endl;
			cout << " Failed " << endl;
			cout << "********************" << endl;
		}
		cout << endl;
		k++;
	}
}
