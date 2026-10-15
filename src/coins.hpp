#ifndef COINS_HPP
#define COINS_HPP

#include <iosfwd>

constexpr int CENTS_PER_QUARTER=25;
constexpr int CENTS_PER_DIME=10;
constexpr int CENTS_PER_NICKEL=5;

class Coins{
public:
	//Constructs 'this'Coins object so it has the number
	//of each coin given in the respective parameters.
	Coins(int q, int d, int n, int p);

	//Remove coins from 'coins' and put them into 'this' Coins object.
	void deposit_coins(Coins& coins);

	bool has_exact_change_for_coins(const Coins& coins) const;

	Coins extract_exact_change(const Coins& coin);

	int total_value_in_cents() const;

	void print(std::ostream& out) const;

	bool operator==(const Coins& other)const=default;

private:
	int quarters, dimes, nickels, pennies;
};

std::ostream& operator<<(std::ostream& out, const Coins& coins);

Coins coins_required_for_cents(int amount_in_cents);

void print_cents(int cents, std::ostream& out);

Coins ask_for_coins(std::istream& in, std::ostream& out);

void coins_menu(std::istream& in, std::ostream& out);

#endif


