#pragma once

#include <sstream>
#include <stdexcept>

using namespace std;

class Fone {
private:
    string id;
    string numero;

public:
    Fone(string id, string numero) {
        this->id = id;
        this->numero = numero;
    }

    friend ostream& operator<<(ostream &os, const Fone &fone) {
        os << fone.id << ":" << fone.numero;
        return os;
    }

    string get_id() const {
        return id;
    }

    void set_id(string id) {
        id = id;
    }

    string get_numero() const {
        return numero;
    }

    void set_numero(string numero) {
        numero = numero;
    }

    static bool validate(string numero) {
        for (const auto &n : numero) {
            if ((n != ' (' && n != ') ') && (n > '9' || n < '0')) {
                return false;
            }
        }

        return true;
    }
};