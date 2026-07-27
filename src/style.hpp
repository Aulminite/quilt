#ifndef STYLE_HPP
#define STYLE_HPP

#include "color.hpp"

#include <cstdint>
#include <string>
#include <vector>

class style {
public:
    style() = default;

    bool load(const std::string& filename);

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    color_t colorAt(uint32_t row, uint32_t col) const;

    color_t colorScaledAt(
        uint32_t row,
        uint32_t col,
        uint32_t targetHeight,
        uint32_t targetWidth
    ) const;

private:
    uint32_t width_ = 0;
    uint32_t height_ = 0;

    std::vector<uint32_t> pixels_;
};

#endif