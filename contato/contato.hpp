#pragma once

#include <vector>
#include <memory>
#include "fone.hpp"

using namespace std;

class Contato {
private:
    string nome;
    vector<shared_ptr<Fone>> fones;

protected:
    string prefixo;

public:
    Contato(string nome, const vector<shared_ptr<Fone>> &fones) : nome {nome}, fones {fones}, prefixo {"-"} {}

    friend ostream& operator<<(ostream &os, const Contato &contato) {
        os << contato.prefixo << " " << contato.nome;
        
        for (const auto& fone : contato.fones) {
            os << " || " << *fone << " || ";
        }

        return os;
    }

    void add_fone(shared_ptr<Fone> fone) {
        fones.push_back(fone);
    }

    void rm_fone(int i) {
        fones.erase(fones.begin() + i);
    }

    const vector<shared_ptr<Fone>>& get_fones() const {
        return fones;
    }

    string get_nome() const {
        return nome;
    }

    void set_nome(string nome) {
        nome = nome;
    }
};