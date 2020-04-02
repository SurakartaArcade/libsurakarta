/**
 * attackpath.cc
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
#include <cassert>
#include <iostream>

#include "factory/surakarta_factory.h"

void testAttackLegalityWhenBlocked()
{
  std::vector<ModelBlock *> mocker = {
      new ModelBlock(sk::RED, 0, 0, 3, 3),
      new ModelBlock(sk::BLACK, 2, 0)};
  sk::Surakarta *model = createModel(mocker);

  // Piece is blocked, can't attack
  assert(!model->isLegalAttackBid(sk::NORTH, 2, 2));

  // Piece can directly loop and capture
  assert(model->isLegalAttackBid(sk::NORTH, 0, 2));

  // Piece is black and can't play on this turn
  assert(!model->isLegalAttackBid(sk::WEST, 2, 0));
}

int main()
{
  testAttackLegalityWhenBlocked();
  return 0;
}