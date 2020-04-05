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

// Author: Shukant Pal <shukantpal@outlook.com>

// This file defines the game-modelling class Surakarta.

#ifndef INCLUDE_SKMODEL_H_
#define INCLUDE_SKMODEL_H_

#include <stdint.h>

#include "skattack.h"
#include "skmodeloptions.h"
#include "skmove.h"

namespace sk {

enum Player : int {
    /// Alias for unknown player
    NULL_PLAYER = 0,

    /// Player that "generally" will move first. <code>Surakarta</code>'s first
    /// side-to-move is <code>RED</code> by default.
    RED = 1,

    /// Player that is "generally" the second to move.
    BLACK = 2
};

class Position;

/// Model class for holding a Surakarta game state. It can be used to supply a
/// position to the Surakarta engine.
class Surakarta {
   public:
    /// \param no_init - if true, then the board would not have the initial
    ///  layout of Surakarta (it would be blank).
    Surakarta(bool no_init = false);

    /// This is the recommended constructor for initializing an application's
    /// game-modelling object.
    ///
    /// \param options - configuration of the game rules
    Surakarta(ModelOptions &options);

    /**
     * Copies the given position.
     *
     * @param surakarta
     */
    Surakarta(Surakarta &surakarta);

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
     * @return - whether moving from (start_row, start_column) to (final_row,
     * final_column) is a legal non-attack move.
     */
    bool isLegalStep(int start_row, int start_column, int final_row,
                     int final_column);

    /**
     * Calculates whether the attack move is legal for the current position.
     *
     * Hint: If you have provided a "cut" square that does not lie on the attack
     * path, then that move is not legal. However, if the move is "legal without
     * the cut", then this method will still return true. To check if the attack
     * is legal "with the cut", check the equality the final row/column of the
     * returned move with the cut row/column.
     *
     * @param bid - initial bid of attack
     * @param start_row - starting square row
     * @param start_column - starting square column
     * @param [out] out - move holding all start/final squares.
     * @param cut_row - (optional) square's row to stop at before capturing
     * @param cut_column - (optional) square's column to stop after before
     * capturing
     * @return - whether the move is legal
     */
    bool isLegalAttack(Bid bid, int start_row, int start_column, Move *out = 0,
                       int cut_row = -1, int cut_column = -1);

    /**
     * Moves the piece at (start_row, start_column) to (final_row, final_column)
     * without checking whether it is valid.
     *
     * @param start_row
     * @param start_column
     * @param final_row
     * @param final_column
     */
    Surakarta *move(int start_row, int start_column, int final_row,
                    int final_column);

    /**
     * Expands and applies the given move without checking legality.
     *
     * @param move
     */
    Surakarta *move(Move mv);

    /**
     * Checks the legality of the attack bid and applies the move. If the cut
     * square is not on the attack path, the move will still proceed to capture.
     *
     * @param bid
     * @param start_row
     * @param start_column
     * @param [out] move - actual move that was executed
     * @param cut_row
     * @param cut_column
     */
    Surakarta *attack(Bid bid, int start_row, int start_column, Move * = 0,
                      int cut_row = -1, int cut_column = -1);

    /**
     * @returns - a clone of this position
     */
    Surakarta &clone();

    /**
     * @returns - an array of 36 "players" that can be used to directly edit
     *    the position.
     */
    inline Player *editable() { return this->board_; }

    /**
     * @param bid
     * @param start_row
     * @param start_column
     * @returns - the attacking move from the start square. 0 if it is illegal.
     */
    inline Move getAttack(Bid bid, int start_row, int start_column) {
        Move mv = 0;
        this->isLegalAttack(bid, start_row, start_column, &mv);

        return mv;
    }

   protected:
    Player *board_;
    unsigned int move_count_;
    ModelOptions &options_;

    inline bool isTurn(Player p) { return this->move_count_ % 2 == p; }

    inline Player getPlayer(int row, int column) {
        return this->board_[row * 6 + column];
    }

    inline Player getTurnPlayer() {
        return (Player)((this->move_count_ % 2) + 1);
    }

    inline bool canMoveFrom(int start_row, int start_column) {
        return this->isTurn(this->board_[start_row * 6 + start_column]);
    }

    friend class Position;
};

}  // namespace sk

#endif /* INCLUDE_SKMODEL_H_ */