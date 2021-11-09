#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef SRC_BAT_H_
#define SRC_BAT_H_

#include <iostream>

class Bat {
public:
    Bat(bool first, bool second, bool third, bool fourth, bool fifth, bool withEbola)
        :first(first), second(second), third(third), fourth(fourth), fifth(fifth), withEbola(withEbola){}
    const bool first;
    const bool second;
    const bool third;
    const bool fourth;
    const bool fifth;
    const bool withEbola;

    bool operator[](int i) const {
        switch (i)
        {
        case 1:
            return first;
            break;
        case 2:
            return second;
            break;
        case 3:
            return third;
            break;
        case 4:
            return fourth;
            break;
        case 5:
            return fifth;
            break;
        default:
            std::cerr << "index must between in[1, 5], your index is: " << i <<", invalid!";
            exit(1);
            break;
        }
    }
};

#endif // PBRT_SRC_BAT_H_