#include "Sudoku.h"
#include <fstream>
#include <iostream>

Sudoku::Sudoku()
  : grid()
{ }

void Sudoku::loadFromFile(std::string filename)
{
	std::ifstream file_in(filename.c_str());
	if(!file_in.is_open())
		std::cout << "File not found" << std::endl;
  
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			file_in >> grid[i][j];
		}
	}
}

void Sudoku::print_row(int row) const
{
	for(int i = 0; i < 9; ++i){
		if(i == 3 || i == 6)
			std::cout << "| ";
		std::cout << grid[row][i] << " ";
	}
	std::cout << std::endl;
}

void Sudoku::print() const
{
	for(int i = 0; i < 9; ++i){
		if(i == 3 || i == 6)
			std::cout << "------+-------+------" << std::endl;
		print_row(i);
	}
	std::cout << std::endl;
}

bool Sudoku::equals(const Sudoku &other) const
{
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(grid[i][j] != other.grid[i][j])
				return false;
		}
	}
	return true;
}

bool Sudoku::is_valid_move(int row, int column)
{
	if(grid[row][column] == 0)
		return true;

	for(int i = 0; i < 9; ++i){
		if(i != column && grid[row][i] == grid[row][column])
			return false;
	}

	for(int i = 0; i < 9; ++i){
		if(i != row && grid[i][column] == grid[row][column])
			return false;
	}

	for(int i = 3*(row/3); i < 3*(row/3)+3; ++i){
		for(int j = 3*(column/3); j < 3*(column/3)+3; ++j){
			if((i != row && j != column)
				&& grid[i][j] == grid[row][column])
				return false;
		}

	}
	return true;
}


//Helper for solved
bool Sudoku::is_solved()
{
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(!is_valid_move(i, j) || grid[i][j] == 0)
				return false;
		}

	}
	return true;
}

bool Sudoku::is_valid()
{
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(grid[i][j] != 0 && !is_valid_move(i, j))
				return false;
		}
	}
	return true;
}


bool Sudoku::solve()
{
	if(is_solved())
		return true;
	if(!is_valid())
		return false;

	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(grid[i][j] == 0){
				for(int k = 0; k < 9; ++k){	
					grid[i][j] = k + 1;
					if(!solve())
						grid[i][j] = 0;
					else return true;
				}
				return false;
			}
		}
	}
	return true;
}
