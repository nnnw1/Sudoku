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