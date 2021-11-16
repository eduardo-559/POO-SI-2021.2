#include<iostream>
#include<vector>
#include<list>
#include<utility>
#include<memory>

using namespace std;

class kid{
public:
    string name;
    int age;

    kid(string name, int age) :
    name(name), age(age) {}
    
    friend ostream& operator<<(ostream& os, const kid& k) {
        os << k.name << " de " << k.age << " anos de idade";
        return os;
    }   
};

class pula_pula {
public:
    vector<shared_ptr <kid>> lugares;
    list<shared_ptr <kid>> espera;

    pula_pula(int qtd_lugares = 1) :
    lugares(qtd_lugares, nullptr) {}
        
    void entrar_fila_espera(const shared_ptr<kid>& k) {
        cout << *k << " entrou na fila de espera!" << endl;
        this->espera.push_back(k);
    }

    bool entrar_pula_pula(int vaga) {
        if(vaga < 0 || vaga >= this->lugares.size()) {
            cout << "Vaga inválida!!!" << endl;
            return false;
        }

        if(this->lugares[vaga] != nullptr) {
            cout << "Esta vaga está ocupada!" << endl;
            return false;
        }

        if(this->espera.empty()) {
            cout << "Fila de espera vazia!!!" << endl;
            return false;
        }

        cout << this->espera.front()->name << " entrou no Pula Pula!" << endl; 
        this->lugares[vaga] = this->espera.front();
        this->espera.pop_front();

        return true;
    }

    bool tirando_kid(int vaga) {
        if(vaga < 0 || vaga >= this->lugares.size()) {
            cout << "Nao existe essa vaga no Pula Pula!" << endl;
            return false;
        };

        if(this->lugares[vaga] == nullptr) {
            cout << "Essa vaga do Pula Pula esta vazia!!!" << endl;
            return false;
        };

        cout << this->lugares[vaga]->name << " saiu do Pula Pula!" << endl;
        this->espera.push_back(this->lugares[vaga]);
        this->lugares[vaga] = nullptr;

        return true;
    }

    void imprimir_lista_espera() {
        cout << endl << "----- LISTA DE ESPERA -----" << endl;

        for(auto& k: this->espera) {
            cout << *k << endl;
        }
    }

    void imprimir_pula_pula() {
        cout << endl << "\n----- PULA PULA -----" << endl;

        for(auto& k: this->lugares) {
            if(k != nullptr){
                cout << *k << endl;
            }
        }
    }
};

int main(){
    pula_pula pula(2);

    pula.entrar_fila_espera(make_shared<kid>("Eduardo", 9));
    pula.entrar_fila_espera(make_shared<kid>("Sena", 10));
    cout << endl;

    pula.entrar_pula_pula(0);
    cout << endl;

    pula.entrar_fila_espera(make_shared<kid>("David", 11));
    pula.entrar_fila_espera(make_shared<kid>("Oliveira", 14));
    cout << endl;

    pula.entrar_pula_pula(1);
    cout << endl;

    pula.tirando_kid(0);
    pula.tirando_kid(1);
    cout << endl;

    pula.entrar_pula_pula(0);
    pula.entrar_pula_pula(1);
    cout << endl;
    
    pula.imprimir_lista_espera();
    pula.imprimir_pula_pula();

    return 0;
}