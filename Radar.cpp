//112 -19621447 -kst1a
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>
#include <list>
#include <iterator>

#define FILE_ERROR 0;

using namespace std;

class CRadar {
private:
	string m_strRegNum;
	int m_iSpeed;
public:
	CRadar() : m_strRegNum(" "), m_iSpeed(0) {}
	CRadar(const string& regnum, const int& speed) :
		m_strRegNum(regnum),
		m_iSpeed(speed)
	{}
	CRadar(const CRadar& c) :
		m_strRegNum(c.m_strRegNum),
		m_iSpeed(c.m_iSpeed)
	{}

	const string& getRegNum() const {
		return m_strRegNum;
	}
	const int& getSpeed() const {
		return m_iSpeed;
	}

	friend ostream& operator << (ostream& os, const CRadar& obj) {
		os << obj.m_strRegNum << " " << obj.m_iSpeed;
		return os;
	}
	friend istream& operator >> (istream& is, CRadar& obj) {
		is >> obj.m_strRegNum >> obj.m_iSpeed;
		return is;
	}

	//bool operator <(const CRadar& obj) { // in case i use sort
	//	return m_strRegNum < obj.m_strRegNum;
	//}
	bool operator == (const CRadar& obj) {
		return m_strRegNum == obj.m_strRegNum;
	}
	CRadar& operator = (const CRadar& c) {
		m_strRegNum = c.m_strRegNum;
		m_iSpeed = c.m_iSpeed;
		return *this;
	}
};

class CRadarCollection {
private:
	list<CRadar> database;
public:
	CRadarCollection(const string& filename) {
		fstream ifile(filename, ios_base::in);  
		if (ifile.good()) {
			Input(ifile);
			ifile.close();
		}
		else throw FILE_ERROR;
	}
	istream& Input(istream& in) {
		database.clear();
		copy(istream_iterator<CRadar>(in), istream_iterator<CRadar>(), back_inserter(database));
		return in;
	}
	friend istream& operator >> (istream& in, CRadarCollection& obj) {
		obj.Input(in);
		return in;
	}
	ostream& Output(ostream& out) const {
		copy(database.begin(), database.end(), ostream_iterator<CRadar>(out, "\n"));
		return out;
	}
	friend ostream& operator << (ostream& out, const  CRadarCollection& obj) {
		obj.Output(out);
		return out;
	}

	void Register(const string& RegNum, const int& Speed) {

		if (findRadar(RegNum)) {
			// register the car with the highest speed (replace it with the new data)
		
			CRadar temp_car(RegNum, Speed);                                  // 3029, 90
			CRadar temp(RegNum, findRadar(RegNum));                          // 3029, 62

			if (temp_car.getSpeed() > temp.getSpeed()) {
				replace(database.begin(), database.end(), temp, temp_car);   // 3029 62 stava -> 3029 90
			}
		}
		else { // if car not found in the list
			database.emplace_back(RegNum, Speed);
		}
	}
	int findRadar(const string& RegNum) {
		// find the car from reg number, return speed (trqbva accessor)
		// if there isn't a car with that reg number, return 0
		CRadar temp_car(RegNum, 0);
		auto it = find(database.begin(), database.end(), temp_car);
		if (it != database.end())
			return (*it).getSpeed();                       
		else
			return 0;
	}

	void deleteHide(const string& RegNum) {
		// find the car from reg number and delete it 
		CRadar temp_car(RegNum, 0);
		auto it = find(database.begin(), database.end(), temp_car);
		if (it != database.end())
			database.erase(it);
	}

	vector<CRadar> Speeding(const int& SpeeD) { 
		// create a vector 
		// if any cars speed is more than the parameter SpeeD, insert the cars in the vector 
		vector<CRadar> speedy;
		CRadar limit("", SpeeD);
		for (auto it = database.begin(); it != database.end(); it++) {
			if ((*it).getSpeed() > limit.getSpeed())
				speedy.push_back(*it);
		}
		return speedy;
	}

	void GetAvgSpeed(const int& SpeeD) { 
		double average = 0;
		list<double> speedy;
		CRadar limit("", SpeeD);
		for (auto it = database.begin(); it != database.end(); it++) {
			if ((*it).getSpeed() > limit.getSpeed()) {
				speedy.push_back((*it).getSpeed());
			}
		}
		average = accumulate(speedy.begin(), speedy.end(), 0.0) / speedy.size();
		cout << average;
	}
};

int main() {
	CRadarCollection obj("registeredCars.txt");

	cout << "Radar Collection: " << endl;
	obj.Output(cout);

	cout << "\nRegistering new car to the list: \n";
	obj.Register("3029", 90);
	obj.Output(cout);

	cout << "\nDelete car info from given Reg Number: \n";
	obj.deleteHide("1058");
	obj.Output(cout);

	cout << "\nCars faster than 60km/h (Speed ticket!): \n";
	vector<CRadar> v = obj.Speeding(60);
	copy(v.begin(), v.end(), ostream_iterator<CRadar>(cout, "\n"));

	cout << "\nAverage speed of cars who got speed tickets (>=60km/h): \n";
	obj.GetAvgSpeed(60);
	cout << endl;

	system("pause");
	return 0;
}

// output: 
/*Radar Collection:
0996 120
4820 89
3295 100
2985 91
3283 50
2592 70
1058 60
3029 62

Registering new car to the list:
0996 120
4820 89
3295 100
2985 91
3283 50
2592 70
1058 60
3029 90

Delete car info from given Reg Number:
0996 120
4820 89
3295 100
2985 91
3283 50
2592 70
3029 90

Cars faster than 60km/h (Speed ticket!):
0996 120
4820 89
3295 100
2985 91
2592 70
3029 90

Average speed of cars who got speed tickets (>=60km/h):
93.3333*/