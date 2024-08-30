#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Ru");
    vector<int> a;
    vector<int> b;
    string input;

    cout << "Введите числа для числа a, разделенные пробелами, и нажмите enter: ";
    getline(cin, input);
    istringstream stream(input);
    int num;
    while (stream >> num) {
        a.push_back(num);
    }

    cout << "\nВектор 1: ";
    for (auto x : a)
        cout << x << " ";

    cout << "\nВведите числа для числа b, разделенные пробелами, и нажмите enter: ";
    getline(cin, input);
    istringstream stream2(input);
    while (stream2 >> num) {
        b.push_back(num);
    }

    cout << "\nВектор 2: ";
    for (auto x : b)
        cout << x << " ";

}

