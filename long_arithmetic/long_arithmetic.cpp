﻿#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//вспомогательная функция для удаления ведущих нулей
void remove_leading_zeros(vector<char>& num) {
    while(num.size() > 1 && num[0] == '0') num.erase(num.begin());
    if (num.empty()) num.push_back('0'); //если результат пустой, добавляем '0'
}
//функция сложения двух векторов
vector<char> add_positive_numbers(const vector<char>& num1, const vector<char>& num2) {
    vector<char> result;
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    //сложение чисел справа налево
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += num1[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += num2[j] - '0';
            j--;
        }

        //вот эта штуковина переводит число в другой разряд если оно больше 9
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    //выводим результат в обратном порядке
    reverse(result.begin(), result.end());
    return result;
}
//функция сравнения двух чисел по модулю
bool is_greater_or_equal(const vector<char>& num1, const vector<char>& num2) {
    if (num1.size() != num2.size())
        return num1.size() > num2.size(); //если размер разный, большее по размеру число считается большим

    //если длины одинаковые, сравниваем цифры по порядку
    for (int i = 0; i < num1.size(); i++) {
        if (num1[i] != num2[i])
            return num1[i] > num2[i]; //возвращаем резултат сравнения первой отличной цифры
    }
    return true; //если все цифры одинаковые, числа равны
}
//функция для вычитания двух чисел
vector<char> subtract_positive_numbers(const vector<char>& num1, const vector<char>& num2) {
    vector<char> result;
    int borrow = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int diff = (i >= 0 ? num1[i] - '0' : 0) - (j >= 0 ? num2[j] - '0' : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else 
            borrow = 0;
        
        result.push_back(diff + '0');
        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    remove_leading_zeros(result); //удаление ведущих нулей
    return result;
}

//основная функция сложения с учётом знаков
vector<char> add_long_numbers(const vector<char>& num1, const vector<char>& num2) {
    bool num1_negative = (num1[0] == '-');
    bool num2_negative = (num2[0] == '-');

    //преобразуем числа в абсолютные значения
    vector<char> abs_num1 = num1_negative ? vector<char>(num1.begin() + 1, num1.end()) : num1;
    vector<char> abs_num2 = num2_negative ? vector<char>(num2.begin() + 1, num2.end()) : num2;

    vector<char> result;

    //оба числа положительные
    if (!num1_negative && !num2_negative) result = add_positive_numbers(abs_num1, abs_num2);   
    //оба числа отрицательные
    else if (num1_negative && num2_negative) {
        result = add_positive_numbers(abs_num1, abs_num2);
        result.insert(result.begin(), '-');
    }
    //одно число положительное, другое отрицательное
    else {
        //проверяем, какое из чисел больше по модулю
        if (is_greater_or_equal(abs_num1, abs_num2)) {
            //если abs_num1 >= abs_num2, то вычитаем abs_num2 из abs_num1
            result = subtract_positive_numbers(abs_num1, abs_num2);
            //если num1 отрицательное, то результат будет отрицательный
            if (num1_negative) 
                result.insert(result.begin(), '-');            
        }
        else {
            //если abs_num2 > abs_num1, то вычитаем abs_num1 из abs_num2
            result = subtract_positive_numbers(abs_num2, abs_num1);
            //если num2 отрицательное, то результат положительный, иначе отрицательный
            if (!num1_negative) result.insert(result.begin(), '-');            
        }
    }

    if (result.empty()) result.push_back('0');

    return result;
}



int main() {
    setlocale(LC_ALL, "Ru");

    //создаем два вектора для двух длиннх чисел
    vector<char> num1;
    vector<char> num2;
    string input1, input2;
    
    //ввод и заполнение векторов
    cout << "Введите первое число: ";
    cin >> input1;
    for (char c : input1)
        num1.push_back(c);

    cout << "\nВведите второе число: ";
    cin >> input2;
    for (char c : input2)
        num2.push_back(c);

    // Сложение чисел и вывод результата
    vector<char> result = add_long_numbers(num1, num2);
    cout << "\nРезультат сложения: ";

    for (char c : result) 
        cout << c;
    cout << endl;

    return 0;
}


