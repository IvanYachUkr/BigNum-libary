#include <string>
#include <bits/stdc++.h>
#include "BigNum.h"

std::string power(std::string n, std::string a = "23", std::string p ="1")
// a^p % n | p = n-1, a^(n-1)%p
{
    if (p != "1") {
        p = n.substr(0, n.size() - 2) + std::to_string(((int) n.back() - 1));
    }
    std::string res = "1";

    while (!p.empty())
    {
        int last_digit = (int)p.back();
        if (last_digit & 1) {

            res = (Big_num::karatsuba_algorithm_multiplication(res,a));

            if (res.compare(n)<0) {
                res = reminder(res, n);
            }
        }
        // n must be even now
        p = longDivision(p, 2); // n = n/2
        a = reminder((Big_num::karatsuba_algorithm_multiplication(a,a)) , n);
    }
    return res;
}

/*Recursive function to calculate gcd of 2 numbers*/
std::string gcd(std::string a, std::string b)
{
    if(a.compare(b) < 0)
        return gcd(b, a);
    else if(reminder(a,b) == "0")
        return b;
    else return gcd(b, reminder(a,b));
}

// If n is prime, then always returns true, If n is
// composite than returns false with high probability
// Higher value of k increases probability of correct
// result.
bool isPrime(std::string n, int k)
{
    // Corner cases
    if (n <= "1" || n == "4")  return false;
    if (n <= "3") return true;

    // Try k times
    while (k>0)
    {
        // Pick a random number in [2..n-2]
        // Above corner cases make sure that n > 4
        std::string a = "43";

        // Checking if a and n are co-prime
        if (gcd(n, a) != "1")
            return false;

        // Fermat's little theorem
        if (power(a, Big_num::subtract_big_num(n, "1")) != "1")
            return false;

        k--;
    }

    return true;
}


int is_prime_fermat_test(std::string number){}

#include "IsPrime.h"

bool miillerTest(std::string d, std::string n)
{

    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    if (n <= "1" || n == "4")  return false;
    if (n <= "3") return true;

    std::string a = "43";
    // Compute a^d % n
    std::string x = power(n,a,d);
    std::string n_minus_one = Big_num::subtract_big_num(n, "1");
    if (x == "1"  || x == n_minus_one)
        return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n_minus_one)
    {
        x = reminder((Big_num::karatsuba_algorithm_multiplication(x,x)) , n);
        d = Big_num::karatsuba_algorithm_multiplication(d, "2");

        if (x == "1")      return false;
        if (x == "n-1")    return true;
    }

    // Return composite
    return false;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime_Miller(std::string n, int k)
{
    // Corner cases
    if (n <= "1" || n == "4")  return false;
    if (n <= "3") return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    std::string d = Big_num::subtract_big_num(n, "1");;
    while (reminder(d,"2") == "0")
        d = longDivision(d, 2);

    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}


std::string modulo(std::string base, std::string exponent,
                 std::string mod)
{
    std::string x = "1";
    std::string y = base;
    while (exponent > "0")
    {
        if ((int)exponent.back() %2 == 1)
            x = reminder(Big_num::karatsuba_algorithm_multiplication(x , y) , mod);


        y = reminder(Big_num::karatsuba_algorithm_multiplication(y , y) , mod);
        exponent = longDivision(exponent , 2);
    }

    return reminder(x, mod);
}

// To calculate Jacobian symbol of a given number
int calculateJacobian(std::string a, std::string n)
{
    if (!a.empty())
        return 0;// (0/n) = 0

    int ans = 1;


    if (a == "1")
        return ans;// (1/n) = 1

    while (!a.empty())
    {

        while ( (int)a.back() % 2 == 0 )
        {
            a = longDivision(a,2);
            if (reminder(n , "8") == "3" || reminder(n,"8") == "5")
                ans = -ans;

        }

        swap(a, n);

        if (reminder(a, "4") == "3" && reminder(n , "4") != "3")
            ans = -ans;
        a = reminder(a,n);

        if (a > longDivision(n , 2))
            a = Big_num::subtract_big_num(a , n);

    }

    if (n == "1")
        return ans;

    return 0;
}

// To perform the Solovay-Strassen Primality Test
bool solovoyStrassen(std::string p, int iterations)
{
    if (p < "2")
        return false;
    if (p != "2" && reminder(p , "2") == "0")
        return false;

    for (int i = 0; i < iterations; i++)
    {
        // Generate a random number a
        int y = p.size();
        std::string a = std::to_string( (rand() % (std::max(y, 10000) + 23)) );
        std::string jacobian =
                reminder(
                (Big_num::sum_big_num(p,
                                      std::to_string( calculateJacobian(a, p) )
                                      )
                                      ) , p);
        std::string mod =
                modulo(a,
        longDivision(Big_num::subtract_big_num(p ,"1") , 2),
                       p);

        if (!jacobian.empty() || mod != jacobian)
            return false;
    }
    return true;


}
bool check_powers (std::string num) {

    //If n = ab for integers a > 1 and b > 1, output composite.
    for (unsigned long long b = 2;  std::to_string(b) <= num; b++) {
        for (unsigned long long a = 2; std::to_string(a) <= num; ++a) {
                if (power(num,std::to_string(a),std::to_string(b)) == "0") {
                    return false;
                }
            }

        }

};
//std::string find_r(std::string num){
//    std::string m = "2";
//    unsigned long long  pow = 0;
//    while (m < num){
//        m = Big_num::karatsuba_algorithm_multiplication(m, "2");
//        pow++;
//    }
//    unsigned long long square_log_2_n =pow*pow;
//    unsigned long long r =
//};


bool AKS_test(std::string num){
    std::string first_mult = longDivision(Big_num::sum_big_num(num,"3"), 2);
    std::string f= longDivision(Big_num::subtract_big_num(num,"1"), 2);
    std::string i = "1";

    while (i < Big_num::subtract_big_num(first_mult, "2")){
        first_mult = Big_num::karatsuba_algorithm_multiplication(first_mult, Big_num::sum_big_num(first_mult, i));
        i = Big_num::sum_big_num(i, "1");
    }
    while (i < f){
        first_mult = first_mult ;// /i

    }
    return gcd(first_mult, num) == num;
};