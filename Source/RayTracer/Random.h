#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

inline void seedRandom(unsigned int seed)
{
    srand(seed);
}

inline float random01()
{
    return rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
    if (min > max) std::swap(min, max);
    return (rand() * (max - min)) + min;
}
