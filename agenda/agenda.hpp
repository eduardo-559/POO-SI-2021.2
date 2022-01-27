#pragma once

#include <algorithm>
#include <sstream>
#include "contato.hpp"

using namespace std;

template <typename T>
string to_string(T t) {
    stringstream ss;
    ss << t;

    return ss.str();
}

class Agenda{
public:
    Agenda(){};
    vector<Contato> contatos;

    int findPos(string nome) {
        for (int i = 0; i < (int) contatos.size(); i++) {
            if (contatos[i].getNome() == nome) {
                return i;
            }
        }

        return -1;
    }

    Contato* getContato(string nome) {
        if (!findPos(nome)) {
            return nullptr;
        }

        return &contatos[findPos(nome)];
    }

    friend ostream& operator<<(ostream& os, const Agenda& agenda) {
        if ((int) agenda.contatos.size() == 0) {
            os << "A agenda vazia!!!";
        } else {
            for (int i = 0; i < (int) agenda.contatos.size(); i++) {
                auto contatos = agenda.contatos[i];
                os << i << ":" ;
                os << contatos << endl;
            }
        }
        
        return os;
    }

    void addContato(Contato contato) {
        if (findPos(contato.getNome()) == -1) {
            contatos.push_back(contato);

            sort(contatos.begin(), contatos.end(), [] (auto a, auto b){ 
                return a.getNome() < b.getNome();
            });
            
            return;
        }
        
        int pos = findPos(contato.getNome());
        vector<Fone> fones = contato.getFones();

        for (int i = 0; i < (int) fones.size(); i++) {
            contatos[pos].addFone(fones[i]);
        }
    }

    void rmContato(string nome) {
        int pos = findPos(nome);

        if (pos != -1) {
            contatos.erase(contatos.begin() + pos);
            cout << "Contato apagado com sucesso!!!" << endl;

            return;
        }
        cout << "Contato solicitado nao existe!!!" << endl;

        return;
    }

    vector<Contato> pesquisar(string item){
        vector<Contato> encontrado;

        for (auto contato : this->contatos) {
            auto texto = to_string(contato);

            if (texto.find(item) == string::npos) {
                encontrado.push_back(contato);
            }
        }

        if ((int)encontrado.size() == 0) {
            cout << "Nenhum contato foi encontrado!!!" << endl;
        } else {
            for (int i = 0; i < (int) encontrado.size(); i++) {
                cout << "Contatos de acordo com a pesquisa: " << endl;
            }
        }

        return encontrado;
    }
};