#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Gestiune {
private:
    std::vector<T> elemente;
public:
    void adauga(const T& element) {
        elemente.push_back(element);
    }
    int getNrElemente() const {
        return elemente.size();
    }
    void afiseazaElemente() const {
        for (const auto& element : elemente) {
            std::cout << element << std::endl;
        }
    }
    T& getElement(int index) {
        if (index >= 0 && index < elemente.size()) {
            return elemente[index];
        } else {
            throw std::out_of_range("Index invalid");
        }
    }
};