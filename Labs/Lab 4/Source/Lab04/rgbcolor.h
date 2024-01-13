#pragma once
#include <string>

struct RGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	RGBColor(unsigned char _r, unsigned char _g, unsigned char _b);
	bool operator==(const RGBColor& other) const;
	operator std::string() const;
};

struct RGBCompare {
	bool operator() (const RGBColor& lhs, const RGBColor& rhs) const;
};

struct RGBHash {
public:
	size_t operator()(const RGBColor& color) const;
};