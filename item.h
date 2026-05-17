#pragma once
#include <iostream>
#include <string>
#include "student.h"
class Item {
    std::string nume;
public:
    Item(std::string nume) : nume(nume) {}
    virtual ~Item() {}
    virtual void foloseste(Student* s, int& dificultate_examen) = 0;
    std::string getNume() const {
        return nume;
    }
};

class SticlaApa : public Item {
public:
    SticlaApa() : Item("Sticla de Apa") {}
    void foloseste(Student* s, int& dificultate_examen) override {
        std::cout << "Ai baut o sticla de apa! Energia ta a crescut cu 5!\n";
        s->modificaEnergie(5);
    }
};

class Cafea : public Item {
public:
    Cafea() : Item("Cafea") {}
    void foloseste(Student* s, int& dificultate_examen) override {
        std::cout << "Ai baut o cafea! Energia ta a crescut cu 20!\n";
        s->modificaEnergie(20);
    }
};

class Copiuta : public Item {
public:
    Copiuta() : Item("Copiuta") {}
    void foloseste(Student* s, int& dificultate_examen) override {
        std::cout << "Momentul perfect sa folosesti o copiuta cinstita (-10 dificultate)!\n";
        dificultate_examen -= 10;
    }
};