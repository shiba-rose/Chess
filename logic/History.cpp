#include <vector>
#include <cassert>

#include "types.h"
#include "History.h"
#include "move.h"

MoveRec History::get_last_move() const
{
    assert(moves_.size() != 0);
    return moves_[moves_.size()-1];
}

void History::set_history(const std::vector<MoveRec>& moves)
{
    moves_ = moves;
}