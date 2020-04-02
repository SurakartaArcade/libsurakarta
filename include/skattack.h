/**
 * skattack.h
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

#include "skmove.h"

#ifndef INCLUDE_SKATTACK_H_
#define INCLUDE_SKATTACK_H_

namespace sk
{

/**
 * @param terminal_row
 * @param terminal_column
 * @return - the radius of the loop whose terminal is given
 */
inline int calculateLoopRadius(int terminal_row, int terminal_column)
{
  if (terminal_row == 0 || terminal_row == 5)
  {
    return terminal_row < 3 ? terminal_column : 5 - terminal_column;
  }
  else
  {
    return terminal_column < 3 ? terminal_row : 5 - terminal_row;
  }
}

/**
 * @param terminal_row
 * @param terminal_column
 * @returns - the bid of a piece that would loop through from the given terminal
 */
inline Bid calculateLoopBid(int terminal_row, int terminal_column)
{
  if (terminal_row == 0)
  {
    return NORTH;
  }
  else if (terminal_row == 5)
  {
    return SOUTH;
  }
  else if (terminal_column == 0)
  {
    return WEST;
  }
  else if (terminal_column == 5)
  {
    return EAST;
  }

  return NULL_BID;
}

/**
 * Calculates the ending square of a piece after looping from (in_row, in_column).
 * @param [in] in_row
 * @param [in] in_column
 * @param [out] out_row
 * @param [out] out_column
 * @param [out] out_bid - new bid after looping
 */
inline void calculateLoopTerminal(int in_row, int in_column, int &out_row, int &out_column, Bid &out_bid)
{
  Bid in_bid = calculateLoopBid(in_row, in_column);
  int loop_radius = calculateLoopRadius(in_row, in_column);

  switch (in_bid)
  {
  case NORTH:
    out_row = loop_radius;
    out_column = in_column < 3 ? 0 : 5;
    out_bid = in_column < 3 ? EAST : WEST;
    return;
  case WEST:
    out_row = in_row < 3 ? 0 : 5;
    out_column = loop_radius;
    out_bid = in_row < 3 ? SOUTH : NORTH;
    return;
  case SOUTH:
    out_row = 5 - loop_radius;
    out_column = in_column < 3 ? 0 : 5;
    out_bid = in_column < 3 ? EAST : WEST;
    return;
  case EAST:
    out_row = in_row < 3 ? 0 : 5;
    out_column = 5 - loop_radius;
    out_bid = in_row < 3 ? SOUTH : NORTH;
    return;
  default:
    return;
  }
}

/**
 * Calculates the next square for a piece in an attack move. It can be used to
 * explicitly animate an attack.
 * @param [in] in_row
 * @param [in] in_column
 * @param [in] in_bid
 * @param [out] out_row
 * @param [out] out_column
 * @param [out] out_bid
 * @param [out] is_loop
 */
inline void calculateAttackPath(int in_row, int in_column, Bid in_bid,
                                int &out_row, int &out_column, Bid &out_bid,
                                bool &is_loop)
{
  out_bid = in_bid; // if no looping occurs
  is_loop = false;

  switch (in_bid)
  {
  case NORTH:
    if (in_row - 1 > 0)
    {
      out_row = in_row - 1;
      out_column = in_column;
      return;
    }
    break;
  case WEST:
    if (in_column - 1 > 0)
    {
      out_row = in_row;
      out_column = in_column - 1;
      return;
    }
    break;
  case SOUTH:
    if (in_row + 1 < 5)
    {
      out_row = in_row + 1;
      out_column = in_column;
      return;
    }
    break;
  case EAST:
    if (in_column + 1 < 6)
    {
      out_row = in_row;
      out_column = in_column + 1;
      return;
    }
  default:
    break;
  }

  // Must loop here!
  calculateLoopTerminal(in_row, in_column, out_row, out_column, out_bid);
  is_loop = true;
}

} // namespace sk

#endif /* INCLUDE_SKATTACK_H_ */