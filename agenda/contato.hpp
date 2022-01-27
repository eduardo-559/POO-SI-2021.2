#pragma once

#include "fone.hpp"
#include <vector>

using namespace std;

class Contato{
protected:
    string prefixo = "-";

private:
    vector<Fone> fones;
    string nome;

    bool foneDuplicado(Fone fone) {
        for (int i = 0; i < (int) fones.size(); i++) {
            if ((fones[i].getId() == fone.getId()) && (fones[i].getNumero() == fone.getNumero())) {
                return true;
            }
        }

        return false;
    }

    bool validarIndice(int i) {
        if (i < 0 || i >= (int) fones.size()) {
            cout << "O Fone desejado nao existe!!!" << endl;
            return false;
        }

        return true;
    }

public:
    Contato(string nome = "") : nome{nome} {};

    friend ostream& operator<<(ostream& os, const Contato& contato) {
        os << contato.prefixo << " ";
        os << contato.nome << " ";

        for (int i = 0; i < (int) contato.fones.size(); i++) {
            auto fone = contato.fones[i];
            os << "| " << i << " - " ;
            os << fone << "| ";
        }

        return os;
    }

    bool addFone(Fone fone) {
        if (!fone.validar(fone.getNumero())) {
            return false;
        }
        
        if (foneDuplicado(fone) == true) {
            cout << "Fone  duplicado!!!" << endl;
            return false;
        }

        fones.push_back(fone);
        cout << "Fone adicionado com sucesso!!!" << endl;

        return true;
    }

    bool rmFone(int index){
        if(!validarIndice(index)){
            return false;
        }

        fones.erase(fones.begin() + index);
        cout << "Fone apagado com sucesso!!!" << endl;

        return true;
    }

    vector<Fone> getFones() {
        return fones;
    }

    string getNome() {
        return nome;
    }
};