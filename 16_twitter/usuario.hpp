#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "inbox.hpp"

using namespace std;

class Usuario : public enable_shared_from_this<Usuario> {
private:
    Inbox inbox;
    string nome;
    map<string, shared_ptr<Usuario>> seguidores;
    map<string, shared_ptr<Usuario>> seguindo;

public:
    Usuario(string nome) : nome{nome} {
        this->inbox.setNome(nome);
    }

    Inbox& getInbox() {
        return this->inbox;
    }

    string getNome() const {
        return this->nome;
    }

    map<string, shared_ptr<Usuario>>& getSeguidores() {
        return this->seguidores;
    }

    map<string, shared_ptr<Usuario>>& getSeguindo() {
        return this->seguindo;
    }

    void follow(shared_ptr<Usuario> usuario) {
        if (usuario == nullptr) {
            throw TweetException("Impossivel seguir, Usuario nao cadastrado!!!");
        }
        
        if (usuario->getNome() == this->nome) {
            throw TweetException("Voce não pode seguir a si mesmo!!!");
        }

        auto i = this->seguindo.find(usuario->getNome());

        if (i != this->seguindo.end()) {
            throw TweetException("Impossivel concluir essa acao, usuario ja seguido!!!");
        }

        cout << this->nome << " esta seguindo " << usuario->getNome() << "!!!" << endl;

        this->seguindo[usuario->getNome()] = usuario;
        usuario->seguidores[this->nome] = shared_from_this();
    }

    void unfollow(shared_ptr<Usuario> usuario) {
        if (usuario == nullptr) {
            throw TweetException("Usuario nao cadastrado!!!");
        }
        
        if (usuario->getNome() == this->nome) {
            throw TweetException("Impossivel realizar essa acao!!!");
        }

        auto it = this->seguindo.find(usuario->getNome());

        if (it == this->seguindo.end()) {
            throw TweetException("Impossivel concluir essa acao, usuarios nao se seguem!!!");
        }

        cout << this->nome << " parou de seguir " << usuario->getNome() << "!!!" << endl;

        for (auto [id, Mensagem] : this->inbox.getTimeLine()) {
            if (Mensagem->getRemetente() == usuario->getNome()) {
                this->inbox.getTimeLine().erase(id);
            }
        }

        this->seguindo.erase(usuario->getNome());
        usuario->seguidores.erase(this->nome);
    }

    void like(int Idtweet) {
        auto timeLine = inbox.getTimeLine();
        auto i = timeLine.find(Idtweet);

        if (i != timeLine.end()) {
            i->second->like(this->nome);
            return;
        }

        throw TweetException("Tweet nao encontrado!!!");
    }

    void tweetar(shared_ptr<Mensagem> tweet) {
        this->inbox.guardar(tweet);
        
        for (auto seguidor : this->seguidores) {
            seguidor.second->inbox.guardar(tweet);
        }

    }

    void deletar() {
        auto timeLine = this->inbox.getTimeLine();

        for (auto [id, mensagem] : timeLine) {
            if (mensagem->getRemetente() == this->nome) {
                mensagem->setDeletada();
            }
        }

        for (auto& seguidor : seguidores) {
            auto& seguindo = seguidor.second->getSeguindo();
            auto& seguindores = seguidor.second->getSeguidores();

            seguindores.erase(this->nome); 
            seguindo.erase(this->nome);      
        }
    }

    friend ostream& operator<<(ostream& os, const Usuario& usuario) {
        os << usuario.getNome() << endl;
        
        os << "\t seguidores: [ ";
        for (auto [nome, user] : usuario.seguidores) {
            os << nome << ' ';
        }

        os << "] " << endl << "\t seguindo  : [ ";
        for (auto [nome, user] : usuario.seguindo) {
            os << nome << ' ';
        }        
        os << "]" << endl;

        return os;
    }
};