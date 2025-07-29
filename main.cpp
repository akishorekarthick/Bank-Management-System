#include <fstream>
#include <iostream>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;

struct account {
	char name[20], password[20];
	long long account_no;
	double balance;
} a;

void pause() {
	cout << "Press Enter to continue...";
	cin.ignore();
	cin.get();
}

void create() {
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	char password1[20], password2[20];
	while (true) {
		cout << "Enter your name:\n";
		cin.ignore();
		cin.getline(a.name, 20);
		cout << "Enter password:\n";
		cin.getline(password2, 20);
		cout << "Confirm password:\n";
		cin.getline(password1, 20);
		if (strcmp(password2, password1) != 0) {
			cout << "Error. Enter the details again\n";
			pause();
		} else {
			strcpy(a.password, password1);
			break;
		}
	}
	a.account_no = rng() % 10000000000ll;
	cout << "Your account has been created\nYour account number is " << a.account_no << '\n';
	cout << "Enter the amount to be deposited: ";
	cin >> a.balance;
	cout << "\nThe details of your account:\n";
	cout << "Name: " << a.name << "\nPassword: " << a.password << "\nAccount Number: " << a.account_no << "\nBalance: " << a.balance;
}

void write() {
	ofstream ofile("account.bin", ios::out | ios::binary);
	ofile.write((char*)&a, sizeof(a));
	ofile.close();
}

double car_rate(double p) {
	if (p > 1000000) return 6.1;
	else if (p > 500000) return 5.7;
	else if (p > 250000) return 5;
	else return 6.7;
}

double house_rate(double p) {
	if (p > 5000000) return 10;
	else if (p > 3000000) return 9.5;
	else if (p > 2000000) return 9;
	else return 11;
}

double rate(double p) {
	if (p > 100000) return 10;
	else if (p > 50000) return 7;
	else if (p > 10000) return 5;
	else return 12;
}

void simple_interest(double p, double r) {
	double t;
	cout << "\nEnter the period of time for which you want to borrow the money (in years): ";
	cin >> t;
	double SI = p * r * t / 100;
	cout << "The total amount to be paid at the end of the time period is " << p + SI << '\n';
	cout << "The money has been successfully deposited into your account\n";
	a.balance += p;
}

void fixed_deposit() {
	cout << "\nEnter the amount of money you want to deposit: ";
	int d;
	cin >> d;
	if (d > a.balance) {
		cout << "You do not have enough balance in your account\n";
		cout << "Enter a different amount\n";
		fixed_deposit();
	} else {
		cout << "The percentage interest is " << house_rate(d) << '\n';
		cout << "Enter the time for which you want to deposit the money (in years): ";
		int t;
		cin >> t;
		double si = d * house_rate(d) * t / 100;
		cout << "You will earn Rs. " << d + si << " at the end of your time period\n";
		cout << "The money you have deposited has successfully been deducted from your main balance\n";
		a.balance -= d;
	}
}

void change() {
	char name[20], password[20];
	while (true) {
		cout << "Enter Name:\n";
		cin.ignore();
		cin.getline(name, 20);
		cout << "Enter Password:\n";
		cin.getline(password, 20);
		if (strcmp(name, a.name) != 0 || strcmp(password, a.password) != 0) {
			cout << "The Username or Password is wrong\nPlease retype Username and Password\n";
		} else {
			cout << "You have accessed your account\n";
			break;
		}
	}
	pause();
	int c;
	while (true) {
		cout << "\n1 Deposit Money\n2 Withdraw Money\n3 Change Password\n4 Apply for Loan\n5 Check Balance\n6 Log Out\n";
		cout << "Enter your choice: ";
		cin >> c;
		switch (c) {
			case 1: {
				int l;
			d1:
				cout << "\n1. Fixed deposit\n2. Savings\nEnter your choice: ";
				cin >> l;
				switch (l) {
					case 1:
						fixed_deposit();
						write();
						break;
					case 2: {
						cout << "Enter the amount you want to deposit: ";
						int s;
						cin >> s;
						a.balance += s;
						write();
						break;
					}
					default:
						cout << "Wrong choice. Please enter again.";
						pause();
						goto d1;
				}
				pause();
				break;
			}
			case 2: {
				int amount;
				while (true) {
					cout << "Enter the amount you want to withdraw: ";
					cin >> amount;
					if (amount > a.balance) {
						cout << "You do not have enough money in your account\nPlease enter a different amount\n";
					} else {
						a.balance -= amount;
						cout << "Your new balance is " << a.balance << "\n\n";
						write();
						break;
					}
				}
				break;
			}
			case 3: {
				char password1[20], password2[20];
				while (true) {
					cout << "Enter the new password:\n";
					cin.ignore();
					cin.getline(password1, 20);
					cout << "Confirm new password:\n";
					cin.getline(password2, 20);
					if (strcmp(password1, password2) != 0) {
						cout << "Passwords did not match, retype new password\n";
					} else {
						strcpy(a.password, password1);
						cout << "Your password has been changed\n\n";
						break;
					}
				}
				write();
				break;
			}
			case 4: {
				int x;
			d2:
				cout << "1 Personal loan\n2 Car Loan\n3 Home Loan\nEnter the type of loan you require: ";
				cin >> x;
				double loan;
				switch (x) {
					case 1:
						cout << "Enter the amount you want to borrow (minimum amount 10,000): ";
						cin >> loan;
						cout << "The rate of interest per annum is " << rate(loan);
						simple_interest(loan, rate(loan));
						cout << "\nYour loan has been sanctioned, the amount has been transferred to your account\n";
						pause();
						break;
					case 2:
						cout << "Enter the amount of loan required to purchase your car: ";
						cin >> loan;
						simple_interest(loan, car_rate(loan));
						cout << "Your loan has been sanctioned, the amount has been transferred to your account\n";
						cout << "Your car will belong to the bank (as collateral) and will remain so till the loan has been paid off completely\n";
						pause();
						break;
					case 3:
						cout << "Enter the amount of loan required to purchase your house: ";
						cin >> loan;
						simple_interest(loan, house_rate(loan));
						cout << "Your loan has been sanctioned, the amount has been transferred to your account\n";
						cout << "Your house will belong to the bank (as collateral) and will remain so till the loan has been paid off completely\n";
						pause();
						break;
					default:
						cout << "Wrong choice. Enter again\n";
						pause();
						goto d2;
				}
				break;
			}
			case 5:
				cout << "Your Balance is: Rs. " << a.balance << '\n';
				pause();
				break;
			case 6:
				return;
			default:
				cout << "Invalid choice\n";
		}
	}
}

int main() {
	cout << "____________________________________________________\n";
	cout << "                    Cyber Bank\n";
	cout << "____________________________________________________";

	int b = 0;
	while (b != 3) {
		cout << "\n\n1 Create New Account\n2 Existing Account\n3 Exit\nEnter your choice: ";
		cin >> b;
		ofstream out;
		ifstream in;
		switch (b) {
			case 1:
				out.open("account.bin", ios::out | ios::binary);
				create();
				out.write((char*)&a, sizeof(a));
				out.close();
				break;
			case 2:
				in.open("account.bin", ios::in | ios::binary);
				in.read((char*)&a, sizeof(a));
				in.close();
				change();
				break;
			case 3:
				cout << "\nThank you for banking with us :)\n";
				break;
			default:
				cout << "Error";
		}
	}
	pause();
	return 0;
}

