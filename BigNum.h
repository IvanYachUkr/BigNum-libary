//
// Created by Dir on 17.09.2022.
//

#ifndef LAB2_BIGNUM_H
#define LAB2_BIGNUM_H


#include <string>
#include <utility>


class Big_num{
public:
    std::string num_decimal;
    std::string num_binary;
    explicit Big_num (std::string number = "0"){
        num_decimal = std::move(number);
    }

    Big_num operator + (Big_num const &second_term) const;
    Big_num operator - (Big_num const &second_term) const;
    Big_num operator % (Big_num const &second_term) const;
    friend std::ostream& operator<<(std::ostream& os, const Big_num& bn);




    static std::string remove_leading_zeros(const std::string& num);
    static std::string toom_cook_method_multiplication(std::string first_num, std::string second_num);


};

std::string convert_decimal_to_binary(std::string num_decimal);
std::string convert_binary_to_decimal(std::string num_decimal);
std::string modular_mult(const std::string& num1, const std::string& num2);
std::string long_division(std::string number, int divisor);
std::string remainder(std::string number, const std::string& modulo);
std::string division(const std::string& num, const std::string& divisor);
std::string sum_big_num(std::string first_number,std::string second_number);
std::string subtract_big_num(std::string first_number,std::string second_number);
std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num);
std::string Schonhage_Strassen_Multiplication_method(std::string x, std::string y);
bool compare_nums(const std::string& n1, const std::string& n2);
std::string inverse(const std::string& num, int k);


#endif //LAB2_BIGNUM_H
