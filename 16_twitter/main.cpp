#include <iostream>
#include <map>
#include <memory>
#include "controlador.hpp"

using namespace std;

int main() {
    Controlador sistema; 

    while(true) {
        try {
            string acao {};
            cout << "Digite a acao escolhida: ";
            cin >> acao;
            cin.ignore();
            
            if (acao == "addUsuario") {
                string nome {};
                cout << "Digite o nome do usuario: ";
                cin >> nome;
                cin.ignore();
                sistema.addUsuario(nome);
            }
            
            else if (acao == "removerUsuario") {
                string nome {};
                cout << "Digite o nome do usuario a ser removido: ";
                cin >> nome;
                cin.ignore();
                sistema.removerUsuario(nome);
            }  
            
            else if (acao == "follow") {
                string seguir {}, seguido {};
                cout << "Nome de quem vai seguir: ";
                cin >> seguir;
                cin.ignore();
                cout << "Nome de quem vai ser seguido: ";
                cin >> seguido;
                cin.ignore();
                sistema.getUsuario(seguir)->follow(sistema.getUsuario(seguido));
            }
            
            else if (acao == "unfollow") {
                string seguir {}, seguido {};
                cout << "Nome de quem vai deixar de seguir: ";
                cin >> seguir;
                cin.ignore();
                cout << "Nome de quem vai deixar de ser seguido: ";
                cin >> seguido;
                cin.ignore();
                sistema.getUsuario(seguir)->unfollow(sistema.getUsuario(seguido));
            } 

            else if (acao == "postar") {
                string nome {}, mensagem {};
                cout << "Nome de quem vai postar algo: ";
                cin >> nome;
                cin.ignore();
                cout << "Postagem: ";
                getline(cin, mensagem);
                sistema.twetar(nome, mensagem);
            }

            else if (acao == "like") {
                string nome {};
                int id;
                cout << "Digite o nome de quem vai curtir: ";
                cin >> nome;
                cin.ignore();
                cout << "ID: ";
                cin >> id;
                cin.ignore();
                sistema.getUsuario(nome)->like(id);
            }

            else if (acao == "timeline") {
                string nome {};
                cout << "Nome do usuario: ";
                cin >> nome;
                cin.ignore();
                cout << sistema.getUsuario(nome)->getInbox();
            } 

            else if (acao == "retwetar") {
                string nome {}, mensagem {};
                int id {};
                cout << "Nome de quem vai retuitar: ";
                cin >> nome;
                cin.ignore();
                cout << "ID: ";
                cin >> id;
                cin.ignore();
                cout << "Mensagem: ";
                getline(cin, mensagem);
                sistema.twetar(nome, id, mensagem);            
            }

            else if (acao == "show") {
                cout << sistema << endl;
            }

            else if (acao == "clear") {
                #if defined(_WIN32) || defined(_WIN64)
                    system("cls");
                #else
                    system("clear");
                #endif
            } 
            
            else if (acao == "end") {
                break;
            } 

            else {
                cout << "Comando Invalido!!!" << '\n';
            }

        } catch(TweetException& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}