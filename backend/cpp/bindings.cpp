#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>

#include "sudoku.h"

namespace py = pybind11;

std::vector<std::int32_t> generate_random_board(int size,
                                                float percent_filled) {
  const int board_size = size * size;
  SudokuBoard board(board_size, board_size);
  return board.generateRandomBoard(percent_filled);
}

PYBIND11_MODULE(sudoku, m) {
  m.doc() = "pybind11 sudoku c++ accelerators";  // Optional module docstring
  m.def("generate_random_board", &generate_random_board,
        "Generates random sudoku board with size and percent of filled cells",
        py::arg("size"), py::arg("percent_filled"));
}