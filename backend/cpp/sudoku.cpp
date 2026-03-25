#include "sudoku.h"

#include <iostream>

std::vector<std::int32_t> SudokuBoard::generateRandomBoard(
    float percentFilled) {
  at(randomInt(0, dim_ - 1), randomInt(0, dim_ - 1)) = randomInt(1, dim_);
  solve();
  return board_;
}

std::vector<std::int32_t> SudokuBoard::getCandidates(std::int32_t row,
                                                     std::int32_t col) const {
  assert(row >= 0 && row < dim_);
  assert(col >= 0 && col < dim_);

  if (at(row, col) != 0) {
    return {};
  }

  // I know this could add weird but makes most sense here
  std::vector<bool> seen(dim_ + 1, false);
  for (auto i = 0; i < dim_; i++) {
    seen[at(i, col)] = true;
    seen[at(row, i)] = true;

    const std::int32_t boxRow = (row / boxSz_) * boxSz_ + i / boxSz_;
    const std::int32_t boxCol = (col / boxSz_) * boxSz_ + i % boxSz_;
    seen[at(boxRow, boxCol)] = true;
  }

  std::vector<std::int32_t> result;
  for (auto i = 1; i <= dim_; i++) {
    if (!seen[i]) {
      result.push_back(i);
    }
  }
  return result;
}

bool SudokuBoard::solve() {
  std::int32_t bestBetRow = -1;
  std::int32_t bestBetCol = -1;
  std::vector<std::int32_t> bestBetCandidates;
  for (auto flatIdx = 0; flatIdx < dim_ * dim_; ++flatIdx) {
    const std::int32_t row = flatIdx / dim_;
    const std::int32_t col = flatIdx % dim_;

    if (at(row, col) != 0) {
      continue;
    }

    auto candidates = getCandidates(row, col);
    if (candidates.empty()) {
      return false;  // dead end
    }

    if (bestBetCandidates.empty() ||
        candidates.size() < bestBetCandidates.size()) {
      bestBetRow = row;
      bestBetCol = col;
      bestBetCandidates = std::move(candidates);
      if (bestBetCandidates.size() == 1) {
        break;
      }
    }
  }

  if (bestBetCandidates.empty()) {
    // means the board is solved because we iterated the whole map and couldn't
    // find candidates but it was not a dead end
    return true;
  }

  for (const auto candidate : bestBetCandidates) {
    at(bestBetRow, bestBetCol) = candidate;
    if (solve()) {
      return true;
    }
    at(bestBetRow, bestBetCol) = 0;  // backtrack with the next candidate
  }

  return false;
}

void SudokuBoard::printBoard() {
  for (auto row = 0; row < dim_; ++row) {
    for (auto col = 0; col < dim_; ++col) {
      auto val = at(row, col);
      if (val == 0) {
        std::cout << ". ";
        continue;
      }
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

std::int32_t SudokuBoard::randomInt(std::int32_t min, std::int32_t max) {
  return std::uniform_int_distribution<std::int32_t>(min, max)(rng_);
}