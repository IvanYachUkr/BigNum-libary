#include <string>
#include <bits/stdc++.h>
#include "BigNum.h"
#include "IsPrime.h"



std::string power(std::string n, std::string a = "3", std::string p ="1")
// a^p % n | p = n-1, a^(n-1)%p
{
    if (p == "1") {
        p = subtract_big_num(n, "1");

    }
    std::string res = "1";

    while (p.length() > 1 or p.back() > '0')
    {
        int last_digit = p.back() - '0';

        if (last_digit & 1) {

            res = (karatsuba_algorithm_multiplication(res,a));

            if (compare_nums(res, n)) {
                res = remainder(res, n);
            }

        }

        p = long_division(p, 2);
        a = remainder((karatsuba_algorithm_multiplication(a, a)), n);
    }
    return res;
}


std::string gcd(std::string a, std::string b)
{
    if(compare_nums(b,a))
        return gcd(b, a);
    else if(remainder(a, b) == "0")
        return b;
    else return gcd(b, remainder(a, b));
}


bool is_prime_fermat_test(std::string n, int k) {
    int n_int = n.back() - '0';

    if (n.length() <= 1) {
        if (n_int <= 1 || n_int == 4) return false;
        if (n_int <= 3) return true;
    }

    if (n_int % 2 == 0) {
        return false;
    }


    int y = n.length();

    while (k>0)
    {

        std::string a = std::to_string( (rand() % (std::min(y, 10000) + 3)) + 3 );

        if (gcd(n, a) != "1")
            return false;


        if (power(n,a) != "1")
            return false;

        k--;
    }

    return true;
}





bool miller_rabin_test(std::string d, std::string n)
{


    int n_int = n.back() - '0';

    if (n.length() <= 1) {
        if (n_int <= 1 || n_int == 4) return false;
        if (n_int <= 3) return true;
    }

    if (n_int % 2 == 0) {
        return false;
    }

    std::string a = "7";

    std::string x = power(n,a,d);
    std::string n_minus_one = subtract_big_num(n, "1");
    if (x == "1"  || x == n_minus_one)
        return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n_minus_one)
    {
        x = remainder((karatsuba_algorithm_multiplication(x, x)), n);
        d = karatsuba_algorithm_multiplication(d, "2");

        if (x == "1")      return false;
        if (x == n_minus_one)    return true;
    }

    return false;
}


bool miller_rabin_primality_test(std::string n, int k)
{

    int n_int = n.back() - '0';

    if (n.length() <= 1) {
        if (n_int <= 1 || n_int == 4) return false;
        if (n_int <= 3) return true;
    }

    if (n_int % 2 == 0) {
        return false;
    }

    // Find r such that n = 2^d * r + 1 for some r >= 1
    std::string d = subtract_big_num(n, "1");
    while (d.back()%2 == 0)
        d = long_division(d, 2);

    for (int i = 0; i < k; i++)
        if (!miller_rabin_test(d, n))
            return false;

    return true;
}


std::string modulo(std::string base, std::string exponent,
                 std::string mod)
{
    std::string x = "1";
    std::string y = base;
    while ( compare_nums(exponent,"0") )
    {
        if ( ( exponent.back() - '0')  % 2 == 1)
            x = remainder(karatsuba_algorithm_multiplication(x, y), mod);


        y = remainder(karatsuba_algorithm_multiplication(y, y), mod);
        exponent = long_division(exponent, 2);
    }

    return remainder(x, mod);
}


int calculateJacobian(std::string a, std::string n)
{
    if (a == "0")
        return 0;

    int ans = 1;
    bool minus_a = false;

    if (a == "1")
        return ans;

    while (a != "0")
    {

        if (minus_a)
        {
            minus_a = !minus_a;
            if ( remainder(n , "4") == "3" )
                ans = -ans;
        }

        while ( (a.back()-'0') % 2 == 0 )
        {
            a = long_division(a, 2);
            if (remainder(n, "8") == "3" || remainder(n, "8") == "5")
                ans = -ans;

        }

        swap(a, n);

        if (remainder(a, "4") == "3" && remainder(n, "4") == "3")
            ans = -ans;
        a = remainder(a, n);

        if (compare_nums(karatsuba_algorithm_multiplication(a,"2") , n))
            minus_a = !compare_nums(a,n);

            if (minus_a) {
                a = subtract_big_num(n, a);
            }else {
                a = subtract_big_num(a, n);
            }
    }

    if (n == "1")
        return ans;

    return 0;
}


bool solovay_strassen(std::string p, int iterations)
{
    if (!compare_nums(p,"2"))
        return false;
    if (p != "2" && (p.back() -'0') %2 == 0)
        return false;

    for (int i = 0; i < iterations; i++)
    {
        int y = p.length();
        std::string a = std::to_string( (rand() % (std::min(y, 10000) + 3)) + 3 );
        int cj = calculateJacobian(a, p);
        std::string s;
        if (cj >= 0){
            s = sum_big_num(p,"1");
        } else if (cj == -1){
            s = subtract_big_num(p,"1");
        }
        std::string jacobian =
                remainder(s, p);
        std::string mod =
                modulo(a,
                       long_division(subtract_big_num(p, "1"), 2),
                       p);

        if (jacobian=="0" || mod != jacobian)
            return false;
    }
    return true;


}

bool AKS_primality_test(unsigned long long int n)
{
    std::vector<unsigned long long int> c;

    auto coef = [n,&c]()
    {
        int line = n+1;
        for (unsigned long long  i = 0; i < line/2; i++)
            c.push_back(1);

        int C=1;
        c[0] = C;
        for (unsigned long long i = 1; i <= line/2-1; i++)
        {
            C = C * (line - i) / i;
            c[i] = C;


        }
    };
    coef();

    int i = n/2;
    while (i-- && c[i] % n == 0)
        ;

    return i == 0;
}

bool AKS_primality_test(std::string n) {
    std::string i = "2";
    std::string upper_bound_i = long_division(subtract_big_num(n, "1"), 2);
    std::string line = sum_big_num(n, "1");
    std::string C = n;
    while (compare_nums(upper_bound_i,i) && (remainder(C, n) == "0")) {
        C = long_division(
            (karatsuba_algorithm_multiplication(C, subtract_big_num(line, i))),
            stoll(i));
        i = sum_big_num(i, "1");

        if (remainder(C, n) != "0")
            return false;

    }
    return true;
}


