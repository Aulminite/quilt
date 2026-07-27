#include "style.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>

bool style::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
        return false;

    char magic[4];

    file.read(magic, 4);

    if (std::memcmp(magic, "QSTL", 4) != 0)
        return false;

    uint16_t version;
    file.read(reinterpret_cast<char*>(&version), sizeof(version));

    if (version != 1)
        return false;

    file.read(reinterpret_cast<char*>(&width_), sizeof(width_));
    file.read(reinterpret_cast<char*>(&height_), sizeof(height_));

    uint32_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    if (count != width_ * height_)
        return false;

    pixels_.resize(count);

    file.read(reinterpret_cast<char*>(pixels_.data()),
              count * sizeof(uint32_t));

    return file.good();
}

uint32_t style::getWidth() const
{
    return width_;
}

uint32_t style::getHeight() const
{
    return height_;
}

color_t style::colorAt(uint32_t row, uint32_t col) const
{
    row = std::min(row, height_ - 1);
    col = std::min(col, width_ - 1);

    uint32_t rgb = pixels_[row * width_ + col];

    return {
        static_cast<uint8_t>((rgb >> 16) & 0xFF),
        static_cast<uint8_t>((rgb >> 8) & 0xFF),
        static_cast<uint8_t>(rgb & 0xFF)
    };
}

color_t style::colorScaledAt(
    uint32_t row,
    uint32_t col,
    uint32_t targetHeight,
    uint32_t targetWidth
) const
{
    uint32_t scaledRow =
        row * (static_cast<float>(height_) / targetHeight);

    uint32_t scaledCol =
        col * (static_cast<float>(width_) / targetWidth);

    return colorAt(scaledRow, scaledCol);
}