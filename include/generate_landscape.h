#pragma once
#include <cstddef>
#include <vector>

struct Building {
    int64_t x;
    int64_t z;
    double height;
    float color[3];
};

std::vector<Building> generate_landscape(int64_t length);
void drawCuboid(float x, float y, float z, float height, float const color[3]);