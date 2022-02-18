#pragma once

#include <iostream>
#include <memory>
#include <set>

using namespace std;

class TweetException : public exception {
    string mensagem;

public:
    TweetException(const string& mensagem) : 
        mensagem(mensagem) {
    }
    const char* what() const noexcept override {
        return mensagem.c_str(); 
    }
};

class Mensagem {
private:
    int id;
    bool deletada;
    string mensagem;
    string remetente;
    set<string> likes;
    shared_ptr<Mensagem> retweet;

public:
    Mensagem(int id, string remetente, string msg) : id{id}, remetente{remetente}, mensagem{mensagem}, deletada{false}, retweet{nullptr} {}

    int getId() const {
        return this->id;
    }

    string getRemetente() const {
        return this->remetente;
    }

    bool getDeletada() const {
        return this->deletada;
    }

    void setDeletada() {
        this->deletada = true;
    }

    void setRetweet(shared_ptr<Mensagem> retweet) {
        this->retweet = retweet;
    }

    void like(string nome) {
        auto it = likes.find(nome);
        if (it == likes.end()) {
            likes.insert(nome);
        }
    }

    friend ostream& operator<<(ostream& os, const Mensagem& mensagem) {
        int tab = 0;
        auto* proximoRetweet = &mensagem;
        
        do {
            if (proximoRetweet->getDeletada()) {
                os << string(tab * 2, ' ') << " Esse tweet foi deletado!!!" << endl;
            }
            
            else {
                os << string(tab * 2, ' ') << proximoRetweet->id << " (" << proximoRetweet->remetente << ") - " << proximoRetweet->mensagem << " [ ";           
                for (auto& user : proximoRetweet->likes) {
                    os << user << ' ';
                }            
                os << "]" << endl;
            }

            proximoRetweet = proximoRetweet->retweet.get();
            tab++;

        } while (proximoRetweet != nullptr);

        return os;
    }
};