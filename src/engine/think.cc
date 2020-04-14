// Copyright (C) 2020 Shukant Pal <shukantpal@outlook.com>
//
// This file is part of libsurakarta.
//
// libsurakarta is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libsurakarta is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libsurakarta.  If not, see <https://www.gnu.org/licenses/>.

// Author: Shukant Pal <shukantpal@outlook.com>

#include <skengine.h>

#include <thread>

#include "context.h"
#include "movegen.h"
#include "position.h"

namespace sk {

// simple negamax
int DeepEvaluate(Context& context) {
    if (context.depth == kMaxDepth) {
        return context.position.evaluate();
    }

    Position& pos = context.position;
    std::vector<Move> move_list = GenerateMoves(pos);

    Move best_move = 0;
    int best_eval = -1000000;

    Context child_cxt;
    child_cxt.depth = context.depth + 1;
    child_cxt.position.copyFrom(pos);

    for (std::vector<Move>::iterator mitr = move_list.begin();
         mitr != move_list.end(); mitr++) {
        Move move = *mitr;

        child_cxt.position.move(move);
        int eval = -DeepEvaluate(child_cxt);
        child_cxt.position.copyFrom(pos);

        if (eval > best_eval) {
            best_eval = eval;
            best_move = move;
        }
    }

    return best_eval;
}

Move Think(Surakarta& rootModel, EngineOptions& eg_options) {
    Context root_context;
    Position rootPos(rootModel);

    root_context.position.copyFrom(rootPos);
    root_context.depth = 0;

    int best_move = 0;
    int best_eval = -10000;

    std::vector<Move> move_list = GenerateMoves(rootPos);

    for (std::vector<Move>::iterator mitr = move_list.begin();
         mitr != move_list.end(); mitr++) {
        Move move = *mitr;
        int value = DeepEvaluate(root_context);

        if (value > best_eval) {
            best_move = move;
            best_eval = value;
        }
    }

    return best_move;
}

}  // namespace sk