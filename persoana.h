#pragma once
#include <iostream>
#include <string>
class Persoana {
protected:
    std::string nume;
    int nivel_energie;
    int rezistenta_stres;
public:
    Persoana(std::string nume, int energie, int stres);
    virtual void afiseaza_status() const = 0;
    virtual ~Persoana() {}
};