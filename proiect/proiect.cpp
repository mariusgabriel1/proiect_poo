#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <ctime>
#include <sstream>

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
		if (titlu != nullptr) {
			char* copieTitlu = new char[strlen(titlu) + 1];
			strcpy_s(copieTitlu, strlen(titlu) + 1, titlu);
			this->titlu = copieTitlu;
		}
		
		if (oreRulare != nullptr) {
			int* copieOreRulare = new int[nrOreRulare];
			for (int i = 0; i < nrOreRulare; i++)
			{
				copieOreRulare[i] = oreRulare[i];
			}

			this->oreRulare = copieOreRulare;
		}
		
		this->nrOreRulare = nrOreRulare;
		this->durata = durata;
	}

	Film(int durata) : Film() {
		this->durata = durata;
	}


	Film(const Film& film) : id(film.id) {
		if (film.titlu != nullptr) {
			char* titlu = new char[strlen(film.titlu) + 1];
			strcpy(titlu, film.titlu);
			this->titlu = titlu;
		}
		
		if (film.oreRulare != nullptr) {
			int* copieOreRulare = new int[film.nrOreRulare];
			for (int i = 0; i < film.nrOreRulare; i++)
			{
				copieOreRulare[i] = film.oreRulare[i];
			}
			this->oreRulare = copieOreRulare;
		}
		

		this->nrOreRulare = film.nrOreRulare;
		this->durata = film.durata;
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

	void setDurata(int durata) {
		this->durata = durata;
	}

	void setOreRulare(int nrOreRulare, int* oreRulare) {
		if (oreRulare == nullptr) {
			return;
		}

		this->nrOreRulare = nrOreRulare;

		int* copieOreRulare = new int[nrOreRulare];
		for (int i = 0; i < nrOreRulare; i++)
		{
			copieOreRulare[i] = oreRulare[i];
		}

		this->oreRulare = copieOreRulare;
	}

	char* getTitlu() {
		if (titlu == nullptr) {
			return nullptr;
		}

		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy_s(titlu, strlen(this->titlu) + 1, this->titlu);
		return titlu;
	}

	int* getOreRulare() {
		if (oreRulare == nullptr) {
			return nullptr;
		}

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

	bool operator<(const Film& film) {
		return id < film.id;
	}

	operator char*() {
		if (titlu == nullptr) {
			return nullptr;
		}

		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy(titlu, this->titlu);
		return titlu;
	}

	bool operator!() { 
		return false;
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "film" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& durata, sizeof(durata));
		f.write((char*)& nrOreRulare, sizeof(nrOreRulare));

		for (int i = 0; i < nrOreRulare; i++)
		{
			f.write((char*)& oreRulare[i], sizeof(oreRulare[i]));
		}
		

		int nrCaractere = strlen(titlu);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(titlu, nrCaractere + 1);

		f.close();
	}

	static Film deserialize(int id)
	{
		std::stringstream ss;
		ss << "film" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Film film;

			f.read((char*)& film.id, sizeof(film.id));
	
			f.read((char*)& film.durata, sizeof(film.durata));

			f.read((char*)& film.nrOreRulare, sizeof(film.nrOreRulare));
	
			int* oreRulare = new int[film.nrOreRulare];
			for (int i = 0; i < film.nrOreRulare; i++)
			{
				f.read((char*)& oreRulare[i], sizeof(int));
			}

			film.oreRulare = oreRulare;
	
			int nrCaractere;
			f.read((char*)& nrCaractere, sizeof(nrCaractere));
			char* titlu = new char[nrCaractere + 1];
			f.read(titlu, nrCaractere + 1);
			film.titlu = titlu;

			return film;
		}
	}


	friend ostream& operator<<(ostream&, Film&);
	friend istream& operator>>(istream&, Film&);
};

ostream& operator<<(ostream& output, Film& film) {
	output << "Titlu: " << film.titlu << endl;
	output << "ID: " << film.id << endl;
	output << "Durata: " << film.durata << endl;
	output << "Ore rulare: ";
	for (int i = 0; i < film.nrOreRulare; i++)
	{
		output << film.oreRulare[i] << " ";
	}
	
	output << endl;
	return output;
}

istream& operator>>(istream& input, Film& film) {
	cout << "Titlu: ";

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	film.titlu = new char[strlen(buffer) + 1];
	strcpy_s(film.titlu, strlen(buffer) + 1, buffer);

	cout << "Durata: ";
	input >> film.durata;

	cout << "Nr ore rulare: ";
	input >> film.nrOreRulare;

	cout << "Ore rulare: ";
	film.oreRulare = new int[film.nrOreRulare];

	for (int i = 0; i < film.nrOreRulare; i++)
	{
		input >> film.oreRulare[i];
	}

	cout << endl;

	return input;
}

class Bilet {
private:
	const int id = nrBilete;
	static int nrBilete;

	double pret = 0;
	int rulareId = 0;
	int clientId = 0;
	int loc = 0;

	char* titluFilm = nullptr;


public:
	Bilet() : id(++nrBilete) {

	}


	Bilet(char* titluFilm, double pret, int rulareId,int loc, int clientId) : Bilet() {
		if (titluFilm != nullptr) {
			char* copieTitluFilm = new char[strlen(titluFilm) + 1];
			strcpy(copieTitluFilm, titluFilm);
			this->titluFilm = copieTitluFilm;
		}

		this->pret = pret;
		this->rulareId = rulareId;
		this->loc = loc;
		this->clientId = clientId;
	}

	Bilet(double pret) : Bilet() {
		this->pret = pret;
	}

	Bilet& operator=(const Bilet& bilet)
	{
		new (this) Bilet(bilet);
		return *this;
	}

	Bilet(const Bilet& bilet) : id(bilet.id) {
		this->pret = bilet.pret;
		this->rulareId = bilet.rulareId;
		this->loc = bilet.loc;
		this->clientId = bilet.clientId;

		if (bilet.titluFilm != nullptr) {
			char* copieTitluFilm = new char[strlen(bilet.titluFilm) + 1];
			strcpy(copieTitluFilm, bilet.titluFilm);
			this->titluFilm = copieTitluFilm;
		}
	}

	~Bilet() {
		delete[] titluFilm;
	}

	void setPret(double pret) {
		this->pret = pret;
	}

	void setRulareId(int rulareId) {
		this->rulareId = rulareId;
	}

	void setLoc(int loc) {
		this->loc = loc;
	}

	int getId() {
		return id;
	}

	int getClientId() {
		return clientId;
	}

	int getRulareId() {
		return rulareId;
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
		if (titluFilm == nullptr) {
			return nullptr;
		}

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

	bool operator<(const Bilet& bilet) {
		return id < bilet.id;
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "bilet" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& pret, sizeof(pret));
		f.write((char*)& rulareId, sizeof(rulareId));
		f.write((char*)& loc, sizeof(loc));

		int nrCaractere = strlen(titluFilm);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(titluFilm, nrCaractere + 1);

		f.close();
	}

	static Bilet deserialize(int id)
	{
		std::stringstream ss;
		ss << "bilet" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Bilet bilet;

			f.read((char*)& bilet.id, sizeof(bilet.id));
			f.read((char*)& bilet.pret, sizeof(bilet.pret));
			f.read((char*)& bilet.rulareId, sizeof(bilet.rulareId));
			f.read((char*)& bilet.loc, sizeof(bilet.loc));

			int nrCaractere;
			f.read((char*)& nrCaractere, sizeof(nrCaractere));
			char* titluFilm = new char[nrCaractere + 1];
			f.read(titluFilm, nrCaractere + 1);
			bilet.titluFilm = titluFilm;

			return bilet;
		}
	}

	friend ostream& operator<<(ostream&, Bilet&);
	friend istream& operator>>(istream&, Bilet&);
};

ostream& operator<<(ostream& output, Bilet& bilet) {
	output << "Titlu film: " << bilet.titluFilm << endl;
	output << "Pret: " << bilet.pret << endl;
	output << "Loc: " << bilet.loc << endl;
	output << "Id: " << bilet.id << endl;
	output << "Rulare Id: " << bilet.rulareId << endl;
	output << endl;
	return output;
}

istream& operator>>(istream& input, Bilet& bilet) {
	cout << "Pret:";
	input >> bilet.pret;

	cout << "Rulare id:";
	input >> bilet.rulareId;

	cout << "Client id:";
	input >> bilet.clientId;

	cout << "Titlu film:";
	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	bilet.titluFilm = new char[strlen(buffer) + 1];
	strcpy_s(bilet.titluFilm, strlen(buffer) + 1, buffer);

	cout << endl;

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
		if (nume != nullptr) {
			char* copienume = new char[strlen(nume) + 1];
			strcpy(copienume, nume);
			this->nume = copienume;
		}
	}

	~Client() {
		delete[] nume;
	}

	Client(const Client& client) : id(client.id) {
		if (client.nume != nullptr) {
			char* nume = new char[strlen(client.nume) + 1];
			strcpy(nume, client.nume);
			this->nume = nume;
		}
		else {
			this->nume = nullptr;
		}
		
	}

	Client& operator=(const Client& client)
	{
		new (this) Client(client);
		return *this;
	}

	int getId() {
		return id;
	}

	void setNume(char* nume) {
		if (nume == nullptr) {
			return;
		}

		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	bool operator==(const Client& client) {
		return this->id == client.id;
	}

	char* operator[](int index) {
		if (nume == nullptr) {
			return nullptr;
		}

		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	bool operator!() {
		return false;
	}

	operator char*() {
		if (nume == nullptr) {
			return nullptr;
		}

		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	bool operator<(const Client& client) {
		return id < client.id;
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "client" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
	}

	static Client deserialize(int id)
	{
		std::stringstream ss;
		ss << "client" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Client client;

			f.read((char*)& client.id, sizeof(client.id));

			int nrCaractere;
			f.read((char*)& nrCaractere, sizeof(nrCaractere));
			char* nume = new char[nrCaractere + 1];
			f.read(nume, nrCaractere + 1);
			client.nume = nume;
			
			return client;
		}
	}

	friend ostream& operator<<(ostream&, Client&);
	friend istream& operator>>(istream&, Client&);
};

ostream& operator<<(ostream& output, Client& client) {
	output << "Nume: " << client.nume << endl;
	output << "Id: " << client.id << endl;
	return output;
}

istream& operator>>(istream& input, Client& client) {
	cout << "Nume:";

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	client.nume = new char[strlen(buffer) + 1];
	strcpy_s(client.nume, strlen(buffer) + 1, buffer);

	cout << endl;
	return input;
}



class Sala {
private:
	const int id = nrSali;
	static int nrSali;

	int nrLocuri = 0;
	int* locuri = nullptr;

	int* locuriOcupate = nullptr;
	int nrLocuriOcupate = 0;

	char* nume = nullptr;

public:
	Sala() : id(++nrSali) {

	}

	Sala(char* nume, int nrLocuri) : Sala() {
		this->nrLocuri = nrLocuri;
		
		int* locuri = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++)
		{
			locuri[i] = i;
		}
		this->locuri = locuri;

		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	Sala(int nrLocuri) : Sala() {
		this->nrLocuri = nrLocuri;

		int* locuri = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++)
		{
			locuri[i] = i;
		}
		this->locuri = locuri;
	}


	Sala(const Sala& sala) : id(sala.id) {
		this->nrLocuri = sala.nrLocuri;

		int* locuri = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++)
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

	int getId() {
		return id;
	}

	int getNrLocuri() {
		return nrLocuri;
	}

	void ocupaLoc() {

	}

	void setNume(char* nume) {
		if (nume == nullptr) {
			return;
		}

		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	void setNrLocuri(int nrLocuri) {
		this->nrLocuri = nrLocuri;
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
		if (nume == nullptr) {
			return nullptr;
		}

		char* nume = new char[strlen(this->nume) + 1];
		strcpy(nume, this->nume);
		return nume;
	}

	bool operator<(const Sala& sala) {
		return id < sala.id;
	}

	Sala operator+(Sala& sala) {
		return Sala(nrLocuri + sala.nrLocuri);
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "sala" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& nrLocuri, sizeof(nrLocuri));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
	}

	static Sala deserialize(int id)
	{
		std::stringstream ss;
		ss << "sala" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Sala sala;

			f.read((char*)& sala.id, sizeof(sala.id));

			f.read((char*)& sala.nrLocuri, sizeof(sala.nrLocuri));

			int nrCaractere;
			f.read((char*)& nrCaractere, sizeof(nrCaractere));
			char* nume = new char[nrCaractere + 1];
			f.read(nume, nrCaractere + 1);
			sala.nume = nume;

			return sala;
		}
	}

	friend ostream& operator<<(ostream&, Sala&);
	friend istream& operator>>(istream&, Sala&);
};

ostream& operator<<(ostream& output, Sala& sala) {
	output << "Id: " << sala.id << endl;
	output << "Nume: " << sala.nume << endl;
	output << "Nr locuri: " << sala.nrLocuri << endl;
	return output;
}

istream& operator>>(istream& input, Sala& sala) {
	cout << "Nume: ";

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	sala.nume = new char[strlen(buffer) + 1];
	strcpy_s(sala.nume, strlen(buffer) + 1, buffer);

	cout << "Nr locuri: ";
	cin >> sala.nrLocuri;

	cout << endl;

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
		if (nume != nullptr) {
			char* copieNume = new char[strlen(nume) + 1];
			strcpy(copieNume, nume);
			this->nume = copieNume;
		}
		

		this->salariu = salariu;
	}

	Angajat(int salariu) : Angajat() {
		this->salariu = salariu;
	}

	Angajat(const Angajat& angajat) : id(angajat.id) {
		if (angajat.nume != nullptr) {
			char* copieNume = new char[strlen(angajat.nume) + 1];
			strcpy(copieNume, angajat.nume);
			this->nume = copieNume;
		}
		
	}

	Angajat& operator=(const Angajat& angajat)
	{
		new (this) Angajat(angajat);
		return *this;
	}

	~Angajat() {
		delete[] nume;
	}

	int getId() {
		return id;
	}

	void setNume(char* nume) {
		if (nume == nullptr) {
			return;
		}
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
	}

	void setSalariu(double salariu) {
		this->salariu = salariu;
	}

	bool operator==(const Angajat& angajat) {
		return this->id == angajat.id;
	}

	char* operator[](int index) {
		if (nume == nullptr) {
			return nullptr;
		}
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		return copieNume;
	}

	operator char*() {
		if (nume == nullptr) {
			return nullptr;
		}

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

	bool operator<(const Angajat& angajat) {
		return id < angajat.id;
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "angajat" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& salariu, sizeof(salariu));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
	}

	static Angajat deserialize(int id)
	{
		std::stringstream ss;
		ss << "angajat" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Angajat angajat;

			f.read((char*)& angajat.id, sizeof(angajat.id));
			f.read((char*)& angajat.salariu, sizeof(angajat.salariu));
			
			int nrCaractere;
			f.read((char*)& nrCaractere, sizeof(nrCaractere));
			char* nume = new char[nrCaractere + 1];
			f.read(nume, nrCaractere + 1);
			angajat.nume = nume;

			return angajat;
		}
	}

	friend ostream& operator<<(ostream&, Angajat&);
	friend istream& operator>>(istream&, Angajat&);
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

	cout << endl;

	return input;
}


class Rulare {
private:
	const int id = nrRulari;
	static int nrRulari;

	time_t data = time(0);
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

	Rulare(const Rulare& rulare) : id(rulare.id) {
		this->data = rulare.data;
		this->filmId = rulare.filmId;
		this->salaId = rulare.salaId;
	}

	Rulare& operator=(const Rulare& rulare)
	{
		new (this) Rulare(rulare);
		return *this;
	}

	int getId() {
		return id;
	}

	void setData(time_t data) {
		this->data = data;
	}

	void setFilmId(int filmId) {
		this->filmId = filmId;
	}

	int getFilmId() {
		return filmId;
	}

	int getSalaId() {
		return salaId;
	}


	void setSalaId(int salaId) {
		this->salaId = salaId;
	}

	bool operator==(const Rulare& rulare) {
		return this->id == rulare.id;
	}

	int operator[](int index) {
		return this->data;
	}

	bool operator<(const Rulare& rulare) {
		return id < rulare.id;
	}

	operator int () {
		return id;
	}

	bool operator!() {
		return false;
	}

	void serialize()
	{
		std::stringstream ss;
		ss << "rulare" << id << ".bin";
		std::string fileName = ss.str();

		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& data, sizeof(data));
		f.write((char*)& filmId, sizeof(filmId));
		f.write((char*)& salaId, sizeof(salaId));

		f.close();
	}

	static Rulare deserialize(int id)
	{
		std::stringstream ss;
		ss << "rulare" << id << ".bin";
		std::string fileName = ss.str();

		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			Rulare rulare;

			f.read((char*)& rulare.id, sizeof(rulare.id));
			f.read((char*)& rulare.data, sizeof(rulare.data));
			f.read((char*)& rulare.filmId, sizeof(rulare.filmId));
			f.read((char*)& rulare.salaId, sizeof(rulare.salaId));
			return rulare;
		}
	}

	friend ostream& operator<<(ostream&, Rulare&);
	friend istream& operator>>(istream&, Rulare&);
};

ostream& operator<<(ostream& output, Rulare& rulare) {
	output << "Film id: " << rulare.filmId << endl;
	output << "Data: " << ctime(&rulare.data);
	output << "Sala id: " << rulare.salaId << endl;
	output << "Rulare id: " << rulare.id << endl;
	return output;
}

istream& operator>>(istream& input, Rulare& rulare) {
	string timestamp;
	cout << "Data timestamp:";
	input >> timestamp;

	rulare.data = (time_t)strtol(timestamp.c_str(), NULL, 10);
	
	cout << "Film id:";
	input >> rulare.filmId;
	cout << "Sala id:";
	input >> rulare.salaId;

	cout << endl;

	return input;
}


int Film::nrFilme = 0;
int Bilet::nrBilete = 0;
int Client::nrClienti = 0;
int Sala::nrSali = 0;
int Angajat::nrAngajati = 0;
int Rulare::nrRulari = 0;

class BazaDeDate {
private:
	map<int,Film> filme;
	map<int, Bilet> bilete;
	map<int, Client> clienti;
	map<int, Sala> sali;
	map<int, Angajat> angajati;
	map<int, Rulare> rulari;
	map<int, vector<int>> salaLocuriOcupate;
	map<int, vector<Bilet>> rulareBilete;

public:
	BazaDeDate() {

	}


	void afiseazaSituatieFilme() {
		system("cls");

		if (rulari.empty()) {
			cout << "Nu exista rulari!" << endl;
			int i;
			cout << "Apasa 0 pt meniu" << endl;
			cin >> i;
		}
		else {
			map<int, Rulare>::iterator it;

			for (it = rulari.begin(); it != rulari.end(); it++)
			{
				int filmId = it->second.getFilmId();
				int salaId = it->second.getSalaId();

				if (filme.find(filmId) != filme.end() && sali.find(salaId) != sali.end()) {
					cout << "Rulare:" << endl << it->second;
					cout << "Film:" << endl << filme[filmId];
					cout << "Sala:" << endl << sali[salaId];
					cout << endl;
				}
			}

			int i;
			cout << "Apasa 0 pt meniu" << endl;
			cin >> i;
		}

	}

	void afiseazaSituatieLocuriLibere() {
		system("cls");

		if (rulari.empty()) {
			int i;
			cout << "Nu exista rulari! Apasa 0 pt meniu" << endl;
			cin >> i;
		}
		else {
			map<int, Rulare>::iterator it1;

			for (it1 = rulari.begin(); it1 != rulari.end(); it1++)
			{
				int salaId = it1->second.getSalaId();
				int rulareId = it1->second.getId();

				Sala sala = sali[salaId];

				int nrbilete = rulareBilete[rulareId].size();

				cout << it1->second;
				cout << "Mai sunt " << sala.getNrLocuri() - nrbilete << " locuri libere la aceasta rulare!" << endl;
			}

			int i;
			cout << "Apasa 0 pt meniu" << endl;
			cin >> i;
		}
		
	}

	//operatii film
	void adaugaFilm() {
		system("cls");

		Film film;
		cin >> film;

		filme.insert(pair<int, Film>(film.getId(), film));
		film.serialize();

		system("cls");
		int i;
		cout << film << endl;
		cout << "Film adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeFilm() {
		system("cls");

		int filmId;
		cout << "Id film: ";
		cin >> filmId;
		filme.erase(filmId);

		std::stringstream ss;
		ss << "film" << filmId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Film sters! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaFilm(int optiune) {
		system("cls");

		switch (optiune)
		{
		case 1: {
			int filmId;
			cout << "Id film: ";
			cin >> filmId;

			if (filme.find(filmId) == filme.end()) {
				cout << "Nu exista film!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}
	
			Film film = filme[filmId];

			char titlu[100];

			cout << "Titlu nou:" << endl;
			cin.getline(titlu, 100, '\n');

			film.setTitlu(titlu);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "film" << filmId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			film.serialize();

			break;
		}


		case 2: {
			int filmId;
			cout << "Id film: ";
			cin >> filmId;

			if (filme.find(filmId) == filme.end()) {
				cout << "Nu exista film!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Film film = filme[filmId];

			int durata;

			cout << "Durata noua: " << endl;
			cin >> durata;

			film.setDurata(durata);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "film" << filmId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			film.serialize();

			break;
		}
			

		case 3: {
			int filmId;
			cout << "Id film: ";
			cin >> filmId;

			if (filme.find(filmId) == filme.end()) {
				cout << "Nu exista film!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Film film = filme[filmId];

			int nrOreRulare;

			cout << "Nr de ore rulare noi: " << endl;
			cin >> nrOreRulare;

			int input = 0;
			int* oreRulare = new int[nrOreRulare];
			int i = 0;

			while ((input != 0) && (i < nrOreRulare))
			{
				cin >> input;
				oreRulare[i] = input;
				i++;
			}

			film.setOreRulare(nrOreRulare, oreRulare);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "film" << filmId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			film.serialize();

			break;
		}

		default:
			break;
			
		}
	}

	void afiseazaFilm() {
		system("cls");

		int filmId;
		cout << "Id film: ";
		cin >> filmId;

		if (filme.find(filmId) == filme.end()) {
			cout << "Nu exista film!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Film film = filme[filmId];
		cout << film;

		cout << endl << "Fisier: " << endl;
		cout << Film::deserialize(filmId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//operatii bilet
	void adaugaBilet() {
		system("cls");

		Bilet bilet;
		cin >> bilet;

		if (clienti.find(bilet.getClientId()) == clienti.end()) {
			cout << "Nu exista client!" << endl;
			int i;
			cout << "Apasa 0 pt meniu" << endl;
			cin >> i;
		}
		else {
			if (rulari.find(bilet.getRulareId()) == rulari.end()) {
				cout << "Nu exista rulare!" << endl;
				int i;
				cout << "Apasa 0 pt meniu" << endl;
				cin >> i;
			}
			else {
				//verifica daca exista loc
				Rulare rulare = rulari[bilet.getRulareId()];
				Sala sala = sali[rulare.getSalaId()];

				if (sala.getNrLocuri() > salaLocuriOcupate[sala.getId()].size()) {
					int loc = salaLocuriOcupate[sala.getId()].size() + 1;
					bilet.setLoc(loc);
					salaLocuriOcupate[sala.getId()].push_back(loc);
					rulareBilete[rulare.getId()].push_back(bilet);

					bilete.insert(pair<int, Bilet>(bilet.getId(), bilet));
					bilet.serialize();

					system("cls");
					int i;
					cout << bilet << endl;
					cout << "Bilet adaugat! Apasa 0 pt a continua" << endl;
					cin >> i;
				}
				else {
					// nu mai sunt locuri
					cout << "Nu exista locuri!" << endl;
					int i;
					cout << "Apasa 0 pt meniu" << endl;
					cin >> i;
				}
			}
			
		}
	}

	void stergeBilet() {
		system("cls");

		int biletId;
		cout << "Id bilet: ";
		cin >> biletId;

		bilete.erase(biletId);

		std::stringstream ss;
		ss << "bilet" << biletId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Bilet sters! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaBilet(int optiune) {
		system("cls");

		switch (optiune)
		{
		case 1: {
			int biletId;
			cout << "Id bilet: ";
			cin >> biletId;

			if (bilete.find(biletId) == bilete.end()) {
				cout << "Nu exista bilet!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;
				
				return;
			}
			
			Bilet bilet = bilete[biletId];

			int loc;

			cout << "Loc nou: " << endl;
			cin >> loc;

			bilet.setLoc(loc);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "bilet" << biletId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			bilet.serialize();

			break;
		}
			
		default:
			break;
		}
	}

	void afiseazaBilet() {
		system("cls");

		int biletId;
		cout << "Id bilet: ";
		cin >> biletId;

		if (bilete.find(biletId) == bilete.end()) {
			cout << "Nu exista bilet!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Bilet bilet = bilete[biletId];
		cout << bilet;

		cout << endl << "Fisier: " << endl;
		cout << Bilet::deserialize(biletId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//operatii sala
	void adaugaSala() {
		system("cls");

		Sala sala;
		cin >> sala;

		sala.serialize();

		sali.insert(pair<int, Sala>(sala.getId(), sala));

		system("cls");
		int i;
		cout << sala << endl;
		cout << "Sala adaugata! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeSala() {
		system("cls");

		int salaId;
		cout << "Id sala: ";
		cin >> salaId;

		sali.erase(salaId);

		std::stringstream ss;
		ss << "sala" << salaId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Sala stearsa! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaSala(int optiune) {
		
		switch (optiune)
		{
		case 1: {
			int salaId;
			cout << "Id sala: ";
			cin >> salaId;

			if (sali.find(salaId) == sali.end()) {
				cout << "Nu exista sala!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Sala sala = sali[salaId];

			char nume[100];

			cout << "Nume nou:" << endl;
			cin.getline(nume, 100, '\n');

			sala.setNume(nume);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "sala" << salaId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			sala.serialize();

			break;
		}

			

		case 2: {
			int salaId;
			cout << "Id sala: ";
			cin >> salaId;

			if (sali.find(salaId) == sali.end()) {
				cout << "Nu exista sala!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Sala sala = sali[salaId];


			int nrLocuri;

			cout << "Nr Locuri nou: " << endl;
			cin >> nrLocuri;

			sala.setNrLocuri(nrLocuri);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "sala" << salaId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			sala.serialize();

			break;
		}
			
		default:
			break;
		}
	}

	void afiseazaSala() {
		system("cls");

		int salaId;
		cout << "Id sala: ";
		cin >> salaId;

		if (sali.find(salaId) == sali.end()) {
			cout << "Nu exista sala!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Sala sala = sali[salaId];
		cout << sala;

		cout << endl << "Fisier: " << endl;
		cout << Sala::deserialize(salaId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//operatii client
	void adaugaClient() {
		system("cls");

		Client client;
		cin >> client;

		client.serialize();

		clienti.insert(pair<int, Client>(client.getId(), client));

		system("cls");
		int i;
		cout << client << endl;
		cout << "Client adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeClient() {
		system("cls");

		int clientId;
		cout << "Id client: ";
		cin >> clientId;

		clienti.erase(clientId);

		std::stringstream ss;
		ss << "client" << clientId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Client sters! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaClient(int optiune) {
		switch (optiune)
		{
		case 1: {
			int clientId;
			cout << "Id client: ";
			cin >> clientId;

			if (clienti.find(clientId) == clienti.end()) {
				cout << "Nu exista client!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Client client = clienti[clientId];

			char nume[100];

			cout << "Nume nou:" << endl;
			cin.getline(nume, 100, '\n');

			client.setNume(nume);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "client" << clientId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			client.serialize();

			break;
		}
			
		default:
			break;
		}
	}

	void afiseazaClient() {
		system("cls");

		int salaId;
		cout << "Id sala: ";
		cin >> salaId;

		if (sali.find(salaId) == sali.end()) {
			cout << "Nu exista sala!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Sala sala = sali[salaId];
		cout << sala;

		cout << endl << "Fisier: " << endl;
		cout << Sala::deserialize(salaId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//operatii angajat
	void adaugaAngajat() {
		system("cls");

		Angajat angajat;
		cin >> angajat;

		angajat.serialize();

		angajati.insert(pair<int, Angajat>(angajat.getId(), angajat));

		system("cls");
		int i;
		cout << angajat << endl;
		cout << "Angajat adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeAngajat() {
		system("cls");

		int angajatId;
		cout << "Id angajat: ";
		cin >> angajatId;
		angajati.erase(angajatId);

		std::stringstream ss;
		ss << "angajat" << angajatId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Angajat sters! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaAngajat(int optiune) {

		switch (optiune)
		{
		case 1: {
			int angajatId;
			cout << "Id angajat: ";
			cin >> angajatId;

			if (angajati.find(angajatId) == angajati.end()) {
				cout << "Nu exista angajat!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Angajat angajat = angajati[angajatId];

			char nume[100];

			cout << "Nume nou: " << endl;
			cin.getline(nume, 100, '\n');

			angajat.setNume(nume);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "angajat" << angajatId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			angajat.serialize();

			break;
		}
			

		case 2: {
			int angajatId;
			cout << "Id angajat: ";
			cin >> angajatId;

			if (angajati.find(angajatId) == angajati.end()) {
				cout << "Nu exista angajat!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Angajat angajat = angajati[angajatId];

			double salariu;

			cout << "Salariu nou: " << endl;
			cin >> salariu;

			angajat.setSalariu(salariu);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "angajat" << angajatId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			angajat.serialize();

			break;
		}
			
		default:
			break;
		}
	}

	void afiseazaAngajat() {
		system("cls");

		int angajatId;
		cout << "Id angajat: ";
		cin >> angajatId;

		if (angajati.find(angajatId) == angajati.end()) {
			cout << "Nu exista angajat!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Angajat angajat = angajati[angajatId];
		cout << angajat;

		cout << endl << "Fisier: " << endl;
		cout << Angajat::deserialize(angajatId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//operatii rulare
	void adaugaRulare() {
		system("cls");

		Rulare rulare;
		cin >> rulare;

		rulare.serialize();

		rulari.insert(pair<int, Rulare>(rulare.getId(), rulare));

		system("cls");
		int i;
		cout << rulare << endl;
		cout << "Rulare adaugata! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeRulare() {
		system("cls");

		int rulareId;
		cout << "Id rulare: ";
		cin >> rulareId;

		rulari.erase(rulareId);

		std::stringstream ss;
		ss << "rulare" << rulareId << ".bin";
		std::string fileName = ss.str();

		remove(fileName.c_str());

		int i;
		cout << "Rulare stearsa! Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	void editeazaRulare(int optiune) {
		switch (optiune)
		{
		case 1: {
			int rulareId;
			cout << "Id rulare: ";
			cin >> rulareId;

			if (rulari.find(rulareId) == rulari.end()) {
				cout << "Nu exista rulare!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Rulare rulare = rulari[rulareId];

			int dataRulare;

			cout << "Data rulare noua: " << endl;
			cin >> dataRulare;

			rulare.setData(dataRulare);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "rulare" << rulareId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			rulare.serialize();

			break;
		}
			

		case 2: {
			int rulareId;
			cout << "Id rulare: ";
			cin >> rulareId;

			if (rulari.find(rulareId) == rulari.end()) {
				cout << "Nu exista rulare!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Rulare rulare = rulari[rulareId];

			int filmId;

			cout << "Film id nou: " << endl;
			cin >> filmId;

			rulare.setFilmId(filmId);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "rulare" << rulareId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			rulare.serialize();

			break;
		}
			

		case 3: {
			int rulareId;
			cout << "Id rulare: ";
			cin >> rulareId;

			if (rulari.find(rulareId) == rulari.end()) {
				cout << "Nu exista rulare!" << endl;

				int i;
				cout << "Apasa 0 pt meniu!" << endl;
				cin >> i;

				return;
			}

			Rulare rulare = rulari[rulareId];

			int salaId;

			cout << "Sala id noua: " << endl;
			cin >> salaId;

			rulare.setSalaId(salaId);

			//sterge fisierul si creeaza unul nou cu obiectul editat
			std::stringstream ss;
			ss << "rulare" << rulareId << ".bin";
			std::string fileName = ss.str();

			remove(fileName.c_str());

			rulare.serialize();

			break;
		}
			
		default:
			break;
		}
	}

	void afiseazaRulare() {
		system("cls");

		int rulareId;
		cout << "Id rulare: ";
		cin >> rulareId;

		if (rulari.find(rulareId) == rulari.end()) {
			cout << "Nu exista rulare!" << endl;

			int i;
			cout << "Apasa 0 pt meniu!" << endl;
			cin >> i;

			return;
		}

		Rulare rulare = rulari[rulareId];
		cout << rulare;

		cout << endl << "Fisier: " << endl;
		cout << Rulare::deserialize(rulareId);

		int i;
		cout << "Apasa 0 pt meniu!" << endl;
		cin >> i;
	}

	//debug
	void populeazaBazaDeDate() {
		int* oreRulare = new int[2];
		oreRulare[0] = 13;
		oreRulare[1] = 15;

		char* titlu1 = new char[6];
		strcpy(titlu1, "Film1");
		char* titlu2 = new char[6];
		strcpy(titlu2, "Film2");

		Film film1 = Film(titlu1, oreRulare, 2, 120);
		Film film2 = Film(titlu2, oreRulare, 2, 120);

		film1.serialize();
		film2.serialize();

		filme[film1.getId()] = film1;
		filme[film2.getId()] = film2;

		char* nume1 = new char[7];
		strcpy(nume1, "Andrei");
		char* nume2 = new char[8];
		strcpy(nume2, "Gabriel");

		Angajat angajat1 = Angajat(nume1, 1500);
		Angajat angajat2 = Angajat(nume2, 2000);

		angajat1.serialize();
		angajat2.serialize();

		angajati[angajat1.getId()] = angajat1;
		angajati[angajat2.getId()] = angajat2;

		nume1 = new char[4];
		strcpy(nume1, "Ion");
		nume2 = new char[7];
		strcpy(nume2, "Bogdan");

		Client client1 = Client(nume1);
		Client client2 = Client(nume2);

		client1.serialize();
		client2.serialize();

		clienti[client1.getId()] = client1;
		clienti[client2.getId()] = client2;

		titlu1 = new char[2];
		strcpy(titlu1, "A");
		titlu2 = new char[2];
		strcpy(titlu2, "B");

		Sala sala1 = Sala(titlu1,200);
		Sala sala2 = Sala(titlu2,150);

		sala1.serialize();
		sala2.serialize();

		sali[sala1.getId()] = sala1;
		sali[sala2.getId()] = sala2;

		Rulare rulare1 = Rulare(31233, 1, 1);
		Rulare rulare2 = Rulare(31343, 2, 2);

		rulare1.serialize();
		rulare2.serialize();

		rulari[rulare1.getId()] = rulare1;
		rulari[rulare2.getId()] = rulare2;
	}
};

int afiseazaMeniu() {
	system("cls");

	cout << "1: Emite bilet" << endl;
	cout << "2: Situatie locuri libere" << endl;
	cout << "3: Situatie filme" << endl;

	cout << "4: Optiuni bilet" << endl;
	cout << "5: Optiuni film" << endl;
	cout << "6: Optiuni client" << endl;
	cout << "7: Optiuni sala" << endl;
	cout << "8: Optiuni angajat" << endl;
	cout << "9: Optiuni rulare" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniBilet() {
	system("cls");

	cout << "1: Adauga bilet" << endl;
	cout << "2: Editeaza bilet" << endl;
	cout << "3: Sterge bilet" << endl;
	cout << "4: Afiseaza bilet" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}

int afiseazaOptiuniEditareBilet() {
	system("cls");

	cout << "1: Editeaza loc" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}


int afiseazaOptiuniFilm() {
	system("cls");

	cout << "1: Adauga film" << endl;
	cout << "2: Editeaza film" << endl;
	cout << "3: Sterge film" << endl;
	cout << "4: Afiseaza film" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniEditareFilm() {
	system("cls");

	cout << "1: Editeaza nume" << endl;
	cout << "2: Editeaza durata" << endl;
	cout << "3: Editeaza ore rulare" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}


int afiseazaOptiuniClient() {
	system("cls");

	cout << "1: Adauga client" << endl;
	cout << "2: Editeaza client" << endl;
	cout << "3: Sterge client" << endl;
	cout << "4: Afiseaza client" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniEditareClient() {
	system("cls");

	cout << "1: Editeaza nume" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}


int afiseazaOptiuniSala() {
	system("cls");

	cout << "1: Adauga sala" << endl;
	cout << "2: Editeaza sala" << endl;
	cout << "3: Sterge sala" << endl;
	cout << "4: Afiseaza sala" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniEditareSala() {
	system("cls");

	cout << "1: Editeaza nume" << endl;
	cout << "2: Editeaza nr locuri" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}


int afiseazaOptiuniAngajat() {
	system("cls");

	cout << "1: Adauga angajat" << endl;
	cout << "2: Editeaza angajat" << endl;
	cout << "3: Sterge angajat" << endl;
	cout << "4: Afiseaza angajat" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniEditareAngajat() {
	system("cls");

	cout << "1: Editeaza nume" << endl;
	cout << "2: Editeaza salariu" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}


int afiseazaOptiuniRulare() {
	system("cls");

	cout << "1: Adauga rulare" << endl;
	cout << "2: Editeaza rulare" << endl;
	cout << "3: Sterge rulare" << endl;
	cout << "4: Afiseaza rulare" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;
}

int afiseazaOptiuniEditareRulare() {
	system("cls");

	cout << "1: Editeaza sala id" << endl;
	cout << "2: Editeaza data" << endl;
	cout << "2: Editeaza film id" << endl;
	cout << "0: Meniu" << endl;

	int val;
	cin >> val;
	return val;

}

int main()
{
	BazaDeDate bd;
	bd.populeazaBazaDeDate();

	int optiuneMeniu;
	do
	{
		optiuneMeniu = afiseazaMeniu();

		switch (optiuneMeniu)
		{
		case 1: {
			bd.adaugaBilet();
			break;
		}
		case 2: {
			bd.afiseazaSituatieLocuriLibere();
			break;
		}
		case 3: {
			bd.afiseazaSituatieFilme();
			break;
		}

		case 4: {

			int optiuneBilet = afiseazaOptiuniBilet();

			switch (optiuneBilet)
			{
			case 1: {
				bd.adaugaBilet();
				break;
			}
				
			case 2: {
				int optiuneEditareBilet = afiseazaOptiuniEditareBilet();
				bd.editeazaBilet(optiuneEditareBilet);
				break;
			}
				
			case 3: {
				bd.stergeBilet();
				break;
			}

			case 4: {
				bd.afiseazaBilet();
				break;
			}
			
				
			default:
				break;
			}

			break;
		}

		case 5: {

			int optiuneFilm = afiseazaOptiuniFilm();

			switch (optiuneFilm)
			{
			case 1: {
				bd.adaugaFilm();
				break;
			}
				
			case 2: {
				int optiuneEditareFilm = afiseazaOptiuniEditareFilm();
				bd.editeazaFilm(optiuneEditareFilm);
				break;
			}
				
			case 3: {
				bd.stergeFilm();
				break;
			}


			case 4: {
				bd.afiseazaFilm();
				break;
			}
				
			default:
				break;
			}

			break;
		}


		case 6: {
			system("cls");
			int optiuneClient = afiseazaOptiuniClient();

			switch (optiuneClient)
			{
			case 1: {
				bd.adaugaClient();
				break;
			}
				
			case 2: {
				int optiuneEditareClient = afiseazaOptiuniEditareClient();
				bd.editeazaClient(optiuneEditareClient);
				break;
			}
				
			case 3: {
				bd.stergeClient();
				break;
			}

			case 4: {
				bd.afiseazaClient();
				break;
			}
				
			default:
				break;
			}

			break;
		}

		case 7: {
			system("cls");
			int optiuneSala = afiseazaOptiuniSala();

			switch (optiuneSala)
			{
			case 1: {
				bd.adaugaSala();
				break;
			}
				
			case 2: {
				int optiuneEditareSala = afiseazaOptiuniEditareSala();
				bd.editeazaSala(optiuneEditareSala);
				break;
			}
				
			case 3: {
				bd.stergeSala();
				break;
			}

			case 4: {
				bd.afiseazaSala();
				break;
			}
				
			default:
				break;
			}

			break;
		}

		case 8: {
			system("cls");
			int optiuneAngajat = afiseazaOptiuniAngajat();

			switch (optiuneAngajat)
			{
			case 1: {
				bd.adaugaAngajat();
				break;
			}
				
			case 2: {
				int optiuneEditareAngajat = afiseazaOptiuniEditareAngajat();
				bd.editeazaAngajat(optiuneEditareAngajat);
				break;
			}
				
			case 3: {
				bd.stergeAngajat();
				break;
			}

			case 4: {
				bd.afiseazaAngajat();
				break;
			}
				
			default:
				break;
			}

			break;
		}

		case 9: {
			system("cls");
			int optiuneRulare = afiseazaOptiuniRulare();

			switch (optiuneRulare)
			{
			case 1: {
				bd.adaugaRulare();
				break;
			}
				
			case 2: {
				int optiuneEditareAngajat = afiseazaOptiuniEditareAngajat();
				bd.editeazaAngajat(optiuneEditareAngajat);
				break;
			}
				
			case 3: {
				bd.stergeRulare();
				break;
			}

			case 4: {
				bd.afiseazaRulare();
				break;
			}
				
			default:
				break;
			}

			break;
		}

		default:
			break;
		}

	} while (optiuneMeniu != 0);
	
	return 0;
}