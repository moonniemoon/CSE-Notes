#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <list>
#include <fstream>
#include <algorithm>
#include <cctype> // isdigit()

#define FILE_ERROR 1
#define DATA_ERROR 2

using namespace std;

class Car {
protected:
	int m_iPower;
	string m_strModel;
	string m_strRegNumber;
	string m_strOwner;
public:
	Car() { 
		m_iPower = 0;
		m_strModel = "Unknown";
		m_strRegNumber = "Unknown";
		m_strOwner = "Unknown";
	}
	Car(const int& iPower, const string& strModel, const string& strRegNumber, const string& strOwner) { 
		m_iPower = iPower;
		m_strModel = strModel;
		m_strRegNumber = strRegNumber;
		m_strOwner = strOwner;
	}
	Car(const Car& c) { 
		m_iPower = c.m_iPower;
		m_strModel = c.m_strModel;
		m_strRegNumber = c.m_strRegNumber;
		m_strOwner = c.m_strOwner;
	}

	//Get RegNumber
	const string& GetRegNumber()const {
		return m_strRegNumber;
	}

	//Operators << and >>
	friend ostream& operator<<(ostream& out, const Car& obj) {
		out << obj.m_strModel << " " << obj.m_iPower << " " << obj.m_strRegNumber << " " << obj.m_strOwner;
		return out;
	}
	friend istream& operator>>(istream& in, Car& obj) {
		in >> obj.m_strModel >> obj.m_iPower >> obj.m_strRegNumber >> obj.m_strOwner;
		return in;
	}

	//Operators
	bool operator ==(const Car& obj)const {
		return (m_strOwner == obj.m_strOwner);
	}
	bool operator <(const Car& obj)const {
		return (GetRegNumber() < obj.m_strRegNumber);
	}

	//Static members
	static string city_code;                           //Static veriable (city code) - string. For example Varna is "B"
	static map<string, string> code_to_city;           // From "B" to "VARNA"
	static multimap<string, string> city_to_code;      // From "Varna" to "B"

	//Static functions
	static string return_city_code(const string& rn) {
		// For example:  B 1234 B is pn 
		string code;                                   // Code of the city
		for (int i = 0; i < rn.length(); i++) {
			if (!isdigit(rn[i])) {                     //if it's not digit, aka find the strings
				code.push_back(rn[i]);
			}
			else
				break;
		}
		return code;
	}
	static bool is_equal_codes(const Car& obj) {                       
		return (return_city_code(obj.GetRegNumber()) == city_code);
	}
	static string get_code_from_name(const string& city_name) {
		auto it = city_to_code.find(city_name);                //multimap <string, string> city_to_code{ {"Varna" "B"} ... }
		if (it != city_to_code.end()) {
			return (*it).second;                               // Return the secons aka "B"
		}
		else
			cout << "This city does not exist." << endl;
	}
};

string Car::city_code = "B";
map<string, string> Car::code_to_city{
	{"A", "Burgas"},
	{"B", "Varna"},
	{"BH", "Vidin"},
	{"BP", "Vratsa"},
	{"BT", "VelikoTurnovo"},
	{"E", "Blagoevgrad"},
	{"EB", "Gabrovo"},
	{"EH", "Pleven"},
	{"K", "Kardzhali"},
	{"KH", "Kyustendil"},
	{"M", "Montana"},
	{"H", "Shumen"},
	{"OB", "Lovech"},
	{"P", "Ruse"},
	{"PA", "Pazardzhik"},
	{"PB", "Plovdiv"},
	{"C", "Sofia"},
	{"CA", "Sofia"},
	{"CB", "Sofia"},
	{"CH", "Sliven"},
	{"CM", "Smolyan"},
	{"CO", "Sofia"},
	{"CC", "Silistra"},
	{"CT", "StaraZagora"},
	{"T", "Targovishte"},
	{"TX", "Dobrich"},
	{"Y", "Yambol"},
	{"X", "Haskovo"},
};
multimap<string, string> Car::city_to_code{
	{"Burgas","A"},
	{"Varna","B"},
	{"Vidin","BH"},
	{"Vratsa","BP"},
	{"VelikoTurnovo","BT"},
	{"Blagoevgrad","E"},
	{"Gabrovo","EB"},
	{"Pleven","EH"},
	{"Kardzhali","K"},
	{"Kyustendil","KH"},
	{"Montana","M"},
	{"Shumen","H"},
	{"Lovech","OB"},
	{"Ruse","P"},
	{"Pazardzhik","PA"},
	{"Plovdiv","PB"},
	{"Sofia","C"},
	{"Sofia","CA"},
	{"Sofia","CB"},
	{"Sliven","CH"},
	{"Smolyan","CM"},
	{"Sofia","CO"},
	{"Silistra","CC"},
	{"StaraZagora","CT"},
	{"Targovishte","T"},
	{"Dobrich","TX"},
	{"Yambol","Y"},
	{"Haskovo","X"},
};

class Register {
private:
	list <Car> database;
public:
	Register(const char* filename) {               
		fstream ifile(filename, ios_base::in); //ifstream ifile(filename);
		if (ifile.good()) {
			copy(istream_iterator<Car>(ifile), istream_iterator<Car>(), back_inserter(database));
		}
		else
			throw FILE_ERROR;
	}

	string owner_to_RN(const string& own) {           // Finds - Returns Reg Number, parameter Owner
		Car fake_car(0, "", "", own);
		auto it = find(database.begin(), database.end(), fake_car);
		if (it != database.end()) {
			return (*it).GetRegNumber();
		}
		else {
			cout << "Owner does not exist.";
		}
	}

	list<Car> code_to_carlist(const string& code) {     // Creates - Returns list of objects car (parameter. City code)
		list<Car> result;
		Car::city_code = code;
		copy_if(database.begin(), database.end(), back_inserter(result), Car::is_equal_codes);
		return result;
	}

	friend ostream& operator << (ostream& out, const  Register& obj) {
		copy(obj.database.begin(), obj.database.end(), ostream_iterator<Car>(out, "\n"));
		return out;
	}
	friend istream& operator >> (istream& in, Register& obj) {
		copy(istream_iterator<Car>(in), istream_iterator<Car>(), back_inserter(obj.database)); //chetene na kola
		//car iterator = istream input
		return in;
	}

};

int main() {

	try {
		Register data("car_data.txt");                     //Creating object from Register w file
		cout << "\nData from .txt file: \n\n" << data;     //Outputing object <<
		                          
		cout << "\nRegistrations from city:  VARNA\n";     //Creating - Outputing list w code_to_carlist
		list<Car> temp = data.code_to_carlist(Car::get_code_from_name("Varna"));
		copy(temp.begin(), temp.end(), ostream_iterator<Car>(cout, "\n"));

		//Outputs result from owner_to_RN
		cout << "\nOwner1's car registration number is:  " << data.owner_to_RN("Owner1") << "\n";
	}
	catch (int error) {
		switch (error) {
		case FILE_ERROR:
			cout << "File error! " << endl;
			break;
		case DATA_ERROR:
			cout << "Corrupt data. " << endl;
			break;
		}
	}
	return 0;
}
