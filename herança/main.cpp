#include <iostream>
#include "veiculo.hpp"

using namespace std;

int main() {
    carro carro("Carro", "AUDI", 300, 4, "jfl-9204", "AUDI");
    cout << carro << endl;

    cout << endl;

    moto moto("Moto", "HONDA", 125, 2, "rif-9813", "HONDA");
    cout << moto << endl;

    return 0;
}