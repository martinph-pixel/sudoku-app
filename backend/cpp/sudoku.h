#pragma once

#include <cstdint>
#include <vector>

class SudokuBoard {
 public:
  SudokuBoard() = delete;
  SudokuBoard(std::int32_t rows, std::int32_t cols)
      : rows_(rows), cols_(cols), board_(rows * cols, 0) {};
  std::vector<std::int32_t> generateRandomBoard(float percentFilled);

  std::int32_t& at(std::int32_t row, std::int32_t col) {
    return board_[row * cols_ + col];
  }

 private:
  std::int32_t rows_;
  std::int32_t cols_;
  std::vector<std::int32_t> board_;
};