#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "persoana.h"
#include "materie.h"
#include "gestiune.h"
class Student : public Persoana {
private:
    std::string specializare;
    int an_studiu;
    int credite_acumulate;
    double media_generala;
    Gestiune<Materie> cursuri_active;
    Gestiune<Item> resurse_studiu; //de creat clasa item mai tarziu
public:
    Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media);
    void afiseaza_status() const override;
    void invata(int ore);
    ~Student() {}
};