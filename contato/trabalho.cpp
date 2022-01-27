#include <iostream>
#include "contato.hpp"

using namespace std;

int main() {
    Contato edu("Eduardo", {});
    edu.add_fone(make_shared<Fone>("Casa", "(88)5252525"));
    edu.add_fone(make_shared<Fone>("Celular", "(88)40028922"));

    Contato sena("Sena", {});
    sena.add_fone(make_shared<Fone>("Casa", "(88)12345"));
    sena.add_fone(make_shared<Fone>("Celular", "(88)09876"));

    cout << edu << endl;
    cout << sena << endl;
}