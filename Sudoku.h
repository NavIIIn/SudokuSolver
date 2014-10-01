//Joseph Navin

#include <string>

class Sudoku
{
private: 
	int grid[9][9];
	//helper for print
	void print_row(int row) const;
	bool is_solved();
	bool is_valid_move(int row, int column);
	bool is_valid();
public:
	Sudoku();
	void loadFromFile(std::string filename);
	void print() const;
	bool equals(const Sudoku &other) const;
	bool solve();
};