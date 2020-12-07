#include "parkhaus.h"
#include <iostream>

////////////////////////////////////// Klasse Platzsuchender /////////////////////////////////////////////////////////////

Platzsuchender::Platzsuchender() : kennzeichen{}
{}

Platzsuchender::Platzsuchender(const std::string& kennzeichen) : kennzeichen{ kennzeichen }
{}

std::string Platzsuchender::getKennzeichen()
{
	return kennzeichen;
}

void Platzsuchender::setKennzeichen(const std::string& kennzeichen_)
{
	kennzeichen = kennzeichen_;
}


////////////////////////////////////// Klasse Stellplatz /////////////////////////////////////////////////////////////

Stellplatz::Stellplatz(): id{}, isFree{true}, isRentable{false}, kunde{nullptr}
{}

Stellplatz::~Stellplatz()
{
	delete kunde;
	kunde = nullptr;
}

int Stellplatz::getId() const
{
	return id;
}

void Stellplatz::setId(int id_)
{
	id = id_;
}

bool Stellplatz::getIsFree() const
{
	return isFree;
}

void Stellplatz::setIsFree(bool isFree_)
{
	isFree = isFree_;
}

bool Stellplatz::getIsRentable() const
{
	return isRentable;
}

void Stellplatz::setIsRentable(bool isRentable_)
{
	isRentable = isRentable_;
}

//bool Stellplatz::getIsRented()
//{
//	if (kunde == nullptr) return false;
//	return true;
//}

Platzsuchender* Stellplatz::getKunde() const
{
	return kunde;
}

void Stellplatz::setKunde(const std::string& kennzeichen)
{
	kunde = new Platzsuchender{kennzeichen};
}

void Stellplatz::print() const
{
	std::cout << "\nParkplatznummer: " << id << ", Parkplatz Frei: " << boolToString(isFree) << ", Langzeitparkplatz: " << boolToString(isRentable);
}


/// Hilfsmethode Stellplatz ///
std::string boolToString(bool b)
{
	switch (b)
	{
	case true: return "Ja";
	case false: return "Nein";
	}
}


////////////////////////////////////// Klasse Parkhaus /////////////////////////////////////////////////////////////

Parkhaus::Parkhaus() : parkplaetze{}
{
	for (int i{}; i < 10; ++i)	parkplaetze[i].setId(i + 1);
	for (int i{}; i < 3; ++i) parkplaetze[i].setIsRentable(true);
}

Parkhaus::~Parkhaus()
{
	for (int i{ }; i < 10; ++i) parkplaetze[i].~Stellplatz();
}

void Parkhaus::platzVergeben(const int& platzart)
{
	//platzart 1: Freiplatz, platzart 2: Mietplatz

		switch (platzart)
		{
		case 1: //Freiplatz vergeben
			for (int i{}; i < 10; ++i)
			{
				if (parkplaetze.at(i).getIsRentable() == false
					&& parkplaetze.at(i).getIsFree() == true)
				{
					parkplaetze.at(i).setIsFree(false);

					cout << "\nDer Parkplatz des Kunden hat die Nummer " << parkplaetze.at(i).getId();
					return;
				}
			}
		case 2: //Langzeitmietplatz vergeben
			for (int i{}; i < 10; ++i)
			{
				if (parkplaetze.at(i).getIsRentable() == true
					&& parkplaetze.at(i).getIsFree() == true)
				{
					parkplaetze.at(i).setIsFree(false);

					std::string input{};
					cout << " Der Kunde muss Ihnen nun das Kennzeichen seines Autos nennen. Bitte tippen Sie es hier ohne Leerzeichen ein: \n>";
					std::cin >> input;
					if (!std::cin) throw std::runtime_error{ "incorrect input at Parkhaus::platzVergeben()." };
					parkplaetze.at(i).setKunde(input);

					cout << "\nDer Parkplatz des Kunden hat die Nummer " << parkplaetze.at(i).getId();
					return;
				}
			}
		default: 
			cout << "\nEs sind keine freien Plaetze verfuegbar.";
		}
}

void Parkhaus::platzFreigeben()
{
	int platzId{};

	cout << "\n\nBitte geben Sie die Nummer des Platzes ein, den Sie freigeben moechten.\n>";
	std::cin >> platzId;
	if (!std::cin) throw std::runtime_error{ "incorrect input at Parkhaus::platzFreigeben()" };

	for (int i{}; i < 10; ++i)
	{
		if (platzId == parkplaetze.at(i).getId() 
			&& parkplaetze.at(i).getIsFree() == false) 
		{
			parkplaetze[i].setIsFree(true);

			if (parkplaetze.at(i).getIsRentable() == true)
			{
				parkplaetze[i].~Stellplatz();
			}

			cout << "\nParkplatz Nummer " << platzId << " kann nun neu vermietet werden. ";

			return;
		}
	}
	cout << "\nDer Parkplatz Nummer " << platzId << " war bereits frei. Bitte versuchen Sie es nochmal. ";	
}

void Parkhaus::printAll()
{
	for (int i{}; i < 10; ++i)
	{
		parkplaetze.at(i).print();
	}
}

void Parkhaus::printFree()
{
	for (int i{}; i < 10; ++i)
	{
		if (parkplaetze.at(i).getIsFree() == true)
		{
			parkplaetze.at(i).print();
		}
	}
}

void Parkhaus::printRentable()
{
	for (int i{}; i < 10; ++i)
	{
		if (parkplaetze.at(i).getIsRentable() == true)
		{
			parkplaetze.at(i).print();
			
			cout << ", Kennzeichen: ";
			if (parkplaetze.at(i).getKunde() != nullptr) cout << parkplaetze.at(i).getKunde()->getKennzeichen();
			else cout << "keins";
		}
	}
}

void Parkhaus::anzahlFreierPlätze()
{
	int counterFree{};
	int counterRental{};

	for (int i{}; i < 10; ++i)
	{
		if (parkplaetze.at(i).getIsFree() == true)
		{
			if (parkplaetze.at(i).getIsRentable() == true)	++counterRental;
			else ++counterFree;
		}
	}
	cout << "Es sind " << counterFree << " Kurzzeitparkplaetze und " << counterRental << " verfuegbar. ";
}


void Parkhaus::returnToMenue()
{
	while (true)
	{
		char menu{};
		cout << "\n\n Moechten Sie zum Menue zurueckkehren? Bitte geben Sie 'j' ein.\n>";
		std::cin >> menu;
		if (!std::cin) throw std::runtime_error{ "incorrect input at Parkhaus::menue()" };
		if (menu == 'j') break;
	}
}

void Parkhaus::menue()
{
	while (true) //always true, unless an error is thrown
	{

		int option{};

		do
		{
			cout << "\n\n---------------------------------------- Menue -----------------------------------------";
			cout << "\nBitte waehlen Sie eine der verfuegbaren Optionen aus: \n\t1: Kurzzeitparkplatz vergeben. \n\t2: Langzeitparkplatz vergeben."
				<< "\n\t3: Parkplatz freigeben. \n\t4: Informationen aller Plaetze ansehen. \n\t5: Informationen aller freier Plaetze ansehen."
				<< "\n\t6: Informationen aller Langzeitmietplaetze ansehen. \n\t7: Anzahl an freien Plaetzen ansehen. "
				<< "\n\n Bitte geben Sie nun die Nummer der Option ein, die sie waehlen moechten.\n>";
			std::cin >> option;
			if (!std::cin) throw std::runtime_error{ "incorrect input at Parkhaus::menue()" };

			if (option == 0 || option > 7) { cout << "\nSie haben nur 7 Optionen. Bitte folgen Sie den Instruktionen auf dem Bildschirm."; };

		} while (option == 0 || option > 7);

		switch (option)
		{
		case 1: case 2:
			platzVergeben(option);
			returnToMenue();
			break;
		case 3:
			platzFreigeben();
			returnToMenue();
			break;
		case 4: 
			printAll();
			returnToMenue();
			break;
		case 5: 
			printFree();
			returnToMenue();
			break;
		case 6:
			printRentable();
			returnToMenue();
			break;
		case 7:
			anzahlFreierPlätze();
			returnToMenue();
			break;
		default:
			break;
		}
	}
}



