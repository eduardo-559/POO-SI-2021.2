#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

bool existe(vector<int> fila, int x){
    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] == x)
            return true;
    }

    return false;
}

int contar(vector<int> fila, int x){
    int contador {0};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] == x)
            contador++;
    }

    return contador;
}

int procurar_valor(vector<int> fila, int x){
    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] == x)
            return i;
    }

    return -1;
}

int procurar_valor_apartir(vector<int> fila, int x, int inicio){
    for(int i = inicio; i < (int) fila.size(); i++){
        if(fila[i] == x)
            return i;
    }

    return -1;
}

int procura_menor(vector<int> fila){
    int menor {fila[0]};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < menor)
            menor = fila[i];
    }

    return menor;
}

int procurar_menor_pos(vector<int> fila){
    int menor {fila[0]}, posicao {0};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < menor){
            menor = fila[i];
            posicao = i;
        }
    }

    return posicao;
}

int procurar_menor_pos_apartir(vector<int> fila, int inicio){
    int menor {fila[inicio]}, posicao {inicio};

    for(int i = inicio; i < (int) fila.size(); i++){
        if(fila[i] < menor){
            menor = fila[i];
            posicao = i;
        }
    }

    return posicao;
}

int procurar_melhor_se(vector<int> fila){
    int menor {fila[0]}, homen_calmo {-1};

    for(int i = 0; i < (int) fila.size(); i++){
        if((fila[i] < menor) && fila[i] > 0){
            menor = fila[i];
            homen_calmo = i;
        }
    }

    return homen_calmo;
}

float calcular_stress_medio(vector<int> fila){
    float soma {0};
    for(int i = 0; i < (int) fila.size(); i++){
        soma += abs(fila[i]);
    }

    return soma / fila.size();
}

string mais_homens_ou_mulheres(vector<int> fila){
    int conta_homem {0}, conta_mulher {0};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] > 0)
            conta_homem++;
        else
            conta_mulher++;
    }

    if(conta_homem > conta_mulher)
        return "homens";
    
    if(conta_homem < conta_mulher)
        return "mulheres";
    
    return "empate";
}

string qual_metade_eh_mais_estressada(vector<int> fila){
    int soma_homem {0}, soma_mulher {0};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] > 0)
            soma_homem += fila[i];
        if(fila[i] < 0)
            soma_mulher += abs(fila[i]);
    }

    if(soma_homem > soma_mulher)
        return "homens";

    if(soma_homem < soma_mulher)
        return "mulheres";

    return "empate";
}

vector<int> clonar(const vector<int>& v){
    vector<int> novo_vetor {};

    for(int i = 0; i < (int) v.size(); i++){
        novo_vetor.push_back(v[i]);
    }

    return novo_vetor;
}

vector<int> pegar_homens(const vector<int>& v){
    vector<int> novo_vetor {};

    for(int i = 0; i < (int) v.size(); i++){
        if(v[i] > 0)
            novo_vetor.push_back(v[i]);
    }

    return novo_vetor;
}

vector<int> pegar_calmos(const vector<int>& v){
    vector<int> novo_vetor {};

    for(int i = 0; i < (int) v.size(); i++){
        if(abs(v[i]) < 10)
            novo_vetor.push_back(v[i]);
    }

    return novo_vetor;
}

vector<int> pegar_mulheres_calmas(const vector<int>& v){
    vector<int> novo_vetor {};

    for(int i = 0; i < (int) v.size(); i++){
        if(v[i] < 0 && v[i] >= -10)
            novo_vetor.push_back(v[i]);
    }

    return novo_vetor;
}

vector<int> inverter_com_copia(const vector<int>& v){
    vector<int> novo_vetor {};

    for(int i = 0; i < (int) v.size(); i++){
        novo_vetor.push_back(v[i] * (-1));
    }

    return novo_vetor;
}

void inverter_inplace(vector<int>& v){
    for(int i = 0; i < (int) v.size(); i++){
        v[i] *= (-1);
    }

    cout << endl;

    for(int i = 0; i < (int) v.size(); i++){
        cout << v[i] << " ";
    }
}

int sortear(const vector<int>& v){
    srand(time(NULL));
    return v[rand() % (v.size() - 1)];
}

void embaralhar(vector<int>& v){
    srand(time(NULL));
    for(size_t i{0}; i < v.size(); i++) {
        size_t random{rand() % (v.size() - 1)};
        int aux{v[i]};
        v[i] = v[random];
        v[random] = aux;
    }

    for(int i = 0; i < (int) v.size(); i++){
        cout << v[i] << " ";
    }
}

void ordenar(vector<int>& v){
    for(size_t i{0}; i < v.size(); i++){
        size_t indice_menor{i};
        for(size_t j{i + 1}; j < v.size(); ++j){
            if(v[j] < v[indice_menor]){
                indice_menor = j;
            }
        }
        int aux = v[i];
        v[i] = v[indice_menor];
        v[indice_menor] = aux;
    }

    cout << endl;

    for(int i = 0; i < (int) v.size(); i++){
        cout << v[i] << " ";
    }
}

vector<int> exclusivos(const vector<int>& vet){
    vector<int> aux;
    for(auto i : vet){
        if(!existe(aux, i)){
            aux.push_back(i);
        }
    }
    return aux;
}

vector<int> diferentes(const vector<int>& vet){
    vector<int> dif;
    for(auto i : vet){
        i = std::abs(i);
        if (!existe(dif, i)){
            dif.push_back(i);
        }
    }
    return dif;
}

vector<int> abandonados(const vector<int>& vet){
    vector<int> orfaos{vet};
    for (auto i : exclusivos(orfaos)){
        int indice {procurar_valor(orfaos, i)};

        if(indice != -1) {
            orfaos.erase(orfaos.begin() + indice);
        }
    }
    return orfaos;
}

int main(){
    vector <int> fila {5, 3, -1, -50, -1, -99};
    cout << existe(fila, 4) << endl;
    cout << contar(fila, 1) << endl;
    cout << procurar_valor(fila, 6) << endl;
    cout << procurar_valor_apartir(fila, 1, 2) << endl;
    cout << procura_menor(fila) << endl;
    cout << procurar_menor_pos(fila) << endl;
    cout << procurar_menor_pos_apartir(fila, 3) << endl;
    cout << procurar_melhor_se(fila) << endl;
    cout << calcular_stress_medio(fila) << endl;
    cout << mais_homens_ou_mulheres(fila) << endl;
    cout << qual_metade_eh_mais_estressada(fila) << endl;

    vector<int> novo_vetor = clonar(fila);
    for (int i = 0; i < (int) novo_vetor.size(); i++){
        cout << novo_vetor[i] << " ";
    }

    cout << endl;

    vector<int> vetor_homens = pegar_homens(fila);
    for (int i = 0; i < (int) vetor_homens.size(); i++){
        cout << vetor_homens[i] << " ";
    }

    cout << endl;

    vector<int> vetor_calmos = pegar_calmos(fila);
    for (int i = 0; i < (int) vetor_calmos.size(); i++){
        cout << fila[i] << " ";
    }

    cout << endl;

    vector<int> vetor_mulheres_calmas = pegar_mulheres_calmas(fila);
    for (int i = 0; i < (int) vetor_mulheres_calmas.size(); i++){
        cout << vetor_mulheres_calmas[i] << " ";
    }

    cout << endl;

    vector<int> inverter = inverter_com_copia(fila);
    for (int i = 0; i < (int) inverter.size(); i++){
        cout << inverter[i] << " ";
    }

    inverter_inplace(fila);

    cout << endl;

    cout << sortear(fila) << endl;

    embaralhar(fila);
    ordenar(fila);

    cout << endl;

    vector<int> unico = exclusivos(fila);
    for(int i = 0; i < (int) unico.size(); i++){
        cout << unico[i] << " ";
    }

    cout << endl;

    vector<int> difere = diferentes(fila);
    for(int i = 0; i < (int) difere.size(); i++){
        cout << difere[i] << " ";
    }

    cout << endl;

    vector<int> orfaos = abandonados(fila);
    for(int i = 0; i < (int) orfaos.size(); i++){
        cout << orfaos[i] << " ";
    }

    return 0;
}