#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class Conta {
protected:
    float saldo{0};
    int idConta;
    string IdCliente; 
    string tipo{""};

public:
    Conta(string IdCliente = "", int idConta = -1) : IdCliente{IdCliente}, idConta{idConta} {}

    float getSaldo() {
        return saldo;
    }

    int getId() {
        return idConta;
    }

    string getTipo() {
        return tipo;
    }

    string getIdCliente() {
        return IdCliente;
    }

    virtual void atualizar() = 0;

    virtual void depositar(float valor) {
        if (valor > 0) {
            saldo += valor;
        }else {
            cout << "Impossível depositar um valor abaixo de zero!!!" << endl;
        }
    }

    virtual void sacar(float valor){
        if(valor > 0 && valor <= saldo) {
            saldo -= valor;
        }else {
            cout << "Impossível sacar um valor abaixo de zero!!!" << endl;
        }
    }
    
    virtual void transferir (shared_ptr<Conta> destino, float valor){  
        if(valor < 0){ 
            cout << "Impossível transferir um valor abaixo de zero!!!" << endl; 
        } else if (valor > saldo){
            cout << "Saldo insuficiente para fazer a transferencia!!!" << endl;
        } else{
            if(destino == nullptr){
                cout << "Destinatario invalido!!!" << endl;
            } else{
                saldo -= valor;
                destino->saldo += valor;

                cout << endl << "Transferencia realizada com sucesso para o cliente " << destino->getIdCliente() << ", no valor de R$"<< valor;
            }
        }
    }
    
    friend ostream& operator<<(ostream& os, const Conta& conta) {
        os << conta.idConta << " - " << "Nome: " << conta.IdCliente << ", Saldo: R$" << conta.saldo << ", Tipo: " << conta.tipo << endl;
        return os;
    }
};

class ContaCorrente : public Conta{
public:
    ContaCorrente(int id, string IdCliente) : Conta{IdCliente, id} {
        tipo = "Conta Corrente";
    };  

    virtual void atualizar(){
        saldo -= 20;
    }
};

class ContaPoupanca : public Conta{
public:
    ContaPoupanca(int id, string IdCliente) : Conta{IdCliente, id} {
        tipo = "Conta Poupanca";
    }
    
    virtual void atualizar(){
        saldo += saldo * 0.01;
    }
};

class Cliente{
private:
    string IdCliente;
    vector<shared_ptr<Conta>> contas;

public:
    Cliente(string IdCliente = " ") : IdCliente{IdCliente} {}
    
    void adicionarConta(shared_ptr<Conta> conta){
        contas.push_back(conta);
    } 

    vector<shared_ptr<Conta>> getContas(){
        return contas;
    }

    string getIdCliente(){
        return IdCliente;
    }

    void setIdCliente(string IdCliente){
        IdCliente = IdCliente;
    }
    
    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << cliente.IdCliente << "\n";

        for(auto conta : cliente.contas){
            os << *conta;
        }

        return os;
    }
};

class Banco{
private:
    int NextId{0};
    map<string, shared_ptr<Cliente>> clientes;
    map<int, shared_ptr<Conta>> contas;

    shared_ptr<Conta> getConta(int id){ 
        auto it = contas.find(id);

        if (it == contas.end()){
            cout << "Conta inexistente!!!" << endl;
        }

        return it->second;
    }

    bool procurarNome(string nome) {
        auto it = clientes.find(nome);

        if(it == clientes.end()){
            return false;

        }
        return true;
    }

    bool procurarId(int id) {
        auto it = contas.find(id);

        if(it == contas.end()){
            return false;
        }

        return true;
    }

public:
    Banco() {}

    void adicionarCliente(string nome){
        if(procurarNome(nome)){
            cout << "Nao e possivel adicionar o mesmo cliente duas vezes!!!" << endl;
        } else{
            Cliente cliente(nome);
            ContaCorrente cc(NextId, nome);
            ContaPoupanca cp(NextId, nome);
           
            cliente.adicionarConta(make_shared<ContaCorrente>(cc));
            cliente.adicionarConta(make_shared<ContaPoupanca>(cp));

            clientes[nome] = make_shared<Cliente>(cliente);
            contas[NextId] = make_shared<ContaCorrente>(cc);
            contas[NextId] = make_shared<ContaPoupanca>(cp);

            NextId++;
        }
    }

    void depositar(int id, float valor){
        if(procurarId(id)) {
            getConta(id)->depositar(valor);
        }else {
            cout << "Nao foi possivel realizar o deposito!!!" << endl;
        }
    }

    void sacar(int id, float valor){
        if(procurarId(id) && valor > 0) {
            getConta(id)->sacar(valor);
        }else {
            cout << "Nao foi possivel realizar o saque!!!" << endl;
        }
    }

    void transferir(int idOrigem, int idDestino, float valor){
        if(procurarId(idOrigem) && procurarId(idDestino) && valor > 0) {
            getConta(idOrigem)->transferir(getConta(idDestino), valor);
        }else {
            cout << "Nao foi possivel transferir!!!" << endl;
        }
    }

    void atualizarMensal() {
        for (auto conta : contas) {
            conta.second->atualizar();
        }
    }

    friend ostream& operator<<(ostream& os, Banco& banco) {
        os << endl << "Conta dos clientes: \n";

        for (auto conta : banco.contas) {
            os << *conta.second;
        }

        return os;
    }
};

int main(){
    Banco banco;

    banco.adicionarCliente("Eduardo");
    banco.adicionarCliente("Sena");

    banco.depositar(0, 10000);
    banco.depositar(1, 1550);

    cout << banco << endl;

    banco.sacar(0, 100);
    banco.sacar(1, 150);

    cout << banco;

    banco.transferir(1, 0, 340);
    banco.transferir(0, 1, 5000);

    cout << banco;

    return 0;
}