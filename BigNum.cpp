//
// Created by Dir on 17.09.2022.
//

#include <algorithm>
#include <regex>
#include "BigNum.h"



int Big_num::toom_cook_method_multiplication(std::string first_num, std::string second_num) {
    return 0;
}

int Big_num::shenhage_method_multiplication(std::string first_num, std::string second_num) {
    return 0;
}

int Big_num::shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) {
    return 0;
}

//std::basic_string<char> Big_num::karatsuba_algorithm_multiplication(Big_num first_n, Big_num second_n) {
std::basic_string<char> Big_num::karatsuba_algorithm_multiplication(std::string first_n, std::string second_n) {

//    std::string first_num =  first_n.num_decimal;
//    std::string second_num = second_n.num_decimal;
    std::string first_num =  first_n;
    std::string second_num = second_n;

    if (first_num.length() > second_num.length())
        swap(first_num, second_num);

    // Make both numbers to have
    // same digits
    int len_first_num = first_num.length();
    int len_second_num = second_num.length();

    while (len_second_num > len_first_num) {
        first_num += "0";
        len_first_num++;
    }

    // Base case
    if (len_first_num == 1) {

        int ans = stoi(first_num) * stoi(second_num);
        return std::to_string(ans);
    }

    // Add zeros in the beginning of
    // the strings when length is odd
    if (len_first_num % 2 == 1) {
        len_first_num++;
        first_num = "0" + first_num;
        second_num = "0" + second_num;
    }

    std::string Al, Ar, Bl, Br;

    // Find the values of Al, Ar,
    // Bl, and Br.
    for (int i = 0; i < len_first_num / 2; ++i) {
        Al += first_num[i];
        Bl += second_num[i];
        Ar += first_num[len_first_num / 2 + i];
        Br += second_num[len_first_num / 2 + i];
    }

    // Stores the value of Al * Bl
    std::string Al_multiply_Bl = Big_num::karatsuba_algorithm_multiplication(Al, Bl);

    // Stores the value of Ar * Br
    std::string Ar_multiply_Br = Big_num::karatsuba_algorithm_multiplication(Ar, Br);

    // Stores value of ((Al + Ar)*(Bl + Br) - Al*Bl - Ar*Br)
    std::string A_multiply_B_with_leading_zeros = subtract_big_num(
            karatsuba_algorithm_multiplication(sum_big_num(Al, Ar),
                     sum_big_num(Bl, Br)),
            sum_big_num(Al_multiply_Bl, Ar_multiply_Br));

    // Multiply Al_multiply_Bl by 10^n
    for (int i = 0; i < len_first_num; ++i)
        Al_multiply_Bl +="0";

    // Multiply s by 10^(n/2)
    for (int i = 0; i < len_first_num / 2; ++i)
        A_multiply_B_with_leading_zeros = A_multiply_B_with_leading_zeros + "0";

    // Calculate final answer Al_multiply_Bl + A_multiply_B_with_leading_zeros + s
    std::string ans = sum_big_num(Al_multiply_Bl, sum_big_num(Ar_multiply_Br, A_multiply_B_with_leading_zeros));

    // Remove leading zeroes from ans
    ans = remove_leading_zeros(ans);

    // Return Answer
    return ans;


}

std::string Big_num::sum_big_num(std::string first_number,std::string second_number){
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
    return res;
}


Big_num Big_num::operator+(const Big_num &second_term) const {
    Big_num n;
    std::string first_number = num_decimal;
    std::string second_number = second_term.num_decimal;

    std::string res = sum_big_num(first_number,second_number);

    n.num_decimal = res;

    return n;
}


Big_num Big_num::operator-(const Big_num &second_term) const {
    Big_num n;
    std::string first_number = num_decimal;
    std::string second_number = second_term.num_decimal;

    n.num_decimal = subtract_big_num(first_number, second_number);

    return n;
}


std::string Big_num::convert_decimal_to_binary(std::string num_decimal) {

    return {};
}

std::string Big_num::subtract_big_num(std::string first_number, std::string second_number) {
    std::string res;


    int len_first_num = first_number.length(), len_second_num = second_number.length();


    reverse(second_number.begin(), second_number.end());

    int carry = 0;

    for (int i = 0; i < len_second_num; i++) {

        int subtract
                = ((first_number[i] - '0')
                   - (second_number[i] - '0')
                   - carry);

        if (subtract < 0) {
            subtract = subtract + 10;
            carry = 1;
        }
        else
            carry = 0;

        res.push_back(subtract + '0');
    }

    for (int i = len_second_num; i < len_first_num; i++) {
        int subtract = ((first_number[i] - '0') - carry);

        if (subtract < 0) {
            subtract = subtract + 10;
            carry = 1;
        }
        else
            carry = 0;

        res.push_back(subtract + '0');
    }

    reverse(res.begin(), res.end());
    return res;
}

std::string Big_num::remove_leading_zeros(const std::string& num) {
    // Use regular expression to remove leading 0s
    const std::regex pattern("^0+(?!$)");

    // Replaces the matched value
    // with given string
    std::string num_without_leading_zeros = regex_replace(num, pattern, "");
    return num_without_leading_zeros;
}






