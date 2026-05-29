#ifndef QUILT_HPP
#define QUILT_HPP

#include "color.hpp"
#include "patch.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>

struct style {
    std::vector<color_t> color_pallete;             //set of colors
    std::vector<std::vector<uint8_t>> pattern_data; //2d array - uint8_t defines which color_t to grab from color_pallete
};

class quilt {  
    public:
        quilt(uint8_t patch_size);
        quilt(uint8_t patch_length, uint8_t patch_width);
        quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_size);
        quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_length, uint8_t patch_width);
        ~quilt() = default;

        void print();

        void generate(/*std::vector<style> style_list, uint8_t patch_organization_method*/);
        color_t colorFromStyleScaledAt(int ROW, int COL);
    private:
        void initPatchwork(uint8_t patch_length, uint8_t patch_width);
        bool legalLocation(uint8_t row, uint8_t col);

        std::vector<style> styles_;

        uint8_t length_;
        uint8_t width_;

        std::vector<std::vector<patch>> patchwork_;
};

#endif//QUILT_HPP