// 19621447 - 1A - KST - SELIN TAHSIN KAYAR - zadanie 4
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#define FILE_ERROR 0

using namespace std;

class LibraryBook {
private:
	string m_strName;
	string m_strAuthor;
	bool m_bSituation;
public:
	LibraryBook() : m_strName(""), m_strAuthor(""), m_bSituation(0){}
	LibraryBook(const string& name, const string& author) {
		m_strName = name;
		m_strAuthor = author;
	}
	LibraryBook(const string& name, const string& author, const bool& Available) {
		m_strName = name; 
		m_strAuthor = author;
		m_bSituation = Available;
	}

	const string& getAuthor() const {
		return m_strAuthor;
	}
	const string& getName() const {
		return m_strName;
	}
	const int& getAvailability() const {
		return m_bSituation;
	}

	void TakeBook() {
		m_bSituation = 1; 
	}
	void ReturnBook() {
		m_bSituation = 0; 
	}

	// operator == (check's every data)
	bool operator == (const LibraryBook& obj) {
		return ((m_strName == obj.m_strName) && (m_strAuthor == obj.m_strAuthor) && (m_bSituation == obj.m_bSituation));
	}
	bool operator < (const LibraryBook& obj) {  // Sort
		return m_strName < obj.m_strName;
	}
	
	friend ostream& operator << (ostream& os, const LibraryBook& obj) {
		os << obj.m_strName << " " << obj.m_strAuthor << " " << obj.m_bSituation;
		return os;
	}
	friend istream& operator >> (istream& is, LibraryBook& obj) {
		is >> obj.m_strName >> obj.m_strAuthor >> obj.m_bSituation;
		return is;
	}

};

class Library {
private: 		
	vector<LibraryBook> alphabet;
	string m_LibraryName;
	int m_stelaj;
	int m_CapacityOfStelaj;
	multimap<int, LibraryBook> mmap_location;    // stelaj no, kniga
	map<char, int> map_search;  // for searching a letter from the name, from stelaj no
public:
	Library(const string& filename) {

		fstream ifile(filename, ios_base::in);
		if (ifile.good()) {
			Input(ifile);
			ifile.close();
		}
		else throw FILE_ERROR;
	}

	istream& Input(istream& in) {
		in >> m_LibraryName >> m_stelaj >> m_CapacityOfStelaj;

		copy(istream_iterator<LibraryBook>(in), istream_iterator<LibraryBook>(), inserter(alphabet, alphabet.end()));
		SortVector();

		int i = 0, j = 0;
		for (auto it = alphabet.begin(); it != alphabet.end(); it++) {

			if (j < m_CapacityOfStelaj) {
				mmap_location.insert(make_pair((i + 1), *it));
				j++;
			}
			else {
				i++, j = 0;
				mmap_location.insert(make_pair(i + 1, *it));
				j++;
			}
			
		}
		return in;
	}
	friend istream& operator >> (istream& in, Library& obj) {
		obj.Input(in);
		return in;
	}
	ostream& Output(ostream& out) const {
		copy(alphabet.begin(), alphabet.end(), ostream_iterator<LibraryBook>(out, "\n"));
		return out;
	}
	friend ostream& operator << (ostream& out, const  Library& obj) {
		obj.Output(out);
		return out;
	}
	void SortVector() {
		sort(alphabet.begin(), alphabet.end());
	}


	vector<LibraryBook> AvailableBooks(const int& stelaj_no) {
		vector<LibraryBook> available;
		pair<multimap<int, LibraryBook>::iterator, multimap<int, LibraryBook>::iterator> res;
		res = mmap_location.equal_range(stelaj_no);
		for (auto it = res.first; it != res.second; ++it) {
			if ((*it).second.getAvailability() == 1)
				available.push_back((*it).second);
		}
		return available;
	}
	vector<LibraryBook> UnvailableBooks(const int& stelaj_no) {  // I can add this func. as "else" to the "AvailableBooks" function
																	// but the question says create another function? -not specified detailly
		vector<LibraryBook> available;
		pair<multimap<int, LibraryBook>::iterator, multimap<int, LibraryBook>::iterator> res;
		res = mmap_location.equal_range(stelaj_no);
		for (auto it = res.first; it != res.second; ++it) {
			if ((*it).second.getAvailability() == 0)
				available.push_back((*it).second);
		}
		return available;
	}

	LibraryBook findAvailable(const string& name) {
		LibraryBook temp;
		for (auto it = mmap_location.begin(); it != mmap_location.end(); it++) {
			if (((*it).second.getName() == name) && (*it).second.getAvailability() == 0) {
				temp = (*it).second;
			}
		}
		return temp;
	}
	void getsBook(const string& name) {
		LibraryBook thebook = findAvailable(name);
		thebook.TakeBook();
		replace(alphabet.begin(), alphabet.end(), findAvailable(name), thebook);
	}

	LibraryBook findUnavailable(const string& name) {
		LibraryBook temp;
		for (auto it = mmap_location.begin(); it != mmap_location.end(); it++) {
			if (((*it).second.getName() == name) && (*it).second.getAvailability() == 1) {
				temp = (*it).second;
			}
		}
		return temp;
	}
	void returnsBook(const string& name) {
		LibraryBook thebook1 = findUnavailable(name);
		thebook1.ReturnBook();
		replace(alphabet.begin(), alphabet.end(), findUnavailable(name), thebook1);
	}

};

int main() {
	Library obj("file.txt");
	cout << "file.txt Data: \n";
	obj.Output(cout);
	cout << endl;

	cout << "\nAvailable books in stelaj 1: \n";
	vector<LibraryBook> v = obj.AvailableBooks(1);
	copy(v.begin(), v.end(), ostream_iterator<LibraryBook>(cout, "\n"));
	cout << endl;

	cout << "\nUnavailable books in stelaj 2: \n";
	vector<LibraryBook>v1 = obj.UnvailableBooks(2);
	copy(v1.begin(), v1.end(), ostream_iterator<LibraryBook>(cout, "\n"));
	cout << endl;

	cout << "\nSomeone gets the book with name 'THE_GREAT_GATSBY': \n";
	obj.getsBook("THE_GREAT_GATSBY");
	obj.Output(cout);
	cout << endl;

	cout << "\nSomeone returns the book with name 'THE_GREAT_GATSBY2':\n";
	obj.returnsBook("THE_GREAT_GATSBY2");
	obj.Output(cout);

	return 0;
}
/*
 OUTPUT: 
file.txt Data :
ANIMAL_FARM ORWELL 0
ANIMAL_FARM_2 ORWELL 1
ANIMAL_FARM_3 ORWELL 1
PRIDE_AND_PREJUDICE AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 0
THE_GREAT_GATSBY FITZGERALD 0
THE_GREAT_GATSBY2 FITZGERALD 1
THE_GREAT_GATSBY3 FITZGERALD 1
THE_LITTLE_PRINCE ANTOINE 0
THE_LITTLE_PRINCE2 ANTOINE 1
THE_LITTLE_PRINCE3 ANTOINE 1
TO_KILL_A_MOCKINGBIRD LEE 1
TO_KILL_A_MOCKINGBIRD2 LEE 1
TO_KILL_A_MOCKINGBIRD3 LEE 1

Available books in stelaj 1:
ANIMAL_FARM_2 ORWELL 1
ANIMAL_FARM_3 ORWELL 1
PRIDE_AND_PREJUDICE AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 1

Unavailable books in stelaj 2:
PRIDE_AND_PREJUDICE3 AUSTEN 0
THE_GREAT_GATSBY FITZGERALD 0
THE_LITTLE_PRINCE ANTOINE 0

Someone gets the book with name 'THE_GREAT_GATSBY':
ANIMAL_FARM ORWELL 0
ANIMAL_FARM_2 ORWELL 1
ANIMAL_FARM_3 ORWELL 1
PRIDE_AND_PREJUDICE AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 0
THE_GREAT_GATSBY FITZGERALD 1
THE_GREAT_GATSBY2 FITZGERALD 1
THE_GREAT_GATSBY3 FITZGERALD 1
THE_LITTLE_PRINCE ANTOINE 0
THE_LITTLE_PRINCE2 ANTOINE 1
THE_LITTLE_PRINCE3 ANTOINE 1
TO_KILL_A_MOCKINGBIRD LEE 1
TO_KILL_A_MOCKINGBIRD2 LEE 1
TO_KILL_A_MOCKINGBIRD3 LEE 1

Someone returns the book with name 'THE_GREAT_GATSBY2':
ANIMAL_FARM ORWELL 0
ANIMAL_FARM_2 ORWELL 1
ANIMAL_FARM_3 ORWELL 1
PRIDE_AND_PREJUDICE AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 1
PRIDE_AND_PREJUDICE3 AUSTEN 0
THE_GREAT_GATSBY FITZGERALD 1
THE_GREAT_GATSBY2 FITZGERALD 0
THE_GREAT_GATSBY3 FITZGERALD 1
THE_LITTLE_PRINCE ANTOINE 0
THE_LITTLE_PRINCE2 ANTOINE 1
THE_LITTLE_PRINCE3 ANTOINE 1
TO_KILL_A_MOCKINGBIRD LEE 1
TO_KILL_A_MOCKINGBIRD2 LEE 1
TO_KILL_A_MOCKINGBIRD3 LEE 1
*/