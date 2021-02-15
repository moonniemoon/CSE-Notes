#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <set>

#define FILE_ERROR 1;

using namespace std;

class CPerson {
private:
	string m_strEGN;
	string m_strName;
public:
	CPerson() { //Default
		m_strName = "N/A";
		m_strEGN = "N/A";
	}
	CPerson (const string& strName, const string& strEGN) : //Explicit
		m_strName(strName),
		m_strEGN(strEGN)
	{}

	//Operators
	bool operator < (const CPerson& obj) const {  // sort, set_difference
		return (m_strEGN < obj.m_strEGN);         //if i create a get(), put obj.getEGN()
	}
	bool operator == (const CPerson& obj) const { // unique_copy 
		return (m_strEGN == obj.m_strEGN);
	}

	//Operators << and >>
	friend ostream& operator << (ostream& out, const CPerson& obj) {
		out << obj.m_strEGN << " " << obj.m_strName;
		return out;
	}
	friend istream& operator >> (istream& in, CPerson& obj) {
		in >> obj.m_strEGN >> obj.m_strName;
		return in;
	}
};

class CCity {
private:
	string m_strCityName;
	vector<CPerson> m_person;
public:
	CCity(const string& city_name, const vector <CPerson>& c) {
		m_strCityName = city_name;
		m_person = c;
	}
	CCity(const char* filename) {
		ifstream ifile(filename); //fstream (filename, ios_base::in) ?
		if (ifile.good()) {
			Input(ifile);
			ifile.close();
		}
		else throw FILE_ERROR;
	}
	//Output-Input vector
	ostream& Output(ostream& out) const {
		copy(m_person.begin(), m_person.end(), ostream_iterator<CPerson>(out, "\n"));
		return out;
	}
	istream& Input(istream& in) {
		CPerson person;
		string city_name;
		in >> city_name;
		m_strCityName = city_name;
		m_person.clear();
		copy(istream_iterator<CPerson>(in), istream_iterator<CPerson>(), back_inserter(m_person));
		return in;
	}
	friend istream& operator >> (istream& in, CCity& obj) {
		obj.Input(in);
		return in;
	}

	vector<CPerson> DuplicateEGN() {
		vector<CPerson> result, temp;
		vector<CPerson> ve(m_person.begin(), m_person.end());
		sort(ve.begin(), ve.end());                               // vector nqma sobstven sort, tozi e ot <alg>
		unique_copy(ve.begin(), ve.end(), back_inserter(temp)); // namerihme ednakvite
		//copy(temp.begin(), temp.end(), ostream_iterator<CPerson>(cout, "\n"));
		// 1 2 3 4 5 6
		set_difference(ve.begin(), ve.end(), temp.begin(), temp.end(), back_inserter(result)); //or set_symmetric_difference
		// 1 1 4
		return result;
	}
	void DeleteDuplicatedEGN() {
		vector<CPerson> del_dup(m_person.begin(), m_person.end());
		vector<CPerson> u;
		sort(del_dup.begin(), del_dup.end());
		unique_copy(del_dup.begin(), del_dup.end(), back_inserter(u));
		m_person.clear();
		m_person = u;
		Output(cout);
	}
	
	void removeVector(vector<CPerson>& toRemove) {
		vector<CPerson> v = m_person, result;
		sort(v.begin(), v.end());
		sort(toRemove.begin(), toRemove.end());
		set_difference(v.begin(), v.end(), toRemove.begin(), toRemove.end(), back_inserter(result));
		m_person.clear();
		m_person = result;
	}
	
};


int main() {
	CCity city("Person.txt");
	
	cout << "Everyone (Duplicates included): \n";
	city.Output(cout);

	cout << "\nDuplicates: \n";
	vector<CPerson> examp = city.DuplicateEGN();
	copy(examp.begin(), examp.end(), ostream_iterator<CPerson>(cout, "\n"));

	cout << "\nVector after deleting duplicates: " << endl;
	city.DeleteDuplicatedEGN();
	
	
	cout << "\nVector after  removing an element:\n";

	vector<CPerson> removeVector{
		{"c", "0000002"}              // check default in class CPerson - first name, second egn
	};
	city.removeVector(removeVector);
	city.Output(cout);

	system("pause");
	return 0;
}



