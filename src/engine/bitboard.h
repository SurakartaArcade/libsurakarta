/**
 * Surakarta.hpp
 *
 * Copyright (C) 2020 Shukant Pal <shukantpal@outlook.com>
 *
 * This file is part of libsurakarta.
 *
 * libsurakarta is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libsurakarta is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsurakarta.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * @author Shukant Pal <shukantpal@outlook.com>
 */

#ifndef INCLUDE_SURAKARTA_H_
#define INCLUDE_SURAKARTA_H_

#include "enginetypes.h"

// Filled rows
constexpr sk::Bitboard BB_ROW_1 = (1 << 7) - 1;
constexpr sk ::Bitboard BB_ROW_2 = BB_ROW_1 << (6 * 1);
constexpr sk ::Bitboard BB_ROW_3 = BB_ROW_1 << (6 * 2);
constexpr sk ::Bitboard BB_ROW_4 = BB_ROW_1 << (6 * 3);
constexpr sk ::Bitboard BB_ROW_5 = BB_ROW_1 << (6 * 4);
constexpr sk ::Bitboard BB_ROW_6 = BB_ROW_1 << (6 * 5);

// Filled columns
constexpr sk ::Bitboard BB_COL_1 = 1 | (1 << 6) | (1 << 12) | (1 << 18) | (1 << 24) | (1 << 30) | (1 << 36);
constexpr sk ::Bitboard BB_COL_2 = BB_COL_1 << 1;
constexpr sk ::Bitboard BB_COL_3 = BB_COL_1 << 2;
constexpr sk ::Bitboard BB_COL_4 = BB_COL_1 << 3;
constexpr sk ::Bitboard BB_COL_5 = BB_COL_1 << 4;
constexpr sk ::Bitboard BB_COL_6 = BB_COL_1 << 5;

#endif /* INCLUDE_SURAKARTA_H_ */
