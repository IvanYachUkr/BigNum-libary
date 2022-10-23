//
// Created by Dir on 17.09.2022.
//

#ifndef LAB2_BIGNUM_H
#define LAB2_BIGNUM_H


#include <string>
#include <utility>

class BigNum_Abstract {
public:
    std::string num;
    virtual ~BigNum_Abstract() = default;
    //virtual std::string convert_decimal_to_binary(std::string num_decimal) = 0;
    //virtual int karatsuba_algorithm_multiplication(Big_num first_num, Big_num second_num) = 0;
    virtual std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num) = 0;
    virtual int toom_cook_method_multiplication(std::string first_num, std::string second_num) = 0;
    virtual  int shenhage_method_multiplication(std::string first_num, std::string second_num) = 0;
    virtual int shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) = 0;
};

class Big_num : public BigNum_Abstract {
public:
    std::string num_decimal;
    std::string num_binary;
    explicit Big_num (std::string number = "0"){
        num_decimal = std::move(number);
        num_binary = convert_decimal_to_binary(num_decimal);
    }

    Big_num operator + (Big_num const &second_term) const;
    Big_num operator - (Big_num const &second_term) const;
    static std::string convert_decimal_to_binary(std::string num_decimal);
    //std::basic_string<char> karatsuba_algorithm_multiplication(Big_num first_num, Big_num second_num) override;

    static std::string sum_big_num(std::string first_number,std::string second_number);
    static std::string subtract_big_num(std::string first_number,std::string second_number);

    static std::string remove_leading_zeros(const std::string& num);
    std::basic_string<char> karatsuba_algorithm_multiplication(std::string first_num, std::string second_num) override;
    int toom_cook_method_multiplication(std::string first_num, std::string second_num) override;
    int shenhage_method_multiplication(std::string first_num, std::string second_num) override;
    int shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) override;
};



#endif //LAB2_BIGNUM_H
