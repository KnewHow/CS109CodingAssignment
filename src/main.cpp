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
std::array<bool, 5> checkTIsIndependentWithG();
bool checkTIsIndependentWithGI(int index);
bool compare_float(float v1, float v2);
float calculateEK();
int calculateGeneExpress(int index);

int main(int argc, char** argv) {
    if(argc < 1) {
        std::cerr << "Not provide data file!" << std::endl;
        exit(1);
    }
    std::string filepath = std::string(argv[1]);
    readBatsFromFile(filepath);
    // calculateProbT();
    // calculateProbG();
    checkTIsIndependentWithG();
    //calculateEK();
    return 0;
}

float calculateEK() {
    float expectation = 0;
    for(int i = 0; i < 5; ++i) {
        float p_GI = calculateProbGI(i + 1);
        int expressed = calculateGeneExpress(i + 1);
        expectation += p_GI * expressed;
    }
    std::cout << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << "EK is: " << expectation << std::endl;
    return expectation;
}

int calculateGeneExpress(int index) {
    int expressed = 0;
    for(int i = 0; i < bats.size(); ++i)
        if(bats[i][index])
            ++expressed;
    return expressed;
}

std::array<bool, 5> checkTIsIndependentWithG() {
    std::array<bool, 5> rs;
    for(int i = 0; i < 5; ++i)
        rs[i] = checkTIsIndependentWithGI(i + 1);
    return rs;
}

bool checkTIsIndependentWithGI(int index) {
    int TandGISum = 0;
    for(int i = 0; i < bats.size(); ++i) {
        if(bats[i][index] && bats[i].withEbola)
            ++TandGISum;
    }
    float p_GI = calculateProbGI(index);
    float p_TandGI = (float)TandGISum / bats.size();
    float p_T = calculateProbT();
    float p_Tbefore_GI = p_TandGI / p_GI;
    bool r = compare_float(p_Tbefore_GI, p_T);
    std::cout << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << "P(T) is: " << p_T << std::endl;
    std::cout << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << "P(G_" << index << ") is:" << p_GI << ", P(T and G_" << index << ") is: " << p_TandGI << ", P(T | G_" << index << ") is: " << p_Tbefore_GI << ", they are independent: " << std::boolalpha << r << std::endl;
    return r;
}

bool compare_float(float v1, float v2) {
    float ShadowEpsilon = 0.0001f;
    if(std::abs(v1 - v2) < ShadowEpsilon)
        return true;
    else 
        return false;
}

float calculateProbT() {
    int totol = bats.size();
    int withEbola = 0;
    for(int i = 0; i < bats.size(); ++i)
        if(bats[i].withEbola) ++withEbola;
    
    float p = (float)withEbola / totol;
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




