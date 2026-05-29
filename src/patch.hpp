#ifndef PATCH_HPP
#define PATCH_HPP

#include "color.hpp"
#include <cstdlib>
#include <vector>

class patch {
    public:
        patch(uint8_t size);
        patch(uint8_t length, uint8_t width);
        ~patch() = default;

        void setBaseColor(uint8_t r, uint8_t g, uint8_t b);
        void setBaseColor(color_t c);

        void setTileColor(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b);
        void setTileColor(uint8_t row, uint8_t col, color_t c);

        color_t getTileColor(uint8_t row, uint8_t col);
        
        void printTile(uint8_t row, uint8_t col);
        
        uint8_t getLength();
        uint8_t getWidth();
    private:
        bool legalLocation(uint8_t row, uint8_t col);

        uint64_t style_;

        uint8_t length_;
        uint8_t width_;

        std::vector<std::vector<color>> element_;
};

#endif//PATCH_HPP