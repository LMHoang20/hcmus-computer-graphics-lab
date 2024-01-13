#pragma once
#include "fcoordinate.h"
#include "rgbcolor.h"
#include <numbers> 
#include <vector>

constexpr int WIDTH = 500;
constexpr int HEIGHT = 500;

constexpr double PI = std::numbers::pi;

const std::vector < fCoordinate > directions({ fCoordinate(0, 1), fCoordinate(0, -1), fCoordinate(1, 0), fCoordinate(-1, 0) });

const fCoordinate LEFT(-1, 0);
const fCoordinate RIGHT(1, 0);
const fCoordinate UP(0, 1);
const fCoordinate DOWN(0, -1);

const RGBColor defaultBoundaryColor(255, 255, 255);
const RGBColor backgroundColor(0, 0, 0);