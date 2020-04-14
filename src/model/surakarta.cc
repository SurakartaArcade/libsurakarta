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
//

// Author: Shukant Pal <shukantpal@outlook.com>

#include <skmodel.h>

#include <cstdlib>
#include <iostream>

namespace sk {

// Used as a placeholder when ModelOptions is not provided.
ModelOptions kNullOptions;

void WriteInitialLayout(Player *board) {
    for (int i = 0; i < 12; i++) {
        board[i] = RED;
    }

    for (int i = 12; i < 24; i++) {
        board[i] = NULL_PLAYER;
    }

    for (int i = 36 - 12; i < 36; i++) {
        board[i] = BLACK;
    }
}

Surakarta::Surakarta(bool no_init)
    : options_(no_init ? kNullOptions : *new ModelOptions()) {
    board_ = new Player[36];
    move_count_ = 0;

    if (!no_init) {
        WriteInitialLayout(board_);
    }
}

Surakarta::Surakarta(ModelOptions &options) : options_(options) {
    board_ = new Player[36];
    move_count_ = 0;

    WriteInitialLayout(board_);
}

Surakarta::Surakarta(Surakarta &copy) : options_(copy.options_) {
    board_ = new Player[36];
    move_count_ = copy.move_count_;

    for (int i = 0; i < 36; i++) {
        board_[i] = copy.board_[i];
    }
}

bool Surakarta::isLegal(Move mv) {
    if (IsMoveAttack(mv)) {
        Move actual;

        isLegalAttack(GetMoveBid(mv), GetMoveStartRow(mv),
                      GetMoveStartColumn(mv), &actual, GetMoveFinalRow(mv),
                      GetMoveFinalColumn(mv));

        return (mv & ((1 << 24) - 1)) ==
               actual;  // move encoding bits are equal
    }

    return isLegalStep(GetMoveStartRow(mv), GetMoveStartColumn(mv),
                       GetMoveFinalRow(mv), GetMoveFinalColumn(mv));
}

bool Surakarta::isLegalStep(int start_row, int start_column, int final_row,
                            int final_column) {
    return canMoveFrom(start_row, start_column) &&
           getPlayer(final_row, final_column) &&
           std::abs(start_row - final_row) <= 1 &&
           std::abs(final_row - final_column) <= 1;
}

bool Surakarta::isLegalAttack(Bid start_bid, int start_row, int start_column,
                              Move *out, int cut_row, int cut_column) {
    if (getPlayer(start_row, start_column) != getTurnPlayer()) {
        return false;  // not player's turn
    }

    int row = start_row;
    int column = start_column;
    Bid bid = start_bid;
    bool was_loop_step = false;

    int self_cross_count =
        0;  // no. of times we have passed through our initial square
    int loop_count = 0;      // no. of times we have looped
    bool cut_found = false;  // whether we passed over cut square
    Player turn_player = getTurnPlayer();

    while (true) {
        calculateAttackPath(row, column, bid, row, column, bid, was_loop_step);

        bool is_self_cross = false;

        if (row == start_row && column == start_column) {
            self_cross_count++;
            is_self_cross = true;

            if (self_cross_count > 1) {
                return false;  // indicates infinite loop
            }
        }

        Player occupant = getPlayer(row, column);

        if (!is_self_cross && occupant == turn_player) {
            return false;  // can't land on our own piece
        }

        if (was_loop_step) {
            ++loop_count;
        }
        if (cut_row == row && cut_column == column) {
            cut_found = true;
        }
        if (occupant && occupant != turn_player) {
            if (loop_count == 0) {
                return false;  // must loop once to capture
            }

            break;
        }
    }

    if (out) {
        *out = CreateMove(start_row, start_column, cut_found ? cut_row : row,
                          cut_found ? cut_column : column, true, start_bid);
    }

    return true;
}

Surakarta *Surakarta::move(int start_row, int start_column, int final_row,
                           int final_column) {
    int start_square = start_row * 6 + start_column;
    int final_square = final_row * 6 + final_column;

    board_[final_square] = board_[start_square];
    board_[start_square] = NULL_PLAYER;

    return this;
}

Surakarta *Surakarta::move(Move move) {
    this->move(GetMoveStartRow(move), GetMoveStartColumn(move),
               GetMoveFinalRow(move), GetMoveFinalColumn(move));

    return this;
}

Surakarta *Surakarta::attack(Bid bid, int start_row, int start_column,
                             Move *result, int cut_row, int cut_column) {
    Move lresult;

    if (!result) {
        result = &lresult;
    }

    bool isLegal = isLegalAttack(bid, start_row, start_column, result, cut_row,
                                 cut_column);

    if (isLegal) {
        move(*result);
    } else {
        *result = 0;
    }

    return this;
}

Surakarta &Surakarta::clone() { return *new Surakarta(*this); }

}  // namespace sk