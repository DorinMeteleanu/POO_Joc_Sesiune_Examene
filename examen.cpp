#include "examen.h"
Examen::Examen(std::string nume, int dificultate, int stres_provocat, int credite, Profesor* p)
    : nume(nume), dificultate(dificultate), stres_provocat(stres_provocat), credite(credite), profesor(p) {}
std::string Examen::getNume() const {
    return nume;
};
int Examen::getDificultate() const {
    return dificultate;
};
int Examen::getCredite() const {
    return credite;
};
int Examen::getStresProvocat() const {
    return stres_provocat;
};
void Examen::primesteRezolvare(int putere_student) {
    dificultate -= putere_student;
    if(dificultate < 0) {
        dificultate = 0;
    }
};
bool Examen::estePromovat() const {
    return dificultate == 0;
};

Examen::~Examen() {
    delete profesor;
};