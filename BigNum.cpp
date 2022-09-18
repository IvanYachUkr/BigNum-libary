//
// Created by Dir on 17.09.2022.
//

#include <algorithm>
#include "BigNum.h"



int Big_num::toom_cook_method_multiplication(std::string first_num, std::string dec_num) {
    return 0;
}

int Big_num::shenhage_method_multiplication(std::string first_num, std::string dec_num) {
    return 0;
}

int Big_num::shtrassen_shenhage_method_multiplication(std::string first_num, std::string dec_num) {
    return 0;
}

int Big_num::karatsuba_algorithm_multiplication(std::string first_num, std::string dec_num) {
    return 0;
}

Big_num Big_num::operator+(const Big_num &second_term) {
    Big_num n;
    std::string first_number = num_decimal;
    std::string second_number = second_term.num_decimal;

    int len_first_num = first_number.length();
    int len_second_num = second_number.length();

    if (len_first_num > len_second_num)
        swap(first_number, second_number);

    std::string res;

    reverse(first_number.begin(), first_number.end());
    reverse(second_number.begin(), second_number.end());

    int carry = 0;
    for (int i = 0; i < len_first_num; i++) {

        //to convert a digit to its corresponding character use + '0'
        //to covert a character of the digit to the digit subtract '0'

        int sum = ((first_number[i] - '0') + (second_number[i] - '0') + carry);
        res.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    for (int i = len_first_num; i < len_second_num; i++) {
        int sum = ((second_number[i] - '0') + carry);
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry)
        res.push_back(carry + '0');

    reverse(res.begin(), res.end());

    n.num_decimal = res;

    return n;
}

std::string Big_num::convert_decimal_to_binary(std::string num_decimal) {

    return std::string();
}
