
#ifndef QUILT_HPP
#define QUILT_HPP
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <random>
struct color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
class tile {
    public:
        tile(color_t color);
        ~tile() = default;
        void print();
        void setColor(color_t color);
        color_t getColor();
    private:
        color_t color_;
};
class quilt{
    public:
        quilt(uint8_t size);
        quilt(uint8_t length, uint8_t width);
        ~quilt() = default;
        tile& tileAt(uint8_t row, uint8_t col);
        void print();
    private:
        bool inbounds(uint8_t row, uint8_t col);
        uint8_t length;
        uint8_t width;
        std::vector<std::vector<tile>> patchwork;
};
#endif//QUILT_HPP