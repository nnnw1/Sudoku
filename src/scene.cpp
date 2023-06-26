#include <cmath>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "common.h"
#include "scene.h"
#include "utility.inl"

CScene::CScene(int index)
    : _max_column(pow(index, 2)), _cur_point({0, 0})
{
    init();
}

CScene::~CScene()
{
    if (keyMap)
        delete keyMap;
}

void CScene::show() const
{
    cls();

    printUnderLine();

    for(int row = 0; row < _max_column; ++row)
    {
        CBlock block = _row_block[row];
        block.print();
        printUnderLine(row);
    }
}

void CScene::setMode(KeyMode mode)
{
    switch(mode)
    {
        case KeyMode::NORMAL:
            keyMap = new Normal;
            break;

        case KeyMode::VIM:
            keyMap = new Vim;
            break;
    }
}

void CScene::printUnderLine(int line_no) const
{
    for(int column = 0; column < 9; ++column)
        std::cout << "\u254B" << "\u2501" << ((_cur_point.y == line_no && _cur_point.x == column)?"^":"\u2501") << "\u2501";
    std::cout << "\u254B" << std::endl;
}

void CScene::init()
{
    memset(_map, UNSELECTED, sizeof _map);

    for(int col=0; col < _max_column; ++col)  //column_block refers to all of columns
    {
        CBlock column_block;

        for(int row=0; row < _max_column; ++row)
        {
            column_block.push_back(_map + row * 9 + col);
        }
        _column_block[col] = column_block;
    }

    for(int row=0; row < _max_column; ++row)  //row_block refers to all of rows
    {
        CBlock row_block;

        for(int col=0; col < _max_column; ++col)
        {
            row_block.push_back(_map + row * 9 + col);
        }
        _row_block[row] = row_block;
    }

    for(int block_index = 0; block_index < _max_column; ++block_index) //xy_block refers to all of grids, [row][col]
    {
        CBlock xy_block;

        int xy_begin = block_index / 3 *27 + block_index % 3 * 3;
        for(int i=0; i < 3; ++i)
        {
            for(int j=0; j < 3; ++j)
            {
                xy_block.push_back(_map + xy_begin + i * 9 + j);
            }
        }
        _xy_block[block_index / 3][block_index % 3] = xy_block;
    }

    return;
}

bool CScene::setCurValue(const int nCurValue, int &nLastValue)
{
    auto point = _map[_cur_point.x + _cur_point.y * 9];
    if(point.state == State::ERASED)
    {
        nLastValue = point.value;
        setValue(nCurValue);
        return true;
    }
    else   
        return false;
}

void CScene::setValue(const point_t& p, const int value)
{
    _map[p.x + p.y * 9].value = value;
}

void CScene::setValue(const int value)
{
    auto p = _cur_point;
    this->setValue(p, value);
}

/*
@function select some (count) grids to clear
*/
void CScene::eraseRandomGrids(const int count)
{
    point_value_t p = {UNSELECTED, State::ERASED};

    std::vector<int> v(81);
    for(int i=0; i < 81; ++i)
    {
        v[i] = i;
    }

    for(int i=0; i < count; ++i)
    {
        int r = random(0, v.size() - 1);
        _map[v[r]] = p;
        v.erase(v.begin() + r);
    }
}

bool CScene::isComplete()
{
    //not complete if there is any block that is not full
    for(size_t i=0; i < 81; ++i)
    {
        if(_map[i].value == UNSELECTED)
            return false;
    }

    //the number in the block must be valid
    for(int row=0; row < 9; ++row)
    {
        for(int col = 0; col < 9; ++col)
        {
            if(!_row_block[row].isValid() || !_column_block[col].isValid() || !_xy_block[row / 3][col / 3].isValid())
                return false;
        }
    }

    return true;
}

void CScene::save(const char *filename)
{
    std::fstream fs;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    //save _map
    for(int i=0; i < 81; ++i)
    {
        fs << _map[i].value << ' ' << static_cast<int>(_map[i].state) << std::endl;
    }

    //save _cur_point
    fs << _cur_point.x << ' ' << _cur_point.y << std::endl;

    //save _vCommand
    fs << _vCommand.size() << std::endl;
    for(CCommand command : _vCommand)
    {
        point_t point = command.getPoint();
        fs << point.x << ' ' << point.y << ' ' << command.getPreValue() << ' ' << command.getCurValue() << std::endl;
    }

    fs.close();
}

void CScene::load(const char *filename)
{
    std::fstream fs;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    //load _map
    for(int i=0; i < 81; ++i)
    {
        int tmpState;
        fs >> _map[i].value >> tmpState;
        _map[i].state = static_cast<State>(tmpState);
    }

    //load _cur_point
    fs >>_cur_point.x >> _cur_point.y;

    //load _vCommand
    int commandSize;
    fs >> commandSize;
    for(int i = 0; i < commandSize; ++i)
    {
        point_t point;
        int preValue, curValue;
        fs >> point.x >> point.y >> preValue >> curValue;
        _vCommand.emplace_back(this, point, preValue, curValue);
    }
}