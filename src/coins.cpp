#include <iostream>
#include "coins.hpp"

using namespace std;

Coins::Coins(int q, int d, int n, int p){
		quarters = q;
		dimes = d;
		nickels=n;
		pennies=p;
}

void Coins::print(std::ostream& out) const{
		out<<quarters<<" quarters, "<<dimes<<" dimes, "<<nickels<<" nickels, "<<pennies<<" pennies";
}

ostream& operator<<(ostream& out, const Coins& coins){
	coins.print(out);
	return out;
}

Coins coins_required_for_cents(int amount_in_cents){
	int q = amount_in_cents/ CENTS_PER_QUARTER;
	amount_in_cents = amount_in_cents % CENTS_PER_QUARTER;

    int d = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents = amount_in_cents % CENTS_PER_DIME;

    int n = amount_in_cents / CENTS_PER_NICKEL;
    int p = amount_in_cents % CENTS_PER_NICKEL;

    return Coins(q, d, n, p);
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const {
    return quarters >= coins.quarters && dimes >= coins.dimes
        && nickels >= coins.nickels && pennies >= coins.pennies;
}

Coins Coins::extract_exact_change(const Coins& coins) {
    if (!has_exact_change_for_coins(coins)) {
        return Coins(0, 0, 0, 0);
    }
    quarters -= coins.quarters;
    dimes -= coins.dimes;
    nickels -= coins.nickels;
    pennies -= coins.pennies;
    return coins;
}

void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    dimes += coins.dimes;
    nickels += coins.nickels;
    pennies += coins.pennies;
    coins.quarters = 0;
    coins.dimes = 0;
    coins.nickels = 0;
    coins.pennies = 0;
}

int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME
         + nickels * CENTS_PER_NICKEL + pennies;
}

int constexpr CENTS_PER_DOLLAR=100;

void print_cents(int cents, std::ostream& out) {
    int dollars = cents / CENTS_PER_DOLLAR;
    int remainder = cents % CENTS_PER_DOLLAR;
    out << '$' << dollars << '.';
    if (remainder < 10) {
        out << '0';
    }
    out << remainder;
}

Coins ask_for_coins(std::istream& in, std::ostream& out) {
    int q = 0, d = 0, n = 0, p = 0;
    out << "Quarters? ";
    in >> q;
    out << "Dimes? ";
    in >> d;
    out << "Nickels? ";
    in >> n;
    out << "Pennies? ";
    in >> p;
    return Coins(q, d, n, p);
}

void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    int choice = 0;
    while (true) {
        out << "1. Deposit\n2. Extract\n3. Balance\n4. Exit\nChoice? ";
        if (!(in >> choice) || choice == 4) {
            break;
        }
        if (choice == 1) {
            Coins c = ask_for_coins(in, out);
            myCoins.deposit_coins(c);
        } else if (choice == 2) {
            Coins c = ask_for_coins(in, out);
            myCoins.extract_exact_change(c);
        } else if (choice == 3) {
            print_cents(myCoins.total_value_in_cents(), out);
            out << '\n';
        }
    }
}
