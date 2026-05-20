#include "quilt.hpp"

/*
 * Author: Luke Staritz
 * Date:   2026-05-20
*/

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0,255);
    std::vector<std::string> args(argv + 1, argv + argc);

    uint8_t quiltLength = 0;
    uint8_t quiltWidth = 0;
    std::vector<uint16_t> activeStyles;
    bool verbose = false;
    std::string filepath = "";

    const std::string helpmsg = "helptext";

    for(uint8_t i=0;i<argc-1;i++){
        if(args[i]=="-l" || args[i]=="--length"){           //Quilt length
            if(i+1 >= argc-1){ std::cerr << "ERROR: illegal carpet length! (parameter missing)" << std::endl; exit(0); }
            try {
                quiltLength = (uint8_t)std::stoi(args[i+1]); i++;
                if(quiltLength==0){ std::cerr << "ERROR: illegal carpet length! (size 0)" << std::endl; exit(0);}
            } catch (const std::invalid_argument& e) {
                std::cerr << "ERROR: illegal carpet length! (cannot convert '" << args[i+1] << "' to uint8_t)" << std::endl;
                exit(0);
            }
        } else if(args[i]=="-w" || args[i]=="--width"){     //Quilt Width
            if(i+1 >= argc-1){ std::cerr << "ERROR: illegal carpet width! (parameter missing)" << std::endl; exit(0); }
            try {
                quiltWidth = (uint8_t)std::stoi(args[i+1]); i++;
                if(quiltWidth==0){ std::cerr << "ERROR: illegal carpet width! (size 0)" << std::endl; exit(0); }
            } catch (const std::invalid_argument& e) {
                std::cerr << "ERROR: illegal carpet width! (cannot convert '" << args[i+1] << "' to uint8_t)" << std::endl;
                exit(0);
            }
        } else if(args[i]=="-v" || args[i]=="--verbose"){   //Verbose construction
            std::cout << "quilt: [VERBOSE MODE]" << std::endl;
            verbose = true;
        } else if(args[i]=="-s" || args[i]=="--save"){      //Save quilt to image file
            std::cout << "WARNING: saving functionality is not yet available!" << std::endl;
        } else if(args[i]=="-p" || args[i]=="--patches"){   //Style list
            std::cout << "WARNING: patch style functionality is not yet available!" << std::endl;
        } else if(args[i]=="-h" || args[i]=="--help"){      //Program help
            std::cout << helpmsg << std::endl;
            exit(0);
        } else {
            std::cout << "WARNING: unknown flag or parameter \"" << args[i] << "\" was ignored!" << std::endl;
        }
    }

    if((!quiltLength)&&(!quiltWidth)){ 
        std::cerr << "ERROR: quilt size not set!" << std::endl;
        exit(0); 
    } else if ((!quiltLength)||(!quiltWidth)) {
        if(!quiltLength) { quiltLength=quiltWidth; }
        else { quiltWidth=quiltLength; }
    }
    if(verbose){
        std::cout << "quilt::(" 
            << std::to_string(quiltLength) << "," 
            << std::to_string(quiltWidth) << ")" << std::endl;
    }
    
    quilt q(quiltLength,quiltWidth);

    for(uint8_t r=0;r<quiltLength;r++){
        for(uint8_t c=0;c<quiltLength;c++){
            color_t randc;
            randc.r = dis(gen);
            randc.g = dis(gen);
            randc.b = dis(gen);
            q.tileAt(r,c).setColor(randc);
        }
    }

    q.print();


    return 0;
}

//TILE FUNCTION DEFS
tile::tile(color_t color) : color_(color) { ; }
void tile::print() { 
    char escseq[50];
    sprintf(escseq, "\033[38;2;%d;%d;%dm\u2588\033[0m", static_cast<int>(color_.r), static_cast<int>(color_.g), static_cast<int>(color_.b));
    printf("%s", escseq);
    
}
void tile::setColor(color_t color) { color_ = color; }
color_t tile::getColor() { return color_; }

//QUILT FUNCTION DEFS
quilt::quilt(uint8_t size) : length(size), width(size), patchwork(size, std::vector<tile>(size,tile({0,0,0}))) { ; }
quilt::quilt(uint8_t length, uint8_t width) : length(length), width(width), patchwork(length, std::vector<tile>(width,tile({0,0,0}))) { ; }
tile& quilt::tileAt(uint8_t row,uint8_t col){
    if(inbounds(row,col)){
        return patchwork[row][col];
    }
    return patchwork[0][0];
}
void quilt::print(){
    for(uint8_t row=0;row<length;row++){
        for(uint8_t col=0;col<width;col++){
            tileAt(row,col).print();
        } std::cout << "\n";
    }
}
bool quilt::inbounds(uint8_t row, uint8_t col) { return row < length && col < width; }
