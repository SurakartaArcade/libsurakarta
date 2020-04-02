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

#ifndef INCLUDE_SKTYPES_H_
#define INCLUDE_SKTYPES_H_

#include <stdint.h>
namespace sk
{
/**
 * For each type of piece, the first 36 bits of a bitboard define whether that
 * type of piece is present on a square represented by those bits.
 */
typedef uint64_t Bitboard;

typedef uint64_t Move;

typedef unsigned int Square;

} // namespace sk

#endif /* INCLUDE_SKTYPES_H_ */