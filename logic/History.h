#pragma once

#include <vector>

#include "types.h"
#include "move.h"


class History 
{
public:

    // для тестов
    void set_history(const std::vector<MoveRec>& moves);

    MoveRec get_last_move() const;
private:
    std::vector<MoveRec> moves_;
};