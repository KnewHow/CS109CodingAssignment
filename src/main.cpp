#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <array>

#include "bat.h"

std::vector<Bat> bats;

void readBatsFromFile(const std::string &filepath);
inline bool stringToBool(const std::string &boolStr);
float calculateProbT();
std::array<float, 5> calculateProbG();
float calculateProbGI(int index);

int main(int argc, char** argv) {
    if(argc < 1) {
        std::cerr << "Not provide data file!" << std::endl;
        exit(1);
    }
    std::string filepath = std::string(argv[1]);
    readBatsFromFile(filepath);
    calculateProbT();
    calculateProbG();
    return 0;
}

float calculateProbT() {
    int totol = bats.size();
    int withEbola = 0;
    for(int i = 0; i < bats.size(); ++i)
        if(bats[i].withEbola) ++withEbola;
    
    float p = (float)withEbola / totol;
    std::cout << "P(T) is: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << p << std::endl;
    return p;
}

std::array<float, 5> calculateProbG() {
    std::array<float, 5> rs;
    for(int i = 0; i < rs.size(); ++i)
        rs[i] = calculateProbGI(i + 1);
    
    for(int i = 0; i < rs.size(); ++i)
        std::cout << "P(G_" << i + 1 <<") is: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << rs[i] << std::endl;
    return rs;
}

float calculateProbGI(int index) {
    int totol = bats.size();
    int apperaTimes = 0;
    for(int i = 0; i < bats.size(); ++i)
        if(bats[i][index]) ++apperaTimes;
    
    float p = (float)apperaTimes / totol;
    return p;
}


void readBatsFromFile(const std::string &filepath) {
    std::ifstream in;
    in.open(filepath, std::ifstream::in);
    if(in.fail()) return;
    std::string line;
    while(!in.eof()) {
        std::getline(in, line);
        if(line.empty()) continue;
        std::istringstream iss(line.c_str());
        std::stringstream ss(line);
        std::string boolStr;
        std::string arr[6];
        int i = 0;
        while(getline(ss, boolStr, ',')) {
            arr[i++] = boolStr;
        }
        arr[5].erase(std::remove(arr[5].begin(), arr[5].end(), '\r'), arr[5].end());
        Bat b(stringToBool(arr[0]), stringToBool(arr[1]), stringToBool(arr[2]), stringToBool(arr[3]), stringToBool(arr[4]), stringToBool(arr[5]));
        bats.push_back(b);
    }

    in.close();
}

inline bool stringToBool(const std::string &boolStr) {
    if(boolStr == "False")
        return false;
    else
        return true;
}




