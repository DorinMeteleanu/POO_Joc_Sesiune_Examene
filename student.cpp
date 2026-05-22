#include "student.h"
Student::Student(std::string nume, int energie, int stres, std::string specializare, int an_studiu, int credite, double media)
    : Persoana(nume, energie, stres), specializare(specializare), an_studiu(an_studiu), credite_acumulate(credite), media_generala(media), bani(50), bonus_pregatire(0), stres_curent(0) {
        strategie_curenta = new StrategieNormala();
    }
void Student::afiseaza_status() const {
    std::cout << "Student: " << nume << "\n";
    std::cout << "Nivel ENERGIE: " << nivel_energie << "/ 150\n";
    std::cout << "Nivel STRES: " << stres_curent << " / " << rezistenta_stres << "\n";
    std::cout << "Bani in portofel: " << bani << "\n";
    std::cout << "Bonus din pregatire: " << bonus_pregatire << "\n";
    std::cout << "=================================\n";
    std::cout << "Specializare: " << specializare << "\n";
    std::cout << "An studiu: " << an_studiu << "\n";
    std::cout << "CREDITE acumulate: " << credite_acumulate << "\n";
    std::cout << "Media generala: " << media_generala << "\n";
};

std::string Student::getNume() const {
    return nume;
};

std::string Student::getSpecializare() const {
    return specializare;
};
int Student::getAnStudiu() const {
    return an_studiu;
};

double Student::getMedieGenerala() const {
    return media_generala;
};
void Student::invata(int ore) {
        strategie_curenta->aplicaStrategie(ore, nivel_energie, stres_curent, bonus_pregatire);
        if (nivel_energie < 20) {
            std::cout << "\n[!] Ar fi o idee buna sa bea o cafelutza! Energia e foarte low\n";
        }
        if(stres_curent >= 23 && stres_curent < 25) {
            std::cout << "\n[!!] Atentie, nivelul de stres este foarte mare, trebuie sa te relaxezi inainte sa mai inveti iar singur si sa iei bonus\n";
        }
};
int Student::getEnergie() const {
    return nivel_energie;
};
void Student::modificaEnergie(int cantitate) {
    nivel_energie += cantitate;
    if (nivel_energie < 0) {
        nivel_energie = 0;
    }
};

int Student::getCredite() const {
    return credite_acumulate;
};

void Student::adaugaCredite(int n) {
    credite_acumulate += n;
};

int Student::getBani() const {
    return bani;
};

void Student::modificaBani(int cantitate) {
    bani += cantitate;
    if(bani < 0) {
        bani = 0;
    }
};

int Student::getBonus() const {
    return bonus_pregatire;
};

void Student::reseteazaBonus(int reducere) {
    bonus_pregatire -= reducere;
};

void Student::relaxare() {
    stres_curent -= 20;
    if(stres_curent < 0) {
        stres_curent = 0;
    }
    nivel_energie += 10;
    std::cout << "Relaxarea a avut efect, surprinzator. Stresul a scazut.\n";
};

int Student::getStresCurent() const {
    return stres_curent;
};

void Student::setStres(int s) {
    stres_curent = s;
};

void Student::setBani(int b) {
    bani = b;
};

void Student::setBonus(int b) {
    bonus_pregatire = b;
};

void Student::adaugaNota(int nota) {
    note_obtinute.push_back(nota);
    double suma = 0;
    for(int n : note_obtinute) {
        suma += n;
    }
    media_generala = suma/note_obtinute.size();
};

void Student::scadeCooldowns() {
    if(st_hardcore > 0) st_hardcore--;
    if(st_normal > 0) st_normal--;
    if(st_relaxat > 0) st_relaxat--;
};

void Student::setStrategie(StrategieInvatare* s) {
    if (strategie_curenta) delete strategie_curenta;
    strategie_curenta = s;
};

int Student::getSTHardcore() const {
    return st_hardcore;
};

int Student::getSTNormal() const {
    return st_normal;
};

int Student::getSTRelaxat() const {
    return st_relaxat;
};

void Student::setSTHardcore(int v) {
    st_hardcore = v;
}; 

void Student::setSTNormal(int v) {
    st_normal = v;
}; 

void Student::setSTRelaxat(int v) {
    st_relaxat = v;
}; 


