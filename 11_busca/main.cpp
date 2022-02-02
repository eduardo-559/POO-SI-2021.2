#include <iostream>
#include "fone.hpp"
#include "contato.hpp"
#include "agenda.hpp"

using namespace std;

int main() 
{
    Agenda agenda;

    Contato edu{"Eduardo"};
    Contato sena{"Sena"};

    edu.addFone(Fone {"tim", "9988"});
    sena.addFone(Fone {"vivo", "9687"});

    agenda.addContato(edu);
    agenda.addContato(sena);

    cout << endl;
    sena.addFone(Fone {"vivo", "123abc"});
    cout << endl;

    cout << agenda << endl;

    agenda.rmContato("Eduardo");
    cout << endl;

    agenda.pesquisar("sena");
    
    cout << endl << agenda << endl;

    return 0;
}