//
// Created by Dir on 24.10.2022.
//

#ifndef LAB2_ISPRIME_H
#define LAB2_ISPRIME_H

std::string power(std::string n, std::string a, std::string);
std::string gcd(std::string a, std::string b);
bool isPrime_Miller(std::string n, int k);
bool is_prime_fermat_test(std::string n, int k);
bool AKS_test(std::string num);
bool solovoyStrassen(std::string p, int iterations);
bool isPrimeAKS(unsigned long long int n);

#endif //LAB2_ISPRIME_H
