#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <locale>

using namespace std;

class IMedico;
class IPaciente {
public:
    virtual void addMedico(IMedico* medico) = 0;
    virtual void removerMedico(IMedico* medico) = 0;
    virtual string getDiagnostico() const = 0;
    virtual string getNome() const = 0;
    virtual map<string, IMedico*>& getMedicos() = 0;
};

class IMedico {
public:
    virtual void addPaciente(IPaciente* paciente) = 0;
    virtual void removerPaciente(IPaciente* paciente) = 0;
    virtual string getEspecialidade() const = 0;
    virtual string getNome() const = 0;
    virtual map<string, IPaciente*>& getPacientes() = 0;    
};

class Medico : public IMedico {
private:
    string nome;
    string especialidade;
    map<string, IPaciente*> pacientes;

public:
    Medico(string nome, string especialidade) : nome{nome}, especialidade{especialidade} {}

    void addPaciente(IPaciente* paciente) override {
        this->pacientes[paciente->getNome()] = paciente;
    }

    void removerPaciente(IPaciente* paciente) override {
        this->pacientes.erase(paciente->getNome());
    }

    string getNome() const override {
        return this->nome;
    }

    string getEspecialidade() const override {
        return this->especialidade;
    }

    map<string, IPaciente*>& getPacientes() override {
        return this->pacientes;
    }

    friend ostream& operator<<(ostream& os, IMedico* med) {
        string inicio = "Medico: " + med->getNome() + "|| Especialidade: " + med->getEspecialidade();
        os << inicio;
        
        os << setw(40 - inicio.length()) << "Pacientes: [ ";
        for (auto paciente : med->getPacientes()) {
            os << paciente.second->getNome() << ' ';
        }
        
        os << "]";
        return os;
    } 
};

class Paciente : public IPaciente {
private:
    string nome;
    string diagnostico;
    map<string, IMedico*> medicos;

public:
    Paciente(string nome, string diagnostico) : nome{nome}, diagnostico{diagnostico} {}

    virtual void addMedico(IMedico* medico) override {
        this->medicos[medico->getNome()] = medico;
    }

    virtual void removerMedico(IMedico* medico) override {
        this->medicos.erase(medico->getNome());
    }

    virtual string getNome() const override {
        return this->nome;
    }

    virtual string getDiagnostico() const override {
        return this->diagnostico;
    }

    virtual map<string, IMedico*>& getMedicos() override {
        return this->medicos;
    }

    friend ostream& operator<<(ostream& os, IPaciente* pac) {
        string inicio = "Paciente: " + pac->getNome() + " || Diagnostico: " + pac->getDiagnostico();
        os << inicio;

        os << setw(40 - inicio.length()) << "Medicos: [ ";
        for (auto medicos : pac->getMedicos()) {
            os << static_cast<Medico*>(medicos.second)->getNome() << " ";
        }

        os << "]";
        return os;
    }
};

class HospitalException : public exception {
    string erro;
public:
    HospitalException(const string& erro) : erro(erro) {}

    const char* what() const noexcept override {
        return erro.c_str(); 
    }
};

class Hospital {
private:
    map<string, IPaciente*> pacientes;
    map<string, IMedico*> medicos;

public:
    Hospital() {}

    void addMedico(string nome, string especialidade) {
        auto i = this->medicos.find(nome);

        if (i == this->medicos.end()) {
            IMedico* med = new Medico(nome, especialidade);
            this->medicos[nome] = med;

            cout << "Doutor " << nome << " cadastrado" << endl;

            return;
        }

        throw HospitalException("Medico ja se encontra cadastrado!!!");
    }

    void addPaciente(string nome, string diagnostico) {
        auto i = this->pacientes.find(nome);

        if (i == this->pacientes.end()) {
            IPaciente* pac = new Paciente(nome, diagnostico);
            this->pacientes[nome] = pac;

            cout << "Paciente " << nome << " cadastrado" << endl;

            return;
        }

        throw HospitalException("Paciente ja se encontra cadastrado!!!");
    }

    void vincular(string nomeMedico, string nomePaciente) {
        auto iMed = this->medicos.find(nomeMedico);
        auto iPac = this->pacientes.find(nomePaciente);

        if (iMed == this->medicos.end() && iPac == this->pacientes.end()) {
            throw HospitalException("Medico e Paciente nao cadastrados");
            return;
        }

        if (iMed == this->medicos.end()) {
            throw HospitalException("Medico nao cadastrado");
            return;           
        }

        if (iPac == this->pacientes.end()) {
            throw HospitalException("Paciente nao cadastrado");
            return;           
        }

        auto listaMedico = iPac->second->getMedicos();

        for (auto medico : listaMedico) {
            if (medico.second->getEspecialidade() == iMed->second->getEspecialidade()) {
                throw HospitalException("O paciente ja se encontra com outro medico com a mesma especialidade!!!");
                return;
            }
        }

        iPac->second->addMedico(iMed->second);
        iMed->second->addPaciente(iPac->second);

        cout << "Doutor " << nomeMedico << " e Paciente " << nomePaciente << " estao vinculados" << endl;
    }

    void removerPaciente(string nome) {
        auto i = this->pacientes.find(nome);

        if (i == this->pacientes.end()) {
            throw HospitalException("Paciente nao cadastrado!!!");
            return;
        }

        for (auto medico : i->second->getMedicos()) {
            medico.second->getPacientes().erase(nome);
        }

        this->pacientes.erase(i);

        cout << "Paciente " << nome << " removido do hospital" << endl;
    }

    void removerMedico(string nome) {
        auto i = this->medicos.find(nome);

        if (i == this->medicos.end()) {
            throw HospitalException("Medico nao cadastrado!!!");
            return;
        }

        for (auto paciente : i->second->getPacientes()) {
            paciente.second->getMedicos().erase(nome);
        }

        this->medicos.erase(i);

        cout << "Doutor " << nome << " removido do hospital" << endl;
    }

    friend ostream& operator<<(ostream& os, Hospital& hospital) {
        os << "LISTA HOSPITAL: " << endl;
        for (auto paciente : hospital.pacientes) {
            os << static_cast<Paciente*>(paciente.second) << endl;
        }

        cout << endl << "----------------------------" << endl;

        for (auto medico : hospital.medicos) {
            os << static_cast<Medico*>(medico.second) << endl;
        }

        return os;     
    }
};

int main() {
    Hospital hospital;
    
    while (true) {
        string acao {""};
        cout << "Digite a acao desejada: " << endl;
        cin >> acao;

        try {
            if (acao == "addMedico") {
                string nome, especialidade;

                cout << "Digite o nome do Medico: ";
                cin >> nome;

                cout << "Digite a especialidade: ";
                cin >> especialidade;

                hospital.addMedico(nome, especialidade);

                continue;
            }

            if (acao == "removerMedico") {
                string nome;

                cout << "Digite o nome do medico que deseja remover: ";
                cin >> nome;

                hospital.removerMedico(nome);

                continue;
            }

            if (acao == "addPaciente") {
                string nome, diagnostico;

                cout << "Digite o nome do paciente: ";
                cin >> nome;

                cout << "Digite o diagnostico do paciente: ";
                cin >> diagnostico;

                hospital.addPaciente(nome, diagnostico);

                continue;
            }

            if (acao == "removerPaciente") {
                string nome;

                cout << "Digite o nome do paciente que deseja remover: ";
                cin >> nome;

                hospital.removerPaciente(nome);    
                        
                continue;
            }

            if (acao == "vincular") {
                string nomeMedico, nomePaciente;

                cout << "Digite o nome do medico que deseja vincular ao paciente: ";
                cin >> nomeMedico;

                cout << "Digite o nome do paciente que deseja vincular ao medico: ";
                cin >> nomePaciente;

                hospital.vincular(nomeMedico, nomePaciente);

                continue;
            }

            if (acao == "show") {
                cout << hospital << endl;            
                continue;
            }

            if (acao == "clear") {
                #if defined(_WIN32) || defined(_WIN64)
                    system("cls");
                #else
                    system("clear");
                #endif
                continue;
            }

            if (acao == "end") {
                exit(1);
            }

            else {
                cout << "Comando invalido, digite o comando novamente: " << endl;
                continue;
            }

        } catch(HospitalException& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}