#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Ghiozdan {
private:
    std::vector<T*> elemente;
    int capacitate_maxima;
public:
    Ghiozdan(int capacitate) : capacitate_maxima(capacitate) {}
    void adauga(T* element) {
        if (elemente.size() < capacitate_maxima) {
            elemente.push_back(element);
        } else {
            delete element;
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
        for (size_t i = 0; i < elemente.size(); ++i) {
            std::cout << i << ": " << elemente[i]->getNume() << std::endl;
        }
    }
    T* getElement(int index) {
        if(index < 0 || index >= (int)(elemente.size())) {
            throw std::out_of_range("Index invalid!");
        }
        T* element_ales = elemente[index];
        elemente.erase(elemente.begin() + index);
        return element_ales;
    }
    bool esteGol() const {
        return elemente.empty();
    }
    ~Ghiozdan() {
        for (auto& element : elemente) {
            delete element;
        }
    }
};