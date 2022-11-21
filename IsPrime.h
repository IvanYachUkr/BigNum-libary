//
// Created by Dir on 24.10.2022.
//

#ifndef LAB2_ISPRIME_H
#define LAB2_ISPRIME_H

std::string power(std::string n, std::string a, std::string);
std::string gcd(std::string a, std::string b);
bool miller_rabin_primality_test(std::string n, int k);
bool is_prime_fermat_test(std::string n, int k);
bool AKS_test(std::string num);
bool solovay_strassen(std::string p, int iterations);
bool AKS_primality_test(unsigned long long int n);

#endif //LAB2_ISPRIME_H
