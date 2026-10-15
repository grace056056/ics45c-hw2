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

