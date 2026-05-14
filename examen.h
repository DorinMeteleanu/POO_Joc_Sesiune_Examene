#pragma once
#include <iostream>
#include <string>
#include "materie.h"
#include "student.h"
class Examen {
private:
    std::string nume;
    int dificultate;
    int stres_provocat;
    int credite;
public:
    Examen(std::string nume, int dificultate, int stres_provocat, int credite);
    virtual ~Examen();
    virtual void sustineExamen(Student* student) = 0;

    std::string getNume() const;
    int getDificultate() const;
    int getStresProvocat() const;
    int getCredite() const;

    void primesteRezolvare(int putere_student);
    bool estePromovat() const;
};