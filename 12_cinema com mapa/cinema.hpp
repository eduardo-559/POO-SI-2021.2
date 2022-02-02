#pragma once

#include <iostream>
#include <memory>
#include <map>
#include "cliente.hpp"

using namespace std;

class Cinema {
private:
    const int qtd_cadeiras;
    int sentados;
    map<int, shared_ptr<Cliente>> cadeiras;

public:
    Cinema(int qtd_cadeiras) : qtd_cadeiras{qtd_cadeiras}, sentados{0} {}

    void reservar(string nome, string telefone, int indice) {
        if (qtd_cadeiras == sentados) {
            cout << "Cinema lotado." << endl;
        }

        if (indice < 0 || indice >= qtd_cadeiras) {
            cout << "indice invalido." << endl;
        }

        for (auto& [indice, cliente] : cadeiras) {
            if (cliente != nullptr && cliente->getNome() == nome) {
                cout << nome << " ja esta no cinema." << endl;
            }
        }

        if (cadeiras[indice] != nullptr) {
            cout << "Cadeira ja esta ocupada." << endl;
            return;
        }

        auto cliente = make_shared<Cliente>(nome, telefone);
        cadeiras[indice] = cliente;

        cout << nome << " entrou no cinema." << endl;
        this->sentados++;
    }

    void cancelar(string nome) {
        for (auto& [indice, cliente] : cadeiras) {
            if (cliente->getNome() == nome) {
                cadeiras.erase(indice);
                cout << nome << " saiu do cinema." << endl;
            }
        }

        cout << nome << " nao esta no cinema.\n";
    }

    friend ostream& operator<<(ostream& os, const Cinema& cinema) {        
        for (int i = 0; i < cinema.qtd_cadeiras; i++) {
            auto it = cinema.cadeiras.find(i);

            if (it != cinema.cadeiras.end()) {
                os << "[" << it->first << ":" << it->second->getNome() << "] ";
            } else {
                os << "[- - - - -] ";
            }
        }
        
        return os;
    }
};