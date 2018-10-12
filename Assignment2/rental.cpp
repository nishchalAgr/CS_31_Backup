#include <iostream>
#include <string>

using namespace std;

int main() {

	int start = 0;
	int end = 0;
	int days = 0;
	int month = 0;
	int check = 0; //if check is equal to one, then the program will end

	string name;
	string luxury;

	double base = 0.0; //based on luxury, per day charge
	double perMile = 0.0; //0 - 100 = .27/mile ; 100 - 400 = .21/mile or .27/mile(dec - march) ; 400+ - 0.19/mile 
	double ans = 0.0;

	cout << "odometer at start: ";
	cin >> start;


	if (start < 0) {

		cout << "---" << endl;
		cout << "Starting odometer must be nonnegative" << endl;
		return 0;

	}

	cout << "odometer at end: ";
	cin >> end;

	if (end - start < 0) {

		cout << "---" << endl;
		cout << "The final odometer reading must be at least as large as the starting reading" << endl;
		return 0;

	}

	cout << "Rental days: ";
	cin >> days;

	if (days < 0) {

		cout << "---" << endl;
		cout << "The number of rental days must be larger than zero" << endl;
		return 0;

	}

	cin.ignore(10000, '\n');

	cout << "Customer name: ";
	getline(cin, name);

	if (name.compare("") == 0) {

		cout << "---" << endl;
		cout << "You must enter a customer name" << endl;
		return 0;

	}

	cout << "Luxury Car? (y/n): ";
	getline(cin, luxury);

	if (luxury.compare("y") != 0 && luxury.compare("n") != 0) {

		cout << "---" << endl;
		cout << "You must enter y or n" << endl;
		return 0;

	}

	cout << "Month (1 = Jan, 2 = Feb, ect): ";
	cin >> month;

	if (month < 1 || month > 12) {

		cout << "---" << endl;
		cout << "The month number must be in the range 1 through 12" << endl;
		return 0;

	}

	int miles = end - start;

	if (luxury.compare("y") == 0) {

		base = 61;

	}
	else {

		base = 33;

	}

	base = base * days;
	ans += base;

	if (miles < 100) {

		ans += 0.27 * miles; // for if total miles is less than 100

	}
	else if (miles > 100 && miles <= 400) {

		ans += 0.27 * 100; // for if total miles is more than 100, so calculates the first 100 miles

		if (month <= 3 || month == 12) {

			ans += 0.27 * (miles - 100); //for winter months and total miles is more than 100 but less than 400

		}
		else {

			ans += 0.21 * (miles - 100); //for non-winter months and total miles is more than 100 but less than 400

		}

	}
	else if (miles > 400) {

		ans += 0.27 * 100; // for if total miles is more than 100, so calculates the first 100 miles

		if (month <= 3 || month == 12) {

			ans += 0.27 * 300; // for winter months and total miles is more than 400, so calculates the miles from 100 to 400

		}
		else {

			ans += 0.21 * 300; // for non-winter months and total miles is more than 400, so calculates the miles from 100 to 400

		}

		ans += 0.19 * (miles - 400); // adds rate for each miles above 400

	}

	cout << "---" << endl;
	cout << "The rental charge for " << name << " is $" << ans << endl;
	cin >> base;

}