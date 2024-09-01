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
void print_vector(const vector<int>& num_vector) {
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


int main()
{
    setlocale(LC_ALL, "Ru");
    vector<int> a = read_long_number();
    vector<int> b = read_long_number();

    

    vector<int> sum = sum_long_numbers(a, b);
    cout << "\nСумма чисел: ";
    print_vector(sum);

    return 0;
}

