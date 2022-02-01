#include <iostream>
#include "cinema.hpp"

using namespace std;

int main() {
    Cinema cinema(2);

    cinema.reservar("Eduardo", "12345", 0);
    cinema.reservar("Sena", "67890", 1);
    cout << cinema << endl;

    cinema.cancelar("sena");

    cout << cinema << endl;

    return 0;
}