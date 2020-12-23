#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>

using namespace std;

class Film {
private:
	const int id = nrFilme;
	static int nrFilme;

	char* titlu;
	int* oreRulare;
	int nrOreRulare;
	

public:
	//constructori
	Film() : id(++nrFilme) {
		titlu = nullptr;
		oreRulare = nullptr;
	}

	Film(char* titlu, int* oreRulare, int nrOreRulare) : Film() {
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
		char* titlu = new char[strlen(titlu) + 1];
		strcpy(titlu, this->titlu);
		return titlu;
	}

	bool operator==(const Film& film) {
		return this->id == film.id;
	}

	//TODO: - todo
	Film operator+(Film& film) {
		Film f;
		return f;
	}

	bool operator<=(const Film& film) {
		return strcmp(this->titlu, film.titlu) < 0;
	}

	operator int() const {
		return this->id;
	}

	friend ostream& operator<<(ostream&, Film&);
	friend istream& operator>>(istream&, Film&);
	friend ofstream& operator<<(ofstream&, Film);
	friend ifstream& operator>>(ifstream&, Film&);
};

ostream& operator<<(ostream& output, Film& film) {
	output << "titlu: " << film.titlu << endl;
	output << "id: " << film.id << endl;
	return output;
}

istream& operator>>(istream& input, Film& film) {
	cout << "Titlu:" << endl;
	return input;
}

class Bilet {
private:
	const int id = nrBilete;
	static int nrBilete;

	double pret;
	int rulareId;

	char* titluFilm;


public:
	Bilet() : id(++nrBilete) {
		pret = 0;
		rulareId = 0;
		titluFilm = nullptr;
	}


	Bilet(char* titluFilm, double pret, int rulareId) : Bilet() {
		char* copieTitluFilm = new char[strlen(titluFilm) + 1];
		strcpy(copieTitluFilm, titluFilm);
		this->titluFilm = copieTitluFilm;

		this->pret = pret;
		this->rulareId = rulareId;
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

	//TODO: - todo
	int operator+(Bilet& bilet) {
		return pret + bilet.pret;
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

	//TODO: - todo
	Client operator+(Client& client) {
		Client c;
		return c;
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
	input >> client.nume;
	return input;
}

class Sala {
private:
	const int id = nrSali;
	static int nrSali;

	int capacitateLocuri = 0;
	int randuri = 0;
	int coloane = 0;
	int** dispunereLocuri;

	int* locuriOcupate;
	int nrLocuriOcupate = 0;

	char* nume;

public:
	Sala() : id(++nrSali) {
		dispunereLocuri = nullptr;
		locuriOcupate = nullptr;
		nume = nullptr;
	}

	Sala(char* nume, int randuri, int coloane) : Sala() {
		this->randuri = randuri;
		this->coloane = coloane;
		this->capacitateLocuri = randuri * coloane;

		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	Sala(int capacitateLocuri) : Sala() {
		this->capacitateLocuri = capacitateLocuri;
	}

	Sala(const Sala& sala) {
		this->randuri = sala.randuri;
		this->coloane = sala.coloane;
		this->capacitateLocuri = randuri * coloane;

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

	int operator+(Sala& sala) {
		return capacitateLocuri + sala.capacitateLocuri;
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
	cout << "randuri:";
	input >> sala.randuri;
	cout << "coloane:";
	input >> sala.coloane;
	return input;
}

class Loc {
private:
	const int id;

public:
	Loc(int id) : id(id) {

	}

	bool operator==(const Loc& loc) {
		return this->id == loc.id;
	}

	int operator[](int index) {
		return this->id;
	}
};

class Angajat {
private:
	const int id = nrAngajati;
	static int nrAngajati;

	char* nume;
	double salariu = 0;

public:
	Angajat() : id(++nrAngajati) {
		nume = nullptr;
	}

	Angajat(char* nume, int salariu) : Angajat() {
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;

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

	double operator+(Angajat& angajat) {
		return salariu + angajat.salariu;
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
	cout << "nume:";
	input >> angajat.nume;
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
	output << "id: " << rulare.id << endl;
	output << "data: " << rulare.data << endl;
	return output;
}

istream& operator>>(istream& input, Rulare& rulare) {
	cout << "data:";
	input >> rulare.data;
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