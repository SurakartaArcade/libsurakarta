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

#ifndef ENGINE_MOVEGEN_H_
#define ENGINE_MOVEGEN_H_

#include <position.h>

#include <vector>

namespace sk {

// Generates all possible moves (of the given type) and pushes them into a
// vector buffer.
template <MoveType>
std::vector<Move> &GenerateMoves(const Position &, std::vector<Move> *buffer);

}  // namespace sk

#endif /* ENGINE_MOVEGEN_H_ */