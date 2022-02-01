#include <iostream>

using namespace std;

class veiculo {
private:
    string tipo;
    string marca;

public:
    int roda;
    int velocidade;

    veiculo(string tipo, string marca, int velocidade, int roda) :
        tipo(tipo), marca(marca), velocidade(velocidade), roda(roda) {
            cout << " Veiculo criado e da marca " << marca << endl;
        }

    virtual ~veiculo() {
        cout << tipo << " destruido com sucesso!!!" << endl << endl;
    }

    virtual void setTipo(string tipo) {
        tipo = tipo;
    }

    virtual string getTipo() {
        return tipo;
    }

    virtual void setMarca(string marca) {
        marca = marca;
    }

    virtual string getMarca() {
        return marca;
    }

    virtual void setVelocidade(int velocidade) {
        velocidade = velocidade;
    }

    virtual int getVelocidade() {
        return velocidade;
    }

    virtual void setRoda(int roda) {
        roda = roda;
    }

    virtual int getRoda() {
        return roda;
    }

    friend ostream& operator<<(ostream& os, veiculo& veiculo) {
        os << "Tipo: " << veiculo.getTipo() << " , " << "marca: " << veiculo.getMarca() << " , " << "velocidade: " << veiculo.getVelocidade() << " e " << "roda: " << veiculo.getRoda() << endl;
        return os;
    }
};

class carro : public veiculo{
    string placa;
    string marcaCarro;

public:
    bool numPortas{true};

    carro(string tipo, string marca, int velocidade, int roda, string placa, string marcaCarro) :
        veiculo(tipo, marca, velocidade, roda), placa(placa), marcaCarro(marcaCarro) {
        }

    virtual ~carro() {
        cout << "Veiculo da marca " << marcaCarro << " destruido!!!" << endl;
    }

    virtual bool getNumPortas() const{
        return numPortas;
    }

    virtual string getPlacaCarro() const{
        return placa;
    }

    virtual string getMarcaCarro() const{
        return marcaCarro;
    }

    friend ostream& operator<<(ostream& os, const carro& carro) {
        os << "Placa do veiculo: " << carro.getPlacaCarro() << " , " << "Marca do veicuo: " << carro.getMarcaCarro() << " , " << "Quantidade de portas: " << (carro.numPortas ? "Duas portas" : "Quatro portas");
        return os;
    }
};

class moto : public veiculo{
    string placa;
    string marcaMoto;

public:
    moto(string tipo, string marca, int velocidade, int roda, string placa, string marcaMoto) :
        veiculo(tipo, marca, velocidade, roda), placa(placa), marcaMoto(marcaMoto) {
        }

    virtual ~moto() {
        cout << "Veiculo da marca " << marcaMoto << " destruido!!!" << endl;
    }

    virtual string getPlacaMoto() const{
        return placa;
    }

    virtual string getMarcaMoto() const{
        return marcaMoto;
    }

    friend ostream& operator<<(ostream& os, const moto& moto) {
        os << "Placa do veiculo: " << moto.getPlacaMoto() << " , " << "Marca do veicuo: " << moto.getMarcaMoto() << endl;
        return os;
    }
};
