#include "profesor.h"
class ProfesorExigent : public Profesor {
public:
    ProfesorExigent(std::string n);
    void reactioneaza(Student* s, int& d) override;
};

class ProfesorRelaxat : public Profesor {
public:
    ProfesorRelaxat(std::string n);
    void reactioneaza(Student* s, int& d) override;
};
