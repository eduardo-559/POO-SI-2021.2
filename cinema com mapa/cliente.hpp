#pragma once

#include <iostream>

using namespace std;

class Cliente {
private:
    string nome;
    string fone;

public:
    Cliente(string nome = "", string fone = "") : nome{nome}, fone{fone} {}

    string getNome() const {
        return this->nome;
    }

    string getFone() const {
        return this->fone;
    }

    void setNome(string str) {
        this->nome = str;
    }

    void setFone(string str) {
        this->fone = str;
    }

    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << "Cliente: " << cliente.getNome() << ", Fone: " << cliente.getFone();
        return os;
    }
};