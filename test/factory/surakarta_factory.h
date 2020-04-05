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

#ifndef TEST_SURAKARTA_FACTORY_H_
#define TEST_SURAKARTA_FACTORY_H_

#include <skmodel.h>

#include <vector>

// Used to feed verbose instructions to SurakartaFactory to mock a position.
typedef struct ModelBlock {
    sk::Player color;
    int row;
    int column;
    int rowRange;
    int columnRange;

    ModelBlock(sk::Player color, int row, int column, int rowRange = 1,
               int columnRange = 1) {
        this->color = color;
        this->row = row;
        this->column = column;
        this->rowRange = rowRange;
        this->columnRange = columnRange;
    }
} ModelBlock;

sk::Surakarta *createModel(std::vector<ModelBlock *> &arr);

#endif /* TEST_SURAKARTA_FACTORY_H_ */