#pragma once
#include <iostream>
#include <string>
#include "materie.h"
#include "student.h"
#include "ghiozdan.h"
#include "item.h"
#include "profesor.h"
class Examen {
protected:
    std::string nume;
    int dificultate;
    int stres_provocat;
    int credite;
    Profesor* profesor;
public:
    Examen(std::string nume, int dificultate, int stres_provocat, int credite, Profesor* p);
    virtual ~Examen();
    virtual void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) = 0;

    std::string getNume() const;
    int getDificultate() const;
    int getStresProvocat() const;
    int getCredite() const;

    void primesteRezolvare(int putere_student);
    bool estePromovat() const;
};