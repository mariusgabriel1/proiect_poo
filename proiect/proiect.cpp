#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>

using namespace std;

class Film {
private:
	const int id = nrFilme;
	static int nrFilme;

	char* titlu = nullptr;
	int* oreRulare = nullptr;
	int nrOreRulare = 0;
	int durata = 0;

public:
	Film() : id(++nrFilme) {
		
	}

	Film(char* titlu, int* oreRulare, int nrOreRulare, int durata) : Film() {
		char* copieTitlu = new char[strlen(titlu) + 1];
		strcpy_s(copieTitlu, strlen(titlu) + 1, titlu);
		this->titlu = copieTitlu;
		
		int* copieOreRulare = new int[nrOreRulare];
		for (int i = 0; i < nrOreRulare; i++)
		{
			copieOreRulare[i] = oreRulare[i];
		}

		this->oreRulare = copieOreRulare;
		this->nrOreRulare = nrOreRulare;
		this->durata = durata;
	}

	Film(int durata) : Film() {
		this->durata = durata;
	}


	Film(const Film& film) {
		char* titlu = new char[strlen(film.titlu) + 1];
		strcpy(titlu, film.titlu);
		this->titlu = titlu;

		int* copieOreRulare = new int[film.nrOreRulare];
		for (int i = 0; i < film.nrOreRulare; i++)
		{
			copieOreRulare[i] = film.oreRulare[i];
		}

		this->oreRulare = copieOreRulare;
		this->nrOreRulare = film.nrOreRulare;
	}

	Film& operator=(const Film& film)
	{
		new (this) Film(film);
		return *this;
	}

	~Film() {
		delete[] titlu;
		delete[] oreRulare;
	}

	void setTitlu(char* titlu) {
		if (titlu != nullptr) {
			delete[] this->titlu;

			char* copieTitlu = new char[strlen(titlu) + 1];
			strcpy_s(copieTitlu, strlen(titlu) + 1, titlu);
			this->titlu = copieTitlu;
		}
	}

	char* getTitlu() {
		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy_s(titlu, strlen(this->titlu) + 1, this->titlu);
		return titlu;
	}

	int* getOreRulare() {
		int* copieOreRulare = new int[nrOreRulare];
		for (int i = 0; i < nrOreRulare; i++)
		{
			copieOreRulare[i] = oreRulare[i];
		}

		return copieOreRulare;
	}

	int getId() {
		return id;
	}


	char* operator[](int index) {
		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy(titlu, this->titlu);
		return titlu;
	}

	bool operator==(const Film& film) {
		return this->id == film.id;
	}

	Film operator+(Film& film) {
		return Film(durata + film.durata);
	}

	bool operator<=(const Film& film) {
		return strcmp(this->titlu, film.titlu) < 0;
	}

	operator char*() {
		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy(titlu, this->titlu);
		return titlu;
	}

	bool operator!() { 
		return false;
	}

	friend ostream& operator<<(ostream&, Film&);
	friend istream& operator>>(istream&, Film&);
	friend ofstream& operator<<(ofstream&, Film);
	friend ifstream& operator>>(ifstream&, Film&);
};

ostream& operator<<(ostream& output, Film& film) {
	output << "Titlu: " << film.titlu << endl;
	output << "ID: " << film.id << endl;
	output << "Durata: " << film.durata << endl;
	return output;
}

istream& operator>>(istream& input, Film& film) {
	cout << "Titlu: " << endl;

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	film.titlu = new char[strlen(buffer) + 1];
	strcpy_s(film.titlu, strlen(buffer) + 1, buffer);

	cout << "Durata: " << endl;
	input >> film.durata;

	return input;
}

class Bilet {
private:
	const int id = nrBilete;
	static int nrBilete;

	double pret = 0;
	int rulareId = 0;
	int loc = 0;

	char* titluFilm = nullptr;


public:
	Bilet() : id(++nrBilete) {

	}


	Bilet(char* titluFilm, double pret, int rulareId,int loc) : Bilet() {
		char* copieTitluFilm = new char[strlen(titluFilm) + 1];
		strcpy(copieTitluFilm, titluFilm);
		this->titluFilm = copieTitluFilm;

		this->pret = pret;
		this->rulareId = rulareId;
		this->loc = loc;
	}

	Bilet(double pret) : Bilet() {
		this->pret = pret;
	}

	Bilet& operator=(const Bilet& bilet)
	{
		new (this) Bilet(bilet);
		return *this;
	}

	Bilet(const Bilet& bilet) {
		char* titluFilm = new char[strlen(bilet.titluFilm) + 1];
		strcpy(titluFilm, bilet.titluFilm);
		this->titluFilm = titluFilm;

		this->pret = bilet.pret;
		this->rulareId = bilet.rulareId;
		this->loc = bilet.loc;
	}

	~Bilet() {
		delete[] titluFilm;
	}

	Bilet(double pret) : Bilet() {
		this->pret = pret;
	}

	void setPret(double pret) {
		this->pret = pret;
	}


	void setTitluFilm(char* titluFilm) {
		if (titluFilm != nullptr) {
			char* copieTitluFilm = new char[strlen(titluFilm) + 1];
			strcpy(copieTitluFilm, titluFilm);
			this->titluFilm = copieTitluFilm;
		}
		
	}

	double getPret() {
		return pret;
	}

	bool operator==(const Bilet& bilet) {
		return this->id == bilet.id;
	}

	int operator[](int index) {
		return this->id;
	}

	operator char*() {
		char* titluFilm = new char[strlen(this->titluFilm) + 1];
		strcpy(titluFilm, this->titluFilm);
		return titluFilm;
	}

	bool operator!() {
		return false;
	}

	Bilet operator+(Bilet& bilet) {
		return Bilet(pret + bilet.pret);
	}

	friend ostream& operator<<(ostream&, Bilet&);
	friend istream& operator>>(istream&, Bilet&);
	friend ofstream& operator<<(ofstream&, Bilet);
	friend ifstream& operator>>(ifstream&, Bilet&);
};

ostream& operator<<(ostream& output, Bilet& bilet) {
	output << "pret: " << bilet.pret << endl;
	output << "id: " << bilet.id << endl;
	return output;
}

istream& operator>>(istream& input, Bilet& bilet) {
	cout << "Titlu film: " << endl;

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	bilet.titluFilm = new char[strlen(buffer) + 1];
	strcpy_s(bilet.titluFilm, strlen(buffer) + 1, buffer);

	cout << "Pret:" << endl;
	input >> bilet.pret;
	cout << "Rulare id:" << endl;
	input >> bilet.rulareId;
	return input;
}

class Client {
private:
	const int id = nrClienti;
	static int nrClienti;

	char* nume;

public:
	Client() : id(++nrClienti) {
		nume = nullptr;
	}

	Client(char* nume) : Client() {
		this->nume = nume;
	}

	~Client() {
		delete[] nume;
	}

	Client(const Client& client) {
		char* nume = new char[strlen(client.nume) + 1];
		strcpy(nume, client.nume);
		this->nume = nume;
	}

	Client& operator=(const Client& client)
	{
		new (this) Client(client);
		return *this;
	}

	bool operator==(const Client& client) {
		return this->id == client.id;
	}

	char* operator[](int index) {
		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	bool operator!() {
		return false;
	}

	operator char*() {
		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	friend ostream& operator<<(ostream&, Client&);
	friend istream& operator>>(istream&, Client&);
	friend ofstream& operator<<(ofstream&, Client);
	friend ifstream& operator>>(ifstream&, Client&);
};

ostream& operator<<(ostream& output, Client& client) {
	output << "nume: " << client.nume << endl;
	output << "id: " << client.id << endl;
	return output;
}

istream& operator>>(istream& input, Client& client) {
	cout << "Nume:";

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	client.nume = new char[strlen(buffer) + 1];
	strcpy_s(client.nume, strlen(buffer) + 1, buffer);

	return input;
}

class Sala {
private:
	const int id = nrSali;
	static int nrSali;

	int capacitateLocuri = 0;
	int* locuri = nullptr;

	int* locuriOcupate = nullptr;
	int nrLocuriOcupate = 0;

	char* nume = nullptr;

public:
	Sala() : id(++nrSali) {

	}

	Sala(char* nume, int capacitateLocuri) : Sala() {
		this->capacitateLocuri = capacitateLocuri;
		
		int* locuri = new int[capacitateLocuri];
		for (int i = 0; i < capacitateLocuri; i++)
		{
			locuri[i] = i;
		}
		this->locuri = locuri;

		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	Sala(int capacitateLocuri) : Sala() {
		this->capacitateLocuri = capacitateLocuri;

		int* locuri = new int[capacitateLocuri];
		for (int i = 0; i < capacitateLocuri; i++)
		{
			locuri[i] = i;
		}
		this->locuri = locuri;
	}


	Sala(const Sala& sala) {
		this->capacitateLocuri = sala.capacitateLocuri;

		int* locuri = new int[capacitateLocuri];
		for (int i = 0; i < capacitateLocuri; i++)
		{
			locuri[i] = i;
		}
		this->locuri = locuri;

		char* copieNume = new char[strlen(sala.nume) + 1];
		strcpy(copieNume, sala.nume);
		this->nume = copieNume;
	}

	Sala& operator=(const Sala& sala)
	{
		new (this) Sala(sala);
		return *this;
	}

	~Sala() {
		delete[] locuriOcupate;
		delete[] nume;
	}

	void ocupaLoc() {

	}

	void elibereazaLoc(int rand, int coloana) {

	}

	bool operator==(const Sala& sala) {
		return this->id == sala.id;
	}

	int operator[](int index) {
		return this->id;
	}

	bool operator!() {
		return false;
	}

	operator char*() {
		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	Sala operator+(Sala& sala) {
		return Sala(capacitateLocuri + sala.capacitateLocuri);
	}

	friend ostream& operator<<(ostream&, Sala&);
	friend istream& operator>>(istream&, Sala&);
	friend ofstream& operator<<(ofstream&, Sala);
	friend ifstream& operator>>(ifstream&, Sala&);
};

ostream& operator<<(ostream& output, Sala& sala) {
	output << "id: " << sala.id << endl;
	return output;
}

istream& operator>>(istream& input, Sala& sala) {
	cout << "Nume: " << endl;

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	sala.nume = new char[strlen(buffer) + 1];
	strcpy_s(sala.nume, strlen(buffer) + 1, buffer);

	return input;
}

class Angajat {
private:
	const int id = nrAngajati;
	static int nrAngajati;

	char* nume = nullptr;
	double salariu = 0;

public:
	Angajat() : id(++nrAngajati) {

	}

	Angajat(char* nume, int salariu) : Angajat() {
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;

		this->salariu = salariu;
	}

	Angajat(int salariu) : Angajat() {
		this->salariu = salariu;
	}

	Angajat(const Angajat& angajat) {
		char* copieNume = new char[strlen(angajat.nume) + 1];
		strcpy(copieNume, angajat.nume);
		this->nume = copieNume;
	}

	Angajat& operator=(const Angajat& angajat)
	{
		new (this) Angajat(angajat);
		return *this;
	}

	~Angajat() {
		delete[] nume;
	}


	bool operator==(const Angajat& angajat) {
		return this->id == angajat.id;
	}

	char* operator[](int index) {
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		return copieNume;
	}

	operator char*() {
		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	bool operator!() {
		return false;
	}

	Angajat operator+(Angajat& angajat) {
		return Angajat(salariu + angajat.salariu);
	}

	friend ostream& operator<<(ostream&, Angajat&);
	friend istream& operator>>(istream&, Angajat&);
	friend ofstream& operator<<(ofstream&, Angajat);
	friend ifstream& operator>>(ifstream&, Angajat&);
};

ostream& operator<<(ostream& output, Angajat& angajat) {
	output << "id: " << angajat.id << endl;
	output << "nume: " << angajat.nume << endl;
	return output;
}
istream& operator>>(istream& input, Angajat& angajat) {
	cout << "Nume: " << endl;

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	angajat.nume = new char[strlen(buffer) + 1];
	strcpy_s(angajat.nume, strlen(buffer) + 1, buffer);

	return input;
}

class Rulare {
private:
	const int id = nrRulari;
	static int nrRulari;

	int data = 0;
	int filmId = 0;
	int salaId = 0;

public:
	Rulare() : id(++nrRulari) {

	}

	Rulare(int data, int filmId, int salaId) : Rulare() {
		this->data = data;
		this->filmId = filmId;
		this->salaId = salaId;
	}


	bool operator==(const Rulare& rulare) {
		return this->id == rulare.id;
	}

	int operator[](int index) {
		return this->data;
	}

	friend ostream& operator<<(ostream&, Rulare&);
	friend istream& operator>>(istream&, Rulare&);
	friend ofstream& operator<<(ofstream&, Rulare);
	friend ifstream& operator>>(ifstream&, Rulare&);
};

ostream& operator<<(ostream& output, Rulare& rulare) {
	output << "filmid: " << rulare.filmId << endl;
	output << "data: " << rulare.data << endl;
	output << "salaid: " << rulare.salaId << endl;
	return output;
}

istream& operator>>(istream& input, Rulare& rulare) {
	cout << "data:";
	input >> rulare.data;
	cout << "filmid:";
	input >> rulare.filmId;
	cout << "salaid:";
	input >> rulare.salaId;
	return input;
}

int Film::nrFilme = 0;
int Bilet::nrBilete = 0;
int Client::nrClienti = 0;
int Sala::nrSali = 0;
int Angajat::nrAngajati = 0;
int Rulare::nrRulari = 0;

int main()
{
	return 0;
}