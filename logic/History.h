#pragma once

#include <vector>

#include "types.h"
#include "move.h"


class History 
{
public:

    // для тестов
    void set_history(const std::vector<Move>& moves);

    Move get_last_move() const;
private:
    std::vector<Move> moves_;
};