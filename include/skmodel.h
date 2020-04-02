/**
 * skmodel.h
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

#ifndef INCLUDE_SKMODEL_H_
#define INCLUDE_SKMODEL_H_

#include <stdint.h>
#include "skattack.h"
#include "skmove.h"

namespace sk
{

enum Player : int
{
  NULL_PLAYER = 0,
  RED = 1,
  BLACK = 2
};

/**
 * Model class for holding a Surakarta game state. It can be used to supply a
 * position to the Surakarta engine.
 */
class Surakarta
{
public:
  Surakarta();
  Surakarta(Surakarta &);

  /**
   * @param mv
   * @return - whether the given move is legal in the current position
   */
  bool isLegal(Move mv);

  /**
   * @param start_row
   * @param start_column
   * @param final_row
   * @param final_column
   * @return - whether moving from (start_row, start_column) to (final_row, final_column) is
   *    a legal non-attack move.
   */
  bool isLegalStep(int start_row, int start_column, int final_row, int final_column);

  /**
   * Calculates whether the attack move is legal for the current position.
   * 
   * TRAP: If you have provided a "cut" square that does not lie on the attack path, then
   * that move is not legal. However, if the move is "legal without the cut", then this
   * method will still return true. To check if the attack is legal "with the cut", check
   * the equality the final row/column of the returned move with the cut row/column.
   * 
   * @param bid - initial bid of attack
   * @param start_row - starting square row
   * @param start_column - starting square column
   * @param [out] out - move holding all start/final squares.
   * @param cut_row - (optional) square's row to stop at before capturing
   * @param cut_column - (optional) square's column to stop after before capturing
   * @return - whether the move is legal
   */
  bool isLegalAttackBid(Bid bid, int start_row, int start_column, Move *out = 0, int cut_row = -1, int cut_column = -1);

  Surakarta nextMove(int start_row, int start_column,
                     int final_row, int final_column,
                     bool is_attack = false, int bid = NULL_BID);
  Surakarta nextMoveToken(Move);
  Surakarta nextMoveAttack(Bid, int start_row, int start_column, Move * = 0);

  Surakarta &clone();

  inline Player *editable()
  {
    return this->board;
  }

  inline Move getAttack(Bid bid, int start_row, int start_column)
  {
    Move mv = 0;
    this->isLegalAttackBid(bid, start_row, start_column, &mv);

    return mv;
  }

protected:
  Player *board;
  unsigned int move_count;

  inline bool isTurn(Player p)
  {
    return this->move_count % 2 == p;
  }

  inline Player getPlayer(int row, int column)
  {
    return this->board[row * 6 + column];
  }

  inline Player getTurnPlayer()
  {
    return (Player)((this->move_count % 2) + 1);
  }

  inline bool canMoveFrom(int start_row, int start_column)
  {
    return this->isTurn(this->board[start_row * 6 + start_column]);
  }
};

} // namespace sk

#endif /* INCLUDE_SKMODEL_H_ */