//
// Created by Dir on 17.09.2022.
//

#include <algorithm>
#include <regex>
#include <iomanip>
#include <utility>
#include "BigNum.h"


//Overloaded operators
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

std::ostream& operator<<(std::ostream& os, const Big_num& bm)
{
    os << bm.num_decimal;
    return os;
}


Big_num Big_num::operator%(const Big_num &second_term) const {
    Big_num n;
    n.num_decimal = remainder(num_decimal, second_term.num_decimal);
    return Big_num();
}
// End of downloaded operatords









// Operators

bool compare_nums(const std::string& n1, const std::string& n2){
    int len1 = n1.length();
    int len2 = n2.length();
    if (len1 == len2){
        return n1>n2;
    }
    else {
        return len1>len2;
    }
}


std::string long_division(std::string number, int divisor)
{
    if ((number.back() - '0')%2 == 1 and divisor == 2){
        number= subtract_big_num(number, "1");
    }
    if (number == "1"){
        return "0";
    }

    std::string ans;


    int index = 0;
    int temp = number[index] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++index] - '0');


    while (number.size() > index) {

        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++index] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}

std::string remainder(std::string number, const std::string& modulo){
    //number%modulo
    int a = number.length() - modulo.length();
    std::string m = std::string(std::max(0,a), '0') + modulo;
    if (number == modulo){
        return "0";
    } else if (compare_nums(number, modulo)) { //number.compare(modulo)
        while ( (number.length() > modulo.length()) or (!compare_nums( modulo, number)) ) {
            std::string n1_copy;
            std::string n2_copy = modulo;

            n2_copy += std::string(number.length() - modulo.length() - (number.length() != modulo.length()), '0');
            n1_copy = subtract_big_num(number, n2_copy);
            number = n1_copy;
        }

    }
    return number;
}



std::string sum_big_num(std::string first_number,std::string second_number){
    int len_first_num = first_number.length();
    int len_second_num = second_number.length();

    if (len_first_num > len_second_num)
        swap(first_number, second_number);

    first_number = std::string(abs(len_first_num - len_second_num), '0') + first_number;

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



std::string subtract_big_num(std::string first_number, std::string second_number) {
    std::string res;


    int len_first_num = first_number.length();
    int len_second_num = second_number.length();


    reverse(second_number.begin(), second_number.end());
    reverse(first_number.begin(), first_number.end());

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
    res = Big_num::remove_leading_zeros(res);
    if (res.empty()){
        res = "0";
    }
    return res;
}
// End of operators










// support functions

std::string convert_decimal_to_binary(std::string num_decimal) {
    std::string num_binary;
    while (num_decimal > "0"){
        std::string rem = remainder(num_decimal, "2");
        num_binary =  rem + num_binary;
        num_decimal = long_division(
                num_decimal.substr(0, num_decimal.length()-1)+
                        std::to_string(num_decimal.back() - rem[0]),
                2);
    }
    return num_binary;
}

std::string convert_binary_to_decimal(std::string num_binary) {
    std::string num_decimal;
    int len_binary = num_binary.length();
    reverse(num_binary.begin(), num_binary.end());
    std::string two_to_power = "1";
    for (int i = 0; i < len_binary; ++i) {
        std::string pow = num_binary.substr(i, 1);
        num_decimal = sum_big_num(num_decimal, karatsuba_algorithm_multiplication(two_to_power, pow));
        two_to_power = karatsuba_algorithm_multiplication(two_to_power, "2");
    }
    return num_decimal;
}



std::string Big_num::remove_leading_zeros(const std::string& num) {
    //(?!$) is a negative lookahead. It will look for any match of abc that is not directly followed by a $ (end of line)
    const std::regex pattern("^0+(?!$)");

    std::string num_without_leading_zeros = regex_replace(num, pattern, "");
    return num_without_leading_zeros;
}
// End of support functions









//Multiplication methods

std::string Big_num::toom_cook_method_multiplication(std::string first_num, std::string second_num) {

    Big_num n;

    first_num = convert_decimal_to_binary(first_num);
    second_num = convert_decimal_to_binary(second_num);

    if (first_num.length()<second_num.length()){
        swap(first_num, second_num);
    }
    second_num = std::string(first_num.length() - second_num.length(), '0') + second_num;

    int len_first_num = first_num.size();

    int len_second_num = second_num.size();

    int numbers_len = std::max(len_first_num, len_second_num);
    int one_third_numbers_len = numbers_len / 3;
    if (len_first_num < len_second_num){
        swap(first_num, second_num);
        std::swap(len_first_num, len_second_num);
    }
    second_num = std::string (len_first_num-len_second_num, '0') + second_num;



    std::string  A1 = first_num.substr(0, one_third_numbers_len);
    std::string  A2 = first_num.substr(one_third_numbers_len, one_third_numbers_len);
    std::string  A3 = first_num.substr(2 * one_third_numbers_len, numbers_len + 1 );

    A1 = convert_binary_to_decimal(A1);
    A2 = convert_binary_to_decimal(A2);
    A3 = convert_binary_to_decimal(A3);

    std::string  B1 = second_num.substr(0, one_third_numbers_len);
    std::string  B2 = second_num.substr(one_third_numbers_len, one_third_numbers_len);
    std::string  B3 = second_num.substr(2 * one_third_numbers_len, numbers_len+1);

    B1 = convert_binary_to_decimal(B1);
    B2 = convert_binary_to_decimal(B2);
    B3 = convert_binary_to_decimal(B3);

    std::string W0 = karatsuba_algorithm_multiplication(A3 , B3);

    std::string W1 = karatsuba_algorithm_multiplication(
            sum_big_num( (sum_big_num(A3, A2)), A1),

            sum_big_num( (sum_big_num(B3, B2)), B1)
            );
    std::string W2 = karatsuba_algorithm_multiplication(
            sum_big_num(
                    (sum_big_num(A3,
                                 karatsuba_algorithm_multiplication(A2, "2"))),
                                        karatsuba_algorithm_multiplication(A1, "4")),

            sum_big_num(
                    (sum_big_num(B3,
                                 karatsuba_algorithm_multiplication(B2, "2"))),
                    karatsuba_algorithm_multiplication(B1, "4"))
            );
    std::string W3 = karatsuba_algorithm_multiplication(
            sum_big_num(
                    (sum_big_num(A3,
                                 karatsuba_algorithm_multiplication(A2, "3"))),
                    karatsuba_algorithm_multiplication(A1, "9")),

            sum_big_num(
                    (sum_big_num(B3,
                                 karatsuba_algorithm_multiplication(B2, "3"))),
                    karatsuba_algorithm_multiplication(B1, "9"))
    );
    std::string W4 = karatsuba_algorithm_multiplication(
            sum_big_num(
                    (sum_big_num(A3,
                                 karatsuba_algorithm_multiplication(A2, "4"))),
                    karatsuba_algorithm_multiplication(A1, "16")),

            sum_big_num(
                    (sum_big_num(B3,
                                 karatsuba_algorithm_multiplication(B2, "4"))),
                    karatsuba_algorithm_multiplication(B1, "16"))
            );
    std::string W4_sub_W3 = subtract_big_num(W4, W3);
    std::string W3_sub_W2 = subtract_big_num(W3, W2);
    std::string W2_sub_W1 = subtract_big_num(W2, W1);
    std::string W1_sub_W0 = subtract_big_num(W1, W0);


    std::string C0 = W0;

    std::string C1 = W1_sub_W0;


    std::string C2 = long_division(
            subtract_big_num(W2_sub_W1 , C1),
                                  2);

    std::string middle_term =  long_division(
            subtract_big_num(W3_sub_W2, W2_sub_W1),
            2);
    std::string C3 = long_division(
            subtract_big_num(middle_term,C2),
            3) ;

    std::string C4 =
            long_division(
            subtract_big_num(

                    long_division(
                            subtract_big_num(
                            long_division( subtract_big_num(W4_sub_W3, W3_sub_W2), 2),
                        middle_term),
                        3),

                        C3),
            4);
    C3 = subtract_big_num(C3, karatsuba_algorithm_multiplication("3", C4));
    C2 = subtract_big_num(C2, karatsuba_algorithm_multiplication("2", C3));
    C1 = subtract_big_num(C1,  C2);

    C3 = subtract_big_num(C3, karatsuba_algorithm_multiplication("2", C4));
    C2 = subtract_big_num(C2, C3);
    C3 = subtract_big_num(C3, C4);


    std::string res;

    res = karatsuba_algorithm_multiplication("65536", C4);
    res = sum_big_num(res, karatsuba_algorithm_multiplication("4096", C3));
    res = sum_big_num(res, karatsuba_algorithm_multiplication("256", C2));
    res = sum_big_num(res, karatsuba_algorithm_multiplication("16", C1));
    res = sum_big_num(res, C0);

    return res;
}


std::string karatsuba_algorithm_multiplication(std::string first_n, std::string second_n) {

    std::string first_num =  std::move(first_n);
    std::string second_num = std::move(second_n);

    if (first_num.length() > second_num.length())
        swap(first_num, second_num);


    int len_first_num = first_num.length();
    int len_second_num = second_num.length();

    first_num = std::string(len_second_num - len_first_num, '0') + first_num;
    len_first_num += len_second_num - len_first_num;



    if (len_first_num == 1) {

        int ans = stoi(first_num) * stoi(second_num);
        std::string ans_str = std::to_string(ans);
        return ans_str;
    }


    if (len_first_num % 2 == 1) {
        len_first_num++;
        first_num = "0" + first_num;
        second_num = "0" + second_num;
    }

    std::string A_left_most, A_right_most, B_left_most, B_right_most;

    // Find the values of A_left_most, A_right_most,
    // B_left_most, and B_right_most.
    for (int i = 0; i < len_first_num / 2; ++i) {
        A_left_most += first_num[i];
        B_left_most += second_num[i];
        A_right_most += first_num[len_first_num / 2 + i];
        B_right_most += second_num[len_first_num / 2 + i];
    }

    //A_left_most * B_left_most
    std::string Al_multiply_Bl = karatsuba_algorithm_multiplication(A_left_most, B_left_most);

    //A_right_most * B_right_most
    std::string Ar_multiply_Br = karatsuba_algorithm_multiplication(A_right_most, B_right_most);

    // ((A_left_most + A_right_most)*(B_left_most + B_right_most) - A_left_most*B_left_most - A_right_most*B_right_most)
    std::string A_multiply_B_with_leading_zeros = subtract_big_num(
            karatsuba_algorithm_multiplication(sum_big_num(A_left_most, A_right_most),
                     sum_big_num(B_left_most, B_right_most)),
            sum_big_num(Al_multiply_Bl, Ar_multiply_Br));

    for (int i = 0; i < len_first_num; ++i)
        Al_multiply_Bl +="0";

    for (int i = 0; i < len_first_num / 2; ++i)
        A_multiply_B_with_leading_zeros = A_multiply_B_with_leading_zeros + "0";

    //Al_multiply_Bl + A_multiply_B_with_leading_zeros + s
    std::string ans = sum_big_num(Al_multiply_Bl, sum_big_num(Ar_multiply_Br, A_multiply_B_with_leading_zeros));
    
    ans = Big_num::remove_leading_zeros(ans);
    
    return ans;


}














std::string Schonhage_Strassen_Multiplication_method(std::string x, std::string y)
{
    //sources https://en.wikipedia.org/wiki/Schönhage–Strassen_algorithm#Convolutions
    // https://www.geeksforgeeks.org/java-program-to-implement-the-schonhage-strassen-algorithm-for-multiplication-of-two-numbers/#:~:text=So%2C%20Schonhage-Strassen%27s%20algorithm%20is,Acyclic%20Convolution%20or%20Linear%20Convolution.
    int n = x.length();
    int m = y.length();
    int linear_convolution[n + m - 1];
    for (int i = 0; i < (n + m - 1); i++)
        linear_convolution[i] = 0;

    std::string p = x;
    for (int i = 0; i < m; i++)
    {
        x = p;
        for (int j = 0; j < n; j++)
        {
            linear_convolution[i + j] += (y.back() - '0') * (x.back() - '0');
            x = std::string(x, 0, x.length() - 1);
        }
        y = std::string(y, 0, y.length() - 1);
    }

    std::string product = "0";
    int nextCarry = 0;
    //std::string base = "";
    int b = 0;
    for (int i = 0; i < n + m - 1; i++)
    {
        linear_convolution[i] += nextCarry;
        //product = sum_big_num(product , std::to_string(base * (linear_convolution[i] % 10) ) );
        product = sum_big_num(product , std::to_string((linear_convolution[i] % 10) ) + std::string(b, '0'));
        nextCarry = linear_convolution[i] / 10;
        //base = karatsuba_algorithm_multiplication(base, "10");
        b++;
    }
    return product;

}



//Operators for float numbers

std::string mult_float(const std::string& num1, const std::string& num2){
    if (num2 == "1"){
        return num1;
    }

    int base2 = num2.length();

    int pow_of_ten_2 = base2 - 2;

    std::string n1 = num1;
    std::string n2 = num2.substr(2,base2 +1 );
    n2 = Big_num::remove_leading_zeros(n2);

    std::string mult = karatsuba_algorithm_multiplication(n1, n2);
    int mult_len = mult.length();
    std::string res =std::string( std::max(pow_of_ten_2-mult_len,0),'0') + mult;
    res.insert(res.length()-pow_of_ten_2, ".");

    if (res[0] == '.' )
        res = std::string(1, '0') +res;



    return res;
}

std::string subtract_float(const std::string& num1, const std::string& num2){
    int base1 = num1.length();
    int base2 = num2.length();
    int pow_of_ten_1 = base1 - 2;
    int pow_of_ten_2 = base2 - 2;
    std::string n1 = num1.substr(2,base1 +1 );

    std::string n2 = num2.substr(2,base2 +1 );
    n1 = n1 + std::string(std::max(0,pow_of_ten_2-pow_of_ten_1),'0');

    int num_of_leading_zeros = n1.length() - (Big_num::remove_leading_zeros(n1)).length();

    std::string subtr = subtract_big_num(n1, n2);

    subtr = Big_num::remove_leading_zeros(subtr);
    std::string res ="0." + std::string( std::max(num_of_leading_zeros,0),'0') + subtr;

    return res;
}

std::string mult_two_float(const std::string& num1, const std::string& num2){

    int base1 = num1.length();
    int base2 = num2.length();
    int pow_of_ten_1 = base1 - 2;
    int pow_of_ten_2 = base2 - 2;
    std::string n1 = num1.substr(2,base1 +1 );

    std::string n2 = num2.substr(2,base2 +1 );

    n1 = Big_num::remove_leading_zeros(n1);
    n2 = Big_num::remove_leading_zeros(n2);

    std::string mult = karatsuba_algorithm_multiplication(n1, n2);
    int mult_len = mult.length();

    std::string res =std::string( std::max(pow_of_ten_2+pow_of_ten_1-mult_len,0),'0') + mult;
    res.insert(res.length()-pow_of_ten_2-pow_of_ten_1, ".");

    if (res[0] == '.' )
        res = std::string(1, '0')+res;

    return res;
}


std::string fixed_precision_inverse(const std::string& num){
    int base = num.length();
    unsigned long long approx_num = stoll(num.substr(0,std::min(19, base)));
    long double x = 1.0/approx_num;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2*base ) << x;
    std::string x_str = stream.str();

    return x_str;
}


std::string inverse(const std::string& num, int k){
    std::string x = fixed_precision_inverse(num);

    for (int i = 0; i < k; ++i) {
        std::string x_square = mult_two_float(x,x);
        std::string coef1 = mult_float("2",x);
        std::string coef2 = mult_float(num,x_square);
        x = subtract_float(coef1, coef2);
        x = x.substr(0, std::min(x.length(), (k+1)*2*num.length()));
    }

    return x;
}








std::string division(const std::string& num, const std::string& divisor){
    std::string divisor_inverse = fixed_precision_inverse(divisor);
    return mult_float(num, divisor_inverse);
}








std::string modulo_inverse(std::string a, std::string m)
{
    std::string m0 = m, t, q;
    std::string x0 = "0", x1 = "1";
    bool sign_x_0 = true;

    if (m == "1")
        return "0";


    while (compare_nums(a,"1")) {

        int m_int = stoll(m);

        q = long_division(subtract_big_num(a,remainder(a,m)),m_int);

        t = m;


        m = remainder(a,m), a = t;

        t = x0;

        std::string mult = karatsuba_algorithm_multiplication(q , x0);
        if (sign_x_0)
            if (compare_nums(x1, mult))
                x0 = subtract_big_num(x1, mult);

            else {
                x0 = subtract_big_num(mult, x1);
                sign_x_0 = false;
            }
        else
            x0 = sum_big_num(x1, mult);

        x1 = t;
    }


    return x1;
}


std::string solve_chinese_remainder_th(std::string num[], std::string rem[], int k)
{
    // Compute mult_all_nums of all numbers

    auto mult_all_nums = [k, num] (int i) -> std::string {
        std::string prod = "1";
        for (int j = 0; j < k; j++) {
            if (j != i)
                prod = karatsuba_algorithm_multiplication(num[i], prod);
        }
        return prod;
    };


    std::string result = "0";


    for (int i = 0; i < k; i++) {


        std::string product = mult_all_nums(i);
        result = sum_big_num(result, karatsuba_algorithm_multiplication(
                karatsuba_algorithm_multiplication(rem[i] , modulo_inverse(product, num[i]) )
                                                                , product));
    }

    return remainder(result , mult_all_nums(k + 1));
}






std::string modular_mult(const std::string& num1, const std::string& num2){


    std::string m1 = "8388607";//2^23 - 1
    std::string m2 = "33554431";//2^25 - 1
    std::string m3 = "67108863";//2^26 - 1
    std::string m4 = "134217727";//2^27 - 1
    std::string m5 = "536870911";//2^29 - 1
    std::string m6 = "2147483647";//2^31 - 1

    if ( (num1.length() < m6.length()/2) and (num1.length() < m6.length()/2) ){
        return karatsuba_algorithm_multiplication(num1, num2);
    }


    std::string u1 = remainder(num1, m1);
    std::string u2 = remainder(num1, m2);
    std::string u3 = remainder(num1, m3);
    std::string u4 = remainder(num1, m4);
    std::string u5 = remainder(num1, m5);
    std::string u6 = remainder(num1, m6);


    std::string v1 = remainder(num2, m1);
    std::string v2 = remainder(num2, m2);
    std::string v3 = remainder(num2, m3);
    std::string v4 = remainder(num2, m4);
    std::string v5 = remainder(num2, m5);
    std::string v6 = remainder(num2, m6);

    std::string w1 = remainder(karatsuba_algorithm_multiplication(v1, u1), m1);
    std::string w2 = remainder(karatsuba_algorithm_multiplication(v2, u2), m2);
    std::string w3 = remainder(karatsuba_algorithm_multiplication(v3, u3), m3);
    std::string w4 = remainder(karatsuba_algorithm_multiplication(v4, u4), m4);
    std::string w5 = remainder(karatsuba_algorithm_multiplication(v5, u5), m5);
    std::string w6 = remainder(karatsuba_algorithm_multiplication(v6, u6), m6);

    std::string moduli[] = {m1,m2,m3,m4,m5,m6};
    std::string rem[] = {w1,w2,w3,w4,w5,w6};
    std::string w = solve_chinese_remainder_th(moduli, rem, 6);

    return w;


}









