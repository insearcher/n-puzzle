#include "Move.hpp"

Move::Move(int dx, int dy)
        : dx(dx),
          dy(dy) {}

Puzzle Move::Execute(const Puzzle &puzzle) const {
    std::vector<int> cells = puzzle.GetCells();
    const auto[row, column] = puzzle.GetPosition(0);

    std::swap(cells[row * puzzle.GetSize() + column], cells[(row + dy) * puzzle.GetSize() + column + dx]);
    return Puzzle(puzzle.GetSize(), cells);
}

bool Move::IsMovable(const Puzzle &puzzle) const {
    const auto[row, column] = puzzle.GetPosition(0);

    if (column + dx < 0 || column + dx >= puzzle.GetSize()
        || row + dy < 0 || row + dy >= puzzle.GetSize()) {
        return false;
    }
    return true;
}
