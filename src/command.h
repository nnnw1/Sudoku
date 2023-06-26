#ifndef _SUDOKU_COMMAND_H_
#define _SUDOKU_COMMAND_H_

#include <memory>
#include "common.h"

class CScene;
class CCommand
{
public:
    CCommand(CScene *pOwner);
    CCommand(CScene *pOwner, const point_t &point, int preValue, int curValue);
    CCommand(const CCommand &);
    ~CCommand();

    bool execute(int nInputValue);
    void undo();

private:
    CScene *_pOwner;
    point_t _stPoint;
    int _nPreValue;
    int _nCurValue;
};

#endif