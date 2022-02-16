#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <map>
using namespace std;

//-----------------------------------------------------------
// INTERFACES
//-----------------------------------------------------------

class IMedico;
class IPaciente {
public:
    virtual void addMedico(IMedico* medico) = 0;
    virtual void rmMedico(IMedico* medico) = 0;
    virtual string getDiagnostico() const = 0;
    virtual string getNome() const = 0;
    virtual map<string, IMedico*>& getMedicos() = 0;
};

class IMedico {
public:
    virtual void addPaciente(IPaciente* paciente) = 0;
    virtual void rmPaciente(IPaciente* paciente) = 0;
    virtual string getEspecialidade() const = 0;
    virtual string getNome() const = 0;
    virtual map<string, IPaciente*>& getPacientes() = 0;    
};

//-----------------------------------------------------------
// Medico
//-----------------------------------------------------------
class Medico : public IMedico {
private:
    string nome;
    string especialidade;
    map<string, IPaciente*> pacientes;

public:
    Medico(string nome, string especialidade)
    : nome{nome}, especialidade{especialidade} {}

    void addPaciente(IPaciente* paciente) override {
        this->pacientes[paciente->getNome()] = paciente;
    }

    void rmPaciente(IPaciente* paciente) override {
        this->pacientes.erase(paciente->getNome());
    }

    string getEspecialidade() const override {
        return this->especialidade;
    }

    string getNome() const override {
        return this->nome;
    }

    map<string, IPaciente*>& getPacientes() override {
        return this->pacientes;
    }

    friend ostream& operator<<(ostream& os, IMedico* med) {
        string inicio = "Med: " + med->getNome() + ":" + med->getEspecialidade();
        os << inicio;
        
        os << setw(40 - inicio.length()) << "Pacs: [ ";
        for (auto pacs : med->getPacientes()) {
            os << pacs.second->getNome() << ' ';
        }
        
        os << "]";
        return os;
    } 
};


//-----------------------------------------------------------
// Paciente
//-----------------------------------------------------------
class Paciente : public IPaciente {
private:
    string nome;
    string diagnostico;
    map<string, IMedico*> medicos;

public:
    Paciente(string nome, string diagnostico)
    : nome{nome}, diagnostico{diagnostico} {}

    virtual void addMedico(IMedico* medico) override {
        this->medicos[medico->getNome()] = medico;
    }

    virtual void rmMedico(IMedico* medico) override {
        this->medicos.erase(medico->getNome());
    }

    virtual string getDiagnostico() const override {
        return this->diagnostico;
    }

    virtual string getNome() const override {
        return this->nome;
    }

    virtual map<string, IMedico*>& getMedicos() override {
        return this->medicos;
    }

    friend ostream& operator<<(ostream& os, IPaciente* pac) {
        string inicio = "Pac: " + pac->getNome() + ":" + pac->getDiagnostico();
        os << inicio;

        os << setw(40 - inicio.length()) << "Meds: [ ";
        for (auto meds : pac->getMedicos()) {
            os << static_cast<Medico*>(meds.second)->getNome() << " ";
        }

        os << "]";
        return os;
    }
};


//-----------------------------------------------------------
// Hospital
//-----------------------------------------------------------
class HospitalException : public exception {
    string message;
public:
    HospitalException(const string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Hospital {
private:
    map<string, IPaciente*> pacientes;
    map<string, IMedico*> medicos;

public:
    Hospital() {}

    void addMedico(string nome, string especialidade) {
        auto it = this->medicos.find(nome);
        if (it == this->medicos.end()) {
            IMedico* med = new Medico(nome, especialidade);
            this->medicos[nome] = med;
            cout << "medico " << nome << " cadastrado\n";
            return;
        }

        throw HospitalException("erro: medico ja cadastrado");
    }

    void addPaciente(string nome, string diagnostico) {
        auto it = this->pacientes.find(nome);
        if (it == this->pacientes.end()) {
            IPaciente* pac = new Paciente(nome, diagnostico);
            this->pacientes[nome] = pac;
            cout << "paciente " << nome << " cadastrado\n";
            return;
        }

        throw HospitalException("erro: paciente ja cadastrado");
    }

    void vincular(string nome_m, string nome_p) {
        auto it_m = this->medicos.find(nome_m);
        auto it_p = this->pacientes.find(nome_p);

        if (it_m == this->medicos.end() && it_p == this->pacientes.end()) {
            throw HospitalException("erro: medico e paciente nao cadastrados");
            return;
        }

        if (it_m == this->medicos.end()) {
            throw HospitalException("erro: medico nao cadastrado");
            return;           
        }

        if (it_p == this->pacientes.end()) {
            throw HospitalException("erro: paciente nao cadastrado");
            return;           
        }

        auto lista_medicos = it_p->second->getMedicos();
        for (auto med : lista_medicos) {
            if (med.second->getEspecialidade() == it_m->second->getEspecialidade()) {
                throw HospitalException("erro: existe outro medico com a mesma especialidade para o paciente");
                return;
            }
        }

        it_p->second->addMedico(it_m->second);
        it_m->second->addPaciente(it_p->second);
        cout << "medico " << nome_m << " e paciente " << nome_p << " estao vinculados\n";
    }

    void removerPaciente(string nome) {
        auto it = this->pacientes.find(nome);
        if (it == this->pacientes.end()) {
            throw HospitalException("erro: paciente nao cadastrado");
            return;
        }

        for (auto med : it->second->getMedicos()) {
            med.second->getPacientes().erase(nome);
        }

        this->pacientes.erase(it);
        cout << "paciente " << nome << " removido do hospital\n";
    }

    void removerMedico(string nome) {
        auto it = this->medicos.find(nome);
        if (it == this->medicos.end()) {
            throw HospitalException("erro: medico nao cadastrado");
            return;
        }

        for (auto pac : it->second->getPacientes()) {
            pac.second->getMedicos().erase(nome);
        }

        this->medicos.erase(it);
        cout << "medico " << nome << " removido do hospital\n";
    }

    friend ostream& operator<<(ostream& os, Hospital& hosp) {
        os << "LISTA HOSPITAL: \n";
        for (auto pac : hosp.pacientes) {
            os << static_cast<Paciente*>(pac.second) << '\n';
        }

        for (auto med : hosp.medicos) {
            os << static_cast<Medico*>(med.second) << '\n';
        }

        return os;     
    }

};


int main() {
    Hospital hospital;
    
    while (true) {
        cout << '\n';
        string cmd {""};
        cin >> cmd;

        try {
            if (cmd == "addmed") {
                string nome, especialidade;
                cin >> nome >> especialidade;
                hospital.addMedico(nome, especialidade);
                continue;
            }

            if (cmd == "addpac") {
                string nome, diagnostico;
                cin >> nome >> diagnostico;
                hospital.addPaciente(nome, diagnostico);
                continue;
            }

            if (cmd == "vinc") {
                string nome_m, nome_p;
                cin >> nome_m >> nome_p;
                hospital.vincular(nome_m, nome_p);
                continue;
            }

            if (cmd == "rmmed") {
                string nome;
                cin >> nome;
                hospital.removerMedico(nome);
                continue;
            }

            if (cmd == "rmpac") {
                string nome;
                cin >> nome;
                hospital.removerPaciente(nome);            
                continue;
            }

            if (cmd == "show") {
                cout << hospital << '\n';            
                continue;
            }

            if (cmd == "clear") {
                #if defined(_WIN32) || defined(_WIN64)
                    system("cls");
                #else
                    system("clear");
                #endif
                continue;
            }

            if (cmd == "end") {
                exit(1);
            }

            else {
                cout << "Comando invalido\n";
                continue;
            }

        } catch(HospitalException& he) {
            cout << he.what() << '\n';
        }
    }

    return 0;
}