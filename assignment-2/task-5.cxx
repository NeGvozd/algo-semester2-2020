/****************************************************************************
Ricked out
****************************************************************************/

#include <iostream>
#include <vector>
#include <limits>


struct Exchange {
    int currency;
    double rate;
    double commission;
};


int main()
{
    int currencies_count, changes_count, start_currency;
    double start_amount;

    std::cin >> currencies_count >> changes_count >> start_currency >> start_amount;
    --start_currency;

    std::vector<std::vector<Exchange>> exchanges(currencies_count);
    for (int i = 0; i < changes_count; ++i) {
        int a_currency, b_currency;
        double a_rate, b_rate, a_commission, b_commission;

        std::cin >> a_currency >> b_currency >> a_rate >> a_commission >> b_rate >> b_commission;

        a_currency--;
        b_currency--;

        exchanges[a_currency].push_back({b_currency, a_rate, a_commission});
        exchanges[b_currency].push_back({a_currency, b_rate, b_commission});
    }

    std::vector<double> profit(currencies_count, 0);
    profit[start_currency] = start_amount;

    for (int i = 0; i < currencies_count-1; ++i) {
        for (int j = 0; j < exchanges.size(); ++j) {
            for (const auto& exchange : exchanges[j]) {
                double new_profit = (profit[j] - exchange.commission) * exchange.rate;
                if (new_profit > profit[exchange.currency]) {
                    profit[exchange.currency] = new_profit;
                }
            }
        }
    }

    for (int i = 0; i < currencies_count; ++i) {
        for (const auto& exchange : exchanges[i]) {
            if (profit[exchange.currency] < (profit[i]-exchange.commission) * exchange.rate) {
                std::cout << "YES" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "NO" << std::endl;
    return 0;
}