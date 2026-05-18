#pragma once
#include "examen.h"
#include "examenFactory.h"
#include "item.h"
#include "student.h"
#include "ghiozdan.h"
class GameManager {
private:
    GameManager();
    static GameManager* instanta;
    Student* student;
    Ghiozdan<Item>* ghiozdan;

    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;
public:
    static GameManager* getInstanta();
    void pornesteJocul();
    void magazin();
    void sustineExamen();
    void afiseazaMeniu();

    void salveazaJoc();
    void incarcaJoc();
    ~GameManager();

};