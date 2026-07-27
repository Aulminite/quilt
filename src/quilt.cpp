#include "quilt.hpp"

quilt::quilt(uint8_t patch_size) : length_(5), width_(5), rng_(std::random_device{}()) { initPatchwork(patch_size, patch_size); }
quilt::quilt(uint8_t patch_length, uint8_t patch_width) : length_(5), width_(5), rng_(std::random_device{}()) { initPatchwork(patch_length, patch_width); }
quilt::quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_size) : length_(quilt_length), width_(quilt_width), rng_(std::random_device{}()) { initPatchwork(patch_size, patch_size); }
quilt::quilt(uint8_t quilt_length, uint8_t quilt_width, uint8_t patch_length, uint8_t patch_width) : length_(quilt_length), width_(quilt_width), rng_(std::random_device{}()) { initPatchwork(patch_length, patch_width); }

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

void quilt::addStyle(const std::string& filename)
{
    style s;

    if (s.load(filename))
    {
        styles_.push_back(s);
    }
    else
    {
        std::cerr << "Failed to load style: " << filename << "\n";
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

void quilt::generate(){
    if(styles_.empty()){
        std::cerr << "No styles loaded.\n";
        return;
    }
    uint8_t plen = patchwork_[0][0].getLength();
    uint8_t pwid = patchwork_[0][0].getWidth();
    std::uniform_int_distribution<size_t> dist(
        0,
        styles_.size()-1
    );
    for(int QL = 0; QL < length_; QL++){
        for(int QW = 0; QW < width_; QW++){
            style& selected = styles_[dist(rng_)];
            for(int PL = 0; PL < plen; PL++){
                for(int PW = 0; PW < pwid; PW++){
                    patchwork_[QL][QW].setTileColor(
                        PL,PW,selected.colorScaledAt(PL,PW,plen,pwid)
                    );
                }
            }
        }
    }
}
