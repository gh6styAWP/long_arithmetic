#include <iostream>
#include <vector>
#include <string>
using namespace std;
//с положительными числами все работает
//с одним отрицательным или обоими отрицательными не работает

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
    bool a_negative = false;
    bool b_negative = false;

    // Проверка знака первого числа
    if (!a.empty() && a[0] == '-') {
        a_negative = true;
    }

    // Проверка знака второго числа
    if (!b.empty() && b[0] == '-') {
        b_negative = true;
    }

    vector<int> abs_a = a_negative ? vector<int>(a.begin() + 1, a.end()) : a;
    vector<int> abs_b = b_negative ? vector<int>(b.begin() + 1, b.end()) : b;

    vector<int> result(abs_a.size() + abs_b.size(), 0);

    // Умножаем каждую цифру из abs_a на каждую цифру из abs_b
    for (int i = abs_a.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = abs_b.size() - 1; j >= 0; j--) {
            int product = abs_a[i] * abs_b[j] + result[i + j + 1] + carry;
            carry = product / 10;
            result[i + j + 1] = product % 10;
        }
        result[i] += carry;
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.front() == 0) {
        result.erase(result.begin());
    }

    // Если знаки разные, результат отрицательный
    if (a_negative != b_negative) {
        result.insert(result.begin(), '-');
    }

    return result;
}

//функция div
vector<int> divide_long_numbers(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    vector<int> current;

    for (int digit : a) {
        current.push_back(digit);

        // Удаляем ведущие нули
        while (current.size() > 1 && current.front() == 0) {
            current.erase(current.begin());
        }

        int count = 0;
        while (subtract_long_numbers(current, b).second == false) { // Проверяем, что текущий результат >= 0
            current = subtract_long_numbers(current, b).first;
            count++;
        }

        result.push_back(count);
    }

    // Удаляем ведущие нули из результата
    while (result.size() > 1 && result.front() == 0) {
        result.erase(result.begin());
    }

    // Если результат пустой, это означает, что частное равно нулю
    if (result.empty()) {
        result.push_back(0);
    }

    return result;
}

//функция деления mod
vector<int> mod_long_numbers(const vector<int>& a, const vector<int>& b) {
    vector<int> current;

    for (int digit : a) {
        current.push_back(digit);

        // Удаляем ведущие нули
        while (current.size() > 1 && current.front() == 0) {
            current.erase(current.begin());
        }

        while (subtract_long_numbers(current, b).second == false) { // Проверяем, что текущий результат >= 0
            current = subtract_long_numbers(current, b).first;
        }
    }

    // Удаляем ведущие нули из остатка
    while (current.size() > 1 && current.front() == 0) {
        current.erase(current.begin());
    }

    return current;
}




int main() {
    setlocale(LC_ALL, "Ru");

    vector<int> a = read_long_number();
    vector<int> b = read_long_number();

    //сложение
    vector<int> sum = sum_long_numbers(a, b);
    cout << "\nСумма чисел (a + b): ";
    print_vector(sum);

    //вычитание
    auto subtract_ab = subtract_long_numbers(a, b);
    cout << "\nРазница чисел (a - b): ";
    print_vector(subtract_ab.first, subtract_ab.second);

    auto subtract_ba = subtract_long_numbers(b, a);
    cout << "\nРазница чисел (b - a): ";
    print_vector(subtract_ba.first, subtract_ba.second);

    //умножение
    vector<int> multiply = multiply_long_numbers(a, b);
    cout << "\nПроизведение чисел (a * b): ";
    print_vector(multiply);

    //деление div
    vector<int> div_ab = divide_long_numbers(a, b);
    cout << "\nЧастное чисел (a div b): ";
    print_vector(div_ab);

    vector<int> div_ba = divide_long_numbers(b, a);
    cout << "\nЧастное чисел (b div a): ";
    print_vector(div_ba);

    //деление mod
    vector<int> mod_ab = mod_long_numbers(a, b);
    cout << "\nОстаток от деления чисел (a mod b): ";
    print_vector(mod_ab);

    vector<int> mod_ba = mod_long_numbers(b, a);
    cout << "\nОстаток от деления чисел (b mod a): ";
    print_vector(mod_ba);


    //testtest

    return 0;
}


