/*
	Author: Kat Bergen

	Three classes to handle the parking lot. 
	1) Platzsuchender: person searching for a parking space
	2) Stellplatz: parking spot with id
	3) Parkhaus: parking lot management system

	v1 06.12.2020
*/

#ifndef PARKHAUS_H
#define PARKHAUS_H

#include "myArray.h"
#include <string>

class Platzsuchender {
private:
	std::string kennzeichen;

public:
	Platzsuchender();
	Platzsuchender(const std::string& kennzeichen);

	std::string getKennzeichen();
	void setKennzeichen(const std::string& kennzeichen_);
};

class Stellplatz {
private:
	int id;
	bool isFree;
	bool isRentable;
	Platzsuchender* kunde;

public:
	Stellplatz();
	~Stellplatz();

	int getId() const;
	void setId(int id_); 

	bool getIsFree() const;
	void setIsFree(bool isFree_);
	
	bool getIsRentable() const;
	void setIsRentable(bool isRentable_);

	Platzsuchender* getKunde() const;
	void setKunde(const std::string& kennzeichen);

	void print() const;
};

std::string boolToString(bool b);

class Parkhaus {
private:
	MyArray<Stellplatz, 10> parkplaetze{ Stellplatz() };

public:
	Parkhaus();
	~Parkhaus();

	void platzVergeben(const int& platzart);
	void platzFreigeben();

	void printAll();
	void printFree(); 
	void printRentable();
	void anzahlFreierPlätze();
	
	void returnToMenue();
	void menue(); 
	
};

#endif // !PARKHAUS_H
