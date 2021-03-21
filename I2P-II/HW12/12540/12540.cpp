#include "function.h"

void IdiotSandwich::print(std::ostream &out) {
    out << "An idiot sandwich with intelligence level " << intelligence << " only.";
}


void NormalSandwich::print(std::ostream &out) {
    out << name << ". Masterpiece of sandwiches.";
}

std::istream & operator >> (std::istream &in, Dish &d) {
    std::string name;
    in >> name;
    if (name == "Ramsay") {
        int lvl;
        in >> lvl;
        d.food = new IdiotSandwich(lvl);
    } else {
        d.food = new NormalSandwich(name);
    }
    return in;
}

Dish::~Dish() {
    delete food;
}

