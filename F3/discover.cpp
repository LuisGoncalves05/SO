#include <iostream>

using namespace std;

int main() {
    int number_len = 9;
    int numbers[number_len] = {2, 2, 2, 2, 3, 3, 3, 9, 3};
    int value_range = 10;
    int counts[value_range];
    for (int k = 0; k < value_range; k++) {
        counts[k] = 0;
    }

    int max_number = numbers[0];
    counts[max_number] = 1;
    int maximum_counts = 1;
    for (int k = 1; k < number_len; k++) {
        int current_number = numbers[k];
        counts[current_number] += 1;
        if (max_number == current_number || counts[current_number] > counts[max_number]) {
            max_number = current_number;
            maximum_counts = 1;
        } else if (counts[current_number] == counts[max_number]) {
            maximum_counts++;
        }
    }


    for (int element: numbers) cout << element << ' ';
    cout << endl;
    for (int element: counts) cout << element << ' ';
    cout << endl;

    cout << max_number << ' ' << maximum_counts << endl;
}