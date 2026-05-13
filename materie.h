#pragma once
#include <iostream>
#include <string>
#include <vector>
class Materie {
private:
    std::string nume;
    int credite;
    int dificultate;
    int progres;
public:
    Materie(std::string nume, int credite, int dificultate, int progres);

};