#include "patch.hpp"

patch::patch(uint8_t size) : length_(size), width_(size) {
    element_.resize(length_);
    for (auto& row : element_) {
        row.resize(width_, color{0,0,0}); // default color
    }
}
patch::patch(uint8_t length, uint8_t width) : length_(length), width_(width) {
    element_.resize(length_);
    for (auto& row : element_) {
        row.resize(width_, color{0,0,0}); // default color
    }
}
bool patch::legalLocation(uint8_t row, uint8_t col){ return (row<length_)&&(col<width_); }

void patch::setTileColor(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b) { if(legalLocation(row,col)){ element_[row][col].set(r,g,b); } }
void patch::setTileColor(uint8_t row, uint8_t col, color_t c) { if(legalLocation(row,col)){ element_[row][col].set(c); } }

color_t patch::getTileColor(uint8_t row, uint8_t col) { if(legalLocation(row,col)){ return element_[row][col].get(); } return {0,0,0}; }

void patch::printTile(uint8_t row, uint8_t col) { if(legalLocation(row,col)){ std::cout << element_[row][col].getEscCode() << "\u2588" << "\033[0m"; } }

uint8_t patch::getLength() {return length_;}
uint8_t patch::getWidth() {return width_;}





