#pragma once
#include <cstddef>
#include <vector>

struct Building {
    int64_t x;
    int64_t z;
    double height;
};

std::vector<Building> generate_landscape(std::size_t length);
void drawCuboid(float x, float y, float z, float height);