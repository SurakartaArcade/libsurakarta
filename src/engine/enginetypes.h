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

// This file defines all the simple types used in the libsurakarta engine.

#ifndef INCLUDE_SKTYPES_H_
#define INCLUDE_SKTYPES_H_

#include <stdint.h>

namespace sk {

// Bitboard representation of a Surakarta position. The "on" bits indicate
// whether a given type of piece is placed on the corresponding squares.
typedef uint64_t Bitboard;

typedef uint32_t Square;

// Evaluation of a given position - +ve values indicate RED has the advantage,
// while -ve values indicate BLACK has the advantage.
typedef int Value;

}  // namespace sk

#endif /* INCLUDE_SKTYPES_H_ */