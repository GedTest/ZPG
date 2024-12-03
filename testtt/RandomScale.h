#pragma once
#include "Scale.h"


class RandomScale : public Scale {
public:
    RandomScale(float maxScale=1.0f);
    RandomScale(float factorX, float factorY, float factorZ);
};
