#pragma once
#include <iostream>
#include <vector>
#include "examen.h"
#include "tipuriExamen.h"
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
        int index_materie = rand() % materii_disponibile.size();
        std::string materie = materii_disponibile[index_materie];
        int tip_examen = rand() % 3;
        switch(tip_examen) {
            case 0:
                std::cout << "[!!!] Se pregateste un examen SCRIS la " << materie << "!\n";
                return new ExamenScris(materie);
            case 1:
                std::cout << "[!!!] Se pregateste un examen ORAL la " << materie << "!\n";
                return new ExamenOral(materie);
            case 2:
                std::cout << "[!!!] Se pregateste un examen GRILA la " << materie << "!\n";
                return new ExamenGrila(materie);
            default:
                return new ExamenScris(materie); 
        }
    }
};