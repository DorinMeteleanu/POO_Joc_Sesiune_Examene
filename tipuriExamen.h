#pragma once
#include "examen.h"
#include "ghiozdan.h"
#include "item.h"
#include "profesor.h"
#include "tipuriProfesor.h"
class ExamenScris : public Examen {
public:
    ExamenScris(std::string materie, Profesor* p);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;
};

class ExamenOral : public Examen {
public:
    ExamenOral(std::string materie, Profesor* p);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;
};

class ExamenGrila : public Examen {
public:
    ExamenGrila(std::string materie, Profesor* p);
    void sustineExamen(Student* student, Ghiozdan<Item>* ghiozdan) override;

};