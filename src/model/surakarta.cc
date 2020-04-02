/**
 * surakarta.cc
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

#include <skmodel.h>
#include <cstdlib>

sk::Surakarta::Surakarta()
{
  this->board = new Player[36];
  this->move_count = 0;

  // Setup initial board layout
  for (int i = 0; i < 12; i++)
  {
    this->board[i] = RED;
  }

  for (int i = 36 - 12; i < 36; i++)
  {
    this->board[i] = BLACK;
  }
}

bool sk::Surakarta::isLegal(Move mv)
{
  if (isMoveAttack(mv))
  {
    Move actual;

    this->isLegalAttackBid(getMoveBid(mv),
                           getMoveStartRow(mv),
                           getMoveStartColumn(mv),
                           &actual,
                           getMoveFinalRow(mv),
                           getMoveFinalColumn(mv));

    return (mv & ((1 << 24) - 1)) == actual; // move encoding bits are equal
  }

  return this->isLegalStep(getMoveStartRow(mv),
                           getMoveStartColumn(mv),
                           getMoveFinalRow(mv),
                           getMoveFinalColumn(mv));
}

bool sk::Surakarta::isLegalStep(int start_row, int start_column, int final_row, int final_column)
{
  return this->canMoveFrom(start_row, start_column) &&
         this->getPlayer(final_row, final_column) &&
         std::abs(start_row - final_row) <= 1 &&
         std::abs(final_row - final_column) <= 1;
}

bool sk::Surakarta::isLegalAttackBid(Bid start_bid, int start_row, int start_column, Move *out, int cut_row, int cut_column)
{
  int row = start_row;
  int column = start_column;
  Bid bid = start_bid;
  bool was_loop_step = false;

  int self_cross_count = 0; // no. of times we have passed through our initial square
  int loop_count = 0;       // no. of times we have looped
  bool cut_found = false;   // whether we passed over cut square
  Player turn_player = this->getTurnPlayer();

  while (true)
  {
    sk::calculateAttackPath(row, column, bid, row, column, bid, was_loop_step);

    bool is_self_cross = false;

    if (row == start_row && column == start_column)
    {
      self_cross_count++;
      is_self_cross = true;

      if (self_cross_count > 1)
      {
        return false; // indicates infinite loop
      }
    }

    Player occupant = this->getPlayer(row, column);

    if (!is_self_cross && occupant == turn_player)
    {
      return false; // can't land on our own piece
    }

    if (was_loop_step)
    {
      ++loop_count;
    }
    if (cut_row == row && cut_column == column)
    {
      cut_found = true;
    }
    if (occupant && occupant != turn_player)
    {
      break;
    }
  }

  if (out)
  {
    *out = createMove(start_row, start_column,
                      cut_found ? cut_row : row,
                      cut_found ? cut_column : column,
                      true,
                      start_bid);
  }

  return true;
}