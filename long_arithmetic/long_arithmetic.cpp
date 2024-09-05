#include <iostream>
#include <vector>
#include <string>
using namespace std;
//с положительными числами все работает
//с одним отрицательным или обоими отрицательными не работает






int main() {
    setlocale(LC_ALL, "Ru");

    //создаем два вектора для двух длиннх чисел
    vector<char> num1;
    vector<char> num2;
    string input1, input2;

    cout << "Введите первое число: ";
    cin >> input1;

    //заполнение вектора введенными числами
    for (char c : input1)
        num1.push_back(c);

    cout << "\nВведите второе число: ";
    cin >> input2;

    for (char c : input2)
        num2.push_back(c);

   

    return 0;
}


