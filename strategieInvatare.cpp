#include "strategieInvatare.h"
#include "ui_util.h"

void StrategieHardcore::aplicaStrategie(int ore, int& energie, int& stres, int& bonus) {
    energie -= ore*3;
    stres += ore*5;
    bonus += ore*4;
    std::cout << MAGENTA << "[STRATEGIE] Bagi tare! Ochi rosii, dar retii tot!\n" << RESET;
};

int StrategieHardcore::getCooldownValue() const{
    return 3;
};

void StrategieNormala::aplicaStrategie(int ore, int& energie, int& stres, int& bonus) {
    energie -= ore*2;
    stres += ore*3;
    bonus += ore*2;
    std::cout << MAGENTA << "[STRATEGIE] Ai invatat normal. Echilibrat.\n" << RESET;
};

int StrategieNormala::getCooldownValue() const{
    return 2;
};

void StrategieRelaxata::aplicaStrategie(int ore, int& energie, int& stres, int& bonus) {
    energie -= ore*1;
    stres += ore*1;
    bonus += ore/2;
    std::cout << "[STRATEGIE] Ai invatat cu muzica pe fundal. Ai gusturi ciudate. Mai mult te-ai relaxat.\n";
};

int StrategieRelaxata::getCooldownValue() const{
    return 1;
};

StrategieInvatare::~StrategieInvatare() {};