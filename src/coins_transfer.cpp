#include <iostream>

#include "coins.hpp"

using namespace std;

constexpr int CENTS_FOR_CHIPS = 149;
constexpr int CENTS_TO_TRANSFER = 405;

int main() {
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);
    cout << "Piggy bank: " << piggyBank << endl;
    cout << "Pocket: " << pocket << endl;

    Coins chips = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CHIPS));
    cout << "Bought chips using " << chips << endl;

    Coins transfer = piggyBank.extract_exact_change(coins_required_for_cents(CENTS_TO_TRANSFER));
    cout << "Transferred " << transfer << endl;
    pocket.deposit_coins(transfer);

    Coins sofa(10, 10, 10, 10);
    piggyBank.deposit_coins(sofa);
    cout << "Sofa: " << sofa << endl;
    cout << "Piggy bank: " << piggyBank << endl;

    cout << "Balance: ";
    print_cents(piggyBank.total_value_in_cents(), cout);
    cout << endl;
}
