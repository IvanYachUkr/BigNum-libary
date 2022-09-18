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
    virtual int karatsuba_algorithm_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual int toom_cook_method_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual  int shenhage_method_multiplication(std::string first_num, std::string dec_num) = 0;
    virtual int shtrassen_shenhage_method_multiplication(std::string first_num, std::string dec_num) = 0;
};

class Big_num : public BigNum_Abstract {
public:
    std::string num;
    Big_num (std::string number){
        num = std::move(number);
    }
    int karatsuba_algorithm_multiplication(std::string first_num, std::string dec_num) override;
    int toom_cook_method_multiplication(std::string first_num, std::string dec_num) override;
    int shenhage_method_multiplication(std::string first_num, std::string dec_num) override;
    int shtrassen_shenhage_method_multiplication(std::string first_num, std::string dec_num) override;
};



#endif //LAB2_BIGNUM_H
