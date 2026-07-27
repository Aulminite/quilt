#ifndef QUILT_HPP
#define QUILT_HPP

#include "color.hpp"
#include "patch.hpp"
#include "style.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

class quilt {  
public:
    quilt(uint8_t patch_size);
    quilt(uint8_t patch_length, uint8_t patch_width);
    quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_size);
    quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_length, uint8_t patch_width);

    ~quilt() = default;

    void print();

    void generate();

    void addStyle(const std::string& filename);

private:
    void initPatchwork(uint8_t patch_length, uint8_t patch_width);
    bool legalLocation(uint8_t row, uint8_t col);

    std::vector<style> styles_;

    std::mt19937 rng_;

    uint8_t length_;
    uint8_t width_;

    std::vector<std::vector<patch>> patchwork_;
};

#endif