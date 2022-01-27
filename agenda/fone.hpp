#pragma once

#include <iostream>

using namespace std;

class Fone{
private:
    string id;
    string numero;

public: 
    Fone(string id = "", string numero = "") : id{id}, numero{numero} {};

    friend ostream& operator<<(ostream& os, const Fone& fone) {
        os << fone.id  << " " << fone.numero;
        return os;
    }

    static bool validar(string numero) {
        for (char c : numero) {
            if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '(' && c != ')') {
                cout << "O Fone esta invalido! Contem caracteres idesejados!!!" << endl;
                return false;
            }
        }

        cout << "Fone cadastrado com sucesso!!!" << endl;

        return true;
    }

    string getId() {
        return id;
    }

    string getNumero() {
        return numero;
    }
};