#include <iostream>
#include <vector>
#include <stack>
#include "StackSeries.h"

using namespace alg4;

int main()
{
    while (true) {
        string input_series;
        cout << "Input series: ";
        std::cin >> input_series;
        cout << endl;
        if (input_series[0] == '-')
            return 0;
        vector<vector<char>> allseries = StackSeries::getStackSeries(input_series);

        cout << "All possible stack sequences:" << endl;
        for (const auto& series : allseries) {
            for (char c : series) {
                cout << c << " ";
            }
            cout << endl;
        }
        cout << "There are " << allseries.size() << " kind of series" << endl;
    }

    return 0;
}
