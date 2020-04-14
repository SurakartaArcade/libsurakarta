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

#include <stdint.h>

#ifndef INCLUDE_SKMOVE_H_
#define INCLUDE_SKMOVE_H_

namespace sk {

/**
 * Enumeration of possible directions an attack can go in.
 */
enum Bid : int { WEST = 0, NORTH = 1, EAST = 2, SOUTH = 3, NULL_BID = 7 };

/**
 * Types of moves
 */
enum MoveType : int { LEGAL = 0, STEP = 1, CAPTURE = 2, ATTACK = 3 };

/**
 * Encodes the start and final square of a move along with attack information.
 *
 * Bits:
 * 0-6:    Final row
 * 7-12:   Final column
 * 13-18:  Start row
 * 19-24:  Start column
 * 20:     Whether it is an attack
 * 21-23:  Initial direction of attack
 *
 * @see sk::createMove
 */
typedef uint64_t Move;

/**
 * Encodes a move.
 *
 * @param start_row
 * @param start_column
 * @param final_row
 * @param final_column
 * @param is_attack
 * @param bid - initial direction of attack
 */
inline Move CreateMove(int start_row, int start_column, int final_row,
                       int final_column, bool is_attack = false,
                       sk::Bid bid = NULL_BID) {
    return (final_row) | (final_column << 6) | (start_row << 12) |
           (start_column << 18) | (is_attack << 19) | (bid << 20);
}

inline int GetMoveStartRow(Move mv) { return mv & ((1 << 6) - 1); }

inline int GetMoveStartColumn(Move mv) { return (mv >> 6) & ((1 << 6) - 1); }

inline int GetMoveFinalRow(Move mv) { return (mv >> 12) & ((1 << 6) - 1); }

inline int GetMoveFinalColumn(Move mv) { return (mv >> 18) & ((1 << 6) - 1); }

inline bool IsMoveAttack(Move mv) { return (mv >> 19) & 1; }

inline Bid GetMoveBid(Move mv) { return (Bid)((mv >> 20) & ((1 << 3) - 1)); }

}  // namespace sk

#endif /* INCLUDE_SK_MOVE_H_ */