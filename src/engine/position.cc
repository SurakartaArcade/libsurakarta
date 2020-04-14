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

#include "position.h"

#include <bit>
#include <vector>

#include "bitboard.h"

namespace sk {

Position::Position(sk::Surakarta& model) : options_(model.options_) {
    player_bitboards_ = new sk::Bitboard[2];

    player_bitboards_[0] = sk::createPlayerBitboard(model, sk::RED);
    player_bitboards_[1] = sk::createPlayerBitboard(model, sk::BLACK);

    count_red_ = std::__popcount(this->player_bitboards_[0]);
    count_black_ = std::__popcount(this->player_bitboards_[1]);

    side_to_move_ = RED;
}

Position::Position(const Position& copy) : options_(copy.options_) {
    player_bitboards_ = new sk::Bitboard[2];

    player_bitboards_[0] = copy.player_bitboards_[0];
    player_bitboards_[1] = copy.player_bitboards_[1];

    count_red_ = copy.count_red_;
    count_black_ = copy.count_black_;

    side_to_move_ = copy.side_to_move_;
}

Value Position::evaluate() {
    // Each pebble has a value of 2, except those at corner (value = 1)
    return (count_red_ - count_black_) * 2                            //
           - (player_bitboards_[0] & 1) + (player_bitboards_[1] & 1)  //
           - ((player_bitboards_[0] >> 5) & 1) +
           ((player_bitboards_[1] >> 5) & 1)  //
           - ((player_bitboards_[0] >> 30) & 1) +
           ((player_bitboards_[1] >> 30) & 1)  //
           - ((player_bitboards_[0] >> 35) & 1) +
           ((player_bitboards_[1] >> 35) & 1);
}

void Position::copyFrom(Position& pos) {
    player_bitboards_[0] = pos.player_bitboards_[0];
    player_bitboards_[1] = pos.player_bitboards_[1];

    count_red_ = pos.count_red_;
    count_black_ = pos.count_black_;
}

void Position::move(Move move) {
    Square start_sq =
        CreateSquare(GetMoveStartRow(move), GetMoveStartColumn(move));
    Square final_sq =
        CreateSquare(GetMoveFinalRow(move), GetMoveFinalColumn(move));

    if (HasPlayer(GetRedPlayerBitboard(), start_sq)) {
        LiftPlayer(player_bitboards_[0], start_sq);
        PutPlayer(player_bitboards_[0], final_sq);

        if (HasPlayer(GetBlackPlayerBitboard(), final_sq)) {
            --count_black_;
            LiftPlayer(player_bitboards_[1], final_sq);
        }

        side_to_move_ = BLACK;
    } else if (HasPlayer(GetBlackPlayerBitboard(), final_sq)) {
        LiftPlayer(player_bitboards_[1], start_sq);
        PutPlayer(player_bitboards_[1], final_sq);

        if (HasPlayer(GetRedPlayerBitboard(), final_sq)) {
            --count_red_;
            LiftPlayer(player_bitboards_[0], start_sq);
        }

        side_to_move_ = RED;
    }
}

}  // namespace sk