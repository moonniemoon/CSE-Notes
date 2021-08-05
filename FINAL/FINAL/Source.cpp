#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <list>
#include <iomanip>

#include "color.hpp"  // https://github.com/imfl/color-console

#define FILE_ERROR 0
#define DATA_ERROR 2

using namespace std;

int airportMenu();
int funcMenu(string);
map<string, string> city_to_Code = {
	{"VIENNA", "VIE"},
	{"ISTANBUL", "IST"},
	{"VARNA", "VAR"},
	{"SOFIA", "SOF"},
	{"DOHA", "DOH"},
	{"NEW YORK", "JFK"},
	{"MUNICH", "MUC"},
	{"MIAMI", "MIA"},
	{"PARIS", "CDG"}
};


class Plane {
private:
	string s_AircraftType;
	double d_Hours;

public:
	Plane() : d_Hours(0.0) {}
	Plane(const string& s_AircraftType, const double& d_Hours) {
		this->s_AircraftType = s_AircraftType;
		this->d_Hours = d_Hours;
	}

	const string& getType() const { return s_AircraftType; }
	const double& getHours() const { return d_Hours; }

	friend bool operator < (const Plane& lhs, const Plane& rhs) {
		return lhs.d_Hours < rhs.d_Hours;
	}
	friend bool operator == (const Plane& lhs, const Plane& rhs) {
		return lhs.s_AircraftType == rhs.s_AircraftType;
	}

	friend ostream& operator << (ostream& os, const Plane& obj) {
		os << std::left << setw(13) << obj.s_AircraftType << " | "
			<< std::left << setw(12) << obj.d_Hours;
		return os;
	}
	friend istream& operator >> (istream& is, Plane& obj) {
		is >> obj.s_AircraftType >> obj.d_Hours;
		return is;
	}
};


class Airline : public Plane {
private:
	string s_Airline;
	string s_Nationality;
	map<Plane, unsigned> m_pMadeDes;               
	map<Plane, string> m_pDest;
	multimap<string, unsigned> mm_airlinesDest;     

public:
	Airline() : s_Airline(""), s_Nationality("") {}
	Airline(const string& s_Airline, const string& s_Nationality) {
		this->s_Airline = s_Airline;
		this->s_Nationality = s_Nationality;
	}

	friend ostream& operator << (ostream& os, const Airline& obj) {
		os << "\t+--------------+--------------------------------------------------+\n"; 
		os << "\t| " << std::left << setw(12) << dye::light_yellow("Airline") << " | " << std::left << setw(49) << obj.s_Airline << "|\n";
		os << "\t+--------------+--------------------------------------------------+\n"; 
		os << "\t| " << std::left << setw(12) << dye::light_yellow("Nationality") << " | " << std::left << setw(49) << obj.s_Nationality << "|\n";
		os << "\t+--------------+--------------------------------------------------+\n";
		os << "\t| " << std::left << setw(12) << dye::light_yellow("Destinations") << " | " << std::left << setw(49) << obj.mm_airlinesDest.size() << "|\n";
		os << "\t+--------------+---------------+--------------+-------------------+\n"; 
		os << "\t| " << std::left << setw(12) << dye::light_yellow("Destination") << " | " 
			<< std::left << setw(13) << dye::light_yellow("Aircraft Type") << " | " 
			<< std::left << setw(12) << dye::light_yellow("Flight Hours") << " | " 
			<< std::left << setw(17) << dye::light_yellow("Made Destinations") << " |\n";
		os << "\t+--------------+---------------+--------------+-------------------+\n"; 

		for (auto it = obj.m_pMadeDes.begin(); it != obj.m_pMadeDes.end(); it++) {
			os << "\t| " << std::left << setw(12) << obj.m_pDest.find(it->first)->second << " | " 
				<< setw(28) << it->first << " | "
				<< std::left << setw(17) <<it->second << " |\n";
			os << "\t+--------------+---------------+--------------+-------------------+\n"; 
		}
		return os;
	}

	friend istream& operator >> (istream& is, Airline& obj) {
		Plane temp;
		string destination;
		unsigned madeDes;
		int numFlights;

		is >> obj.s_Airline >> obj.s_Nationality >> numFlights;

		for (int i = 0; i < numFlights; i++) {
			is >> temp;
			is >> destination >> madeDes;
			obj.m_pMadeDes.insert(make_pair(temp, madeDes));
			obj.m_pDest.insert(make_pair(temp, destination));
			
			auto a = obj.mm_airlinesDest.find(destination);
			
			if (a == obj.mm_airlinesDest.end())    // not found
				obj.mm_airlinesDest.insert(make_pair(destination, 1));
			else {
				a->second += 1;
			}
		}
		return is;
	}


	const string& getAirline() const { return s_Airline; }
	const string& getNation() const { return s_Nationality; }

	auto GetPlaneMD() const { return m_pMadeDes; }
	auto GetPlaneMap() const { return m_pDest; }
	auto GetMM() const { return mm_airlinesDest; }

	unsigned getTotalPlanes() const { return m_pMadeDes.size(); }
	unsigned getTotalDiffDest() const { return mm_airlinesDest.size(); }   // returns total number of destinations 

	friend bool operator < (const Airline& lhs, const Airline& rhs) {
		return lhs.mm_airlinesDest < rhs.mm_airlinesDest;
	}
	friend bool operator == (const Airline& lhs, const Airline& rhs) {
		return lhs.m_pDest == rhs.m_pDest;
	}

	// Връща списък от самолети, с летателни часове по малко от 2000 и брой дестинации повече от 10
	// Returns list of planes, with <2000h and 10+ destinations
	list<Plane> listPlanes() const {                       
		list<Plane> temp;

		for (auto it = m_pMadeDes.begin(); it != m_pMadeDes.end(); it++) {
			if (((*it).first.getHours() < 2000) && ((*it).second > 10))
				temp.push_back(it->first);
		}
		return temp;
	}

	// Връща френските авиокомпании за 3-ти клас
	// Returns french airlines
	unsigned averageFrench() const { 
		unsigned count = 0;
		if (s_Nationality == "French") {
			count = getTotalDiffDest();  
		}
		return count;
	}
};




class Airport {
	string s_Airport;
	unsigned u_numFlights;    
	multimap<Airline, unsigned> airline_data;

public:
	Airport() : s_Airport(""), u_numFlights(0) {}
	const string& getAirport() const { return s_Airport; }

	Airport(const string& AirportName, const string& fileName) {
		s_Airport = AirportName;
		fstream ifile(fileName, ios_base::in);  
		if (ifile.good()) {
			while (!ifile.eof()) {
				Airline temp;
				ifile >> temp;
				airline_data.insert(make_pair(temp, temp.getTotalPlanes()));
				u_numFlights += temp.getTotalPlanes();
			}
		}
		else
			throw FILE_ERROR;
	}

	friend ostream& operator << (ostream& os, const Airport& obj) {
		os << "\t Airport: " << obj.s_Airport << endl;
		for (auto it = obj.airline_data.begin(); it != obj.airline_data.end(); it++) {
			os << it->first 
				 << "\t| " << std::left << setw(12) << dye::light_yellow("Tot Flights") << " | " << std::left << setw(49) << it->second << "|\n";
			os << "\t+-----------------------------------------------------------------+" << "\n\n\n\n\n";
		}
		os << "\tThis airport has " << dye::light_yellow(obj.u_numFlights) << " flights!\n\n";
		return os;
	}

	// Изчислява средния брой дестинации на френските авиокомпании
	double franceBased() {
		unsigned count = 0;
		double airline = 0.0;
		double average = 0.0;

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			count += it->first.averageFrench();
			if (it->first.averageFrench() > 0)
				airline++;
		}
		average = count / airline;  
		return average;
	}

    // Показване на конзолата самолетите с летателни часове по-малко от 2000 и брой дестинации повече от 10
	void less2000more10() {          
		list<Plane> temp;
		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			temp.merge((*it).first.listPlanes());
		}
		for (const auto& i : temp) {
			cout << "\t" << dye::light_yellow(i.getType()) << " with " << dye::light_yellow(i.getHours()) << " hours" << endl;
		}
	}


	// При подаден аргумент - марка на самолет, връща броя полети и авиокомпанията
	// Returns the number of flights made with A330 by "Airline Name"
	void flightsAirline(const string& aircraftType) {
		Plane temp(aircraftType, 0.0);
		map<Plane, string> mp;

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			mp = it->first.GetPlaneMap();
			int count = 0;			

			for (auto i = mp.begin(); i != mp.end(); i++) {
				if (i->first.getType() == temp.getType()) {
					count++;
				}			
			}

			if (count > 0) {
				if (count == 1)
					cout << "\n\tThere is " << dye::light_yellow(count) << " flight made with " << aircraftType << " by " << dye::light_yellow(it->first.getAirline());
				else
					cout << "\n\tThere are " << dye::light_yellow(count) << " flights made with " << aircraftType << " by " << dye::light_yellow(it->first.getAirline());
			}
		}
	}


	// При подаден аргумент име на дестинацията, връща името на авиокомпанията, обезпечила най-много полети
	// Returns the airline which has made the most flights to the given destination
	void destAirline(const string& destination) {
		multimap<string, unsigned> mm;
		pair<string, unsigned> d = make_pair("", 0);

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {			
			mm = it->first.GetMM();

			for (auto i = mm.begin(); i != mm.end(); i++) {

				if ((i->first == destination) && (i->second > d.second)) {
					d = make_pair(it->first.getAirline(), i->second);
				}
			}	
		}

		if (!d.first.empty())
			cout << "\n\t" << dye::light_yellow(d.first) << " provides flights to " << dye::light_yellow(destination) << " the most.\n\n";
	}
	
	
	// Връща марка самолет, с най-много собствен брой дестинации
	// variant 1:  - returns the plane type with the most "self" destinations. 
	void typeDest_self() {
		map<Plane, unsigned> m;
		pair<string, unsigned> d = make_pair("", 0);

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			m = it->first.GetPlaneMD();

			for (auto i = m.begin(); i != m.end(); i++) {
				if (i->second > d.second)
					d = make_pair(i->first.getType(), i->second);
			}
		}
		cout << "\n\tType: " << dye::light_yellow(d.first) << " Destinations: " << dye::light_yellow(d.second) << "\n\n";
	}

	// Връща коя марка самолет е използвана най-много в летището
	// variant 2:  - returns the plane type with the most destinations (in the airport) -> "B777 is used the most"
	void typeDest_general() {        
		map<Plane, string> m;
		map<string, unsigned> total;
		multimap<unsigned, string> rev;

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			m = it->first.GetPlaneMap();
			
			for (auto i = m.begin(); i != m.end(); i++) {
				if (total.find(i->first.getType()) == total.end()) {	     // key not found
					total.insert(make_pair(i->first.getType(), 1));
				}
				else {														// found
					unsigned n = total.find(i->first.getType())->second;
					total.at(i->first.getType()) = n + 1;
				}
			}
		}

		for (const auto& it : total)
			rev.insert({ it.second, it.first });
		multimap<unsigned, string>::reverse_iterator it = rev.rbegin();
		auto range = rev.equal_range(it->first);                         // if there's more than 1 "max used" plane
		for (auto it = range.first; it != range.second; it++)
			cout << dye::light_yellow(it->second) << " ";


		cout << "\n\n\tList of how many times an aircraft type has been used:";
		for (const auto& i : total) {
			cout << "\n\t" << i.first << " -> " << dye::light_yellow(i.second);
		}
	}


	// При подаден аргумент авиокомпания, връща дестинацията с най-много полети
	// Returns destinaion with the most flights.
	string airlineDest(const string& airlineName) {
		multimap<string, unsigned> mm;
		Airline temp(airlineName, "");
		
		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			if (it->first.getAirline() == temp.getAirline()) {
				mm = it->first.GetMM();

				unsigned currentMax = 0;
				string arg_Max;

				for (auto i = mm.begin(); i != mm.end(); i++) {
					if (i->second > currentMax) {
						arg_Max = i->first;
						currentMax = i->second;
					}
				}
				return arg_Max;
			}
			else cout << "\n\tAll the destinations are unique\n";
		}
	}

	// Връща контейнер от самолети, съдържащ летателните часове >10000 на всички самолети от авиокомпаниите, ползващи летище София.
	// Returns container of planes, >10000h and dest = SOF
	map<Plane, string> planesLAST() {
		map<Plane, string> m, result;

		for (auto it = airline_data.begin(); it != airline_data.end(); it++) {
			m = it->first.GetPlaneMap();                                           // Plane, string -> [A350, 1257h | SOF] ...
			for (auto i = m.begin(); i != m.end(); i++) {
				if ((i->first.getHours() > 10000) && (i->second == "SOF")) {
					result.insert(make_pair(i->first, i->second));
				}
			}
		}
		return result;
	}
};	



int main() {
	int airportCh;
	int funcCh;
	bool exit = false;
	multimap<string, string> code_to_City;

	try {
		Airport ist("IST", "IST.txt");
		Airport var("VAR", "IST.txt");
		Airport sof("SOF", "IST.txt");
		Airport vie("VIE", "IST.txt");
		Airport cdg("CDG", "IST.txt");
		Airport temp;

		while (!exit) {
			do {
				airportCh = airportMenu();
				switch (airportCh) {
				case 1:
					temp = ist;
					break;
				case 2:
					temp = var;
					break;
				case 3:
					temp = sof;
					break;
				case 4:
					temp = vie;
					break;
				case 5:
					temp = cdg;
					break;
				default:
					cout << "\n\t Please select an airport! (1 - 5)\n";
					system("pause");
				}
			} while (airportCh < 1 || airportCh > 5);

			string s = temp.getAirport();

			do {
				string type, dest, air;
				funcCh = funcMenu(s);
				switch (funcCh) {
				case 1:                                                      // Departures board (print)
					system("cls");
					cout << temp;
					system("pause");
					break;

				case 2:                                                      // The average destinations of airlines based in France
					system("cls");
					cout << "\n\tThe average destinations of airlines based in France is: " << dye::light_yellow(temp.franceBased()) << "\n\n";
					system("pause");
					break;

				case 3:                                                      // Planes with <2000 flight hours and >10 destinations
					system("cls");
					cout << "\n\tThe planes with <2000 flight hours and <10 destinations are: \n\n";
					temp.less2000more10();
					cout << "\n\n";
					system("pause");
					break;

				case 4:                                                      // Search flights by aircraft type
					system("cls");
					cout << "\n\tSearch flight by aircraft type: "; cin >> type;
					transform(type.begin(), type.end(), type.begin(), toupper);
					temp.flightsAirline(type);
					cout << "\n\n";
					system("pause");
					break;

				case 5:                                                      // The airline that has provided the most flights to a given destination
					system("cls");
					cout << "\tThe airline that has provided the most flights to a given destination:\n\n";
					cout << "\tDestination : "; cin >> dest;
					transform(dest.begin(), dest.end(), dest.begin(), toupper);   // algorithm - destinations are with upper case 

					if (city_to_Code.count(dest))                                 // count returns 1 if key exists
						dest = (city_to_Code.find(dest)->second);
					else
						cout << "\n\tNo city named " << dest << " exists!\n";
					temp.destAirline(dest);
					system("pause");
					break;

				case 6:                                                      // The plane whose been to the most destinations
					system("cls");
					cout << "\n\tThe plane whose been to the most destinations is: \n";
					temp.typeDest_self();
					system("pause");
					break;

				case 7:                                                      // Most frequently used aircraft type
					system("cls");
					cout << "\n\tThe most frequently used aircraft type is: ";
					temp.typeDest_general();
					cout << "\n\n";
					system("pause");
					break;

				case 8:                                                      // Most visited destination of a given airline
					system("cls");
					cout << "\n\tMost visited destination of a given airline:\n\n";
					cout << "\tAirline : "; cin >> air;
					transform(air.begin(), air.end(), air.begin(), toupper);
					cout << "\n\tThe most visited destination is: " << dye::light_yellow(temp.airlineDest(air)) << "\n\n";
					system("pause");
					break;

				case 9:                                                      // Planes which destination is Sofia and has >10000 flight hours
					system("cls");
					cout << "\n\tPlanes whose destination is Sofia and has >10000 flight hours:\n";
					if (s == "SOF")
						cout << "\n\tThis is airport SOF, no need to search!";
					else {
						for (const auto& i : temp.planesLAST()) {
							cout << "\n\t" << i.first.getType() << " " << i.first.getHours() << " " << i.second;
						}
						cout << "\n\n";
					}
					system("pause");
					break;
				case 10:                                                     // Change airport
					break;
				case 11:                                                     // Exit program
					exit = true;  // end while
					break;
				default:
					cout << "\n\t Please select something between 1 and 11!\n";
				}
			} while (funcCh != 11 && !(funcCh < 1 || funcCh > 9));   // if 10 is pressed - it will restart the while loop
			// if 11 is pressed - it will end the while loop
		}
	}
	catch (int error) {
		switch (error) {
		case FILE_ERROR:
			cout << "File error! " << endl;
			break;
		case DATA_ERROR:
			cout << "Corrupt data! " << endl;
			break;
		}
	}
	return 0;
}


int airportMenu() {
	int ch;
	char prev = cout.fill(' ');
	system("cls");
	cout << "\n\t +===========================+";
	cout << "\n\t |" << setw(22) << dye::light_yellow("Select an airport") << setw(6) << "|";
	cout << "\n\t +===========================+";
	cout << "\n\t |\t" << dye::light_yellow("1.  ") << "IST" << "              |";
	cout << "\n\t |\t" << dye::light_yellow("2.  ") << "VAR" << "              |";
	cout << "\n\t |\t" << dye::light_yellow("3.  ") << "SOF" << "              |";
	cout << "\n\t |\t" << dye::light_yellow("4.  ") << "VIE" << "              |";
	cout << "\n\t |\t" << dye::light_yellow("5.  ") << "CDG" << "              |";
	cout << "\n\t +===========================+";
	cout << "\n\n\t" << dye::light_yellow(" Choice: ");
	cin >> ch;
	return ch;
}


int funcMenu(string airportName) {
	system("cls");
	int ch;
	int l = 41 + ((7 + airportName.size()) / 2);      // something like align:center 
	int r = 83 - l;
	cout << "\n\t +==================================================================================+";
	cout << "\n\t |" << setw(l) << dye::light_yellow("Airport " + airportName) << setw(r) << "|";
	cout << "\n\t +==================================================================================+";
	cout << "\n\t |                                                                                  |";
	cout << "\n\t |\t" << dye::light_yellow("1.  ") << "Departures board (print)" << "                                                |";
	cout << "\n\t |\t" << dye::light_yellow("2.  ") << "The average destinations of airlines based in France" << "                    |";
	cout << "\n\t |\t" << dye::light_yellow("3.  ") << "Planes with <2000 flight hours and >10 destinations" << "                     |";
	cout << "\n\t |\t" << dye::light_yellow("4.  ") << "Search flights by aircraft type" << "                                         |";
	cout << "\n\t |\t" << dye::light_yellow("5.  ") << "The airline that has provided the most flights to a given destination" << "   |";
	cout << "\n\t |\t" << dye::light_yellow("6.  ") << "The plane whose been to the most destinations" << "                           |";
	cout << "\n\t |\t" << dye::light_yellow("7.  ") << "Most frequently used aircraft type" << "                                      |";
	cout << "\n\t |\t" << dye::light_yellow("8.  ") << "Most visited destination of a given airline" << "                             |";
	cout << "\n\t |\t" << dye::light_yellow("9.  ") << "Planes whose destination is Sofia and has >10000 flight hours" << "           |";   
	cout << "\n\t |\t" << dye::light_yellow("10. ") << "Change airport" << "                                                          |";
	cout << "\n\t |\t" << dye::light_yellow("11. ") << "Exit program" << "                                                            |";
	cout << "\n\t |                                                                                  |";
	cout << "\n\t +==================================================================================+";
	cout << "\n\n\t" << dye::light_yellow(" Choice: ");
	cin >> ch;
	return ch;
}