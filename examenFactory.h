#pragma once
#include <iostream>
#include <vector>
#include "examen.h"
#include "tipuriExamen.h"
#include "tipuriProfesor.h"
#include "profesor.h"
class ExamenFactory {
private:
    static inline std::vector<std::string> materii_disponibile = {
        "Programare Orientata pe Obiecte", 
        "Structuri de Date", 
        "Analiza Matematica", 
        "Arhitectura Sistemelor de Calcul",
        "Logica Matematica"
    };
public:
    static Examen* genereazaExamenAleatoriu() {
        Profesor* p;
        if(rand() % 2 == 0) {
            p = new ProfesorExigent("Ionescu");
        }
        else {
            p = new ProfesorRelaxat("Popescu");
        }
        int index_materie = rand() % materii_disponibile.size();
        std::string materie = materii_disponibile[index_materie];
        int tip_examen = rand() % 3;
        switch(tip_examen) {
            case 0:
                std::cout << YELLOW << "[!!!] Se pregateste un examen SCRIS la " << materie << "cu prof. " << p->getTitluComplet() << "!\n" << RESET;
                return new ExamenScris(materie, p);
            case 1:
                std::cout << YELLOW << "[!!!] Se pregateste un examen ORAL la " << materie << "cu prof. " << p->getTitluComplet() << "!\n" << RESET;
                return new ExamenOral(materie, p);
            case 2:
                std::cout << YELLOW << "[!!!] Se pregateste un examen GRILA la " << materie << "cu prof. " << p->getTitluComplet() << "!\n" << RESET;
                return new ExamenGrila(materie, p);
            default:
                return new ExamenScris(materie, p); 
        }
    }
};