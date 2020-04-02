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

#ifndef INCLUDE_SKPOSITION_H_
#define INCLUDE_SKPOSITION_H_

#include "enginetypes.h"
#include "../../include/skmodel.h"

namespace sk
{

class Position
{
public:
  Position();
  Position(Position &clone);

  sk::Move *movesFrom(sk::Square);
  sk::Move *movesTo(sk::Square);

protected:
  sk::Bitboard player_bitboards_;
  int count_red_;
  int count_black_;
}; // namespace sk

} // namespace sk

#endif /* INCLUDE_SKPOSITION_H_ */