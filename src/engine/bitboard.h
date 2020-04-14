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

// This file defines bitboard helper methods.

#include <skmodel.h>

#ifndef INCLUDE_BITBOARD_H_
#define INCLUDE_BITBOARD_H_

#include "enginetypes.h"

namespace sk {

// Filled rows
constexpr Bitboard BB_ROW_1 = (1 << 7) - 1;
constexpr Bitboard BB_ROW_2 = BB_ROW_1 << (6 * 1);
constexpr Bitboard BB_ROW_3 = BB_ROW_1 << (6 * 2);
constexpr Bitboard BB_ROW_4 = BB_ROW_1 << (6 * 3);
constexpr Bitboard BB_ROW_5 = BB_ROW_1 << (6 * 4);
constexpr Bitboard BB_ROW_6 = BB_ROW_1 << (6 * 5);

// Filled columns
constexpr Bitboard BB_COL_1 =
    1 | (1 << 6) | (1 << 12) | (1 << 18) | (1 << 24) | (1 << 30) | (1l << 36);
constexpr Bitboard BB_COL_2 = BB_COL_1 << 1;
constexpr Bitboard BB_COL_3 = BB_COL_1 << 2;
constexpr Bitboard BB_COL_4 = BB_COL_1 << 3;
constexpr Bitboard BB_COL_5 = BB_COL_1 << 4;
constexpr Bitboard BB_COL_6 = BB_COL_1 << 5;

inline Bitboard createPlayerBitboard(Surakarta &model,
                                     Player player = NULL_PLAYER) {
    Bitboard board = 0;

    for (int i = 0; i < 36; i++) {
        if (model.editable()[i] == player) {
            board |= (1l << i);
        }
    }

    return board;
}

inline bool IsPlayerAt(const Bitboard &bitboard, int i) {
    return (bitboard >> i) & 1;
}

// Returns whether the i-th bit in the bitboard in set.
inline bool HasPlayer(const Bitboard &bitboard, int i) {
    return (bitboard >> i) & 1;
}

// Returns whether the bit corresponding to (row, column) is set in the
// bitboard.
inline bool HasPlayer(const Bitboard &bitboard, int row, int column) {
    return (bitboard >> (row * 6 + column)) & 1;
}

inline void LiftPlayer(Bitboard &bitboard, int i) { bitboard &= ~(1 << i); }
inline void PutPlayer(Bitboard &bitboard, int i) { bitboard |= (1 << i); }

}  // namespace sk

#endif /* INCLUDE_BITBOARD_H_ */
