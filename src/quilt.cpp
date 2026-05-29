#include "quilt.hpp"

quilt::quilt(uint8_t patch_size) : length_(5), width_(5) { initPatchwork(patch_size, patch_size); }
quilt::quilt(uint8_t patch_length, uint8_t patch_width) : length_(5), width_(5) { initPatchwork(patch_length, patch_width); }
quilt::quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_size) : length_(quilt_length), width_(quilt_width) { initPatchwork(patch_size, patch_size); }
quilt::quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_length, uint8_t patch_width) : length_(quilt_length), width_(quilt_width) { initPatchwork(patch_length, patch_width); }

bool quilt::legalLocation(uint8_t row, uint8_t col) { return (row<length_)&&(col<width_); }

void quilt::initPatchwork(uint8_t patch_length, uint8_t patch_width){
    patchwork_.resize(length_);
    for (auto& row : patchwork_) {
        row.reserve(width_);
        for (uint8_t c = 0; c < width_; ++c) {
            row.emplace_back(patch_length, patch_width);
        }
    }
}

void quilt::print() { /*print out the quilt!*/
    uint8_t plen = patchwork_[0][0].getLength();
    uint8_t pwid = patchwork_[0][0].getWidth();
    for(int QL=0;QL<length_;QL++){
        for(int PL=0;PL<plen;PL++){
            for(int QW=0;QW<width_;QW++){
                for(int PW=0;PW<pwid;PW++){
                    patchwork_[QL][QW].printTile(PL,PW);
                }
            }
            std::cout << "\n"; 
        }
    }
}

void quilt::generate(/*std::vector<style> style_list, uint8_t patch_organization_method*/) { /*generate the quilt!*/ 
    uint8_t plen = patchwork_[0][0].getLength();
    uint8_t pwid = patchwork_[0][0].getWidth();
    for(int QL=0;QL<length_;QL++){
        for(int QW=0;QW<width_;QW++){
            //set colors of this particular tile!
            for(int PL=0;PL<plen;PL++){
                for(int PW=0;PW<pwid;PW++){
                    patchwork_[QL][QW].setTileColor(PL,PW,colorFromStyleScaledAt(PL,PW));
                }
            }
        }
    }
}

//===========STYLE STUFF===================

/*
patchLength = N
patchWidth = M
styleLength = J
styleWidth = K

scaleFactorL = J/N
scaleFactorW = K/M
PatchPixel(Y,X) = StylePixel(Y*scaleFactorL, X*scaleFactorW)

*/

color_t quilt::colorFromStyleScaledAt(int ROW, int COL){ // change this to colorScaledAt(int ROW, in COL)
    uint8_t styleL = 2;
    uint8_t styleW = 2;
    
    uint8_t plen = patchwork_[0][0].getLength();
    uint8_t pwid = patchwork_[0][0].getWidth();
    
    uint8_t scaled_styleRow = ROW * (float(styleL)/float(plen));
    uint8_t scaled_styleCol = COL * (float(styleW)/float(pwid));

    std::vector<std::vector<color_t>> testStyle = {{{0xFF,0x00,0x00},{0x00,0xFF,0x00}},{{0x00,0x00,0xFF},{0xFF,0xFF,0x00}}};
    
    return testStyle[std::min<uint8_t>(scaled_styleRow,styleL-1)][std::min<uint8_t>(scaled_styleCol,styleW-1)];
}