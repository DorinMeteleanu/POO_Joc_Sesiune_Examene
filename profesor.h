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
    void afiseaza_status() const override;
    virtual void reactioneaza(Student* s);
    void puneNota(Student* s, int dificultate_ramasa);
    std::string getTitluComplet() const;
    virtual void reactioneaza(Student* s, int& dificultate) = 0;
    void exmatriculeaza(Student* s);

    int getRabdare() const;
    void scadeRabdare(int valoare);
    int getExigenta() const;
};