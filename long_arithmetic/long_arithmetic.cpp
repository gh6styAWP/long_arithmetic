#include <iostream>
#include <vector>
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
void print_vector(const vector<int>& num_vector, bool is_negative = false) {
    if (is_negative) {
        cout << "-";
    }
    for (int digit : num_vector)
        cout << digit;

    cout << endl;
}

//функция сложения
vector<int> sum_long_numbers(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int carry = 0;
    int a_size = a.size();
    int b_size = b.size();
    int max_size = max(a_size, b_size);

    for (int i = 0; i < max_size; i++) {
        int digit_a = (i < a_size) ? a[a_size - 1 - i] : 0;
        int digit_b = (i < b_size) ? b[b_size - 1 - i] : 0;

        int sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result.push_back(sum % 10);
    }

    if (carry > 0) {
        result.push_back(carry);
    }

    reverse(result.begin(), result.end());
    return result;
}

//функция вычитания 
pair<vector<int>, bool> subtract_long_numbers(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int borrow = 0;
    bool negative = false;

    const vector<int>* larger;
    const vector<int>* smaller;

    // Определяем, какое число больше
    if (a.size() > b.size() || (a.size() == b.size() && a >= b)) {
        larger = &a;
        smaller = &b;
    }
    else {
        larger = &b;
        smaller = &a;
        negative = true; // результат будет отрицательным
    }

    int larger_size = larger->size();
    int smaller_size = smaller->size();

    for (int i = 0; i < larger_size; i++) {
        int digit_larger = (*larger)[larger_size - 1 - i];
        int digit_smaller = (i < smaller_size) ? (*smaller)[smaller_size - 1 - i] : 0;

        int diff = digit_larger - digit_smaller - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result.push_back(diff);
    }

    // Удаление ведущих нулей
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    reverse(result.begin(), result.end());

    return make_pair(result, negative);
}

//функция умножения
vector<int> multiply_long_numbers(const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size() + b.size(), 0);

    // Умножаем каждую цифру из a на каждую цифру из b
    for (int i = a.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = b.size() - 1; j >= 0; j--) {
            int product = a[i] * b[j] + result[i + j + 1] + carry;
            carry = product / 10;
            result[i + j + 1] = product % 10;
        }
        result[i] += carry;
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.front() == 0) {
        result.erase(result.begin());
    }

    return result;
}



int main() {
    setlocale(LC_ALL, "Ru");

    vector<int> a = read_long_number();
    vector<int> b = read_long_number();

    vector<int> sum = sum_long_numbers(a, b);
    cout << "\nСумма чисел (a + b): ";
    print_vector(sum);

    auto subtract_ab = subtract_long_numbers(a, b);
    cout << "\nРазница чисел (a - b): ";
    print_vector(subtract_ab.first, subtract_ab.second);

    auto subtract_ba = subtract_long_numbers(b, a);
    cout << "\nРазница чисел (b - a): ";
    print_vector(subtract_ba.first, subtract_ba.second);

    vector<int> multiply = multiply_long_numbers(a, b);
    cout << "\nПроизведение чисел (a * b): ";
    print_vector(multiply);

    return 0;
}


