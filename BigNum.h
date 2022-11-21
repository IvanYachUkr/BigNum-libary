//
// Created by Dir on 17.09.2022.
//

#ifndef LAB2_BIGNUM_H
#define LAB2_BIGNUM_H


#include <string>
#include <utility>

//class BigNum_Abstract {
//public:
//    std::string num;
//    virtual ~BigNum_Abstract() = default;
//    //virtual std::string convert_decimal_to_binary(std::string num_decimal) = 0;
//    //virtual int karatsuba_algorithm_multiplication(Big_num first_num, Big_num second_num) = 0;
//    virtual std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num) = 0;
//    virtual int toom_cook_method_multiplication(std::string first_num, std::string second_num) = 0;
//    virtual  int shenhage_method_multiplication(std::string first_num, std::string second_num) = 0;
//    virtual int shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) = 0;
//};

//class Big_num : public BigNum_Abstract {
class Big_num{
public:
    std::string num_decimal;
    std::string num_binary;
    explicit Big_num (std::string number = "0"){
        num_decimal = std::move(number);
        //num_binary = convert_decimal_to_binary(num_decimal);
    }

    Big_num operator + (Big_num const &second_term) const;
    Big_num operator - (Big_num const &second_term) const;
    //Big_num operator << (Big_num const &second_term) const;
    Big_num operator % (Big_num const &second_term) const;
    friend std::ostream& operator<<(std::ostream& os, const Big_num& bn);
    //std::basic_string<char> karatsuba_algorithm_multiplication(Big_num first_num, Big_num second_num) override;




    static std::string remove_leading_zeros(const std::string& num);
//    std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num) override;
//    int toom_cook_method_multiplication(std::string first_num, std::string second_num) override;
//    int shenhage_method_multiplication(std::string first_num, std::string second_num) override;
//    int shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) override;

    static std::string toom_cook_method_multiplication(std::string first_num, std::string second_num);
    int shenhage_method_multiplication(std::string first_num, std::string second_num);
    int shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num);


};
//std::ostream& operator<<(std::ostream& os, const Big_num& bn)
//{
//    os << bn.num_decimal;
//    return os;
//}
std::string convert_decimal_to_binary(std::string num_decimal);
std::string convert_binary_to_decimal(std::string num_decimal);
std::string modular_mult(std::string num1, std::string num2);
std::string long_division(std::string number, int divisor);
std::string remainder(std::string number, std::string modulo);
std::string division(std::string num, std::string divisor);
std::string sum_big_num(std::string first_number,std::string second_number);
std::string subtract_big_num(std::string first_number,std::string second_number);
std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num);
std::string Schonhage_Strassen_Multiplication_method(std::string x, std::string y);
bool compare_nums(std::string n1, std::string n2);
std::string inverse(const std::string& num, int k);

#endif //LAB2_BIGNUM_H
