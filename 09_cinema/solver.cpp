#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

class Cliente {
public:
    string id;
    string telefone;

    Cliente(string id = "", string telefone = "") :
    id{id}, telefone{telefone} {}

    string getId() {
        return this->id;
    }

    string getTelefone() {
        return this->telefone;
    }

    void setId(string id) {
        this->id;
    }

    void setTelefone(string telefone) {
        this->telefone;
    }

    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << "Id: " << cliente.id << ", Telefone: " << cliente.telefone << endl;
        return os;
    }
};

class Sala{
    vector<shared_ptr<Cliente>> cadeiras;
    list<shared_ptr<Cliente>> fila;

public:
    Sala(int qtdCadeiras) :
    cadeiras(qtdCadeiras, nullptr){}

    void entrar(const shared_ptr<Cliente>& cliente) {
        this->fila.push_back(cliente);
    }
    
    bool reservarCadeira(int indice) {
        if (indice < 0 || indice >= this->cadeiras.size()) {
            cout << "CINEMA FECHADO!!!\n";
            return false;
        }

        if (this->cadeiras[indice] != nullptr) {
            cout << "CADEIRA RESERVADA!!!\n";
            return false;
        }
        
        if (this->fila.empty()) {
            cout << "FILA VAZIA!!!\n";
            return false;
        }

        this->cadeiras[indice] = this->fila.front();
        this->fila.pop_front();

        return true;
    }

    bool finalizarSessao(int indice) {
        if (indice < 0 || indice >= this->cadeiras.size()) {
            cout << "CINEMA FECHADO!!!\n";
            return false;
        }

        if (this->cadeiras[indice] == nullptr) {
            cout << "CADEIRA VAZIA!!!\n";
            return false;
        }

        this->cadeiras[indice] = nullptr;

        return true;
    }    

    bool cancelar(string indice) {
        for (int i = 0; i < this->cadeiras.size(); i++) {
            if (this->cadeiras[i] != nullptr && this->cadeiras[i]->getId() == indice) {
                this->cadeiras[i] = nullptr;
                return true;
            }
        }

        return false;
    }

    friend ostream& operator<<(ostream& os, const Sala& s) {
        os << endl << "----- CADEIRAS -----" << endl;
        for (int i = 0; i < (int) s.cadeiras.size(); i++) {
            auto& cadeira = s.cadeiras[i];
            os << i << " : " ;

            if (cadeira != nullptr) {
                os << *cadeira;
            } else {
                os << "-----";
                os << " ||| ";    
            }
        }

        os << "\n\nFILA: " << endl;

        for (auto fila : s.fila) {
            os << *fila << " ";
        }

        return os;
    }
};

int main () {
    Sala sala(4);
    sala.entrar(make_shared<Cliente>("Eduardo", "3453"));
    sala.entrar(make_shared<Cliente>("Sena", "3213"));
    sala.entrar(make_shared<Cliente>("Oliveira", "1122"));
    sala.entrar(make_shared<Cliente>("David", "1098"));

    sala.reservarCadeira(0);
    sala.reservarCadeira(1);
    sala.reservarCadeira(0);
    sala.reservarCadeira(1);

    sala.cancelar("David");

    sala.finalizarSessao(1);
    
    cout << sala << endl;

    return 0;
}