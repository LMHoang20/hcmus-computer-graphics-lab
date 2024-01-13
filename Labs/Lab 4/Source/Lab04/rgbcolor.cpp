#include "rgbcolor.h"

RGBColor::RGBColor(unsigned char _r, unsigned char _g, unsigned char _b) : r{_r}, b{_b}, g{_g} { }

bool RGBColor::operator==(const RGBColor& other) const
{
    return r == other.r && g == other.g && b == other.b;
}

RGBColor::operator std::string() const {
    return std::to_string(int(r)) + " " + std::to_string(int(g)) + " " + std::to_string(int(b));
}

bool RGBCompare::operator() (const RGBColor& lhs, const RGBColor& rhs) const
{
    if (lhs.r != rhs.r) return lhs.r < rhs.r;
    if (lhs.g != rhs.g) return lhs.g < rhs.g;
    if (lhs.b != rhs.b) return lhs.b < rhs.b;
    return false;
}

size_t RGBHash::operator()(const RGBColor& color) const {
    return (color.r << 16) + (color.g << 8) + (color.b);
}
