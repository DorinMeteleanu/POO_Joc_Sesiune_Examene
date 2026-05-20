#pragma once
#include "persoana.h"
#include "student.h"
#include "ui_util.h"
#include <iostream>

class Profesor : public Persoana {
protected:
    std::string titlu;
public:
    Profesor(std::string nume, int rabdare, int exigenta, std::string titlu);
    virtual void reactioneaza(Student* s);
    void puneNota(Student* s, int dificultate_ramasa);
    std::string getTitluComplet() const;
};