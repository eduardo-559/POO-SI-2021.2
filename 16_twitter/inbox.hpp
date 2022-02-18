#pragma once

#include <iostream>
#include <map>
#include <memory>
#include "mensagem.hpp"

using namespace std;

class Inbox {
private:
    string nomeUsuario;
    map<int, shared_ptr<Mensagem>> timeLine;

public:
    Inbox() {}

    void setNome(string nomeUsuario) {
        this->nomeUsuario = nomeUsuario;
    }

    map<int, shared_ptr<Mensagem>>& getTimeLine() {
        return this->timeLine;
    }

    shared_ptr<Mensagem>& getMensagem(int Idtweet) {
        auto i = this->timeLine.find(Idtweet);

        if (i != this->timeLine.end()) {
            return i->second;
        }
    }

    void guardar(shared_ptr<Mensagem> tweet) {
        this->timeLine[tweet->getId()] = tweet;
    }

    void deletarApagadas(const vector<int>& idDeletados) {
        for (auto id : idDeletados) {
            this->timeLine.erase(id);
        }
    }

    friend ostream& operator<<(ostream& os, Inbox& inbox) {
        vector<int> idDeletados {};
        
        os << "Inbox do " << inbox.nomeUsuario << endl;

        for (auto i = inbox.timeLine.rbegin(); i != inbox.timeLine.rend(); i++) {
            if (i->second->getDeletada()) {
                idDeletados.push_back(i->second->getId());
            }

            else {
                os << *i->second;
            }
        }

        inbox.deletarApagadas(idDeletados);

        return os;
    }
};