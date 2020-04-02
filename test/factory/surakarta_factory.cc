/**
 * surakarta_factory.cc
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
#include "surakarta_factory.h"

sk::Surakarta *clearModel(sk::Surakarta &model)
{
  for (int i = 0; i < 36; i++)
  {
    model.editable()[i] = sk::NULL_PLAYER;
  }

  return &model;
}

sk::Surakarta *createModel(std::vector<ModelBlock *> &arr)
{
  sk::Surakarta *model = clearModel(*new sk::Surakarta());

  for (int i = 0; i < arr.size(); i++)
  {
    ModelBlock *block = arr.at(i);

    for (int dr = 0; dr < block->rowRange; dr++)
    {
      for (int dc = 0; dc < block->columnRange; dc++)
      {
        model->editable()[(block->row + dr) * 6 + (block->column + dc)] = block->color;
      }
    }
  }

  return model;
}