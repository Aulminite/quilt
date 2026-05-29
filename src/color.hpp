#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <string>
#include <format>
#include <iostream>

struct color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class color {
    public:
        color();
        ~color() = default;
        color(color_t c);
        color(uint8_t r, uint8_t g, uint8_t b);

        void set(color_t c);
        void set(uint8_t r, uint8_t g, uint8_t b);

        color_t get();
        std::string getEscCode();
    private:
        color_t color_;
};


#endif//COLOR_HPP