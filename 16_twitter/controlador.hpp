#pragma once

#include <iostream>
#include <map>
#include "usuario.hpp"

using namespace std;

class Controlador {
private:
    int next;
    map<string, shared_ptr<Usuario>> usuarios;
    map<int, shared_ptr<Mensagem>> tweets;

    shared_ptr<Mensagem> criarTweet(string nome, string mensagem) {
        auto tweet = make_shared<Mensagem>(next, nome, mensagem);
        this->tweets[next] = tweet;
        next++;

        return tweet;
    }

public:
    Controlador() : next{0} {}

    shared_ptr<Usuario> getUsuario(string nome) const {
        auto i = this->usuarios.find(nome);

        if (i != usuarios.end()) {
            return i->second;
        }

        throw TweetException("Usuario nao cadastrado!!!");
    }

    void addUsuario(string nome) {
        auto i = usuarios.find(nome);

        if (i != usuarios.end()) {
            throw TweetException("Usuario ja cadastrado!!!");
        }

        cout << nome << " cadastrado com sucesso!!!" << endl;
        auto usuario = make_shared<Usuario>(nome);
        this->usuarios[nome] = usuario;
    }

    void removerUsuario(string nome) {
        auto i = usuarios.find(nome);

        if (i != usuarios.end()) {
            i->second->deletar();
            this->usuarios.erase(nome);
            cout << nome << " removido com sucesso!!!" << endl;
            return;
        }

        throw TweetException("Impossivel remover, Usuario nao cadastrado!!!");
    }

    void twetar(string nome, string mensagem) {
        this->getUsuario(nome)->tweetar(criarTweet(nome, mensagem));
    }

    void twetar(string nome, int tweetId, string mensagem) {
        auto usuario = this->getUsuario(nome);
        auto tweetOriginal = usuario->getInbox().getMensagem(tweetId);
        auto retweet = criarTweet(nome, mensagem);

        retweet->setRetweet(tweetOriginal);
        this->getUsuario(nome)->tweetar(retweet);
    }

    friend ostream& operator<<(ostream& os, const Controlador& controlador) {
        
        for (auto usuario : controlador.usuarios) {
            os << *usuario.second;
        }

        return os;
    }
};