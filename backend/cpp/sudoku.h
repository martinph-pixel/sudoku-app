#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <random>
#include <vector>

class SudokuBoard {
 public:
  SudokuBoard() = delete;
  SudokuBoard(std::int32_t boxSz)
      : boxSz_(boxSz), dim_(boxSz * boxSz), board_(dim_ * dim_, 0) {};
  std::vector<std::int32_t> generateRandomBoard(float percentFilled);

  std::int32_t& at(std::int32_t row, std::int32_t col) {
    assert(row >= 0 && row < dim_);
    assert(col >= 0 && col < dim_);
    return board_[row * dim_ + col];
  }

  const std::int32_t& at(std::int32_t row, std::int32_t col) const {
    assert(row >= 0 && row < dim_);
    assert(col >= 0 && col < dim_);
    return board_[row * dim_ + col];
  }

  bool solve();

 private:
  std::vector<std::int32_t> getCandidates(std::int32_t row,
                                          std::int32_t col) const;
  void printBoard();
  std::int32_t randomInt(std::int32_t min, std::int32_t max);

  std::int32_t boxSz_;
  std::int32_t dim_;
  std::vector<std::int32_t> board_;
  std::mt19937 rng_{std::random_device{}()};
};