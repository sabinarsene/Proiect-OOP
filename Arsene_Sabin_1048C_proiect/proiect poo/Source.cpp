#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <vector>

using namespace std;
void meniu();
class Exceptie
{
    string mesajExceptie;

public:
    Exceptie(string mesajExceptie)
    {
        this->mesajExceptie = mesajExceptie;
    }

    string getMesajExceptie()
    {
        return mesajExceptie;
    }
};

class Pacient
{
private:
    string CNP;
    char* nume;
    string nrTelefon;

public:
    Pacient()
    {
        CNP = " ";
        nume = new char[strlen("Anonim") + 1];
        strcpy(nume, "Anonim");
        nrTelefon = " ";
    }

    Pacient(string CNP, const char* nume, string nrTelefon)
    {
        this->CNP = CNP;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->nrTelefon = nrTelefon;
    }

    Pacient(const Pacient& p)
    {
        if (p.nume == NULL)
        {
            this->nume = nume;
        }
        else
        {
            this->nume = new char[strlen(p.nume) + 1];
            strcpy(nume, p.nume);
        }
        this->CNP = p.CNP;
        this->nrTelefon = p.nrTelefon;
    }

    Pacient operator=(const Pacient& p)
    {
        if (p.nume != NULL)

        {
            {
                delete[] this->nume;
            }
            this->nume = new char[strlen(p.nume) + 1];
            strcpy(this->nume, p.nume);
        }
        this->CNP = p.CNP;
        this->nrTelefon = nrTelefon;
        return *this;
    }

    ~Pacient()
    {
        delete[] nume;
    }

    char* getNume()
    {
        return nume;
    }
    
    void setNume(const char* numeNou)
    {
        if (strlen(numeNou) > 2)
        {
            delete[] this->nume;
            this->nume = new char[strlen(numeNou) + 1];
            strcpy(this->nume, numeNou);
        }
        else
        {
            throw Exceptie("Nume invalid! (Trebuie sa contina mai mult de doua caractere)");
        }

    }

    string getCNP()
    {
        return CNP;
    }
    void setCNP(string CNP)
    {
        this->CNP = CNP;
    }

    string getnrTelefon()
    {
        return nrTelefon;
    }
    void setnrTelefon(string nrTelefon)
    {
        this->nrTelefon = nrTelefon;
    }

    friend istream& operator>>(istream& in, Pacient& p);
    friend ostream& operator<<(ostream& out, Pacient& p);

};

class Consultatie
{
private:
    Pacient* pacienti;
    int nrPacienti;
    int data;
    int durata;
    string diagnostic;
    static int nrConsultatii;
    const int contor;


public:
    Consultatie() :contor(nrConsultatii++)
    {
        nrPacienti = 0;
        pacienti = new Pacient[0];
        data = 0;
        durata = 0;
        diagnostic = "Nimic";
    }

    Consultatie( int nrPacienti, Pacient* pacienti, int data, int durata, string diagnostic) :contor(nrConsultatii++)
    {   
        this->nrPacienti = nrPacienti;
        this->pacienti = pacienti;
        this->data = data;
        this->durata = durata;
        this->diagnostic = diagnostic;
    }
    

    Consultatie(const Consultatie& c) : contor(nrConsultatii++)
    {
        this->nrPacienti = c.nrPacienti;
        this->pacienti = new Pacient[c.nrPacienti];
        for (int i = 0; i < c.nrPacienti; i++)
        {
            this->pacienti[i] = c.pacienti[i];
        }
        this->data = c.data;
        this->durata = c.durata;
        this->diagnostic = c.diagnostic;
    }


    Pacient* getnrpacienti()
    {
        return pacienti;
    }

    ~Consultatie()
    {
        delete[] pacienti;
    }

    int getData()
    {
        return data;
    }

    void setData(int data)
    {
        this->data = data;
    }

    int getDurata()
    {
        return durata;
    }

    void setDurata(int durata)
    {
        this->durata = durata;
    }

    string getDiagnostic()
    {
        return diagnostic;
    }
    void setDiagnostic(string diagnostic)
    {
        this->diagnostic = diagnostic;
    }

    Consultatie operator++()
    {
            this->durata++;
            this->nrPacienti++;
            return *this;
    }
    Consultatie operator++(int)
    { 
        Consultatie aux = *this;
        this->durata++;
        this->nrPacienti++;
        return aux;
    }
    Consultatie operator--()
    {
        this->durata--;
        this->nrPacienti--;
        return *this;
    }
    Consultatie operator--(int)
    {
        Consultatie aux = *this;
        this->durata--;
        this->nrPacienti++;
        return aux;
    }

    friend istream& operator>>(istream& tastatura, Consultatie& c);
    friend ostream& operator<<(ostream& monitor, Consultatie& c);

    //static void AfisareInFisier(Pacient* pacienti, int nrPacienti, int data,int durata, string diagnostic,int filtru, string numeFisier)
    //{
    //    if (nrPacienti > 0 && pacienti != NULL)
    //    {
    //        ofstream f(numeFisier, ios::out);
    //        for (int i = 0; i < nrPacienti; i++) {
    //            if (pacienti[i].getnrpacienti() >= filtru) {
    //                f << pacienti[i] << endl;
    //            }
    //        }
    //        f.close();
    //    }
    //    else {
    //        cout << "Nu avem ce sa scriem in fisier, ca nu avem consultatii!" << endl;

    //    }
    //}

};

int Consultatie::nrConsultatii = 0;

class Medic {
private:
    int id;
    char* nume;
    Consultatie* consultatii;
    int nrConsultatii;

public:
    Medic()
    {
        this->id = 0;
        this->nume = new char[strlen("Anonim") + 1];
        strcpy(this->nume, "Anonim");
        this->nrConsultatii = nrConsultatii;
        this->consultatii = consultatii;
    }
    Medic(int id, const char* nume, int nrConsultatii)
    {
        this->id = id;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->nrConsultatii = nrConsultatii;
        this->consultatii = new Consultatie[nrConsultatii];
    }

    Consultatie* getConsultatii()
    {
        return consultatii;
    }

    int getNrConsultatii()
    {
        return nrConsultatii;
    }
    void setNrConsultatii(int nrConsultatii)
    {
        this->nrConsultatii = nrConsultatii;
    }

    char* getNume()
    {
        return nume;
    }

    void setNume(char* numeNou)
    {
        if (strlen(numeNou) > 2)
        {
            delete[] this->nume;
            this->nume = new char[strlen(numeNou) + 1];
            strcpy(this->nume, numeNou);
        }
        else
        {
            cout << "Numele este prea mic!";
            // sau throw Exceptie("Nume invalid!(Trebuie sa contina mai mult de 2 caractere)");
        }
    }
    // metoda pentru a obtine id-ul medicului
    int getId()
    {
        return id;
    }

    // metoda pentru a seta id-ul medicului
    void setId(int id)
    {
        this->id = id;
    }

    ~Medic()
    {
        delete[] nume;
        delete[] consultatii;
    }

    friend istream& operator>>(istream& in, Medic& m);
    friend ostream& operator<<(ostream& out, Medic& m);

    //Supraincarcare operator [] (index) pentru returnarea unei de la o anumita pozitie
    Consultatie& operator[](int index)
    {
        if (index >= 0 && index < this->nrConsultatii)
        {
            return consultatii[index];
        }
        else
        {
            throw Exceptie ("Index in afara intervalului!");
        }
    }

    Medic& operator++();
    Medic operator++(int);
    Medic& operator--();
    Medic operator--(int);

};

istream& operator>>(istream& in, Pacient& p)
{
    cout << "Introduceti CNP: ";
    in >> p.CNP;
    char aux[20];
    cout << "Introduceti numele: ";
    in >> aux;
    if (p.nume != NULL)
    {
        delete[] p.nume;
    }
    p.nume = new char[strlen(aux) + 1];
    strcpy(p.nume, aux);
    cout << "Introduceti numarul de telefon: ";
    in >> p.nrTelefon;
    return in;
}

ostream& operator<<(ostream& out, Pacient& p)
{
    out << "CNP: " << p.CNP << endl;
    out << "Nume: " << p.nume << endl;
    out << "Numar de telefon: " << p.nrTelefon << endl;
    return out;
}

istream& operator>>(istream& in, Consultatie& c)
{
    cout << "Introduceti numarul de pacienti: ";
    in >> c.nrPacienti;
    cout << "Introduceti data: ";
    in >> c.data;
    cout << "Introduceti durata: ";
    in >> c.durata;
    cout << "Introduceti diagnosticul: ";
    in >> c.diagnostic;
    return in;
}

ostream& operator<<(ostream& out, Consultatie& c)
{
    out << "Numarul de pacienti: " << c.nrPacienti << endl;
    out << "Data: " << c.data << endl;
    out << "Durata: " << c.durata << endl;
    out << "Diagnosticul: " << c.diagnostic << endl;
    return out;
}

template<typename cls>
void afisareMedic(cls parametru) {
	cout << parametru << endl;
}

istream& operator>>(istream& in, Medic& m)
{
    char aux[20];
    cout << "Introduceti numele medicului: ";
    in >> aux;
    if (m.nume != NULL)
    {
        delete[] m.nume;
    }
    m.nume = new char[strlen(aux) + 1];
    strcpy(m.nume, aux);
    return in;
}

ostream& operator<<(ostream& out, Medic& m)
{
    cout << "Nume medic: " << m.nume << endl;
    return out;
}

void insert()
{
    int optiune;
    do
    {
        cout << endl;
        cout << "1. Adauga consultatie\n";
        cout << "2. Afiseaza gradul de incarcare al medicului\n";
        cout << "3. Afiseaza diagnosticul cel mai frecvent\n";
        cout << "4. Alege alt medic:\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin >> optiune;
        switch (optiune)
        {
        case 1:
        {
            string pacient;
            int data;
            int durata;
            string diagnostic;
            int nrTelefon;
            cout << "Introduceti numele pacientului: ";
            cin >> pacient;
            cout << "Introduceti data programarii: ";
            cin >> data;
            cout << "Introduceti durata consultatiei: ";
            cin >> durata;
            cout << "Introduceti diagnosticul preliminar: ";
            cin >> diagnostic;
            cout << "Nr. Telefon: ";
            cin >> nrTelefon;
        }
        break;

        case 2:
        {   Medic medic;
        int zi = 0;
        int incarcare[6] = { 0, 0, 0, 0, 0, 0 };
        Consultatie consultatii;
        for (int i = 0; i < medic.getNrConsultatii(); i++)
        {
            zi = medic.getConsultatii()[i].getData() % 6;
            incarcare[zi] += medic.getConsultatii()[i].getDurata();
        }
        for (int i = 1; i < 6; i++)
        {
            cout << "Gradul de incarcare pentru ziua " << i << " este " << incarcare[i] << " ore.\n";
        }
        }
        break;

        case 3:
        {
            Medic medic;
            string diagnostic_curent;
            int contor_curent;
            int contor[100] = { 0 };
            string diagnostic[100];
            int pozitie = -1;
            for (int i = 0; i < medic.getNrConsultatii(); i++)
            {
                diagnostic_curent = medic.getConsultatii()[i].getDiagnostic();
                contor_curent = 0;
                for (int j = 0; j <= pozitie; j++)
                {
                    if (diagnostic_curent == diagnostic[j])
                    {
                        contor_curent = contor[j];
                    }
                }
                contor_curent++;
                if (contor_curent == 1)
                {
                    pozitie++;
                    diagnostic[pozitie] = diagnostic_curent;
                }
                contor[pozitie] = contor_curent;
            }
            int maxim = 0;
            int pozitie_maxim = 0;
            for (int i = 0; i <= pozitie; i++)
            {
                if (contor[i] > maxim)
                {
                    maxim = contor[i];
                    pozitie_maxim = i;
                }
            }
            cout << "Diagnosticul cel mai frecvent este: " << diagnostic[pozitie_maxim] << " cu " << maxim << " aparitii.\n";
        } break;
        case 4:
        {    
            meniu();
            break;
        }
        }

    } while (optiune);

};
 
void meniu()
{
    
    cout << "Buna ziua! Acesta este banalul meu proiect! :( " << endl;
    cout << "Alegeti unul dintre medicii de la clinica noastra:" << endl;
    cout << "1. Alexandru Mihai" << endl;
    cout << "2. Luca Bogdan" << endl;
    cout << "3. Mihai Robert" << endl;
    cout << "4. Vartic Andreea" << endl;

 }

int main()
{
    
    //afisareMedic(m1);
    /*Consultatie c1;
    cout << c1;

    Pacient p1;
    cin >> p1;

    Consultatie c2;
    cin >> c2;*/
    //Medic medic;
    Medic m1(10, "Alexandru Mihai", 3);
    Medic m2(2, "Luca Ioan", 4);
    Medic m3(5, "Mihai Robert", 2);
    Medic m4;

    string nume;
    int id;
  
    meniu();
        cout << "Introduceti id-ul medicului: ";

        cin >> id;
        switch (id)
        {
        case 1:
            cout << "Ati ales medicul Alexandru Mihai";
            insert();
            break;

        case 2:
            cout << "Ati ales medicul Luca Ioan";
            insert();
            break;

        case 3:
            cout << "Ati ales medicul Mihai Robert";
            insert();
            break;

        case 4:
            cout << "Ati ales medicul Vartic Andreea";
            insert();
            break;

        default:
            cout << "Medic invalid! ";
            cout << endl;
            //meniu();
            //insert();           
        }        
};