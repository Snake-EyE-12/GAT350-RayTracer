#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

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
    if (min > max) {
        float temp = min;
        min = max;
        max = temp;
    }
    return (rand() * (max - min)) + min;
}
