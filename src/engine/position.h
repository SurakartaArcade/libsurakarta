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

// This file defines a bitboard-based modelling class. This is a "lighter
// version" of Surakarta, and is used by the engine internally.

#ifndef INCLUDE_SKPOSITION_H_
#define INCLUDE_SKPOSITION_H_

#include "../../include/skmodel.h"
#include "bitboard.h"
#include "enginetypes.h"

namespace sk {

// Position models a Surakarta position using one bitboard for each player.
class Position {
   public:
    Position(Surakarta &surakarta);
    Position(Position &clone);

    // Heuristic to evaluate this position
    Value evaluate();

    Bitboard getBitboard(Player player) {
        return player_bitboards_[player - 1];
    }

    ModelOptions &options_;

   protected:
    Bitboard *player_bitboards_;
    int count_red_;
    int count_black_;

   public:
    Player side_to_move_;

    // Player who will move in the current turn.
    inline Player GetSideToMovePlayer() const { return side_to_move_; }

    // White player's bitboard.
    inline Bitboard GetRedPlayerBitboard() const {
        return this->player_bitboards_[0];
    }

    // Black player's bitboard.
    inline Bitboard GetBlackPlayerBitboard() const {
        return this->player_bitboards_[1];
    }

    // Bitboard for the side-to-move player
    inline Bitboard GetSideToMoveBitboard() const {
        return this->player_bitboards_[this->side_to_move_ - 1];
    }

    // Combined red & black bitboard. It can used to check if any player is at a
    // given square.
    inline Bitboard GetNonNullBitboard() const {
        return this->player_bitboards_[0] | this->player_bitboards_[1];
    }

    // Returns the player at the given square.
    inline Player GetPlayer(int i) const {
        if (HasPlayer(GetRedPlayerBitboard(), i)) {
            return RED;
        }
        if (HasPlayer(GetBlackPlayerBitboard(), i)) {
            return BLACK;
        }

        return NULL_PLAYER;
    }

    // Returns the player at (row, column).
    inline Player GetPlayer(int row, int column) const {
        return GetPlayer(row * 6 + column);
    }

};  // namespace sk

inline bool IsPlayerAt(Bitboard bitboard, Square square) {
    return (bitboard >> square) & 1;
}

}  // namespace sk

#endif /* INCLUDE_SKPOSITION_H_ */