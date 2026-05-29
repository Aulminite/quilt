#include "color.hpp"
#include "patch.hpp"
#include "quilt.hpp"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <sstream>
#include <optional>

struct Params {
    uint8_t qL = 0, qW = 0;
    uint8_t pL = 0, pW = 0;
    bool qL_set = false, qW_set = false;
    bool pL_set = false, pW_set = false;
    std::vector<uint8_t> styles;
};

void printError(std::string_view msg);
std::optional<uint8_t> parseUint8(std::string_view s);
std::vector<uint8_t> parseStyleList(std::string_view s);
Params parseArgs(int argc, char** argv);

int main(int argc, char* argv[]){
    Params p = parseArgs(argc, argv);

    std::cout << "qL=" << +p.qL << " qW=" << +p.qW << "\n";
    std::cout << "pL=" << +p.pL << " pW=" << +p.pW << "\n";

    std::cout << "styles: ";
    for (auto s : p.styles) std::cout << +s << " ";
    std::cout << "\n";
    
    if(p.qL != 0 && p.pL != 0){
        quilt q(p.qL,p.qW,p.pL,p.pW);
        q.generate();
        q.print();
    }

    return 0;
}

void printError(std::string_view msg){
    std::cerr<<"[ERROR]"<<msg<<"\n";
}

std::optional<uint8_t> parseUint8(std::string_view s){
    try {
        int v = std::stoi(std::string(s));
        if(v < 0 || v > 255){
            return std::nullopt;
        }
        return static_cast<uint8_t>(v);
    } catch (...){
        return std::nullopt;
    }
}

std::vector<uint8_t> parseStyleList(std::string_view s) {
    std::vector<uint8_t> out;
    if (s.empty()) {
        printError("styles list cannot be empty");
        return out;
    }
    std::stringstream ss{std::string(s)};
    std::string item;
    while (std::getline(ss, item, ',')) {
        auto v = parseUint8(item);
        if (!v) {
            printError("Invalid number in styles list: " + item);
            continue;
        }
        out.push_back(*v);
    }
    return out;
}


Params parseArgs(int argc, char** argv) {
    Params params;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (!arg.starts_with("--")) {
            printError("Unknown argument: " + std::string(arg));
            continue;
        }

        auto eqPos = arg.find('=');
        if (eqPos == std::string_view::npos) {
            printError("Flag requires a value: " + std::string(arg));
            continue;
        }

        std::string key = std::string(arg.substr(2, eqPos - 2));
        std::string value = std::string(arg.substr(eqPos + 1));

        if (key == "qL") {
            auto v = parseUint8(value);
            if (!v) printError("Invalid qL value: " + value);
            else { params.qL = *v; params.qL_set = true; }
        }
        else if (key == "qW") {
            auto v = parseUint8(value);
            if (!v) printError("Invalid qW value: " + value);
            else { params.qW = *v; params.qW_set = true; }
        }
        else if (key == "pL") {
            auto v = parseUint8(value);
            if (!v) printError("Invalid pL value: " + value);
            else { params.pL = *v; params.pL_set = true; }
        }
        else if (key == "pW") {
            auto v = parseUint8(value);
            if (!v) printError("Invalid pW value: " + value);
            else { params.pW = *v; params.pW_set = true; }
        }
        else if (key == "styles") {
            params.styles = parseStyleList(value);
        }
        else {
            printError("Unknown flag: " + key);
        }
    }

    // Mirror logic
    if (params.qL_set && !params.qW_set) params.qW = params.qL;
    if (params.qW_set && !params.qL_set) params.qL = params.qW;

    if (params.pL_set && !params.pW_set) params.pW = params.pL;
    if (params.pW_set && !params.pL_set) params.pL = params.pW;

    return params;
}