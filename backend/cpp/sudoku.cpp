#include "sudoku.h"

std::vector<std::int32_t> SudokuBoard::generateRandomBoard(float percentFilled) {
    at(0, 0) = 1; // Example of filling one cell for testing
    return board_;
}
