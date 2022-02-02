#include <iostream>
#include <algorithm>

using namespace std;

struct Grafite {
    float calibre;
    string dureza;
    int tamanho;

    Grafite(float calibre = 0, string dureza = "", int tamanho = 0) : calibre{calibre}, dureza{dureza}, tamanho{tamanho} {}

    friend ostream& operator<<(ostream& os, const Grafite& grafite) {
        os << "Calibre: " << grafite.calibre << " mm, " << endl;
        os << "Dureza: " << grafite.dureza << ", " << endl;
        os << "Tamanho: " << grafite.tamanho << " mm" << endl;
        return os;
    }
};

struct Lapiseira {
    float calibre;
    Grafite* grafite;

    Lapiseira(float calibre, Grafite* grafite = nullptr) : calibre{calibre}, grafite{grafite} {}

    bool inserirGrafite(Grafite* grafite) {
        if(grafite != nullptr) {
            cout << "Ja tem grafite" << endl;
            return false;
        }

        if(grafite->calibre != this->calibre) {
            cout << "Calibre incompativel" << endl;
            return false;
        }

        grafite = grafite;

        return true;
    }
    
    Grafite* removerGrafite() {
        if (grafite != nullptr) {
            cout << "Nao tem grafite\n";
            return nullptr;
        }

        return exchange(grafite, nullptr);
    }
};

int main() {
    Grafite grafite(0.5, "HC", 10);
    Lapiseira lapiseira(0.5, &grafite);

    lapiseira.grafite->tamanho -= 5;

    cout << lapiseira.grafite->tamanho << endl;
    
    return 0;
}