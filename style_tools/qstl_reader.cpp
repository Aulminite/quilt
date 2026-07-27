#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

struct QuiltStyleImage
{
    uint32_t width;
    uint32_t height;
    std::vector<uint32_t> pixels;
};

bool loadQuiltStyle(QuiltStyleImage& image, const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
        return false;

    char magic[4];
    uint16_t version;

    file.read(magic, sizeof(magic));
    file.read(reinterpret_cast<char*>(&version), sizeof(version));

    if (std::memcmp(magic, "QSTL", 4) != 0)
    {
        std::cerr << "Not a QuiltStyle file.\n";
        return false;
    }

    if (version != 1)
    {
        std::cerr << "Unsupported version: " << version << '\n';
        return false;
    }

    file.read(reinterpret_cast<char*>(&image.width), sizeof(image.width));
    file.read(reinterpret_cast<char*>(&image.height), sizeof(image.height));

    uint32_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    if (count != image.width * image.height)
    {
        std::cerr << "Invalid pixel count.\n";
        return false;
    }

    image.pixels.resize(count);

    file.read(reinterpret_cast<char*>(image.pixels.data()),
              count * sizeof(uint32_t));

    return file.good();
}

void printImage(const QuiltStyleImage& image)
{
    for (uint32_t y = 0; y < image.height; y++)
    {
        for (uint32_t x = 0; x < image.width; x++)
        {
            uint32_t color = image.pixels[y * image.width + x];

            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = color & 0xFF;

            // Print two colored spaces
            std::cout
                << "\x1b[48;2;"
                << (int)r << ";"
                << (int)g << ";"
                << (int)b
                << "m  ";
        }

        // Reset colors and start next row
        std::cout << "\x1b[0m\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file.qst>\n";
        return 1;
    }

    QuiltStyleImage image;

    if (!loadQuiltStyle(image, argv[1]))
    {
        std::cerr << "Failed to load '" << argv[1] << "'.\n";
        return 1;
    }

    std::cout << image.width << " x " << image.height << "\n\n";

    printImage(image);

    std::cout << "\x1b[0m\n";

    return 0;
}