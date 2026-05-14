#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Ghiozdan {
private:
    std::vector<T> elemente;
    int capacitate_maxima;
public:
    Ghiozdan(int capacitate) : capacitate_maxima(capacitate) {}
    void adauga(const T* element) {
        if (elemente.size() < capacitate_maxima) {
            elemente.push_back(*element);
        } else {
            throw std::overflow_error("Ghiozdanul este plin!");
        }
    }
    int getNrElemente() const {
        return elemente.size();
    }
    void afiseazaElemente() const {
        if(elemente.empty()) {
            std::cout << "Ghiozdanul este gol!" << std::endl;
            return;
        }
        for (const auto& element : elemente) {
            std::cout << element << std::endl;
        }
    }
    T* getElement(int index) {
        if(index < 0 || index >= elemente.size()) {
            throw std::out_of_range("Index invalid!");
        }
        T* element_ales = elemente[index];
        elemente.erase(elemente.begin() + index);
        return element_ales;
    }
    bool esteGol() const {
        return elemente.empty();
    }
};