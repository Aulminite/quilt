#include "color.hpp"

color::color() : color_({0x77,0x77,0x77}) {}
color::color(color_t c) : color_(c) {}
color::color(uint8_t r, uint8_t g, uint8_t b) : color_({r,g,b}) {}

void color::set(color_t c){ color_ = c; }
void color::set(uint8_t r, uint8_t g, uint8_t b){ color_ = {r,g,b}; }

color_t color::get(){ return color_; }

std::string color::getEscCode(){ return (std::format("\033[38;2;{};{};{}m", color_.r, color_.g, color_.b)); }
