#include <iostream>
#include <array>

using namespace std;

std::array<std::array<int, 9>, 9>& createField()
{
	std::array<std::array<int, 9>, 9>* field =
	new std::array<std::array<int, 9>, 9>
	{{
		{0,0,0, 0,0,1, 2,8,6},
		{0,5,9, 0,0,8, 0,4,0},
		{0,8,2, 0,0,0, 5,0,0},

		{0,4,0, 5,0,3, 0,2,7},
		{5,2,0, 0,0,0, 0,0,0},
		{3,0,0, 0,0,7, 0,0,1},

		{0,0,0, 1,8,0, 4,7,0},
		{0,0,5, 0,3,0, 0,0,8},
		{4,0,8, 0,0,0, 9,0,5}
	}};
	return *field;
}

void printField(const std::array<std::array<int, 9>, 9>& field)
{
	cout << "-------------" << endl;
	for (int i = 0; i < field.size(); ++i)
	{
		cout << "|" ;
		for (int j = 0; j < field[i].size(); ++j)
		{
			if (field[i][j] != 0)
				cout << field[i][j];
			else
				cout << " ";
			//cout << " ";
			if ((j+1)%3 == 0)
				cout << "|";
			
		}
		cout << endl;
		if ((i+1)%3 == 0)
			cout << "-------------" << endl;
	}
}

bool check(const std::array<std::array<int, 9>, 9>& field, const int i, const int j, const int val)
{
	// row test
	for (int c = 0; c <= 9; ++c)
		if (field[i][c] == val)
			return false;

	// column test
	for (int r = 0; r <= 9; ++r)
		if (field[col][r] == val)
			return false;

	// square test
	int iStart;
	int jStart;

	if (i < 3)
		iStart = 0;
	else if (i < 6)
		iStart = 3;
	else
		iStart = 6;

	
	if (j < 3)
		jStart = 0;
	else if (j < 6)
		jStart = 3;
	else 
		jStart = 6;

	for (int r = iStart; r < iStart + 3; ++r)
		for (int c = jStart; c < jStart + 3; ++c)
			if (field[r][c] == val)
				return false;

	// passes all three
	return true;
}


bool solve(std::array<std::array<int, 9>, 9>& field, int i, int j)
{

	//printField(field);
	if (i == 9)
	{
		return true;
	}

	if (field[i][j] != 0)
	{
		if (j == 8)
			return solve(field,i+1, 0);
		return solve(field, i, j+1);
	}

	for (int val = 1; val <= 9; ++val)
	{
		if (check(field, i, j, val))
		{
			cout << "enter " << i << " in " << j << " -> " << val << endl;
			field[i][j] = val;
			bool result;
			if ( j == 8)
				result = solve(field, i+1, 0);
			else
				result = solve(field, i, j+1);
			
			if (result)
				return true;
				field[i][j] = 0;
		}
	}
	
	cout << "false " << i << " in " << j << endl;
	return false;
}


int main()
{
	std::array<std::array<int, 9>, 9> field = createField();
	printField(field);
	cout << check(field, 4,2,3) << endl;
	cout << solve(field, 0,0) << endl;
	printField(field);


}
