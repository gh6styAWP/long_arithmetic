#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

//функция для заполнения вектора
vector<int> read_long_number() {
    string num_str;
    cout << "Введите число: ";
    cin >> num_str;

    vector<int> num_vector;

    // Преобразуем строку в вектор цифр
    for (char c : num_str) {
        // Проверяем, что символ является цифрой
        if (isdigit(c)) 
            num_vector.push_back(c - '0'); // Преобразуем символ в число и добавляем в вектор       
    }

    return num_vector;
}

//функция вывода вектора
void print_vector(const vector<int>& num_vector) {
    for (int digit : num_vector) 
        cout << digit;  

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    vector<int> a = read_long_number();
    vector<int> b = read_long_number();

    cout << "\nЧисло 1: ";
    print_vector(a);

    cout << "\nЧисло 2: ";
    print_vector(b);





}

