#include <iostream>
#include <vector>
#include <string>
#include "persoana.h"
class Student : public Persoana {
private:
    std::string specializare;
    int an_studiu;
    int credite_acumulate;
    double media_generala;
public:
    Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media);
    void afiseaza_status() const override;
    void invata(int ore);
    ~Student() {}
};