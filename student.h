#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "persoana.h"
#include "materie.h"
class Student : public Persoana {
private:
    std::string specializare;
    int an_studiu;
    int credite_acumulate;
    double media_generala;

    int bani;
    int bonus_pregatire;
    int stres_curent;
public:
    Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media);
    std::string getNume() const;
    std::string getSpecializare() const;
    int getAnStudiu() const;
    double getMedieGenerala() const;
    void afiseaza_status() const override;
    void invata(int ore);
    int getEnergie() const;
    int getCredite() const;
    void adaugaCredite(int n);
    void modificaEnergie(int cantitate);

    int getBani() const;
    void modificaBani(int cantitate);
    int getBonus() const;
    void reseteazaBonus(int reducere);
    void relaxare();
    int getStresCurent() const;

    void setStres(int s);
    void setBani(int b);
    void setBonus(int b);

    ~Student() {}
};