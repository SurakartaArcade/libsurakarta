/**
 * movegen.cc
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

#include "movegen.h"

#include "bitboard.h"

namespace sk {

// Generates a method that will add a Move into a vector if the final
// square is empty (given the initial square). The final square is calculated
// by adding sq_delta (similar for final row & final column)
#define GEN_STEP(name, sq_delta, row_delta, column_delta)                   \
    inline void name(std::vector<Move>* bfr, const Bitboard& bb, Square sq, \
                     int row, int column) {                                 \
        if (HasPlayer(bb, sq + sq_delta)) {                                 \
            bfr->push_back(createMove(row, column, row + row_delta,         \
                                      column + column_delta));              \
        }                                                                   \
    }
GEN_STEP(StepNorthWest, -7, -1, -1)
GEN_STEP(StepNorth, -6, -1, 0)
GEN_STEP(StepNorthEast, -5, -1, +1)
GEN_STEP(StepWest, -1, 0, -1)
GEN_STEP(StepEast, +1, 0, +1)
GEN_STEP(StepSouthWest, +5, +1, -1)
GEN_STEP(StepSouth, +6, +1, 0)
GEN_STEP(StepSouthEast, +7, +1, +1)

// Generates three Step* calls (used for corners which have 3 freedoms)
#define TOUCH_CORNER(bfr, bb, square, row, column, f1, f2, f3) \
    {                                                          \
        f1(bfr, bb, square, row, column);                      \
        f2(bfr, bb, square, row, column);                      \
        f3(bfr, bb, square, row, column);                      \
    }

// Generates five Step* calls (used for edge squares which have five freedoms)
#define TOUCH_EDGE(bfr, bb, square, row, column, f1, f2, f3, f4, f5) \
    {                                                                \
        TOUCH_CORNER(bfr, bb, square, row, column, f1, f2, f3);      \
        f4(bfr, bb, square, row, column);                            \
        f5(bfr, bb, square, row, column);                            \
    }

inline void GenerateCornerStepMoves(const Bitboard stm_bitboard,
                                    const Bitboard nn_bitboard,
                                    std::vector<Move>* buffer) {
    // Northwest corner
    if (HasPlayer(stm_bitboard, 0))
        TOUCH_CORNER(buffer, nn_bitboard, 0, 0, 0, StepEast, StepSouthEast,
                     StepSouth)

    // Northeast corner
    if (HasPlayer(stm_bitboard, 5))
        TOUCH_CORNER(buffer, nn_bitboard, 5, 0, 5, StepSouth, StepSouthWest,
                     StepWest)

    // Southwest corner
    if (HasPlayer(stm_bitboard, 30))
        TOUCH_CORNER(buffer, nn_bitboard, 30, 5, 0, StepNorth, StepNorthEast,
                     StepEast)

    // Southeast corner
    if (HasPlayer(stm_bitboard, 35))
        TOUCH_CORNER(buffer, nn_bitboard, 35, 5, 5, StepWest, StepNorthWest,
                     StepNorth)
}

inline void GenerateEdgeStepMoves(const Bitboard stm_bitboard,
                                  const Bitboard nn_bitboard,
                                  std::vector<Move>* buffer) {
    for (int square = 1; square < 5; square++) {
        if (!HasPlayer(stm_bitboard, square)) continue;

        TOUCH_EDGE(buffer, nn_bitboard, square, 0, square, StepEast,
                   StepSouthEast, StepSouth, StepSouthWest, StepWest)
    }

    // West edge
    for (int row = 1, square = 11; row < 5; row++, square += 6) {
        if (!HasPlayer(stm_bitboard, square)) continue;

        TOUCH_EDGE(buffer, nn_bitboard, square, row, 5, StepSouth,
                   StepSouthWest, StepWest, StepNorthWest, StepNorth)
    }

    // South edge
    for (int column = 1, square = 31; column < 5; column++, square++) {
        if (!HasPlayer(stm_bitboard, square)) {
            continue;
        }

        TOUCH_EDGE(buffer, nn_bitboard, square, 5, column, StepWest,
                   StepNorthWest, StepNorth, StepNorthEast, StepEast)
    }

    // East edge
    for (int row = 1, square = 6; row < 5; row++, square += 6) {
        if (!HasPlayer(stm_bitboard, square)) continue;

        TOUCH_EDGE(buffer, nn_bitboard, square, row, 0, StepNorth,
                   StepNorthEast, StepEast, StepSouthEast, StepSouth)
    }
}

template <>
std::vector<Move>& GenerateMoves<STEP>(const Position& pos,
                                       std::vector<Move>* buffer) {
    if (!buffer) {
        buffer = new std::vector<Move>();
    }

    Bitboard stm_bitboard = pos.GetSideToMoveBitboard();
    Bitboard nn_bitboard = pos.GetNonNullBitboard();

    GenerateCornerStepMoves(stm_bitboard, nn_bitboard, buffer);
    GenerateEdgeStepMoves(stm_bitboard, nn_bitboard, buffer);

    /* Loop through non-border squares which have eight freedoms */
    for (int row = 1, square = 7; row < 5; row++) {
        for (int column = 1; column < 5; column++, square++) {
            if (!HasPlayer(stm_bitboard, square)) continue;

            StepNorthWest(buffer, nn_bitboard, square, row, column);
            StepNorth(buffer, nn_bitboard, square, row, column);
            StepNorthEast(buffer, nn_bitboard, square, row, column);
            StepWest(buffer, nn_bitboard, square, row, column);
            StepEast(buffer, nn_bitboard, square, row, column);
            StepSouthWest(buffer, nn_bitboard, square, row, column);
            StepSouth(buffer, nn_bitboard, square, row, column);
            StepSouthEast(buffer, nn_bitboard, square, row, column);
        }
    }

    return *buffer;
}

// Checks whether an attack from a square in a given direction is valid.
inline bool IsAttackValid(const Position& pos, Bid start_bid, int start_row,
                          int start_column, int& final_row, int& final_column) {
    Bitboard bitboard = pos.GetSideToMoveBitboard();

    // Check if the player at (start_row, start_column) is the side-to-move
    if (HasPlayer(bitboard, start_row, start_column)) {
        return false;
    }

    int row = start_row;
    int column = start_column;
    Bid bid = start_bid;

    bool was_loop_step = false;
    int self_cross_count = 0;
    int loop_count = 0;
    Player turn_player = pos.GetSideToMovePlayer();

    while (true) {
        sk::calculateAttackPath(row, column, bid, row, column, bid,
                                was_loop_step);

        bool is_self_cross = false;

        // The original square is occupied by the moving piece; however, we are
        // allowed to jump over it.
        if (row == start_row && column == start_column) {
            self_cross_count++;
            is_self_cross = true;

            // Jumping over the original square indicates that the attack will
            // result in an infinite loop.
            if (self_cross_count > 1) {
                return false;
            }
        }

        Player occupant = pos.GetPlayer(row, column);

        if (!is_self_cross && occupant == turn_player) {
            return false;
        }

        if (was_loop_step) {
            ++loop_count;
        }
        if (occupant && occupant != turn_player) {
            if (loop_count == 0) {
                return false;
            }

            break;
        }
    }

    final_row = row;
    final_column = column;

    return true;
}

// Generates attack moves with toggle for including "non-capturing" ones.
std::vector<Move>& GenerateAttack(const Position& pos, bool gen_intermediate,
                                  std::vector<Move>& buffer) {
    int capture_row = 0;
    int capture_column = 0;

    int path_row = 0;
    int path_column = 0;
    Bid path_bid = WEST;
    bool is_loop = false;
    int loop_count = 0;

    // Loop through each direction & each square
    for (int start_bid = WEST; start_bid <= SOUTH; start_bid++) {
        for (int row = 0; row < 6; row++) {
            for (int column = 0; column < 6; column++) {
                bool attackValid =
                    IsAttackValid(pos, (Bid)start_bid, row, column, capture_row,
                                  capture_column);

                if (!attackValid) {
                    continue;
                }

                if (!gen_intermediate || !pos.options_.capture_optional_) {
                    buffer.push_back(createMove(row, column, capture_row,
                                                capture_column, true,
                                                (Bid)start_bid));
                    continue;
                }

                path_row = row;
                path_column = column;
                path_bid = (Bid)start_bid;
                loop_count = 0;

                while (path_row != capture_row &&
                       path_column != capture_column) {
                    calculateAttackPath(path_row, path_column, path_bid,
                                        path_row, path_column, path_bid,
                                        is_loop);
                    if (is_loop) {
                        ++loop_count;
                    }

                    if (loop_count == 0) {
                        continue;  // can land only after looping once
                    }

                    buffer.push_back(createMove(row, column, path_row,
                                                path_column, true,
                                                (Bid)start_bid));
                }
            }
        }
    }

    return buffer;
}

// Generates only those attacking moves that capture on an enemy piece.
template <>
std::vector<Move>& GenerateMoves<CAPTURE>(const Position& pos,
                                          std::vector<Move>* buffer) {
    if (!buffer) {
        buffer = new std::vector<Move>();
    }

    GenerateAttack(pos, false, *buffer);
    return *buffer;
}

// Generates capturing & non-capturing attack moves. If model-options disallow
// optional capturing, then only the former are included.
template <>
std::vector<Move>& GenerateMoves<ATTACK>(const Position& pos,
                                         std::vector<Move>* buffer) {
    if (!buffer) {
        buffer = new std::vector<Move>();
    }

    GenerateAttack(pos, true, *buffer);
    return *buffer;
}

// Generates all possible (legal) moves for the side-to-move.
template <>
std::vector<Move>& GenerateMoves<LEGAL>(const Position& pos,
                                        std::vector<Move>* buffer) {
    if (!buffer) {
        buffer = new std::vector<Move>();
    }

    GenerateMoves<ATTACK>(pos, buffer);
    GenerateMoves<STEP>(pos, buffer);

    return *buffer;
}

}  // namespace sk