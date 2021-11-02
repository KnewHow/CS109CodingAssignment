#include <iostream>
#include <random>
#include <stdio.h>

inline int get_random_int(int begin, int end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(begin, end);
    return dist(rng);
}

int main(int, char**) {
    int begin = 1, end = 101;
    int n = 100000;
    int secondWinTimes = 0;
    for(int i = 0; i < n; ++i) {
        int x, y;
        int s = 0;
        while(true) {
            int random = get_random_int(begin, end);
            s += random;
            if(s > 100) {
                x = random;
                break;
            }
        }
        s = 0;
        while(true) {
            int random = get_random_int(begin, end);
            s += random;
            if(s > 200) {
                y = random;
                break;
            }
        }
        if(y > x) ++secondWinTimes;
    }
    float probabilityY = (float)secondWinTimes / n;
    std::cout.precision(3);
    std::cout << "Second win probability is: " << probabilityY << std::endl;
}
