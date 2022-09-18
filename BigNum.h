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
    virtual int karatsuba_algorithm_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual int toom_cook_method_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual  int shenhage_method_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual int shtrassen_shenhage_method_multiplication(std::string first_num, std::string dec_num) = 0;
};

class Big_num : public BigNum_Abstract {
public:
    std::string num_decimal;
    std::string num_binary;
    explicit Big_num (std::string number = "0"){
        num_decimal = std::move(number);
        num_binary = convert_decimal_to_binary(num_decimal);
    }

    Big_num operator + (Big_num const &second_term);
    std::string convert_decimal_to_binary(std::string num_decimal);
    int karatsuba_algorithm_multiplication(std::string first_num, std::string dec_num) override;
    int toom_cook_method_multiplication(std::string first_num, std::string dec_num) override;
    int shenhage_method_multiplication(std::string first_num, std::string dec_num) override;
    int shtrassen_shenhage_method_multiplication(std::string first_num, std::string dec_num) override;
};



#endif //LAB2_BIGNUM_H
