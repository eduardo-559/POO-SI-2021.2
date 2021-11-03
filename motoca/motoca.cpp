#include <iostream>
#include <algorithm>

using namespace std;

struct Pessoa {
    string nome {};
    int idade {};

    Pessoa(string nome = "?", int idade = 0) :
        nome (nome), idade (idade) {}
};

struct Moto {
    Pessoa* pessoa {nullptr};
    int potencia {0};
    int tempo {0};
    bool tem_alguem {false};

    Moto(int potencia = 1) :
        potencia (potencia) {}

    void dados_moto() {
        cout << "\n----- Moto sendo inicializada -----" << endl;
        cout << "Potencia: " << potencia << endl;
        cout << "Minutos restantes: " << tempo << endl;
        cout << "Tem pessoa: " << (tem_alguem ? "Nao" : "Sim");
    }
    
    void comprar_tempo(int tempo) {
        this->tempo = tempo;
        cout << endl << "Tempo comprado com sucesso!!!" << endl;
    }
    
    void descer() {   
        if(tem_alguem) {
            tem_alguem = false;
            cout << pessoa->nome << " desceu da moto!" << endl;
            pessoa = nullptr;
        }
    }
    
    void subir(Pessoa* pessoa) {
        if (!tem_alguem) {
            this->pessoa = pessoa;
            tem_alguem = true;
            cout << "\n" << this->pessoa->nome << " subiu na moto!" << endl;
        }
    }

    void dirigir(int tempo) {
        if (tem_alguem == true) {
            if (pessoa->idade <= 10 && tempo > 0) {
                cout << pessoa->nome << " esta dirigindo agora!\n" << endl;
                if (tempo > this->tempo) {
                    cout << "O tempo acabou. Você andou por " << this->tempo << " minutos!" << endl;
                    this->tempo = 0;
                } else if (tempo < this->tempo) {
                    cout << "O tempo acabou. Voce andou por " << tempo << " minutos!" << endl;
                    cout << "Ainda ha " << (this->tempo - tempo) << " minutos sobrando!" << endl;
                } else if(tempo == this->tempo) {
                    cout << "O tempo acabou. Você andou por " << tempo << " minutos!" << endl;
                }
            } else if (pessoa->idade <= 10 && tempo <= 0) {
                cout << "Desculpe, moto sem tempo!" << endl;
                descer();
            } else if(pessoa->idade > 10) {
                cout << "Idade de " << pessoa->nome << " fora de faixa etaria!" << endl;
                descer();
            }
        }
    }

    void buzinar() {
        if (tem_alguem == true) {
            cout << pessoa->nome << " esta buzinando!";
        } else {
            cout << "\nSem ninguem para buzinar a moto!" << endl;
        }
    }
};

int main() {
    Pessoa p1("Eduardo", 18);
    Pessoa p2("Sena", 7);

    Moto m1(1);
    Moto m2(2);

    m1.dados_moto();
    m1.comprar_tempo(20);
    m1.subir(&p1);
    m1.dirigir(25);
    m1.buzinar();

    m2.dados_moto();
    m2.comprar_tempo(30);
    m2.subir(&p2);
    m2.dirigir(5);
    m2.buzinar();
        
    return 0;
}
