#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

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
		if (film.titlu != nullptr) {
			char* titlu = new char[strlen(film.titlu) + 1];
			strcpy(titlu, film.titlu);
			this->titlu = titlu;
		}
		

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

	void setDurata(int durata) {
		this->durata = durata;
	}

	void setOreRulare(int nrOreRulare, int* oreRulare) {
		this->nrOreRulare = nrOreRulare;

		int* copieOreRulare = new int[nrOreRulare];
		for (int i = 0; i < nrOreRulare; i++)
		{
			copieOreRulare[i] = oreRulare[i];
		}

		this->oreRulare = copieOreRulare;
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

	bool operator<(const Film& film) {
		return id < film.id;
	}

	operator char*() {
		char* titlu = new char[strlen(this->titlu) + 1];
		strcpy(titlu, this->titlu);
		return titlu;
	}

	bool operator!() { 
		return false;
	}

	void serialize(string fileName)
	{
		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& durata, sizeof(durata));
		f.write((char*)& nrOreRulare, sizeof(nrOreRulare));
		f.write((char*)& oreRulare, sizeof(oreRulare));

		int nrCaractere = strlen(titlu);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		//f.write(titlu, nrCaractere + 1);

		f.close();
	}

	static void deserialize(string fileName)
	{
		ifstream f(fileName, ios::binary);

		if (f.is_open()) {
			vector<Film> filme;

			while (true) {
				if (f.eof()) {
					break;
				}

				int size = 0;

				Film film;

				f.read((char*)& film.id, sizeof(film.id));
				size += sizeof(film.id);

				f.read((char*)& film.durata, sizeof(film.durata));
				size += sizeof(film.durata);

				f.read((char*)& film.nrOreRulare, sizeof(film.nrOreRulare));
				size += sizeof(film.nrOreRulare);

				f.read((char*)& film.oreRulare, sizeof(film.oreRulare));
				size += sizeof(film.oreRulare);

				int nrCaractere;
				//f.getLine((char*)& nrCaractere, sizeof(nrCaractere));
				/*char* titlu = new char[nrCaractere + 1];
				f.read(titlu, nrCaractere + 1);
				film.titlu = titlu;*/

				size += sizeof(nrCaractere);
				//size += sizeof(nrCaractere * sizeof(char));

				
				f.seekg(size,ios::cur);
			

				filme.push_back(film);
			}

			f.close();

	
			for (vector<Film>::iterator i = filme.begin(); i != filme.end(); i++)
			{
				cout << *i;
			}
		}
		else {

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

	bool operator<(const Bilet& bilet) {
		return id < bilet.id;
	}

	void serialize(string fileName)
	{
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

	void deserialize(string fileName)
	{
		ifstream f(fileName, ios::binary);

		f.read((char*)& id, sizeof(id));
		f.read((char*)& pret, sizeof(pret));
		f.read((char*)& rulareId, sizeof(rulareId));
		f.read((char*)& loc, sizeof(loc));

		int nrCaractere;
		f.read((char*)& nrCaractere, sizeof(nrCaractere));
		char* titluFilm = new char[nrCaractere];
		f.read(titluFilm, nrCaractere);
		this->titluFilm = titluFilm;

		f.close();
	}

	friend ostream& operator<<(ostream&, Bilet&);
	friend istream& operator>>(istream&, Bilet&);
};

ostream& operator<<(ostream& output, Bilet& bilet) {
	output << "Titlu film: " << bilet.titluFilm << endl;
	output << "Pret: " << bilet.pret << endl;
	output << "Id: " << bilet.id << endl;
	output << endl;
	return output;
}

istream& operator>>(istream& input, Bilet& bilet) {
	cout << "Titlu film: ";

	char buffer[100];
	input >> ws;
	input.getline(buffer, 99);
	bilet.titluFilm = new char[strlen(buffer) + 1];
	strcpy_s(bilet.titluFilm, strlen(buffer) + 1, buffer);

	cout << "Pret:";
	input >> bilet.pret;
	cout << "Rulare id:";
	input >> bilet.rulareId;

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

	int getId() {
		return id;
	}

	void setNume(char* nume) {
		char* copieNume = new char[strlen(nume) + 1];
		strcpy(copieNume, nume);
		this->nume = copieNume;
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

	bool operator<(const Client& client) {
		return id < client.id;
	}

	void serialize(string fileName)
	{
		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
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


	Sala(const Sala& sala) {
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

	void ocupaLoc() {

	}

	void setNume(char* nume) {
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

	void serialize(string fileName)
	{
		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& nrLocuri, sizeof(nrLocuri));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
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

	int getId() {
		return id;
	}

	void setNume(char* nume) {
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

	bool operator<(const Angajat& angajat) {
		return id < angajat.id;
	}

	void serialize(string fileName)
	{
		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& salariu, sizeof(salariu));

		int nrCaractere = strlen(nume);
		f.write((char*)& nrCaractere, sizeof(nrCaractere));
		f.write(nume, nrCaractere + 1);

		f.close();
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

	Rulare(const Rulare& rulare) {
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

	void setData(int data) {
		this->data = data;
	}

	void setFilmId(int filmId) {
		this->filmId = filmId;
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
		return data;
	}

	bool operator!() {
		return false;
	}

	void serialize(string fileName)
	{
		ofstream f;

		f.open(fileName, ios::binary | ios::app);

		f.write((char*)& id, sizeof(id));
		f.write((char*)& data, sizeof(data));
		f.write((char*)& filmId, sizeof(filmId));
		f.write((char*)& salaId, sizeof(salaId));

		f.close();
	}

	friend ostream& operator<<(ostream&, Rulare&);
	friend istream& operator>>(istream&, Rulare&);
};

ostream& operator<<(ostream& output, Rulare& rulare) {
	output << "film id: " << rulare.filmId << endl;
	output << "data: " << rulare.data << endl;
	output << "sala id: " << rulare.salaId << endl;
	return output;
}

istream& operator>>(istream& input, Rulare& rulare) {
	cout << "data:";
	input >> rulare.data;
	cout << "film id:";
	input >> rulare.filmId;
	cout << "sala id:";
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


enum class EditareFilm { titlu, durata, oreRulare };
enum class EditareBilet { titluFilm, pret, rulareId, loc };
enum class EditareClient { nume };
enum class EditareSala { titlu, nrLocuri };
enum class EditareAngajat { nume, salariu };
enum class EditareRulare { dataRulare, filmId, salaId };

class BazaDeDate {
private:
	map<int,Film> filme;
	map<int, Bilet> bilete;
	map<int, Client> clienti;
	map<int, Sala> sali;
	map<int, Angajat> angajati;
	map<int, Rulare> rulari;

public:
	BazaDeDate() {

	}

	void afiseazaSituatieFilme() {
		system("cls");

		map<int, Film>::iterator it;

		for (it = filme.begin(); it != filme.end(); it++)
		{
			cout << it->second;
			cout << endl;
		}

		int i;
		cout << "Apasa 0 pt meniu" << endl;
		cin >> i;

		//Film::deserialize("filme.bin");
	}

	void afiseazaSituatieLocuriLibere() {

	}

	//operatii film
	void adaugaFilm() {
		system("cls");

		Film film;
		cin >> film;

		filme.insert(pair<int, Film>(film.getId(), film));

		film.serialize("filme.bin");

		system("cls");
		int i;
		cout << film << endl;
		cout << "Film adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeFilm() {
		int filmId;
		cout << "Id film";
		cin >> filmId;
		filme.erase(filmId);
	}

	void editeazaFilm(int filmId, EditareFilm optiune) {
		Film film = filme[filmId];

		switch (optiune)
		{
		case EditareFilm::titlu:
			char titlu[100];

			cout << "Titlu nou:" << endl;
			cin.getline(titlu, 100, '\n');

			film.setTitlu(titlu);

			break;

		case EditareFilm::durata:
			int durata;

			cout << "Durata noua: " << endl;
			cin >> durata;

			film.setDurata(durata);

			break;

		case EditareFilm::oreRulare:
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

			break;
		}
	}

	//operatii bilet
	void adaugaBilet() {
		system("cls");

		Bilet bilet;
		cin >> bilet;

		bilete.insert(pair<int, Bilet>(bilet.getId(), bilet));

		system("cls");
		int i;
		cout << bilet << endl;
		cout << "Bilet adaugat! Apasa 0 pt a continua" << endl;
		cin >> i;

	}

	void stergeBilet() {
		int biletId;
		cout << "Id bilet";
		cin >> biletId;

		bilete.erase(biletId);
	}

	void editeazaBilet(int biletId, EditareBilet optiune) {
		Bilet bilet = bilete[biletId];

		switch (optiune)
		{
		case EditareBilet::titluFilm:
			char titlu[100];

			cout << "Titlu nou:" << endl;
			cin.getline(titlu, 100, '\n');

			bilet.setTitluFilm(titlu);

			break;

		case EditareBilet::pret:
			int pret;

			cout << "pret nou: " << endl;
			cin >> pret;

			bilet.setPret(pret);

			break;

		case EditareBilet::rulareId:
			int rulareId;

			cout << "Rulare id nou: " << endl;
			cin >> rulareId;

			//verifica daca exista rulare
			if (rulari.find(rulareId) == rulari.end()) {
				cout << "Rularea nu exista!" << endl;
			}
			else {
				bilet.setRulareId(rulareId);
			}

			break;

		case EditareBilet::loc:
			int loc;

			cout << "Loc nou: " << endl;
			cin >> loc;

			bilet.setLoc(loc);

			break;
		}
	}

	//operatii sala
	void adaugaSala() {
		system("cls");

		Sala sala;
		cin >> sala;

		sali.insert(pair<int, Sala>(sala.getId(), sala));

		system("cls");
		int i;
		cout << sala << endl;
		cout << "Sala adaugata! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeSala() {
		int salaId;
		cout << "Id sala";
		cin >> salaId;

		sali.erase(salaId);
	}

	void editeazaSala(int salaId, EditareSala optiune) {
		Sala sala = sali[salaId];

		switch (optiune)
		{
		case EditareSala::titlu:
			char nume[100];

			cout << "Nume nou:" << endl;
			cin.getline(nume, 100, '\n');

			sala.setNume(nume);

			break;

		case EditareSala::nrLocuri:
			int nrLocuri;

			cout << "Nr Locuri nou: " << endl;
			cin >> nrLocuri;

			sala.setNrLocuri(nrLocuri);

			break;
		}
	}

	//operatii client
	void adaugaClient() {
		system("cls");

		Client client;
		cin >> client;

		clienti.insert(pair<int, Client>(client.getId(), client));

		system("cls");
		int i;
		cout << client << endl;
		cout << "Client adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeClient() {
		int clientId;
		cout << "Id client";
		cin >> clientId;

		clienti.erase(clientId);
	}

	void editeazaClient(int clientId, EditareClient optiune) {
		Client client = clienti[clientId];

		switch (optiune)
		{
		case EditareClient::nume:
			char nume[100];

			cout << "Nume nou:" << endl;
			cin.getline(nume, 100, '\n');

			client.setNume(nume);

			break;
		}
	}

	//operatii angajat
	void adaugaAngajat() {
		system("cls");

		Angajat angajat;
		cin >> angajat;

		angajati.insert(pair<int, Angajat>(angajat.getId(), angajat));

		system("cls");
		int i;
		cout << angajat << endl;
		cout << "Angajat adaugat! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeAngajat() {
		int angajatId;
		cout << "Id angajat";
		cin >> angajatId;
		angajati.erase(angajatId);
	}

	void editeazaAngajat(int angajatId, EditareAngajat optiune) {
		Angajat angajat = angajati[angajatId];

		switch (optiune)
		{
		case EditareAngajat::nume:
			char nume[100];

			cout << "Nume nou:" << endl;
			cin.getline(nume, 100, '\n');

			angajat.setNume(nume);

			break;

		case EditareAngajat::salariu:
			double salariu;

			cout << "Salariu nou:" << endl;
			cin >> salariu;

			angajat.setSalariu(salariu);

			break;
		}
	}

	//operatii rulare
	void adaugaRulare() {
		system("cls");

		Rulare rulare;
		cin >> rulare;

		rulari.insert(pair<int, Rulare>(rulare.getId(), rulare));

		system("cls");
		int i;
		cout << rulare << endl;
		cout << "Rulare adaugata! Apasa 0 pt meniu" << endl;
		cin >> i;
	}

	void stergeRulare() {
		int rulareId;
		cout << "Id rulare";
		cin >> rulareId;

		rulari.erase(rulareId);
	}

	void editeazaRulare(int rulareId, EditareRulare optiune) {
		Rulare rulare = rulari[rulareId];

		switch (optiune)
		{
		case EditareRulare::dataRulare:
			int dataRulare;

			cout << "Data rulare noua:" << endl;
			cin >> dataRulare;

			rulare.setData(dataRulare);

			break;

		case EditareRulare::filmId:
			int filmId;

			cout << "Film id nou:" << endl;
			cin >> filmId;

			rulare.setFilmId(filmId);

			break;

		case EditareRulare::salaId:
			int salaId;

			cout << "Sala id noua:" << endl;
			cin >> salaId;

			rulare.setSalaId(salaId);

			break;
		}
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
	cout << "8: Optiuni anagajat" << endl;
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


int main()
{
	BazaDeDate bd;

	int optiuneMeniu;
	do
	{
		optiuneMeniu = afiseazaMeniu();

		switch (optiuneMeniu)
		{
		case 3: {
			bd.afiseazaSituatieFilme();
			break;
		}

		case 4: {

			int optiuneBilet = afiseazaOptiuniBilet();

			switch (optiuneBilet)
			{
			case 1:
				bd.adaugaBilet();
			case 3:
				bd.stergeBilet();
			default:
				break;
			}

			break;
		}

		case 5: {

			int optiuneFilm = afiseazaOptiuniFilm();

			switch (optiuneFilm)
			{
			case 1:
				bd.adaugaFilm();
			case 3:
				bd.stergeFilm();
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
			case 1:
				bd.adaugaClient();
			case 3:
				bd.stergeClient();
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
			case 1:
				bd.adaugaSala();
			case 3:
				bd.stergeSala();
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
			case 1:
				bd.adaugaAngajat();
			case 3:
				bd.stergeAngajat();
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
			case 1:
				bd.adaugaRulare();
			case 3:
				bd.stergeRulare();
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