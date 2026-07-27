#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

struct QuiltStyleImage
{
    uint32_t width;
    uint32_t height;
    std::vector<uint32_t> pixels;
};

bool saveQuiltStyle(const QuiltStyleImage& image, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);

    if (!file)
        return false;

    // File header
    const char magic[4] = {'Q', 'S', 'T', 'L'};
    uint16_t version = 1;

    file.write(magic, sizeof(magic));
    file.write(reinterpret_cast<const char*>(&version), sizeof(version));

    file.write(reinterpret_cast<const char*>(&image.width), sizeof(image.width));
    file.write(reinterpret_cast<const char*>(&image.height), sizeof(image.height));

    uint32_t count = static_cast<uint32_t>(image.pixels.size());
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    file.write(reinterpret_cast<const char*>(image.pixels.data()),
               count * sizeof(uint32_t));

    return file.good();
}

int main()
{
    QuiltStyleImage image;

    image.width = 6;
    image.height = 6;

    image.pixels = {

        // Row 1
        0x000000, 0x000000, 0xFF0000, 0xFF0000, 0x000000, 0x000000,

        // Row 2
        0x000000, 0xFF0000, 0xFFFFFF, 0xFFFFFF, 0xFF0000, 0x000000,

        // Row 3
        0xFF0000, 0xFFFFFF, 0x0000FF, 0x0000FF, 0xFFFFFF, 0xFF0000,

        // Row 4
        0xFF0000, 0xFFFFFF, 0x0000FF, 0x0000FF, 0xFFFFFF, 0xFF0000,

        // Row 5
        0x000000, 0xFF0000, 0xFFFFFF, 0xFFFFFF, 0xFF0000, 0x000000,

        // Row 6
        0x000000, 0x000000, 0xFF0000, 0xFF0000, 0x000000, 0x000000
    };

    if (saveQuiltStyle(image, "example.qst"))
        std::cout << "Saved example.qst\n";
    else
        std::cout << "Failed to save file.\n";
}