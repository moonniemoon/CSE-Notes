#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>
using namespace std;

class CPools6_49 {
protected: 
	int id;
	set<int> numbers;
public:
	static int last_id;
	CPools6_49() {
		id = ++last_id;
		generator_6num(numbers);
	}
	static void generator_6num(set<int>& gen) {
		while (gen.size() < 6) {
			int i = rand() % 49 + 1;
			gen.insert(i);
		}
	}
	CPools6_49(const set<int>& num) {
		id = ++last_id;
		numbers = num;
	}
	CPools6_49(const CPools6_49& obj) :
		id(obj.id),
		numbers(obj.numbers)
	{}
	const int& GetId() const {
		return id;
	}
	const set<int>& GetNumbers() const {
		return numbers;
	}
	bool operator < (const CPools6_49& obj)const {
		return GetId() < obj.GetId();
	}
	CPools6_49& operator =(const CPools6_49& obj) {
		id = obj.id;
		numbers = obj.numbers;
		return* this;
	}
	static void print_set(ostream& out, const set<int>& s) {
		copy(s.begin(), s.end(), ostream_iterator<int>(out, " "));
	}
	friend ostream& operator << (ostream& out, const CPools6_49& obj) {
		out << obj.id << " | ";
		CPools6_49::print_set(out, obj.GetNumbers());
		return out;
	}
	static void print_SetCPools(ostream& out, const set<CPools6_49>& s) {
		copy(s.begin(), s.end(), ostream_iterator<CPools6_49>(out, "\n"));
	}
};

int CPools6_49::last_id = 0;

int main() {
	const int max_bileti = 10;
	srand(unsigned(time(NULL)));
	set<int> win_num;
	CPools6_49::generator_6num(win_num);

	cout << "Pechelivshi Chisla: ";
	CPools6_49::print_set(cout, win_num);

	cout << "\n_________________________\n";

	vector<CPools6_49> bilet;
	for (int i = 0; i < max_bileti; i++) {
//		bilet.push_back(CPools6_49());
		bilet.emplace_back(); // CPOols6_49 + push_back
		cout << bilet[i] << endl;
	}

	set<CPools6_49> win_set3, win_set4, win_set5, win_set6;
	set<int> win_temp;
	for (const auto& b : bilet) {//moje for po index, iterator i range for	
		
		win_temp.clear();
		set_intersection(win_num.begin(), win_num.end(),
			b.GetNumbers().begin(),
			b.GetNumbers().end(),
			inserter(win_temp, win_temp.begin())
		);		

		cout << "No: " << b.GetId() << " - ";
		CPools6_49::print_set(cout, win_temp);
		cout << endl;
		switch (win_temp.size()) {
		case 3:
			win_set3.insert(b);
			break;
		case 4:
			win_set4.insert(b);
			break;
		case 5:
			win_set5.insert(b);
			break;
		case 6:
			win_set6.insert(b);
			break;
		default: 
			cout << "No winning numbers!\n";
		}
	}
	
	cout << "\nWinning Bilets: \n";
	cout << "------------------\n";
	cout << "win 3: \n";
	CPools6_49::print_SetCPools(cout, win_set3);
	cout << "win 4: \n";
	CPools6_49::print_SetCPools(cout, win_set4);
	cout << "win 5:\n";
	CPools6_49::print_SetCPools(cout, win_set5);
	cout << "win 6:\n";
	CPools6_49::print_SetCPools(cout, win_set6);

	system("pause");

	return 0;
}
