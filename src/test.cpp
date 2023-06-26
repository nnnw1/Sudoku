#include "test.h"
#include <time.h>
#include <iostream>

void test_case1()
{
    CScene scene;

    time_t begin, end;
    time(&begin);
    scene.generate();
    time(&end);

    scene.show();
    std::cout << end - begin << std::endl;
}