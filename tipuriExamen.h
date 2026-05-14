#pragma once
#include "examen.h"
class ExamenScris : public Examen {
public:
    ExamenScris(std::string materie);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;
};

class ExamenOral : public Examen {
public:
    ExamenOral(std::string materie);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;
};

class ExamenGrila : public Examen {
public:
    ExamenGrila(std::string materie);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;
};