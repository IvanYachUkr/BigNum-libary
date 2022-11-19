//
// Created by Dir on 17.09.2022.
//

#include <algorithm>
#include <regex>
#include <iomanip>
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

// End of downloaded operatords











bool compare_nums(std::string n1, std::string n2){
    int len1 = n1.length();
    int len2 = n2.length();
    if (len1 == len2){
        return n1>n2;
    }
    else {
        return len1>len2;
    }
}


//+ - Operations
std::string longDivision(std::string number, int divisor)
{
    if ((number.back() - '0')%2 == 1 and divisor == 2){
        number= subtract_big_num(number, "1");
    }
    if (number == "1"){
        return "0";
    }
    // As result can be very large store it in string
    std::string ans;

    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
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


    int len_first_num = first_number.length(), len_second_num = second_number.length();


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
// End of +- operation










// support functions
std::string convert_decimal_to_binary(std::string num_decimal) {
    std::string num_binary = "";
    while (num_decimal > "0"){
        std::string rem = remainder(num_decimal, "2");
        num_binary =  rem + num_binary;
        num_decimal = longDivision(
                num_decimal.substr(0, num_decimal.length()-1)+
                        std::to_string(num_decimal.back() - rem[0]),
                2);
    }
    return num_binary;
}

std::string convert_binary_to_decimal(std::string num_binary) {
    std::string num_decimal = "";
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
    // Use regular expression to remove leading 0s
    const std::regex pattern("^0+(?!$)");

    // Replaces the matched value
    // with given string
    std::string num_without_leading_zeros = regex_replace(num, pattern, "");
    return num_without_leading_zeros;
}
// End of support functions











std::string Big_num::toom_cook_method_multiplication(std::string first_num, std::string second_num) {

    Big_num n;
    std::string f_n = first_num;
    std::string s_n = second_num;

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


    std::string C2 = longDivision(
            subtract_big_num(W2_sub_W1 , C1),
                                  2);

    std::string middle_term =  longDivision(
            subtract_big_num(W3_sub_W2, W2_sub_W1),
            2);
    std::string C3 = longDivision(
            subtract_big_num(middle_term,C2),
            3) ;

    std::string C4 =
            longDivision(
            subtract_big_num(

                    longDivision(
                            subtract_big_num(
                            longDivision( subtract_big_num(W4_sub_W3, W3_sub_W2), 2),
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

    // Adding
//    C4 = C4 + std::string(4 * one_third_numbers_len , '0');
//    C3 = C3 + std::string(3 * one_third_numbers_len , '0');
//    C2 = C2 + std::string(2 * one_third_numbers_len , '0');
//    C1 = C1 + std::string(1 * one_third_numbers_len , '0');
//    C0 = C0;
    std::string res = "";
//    res = sum_big_num(C4, C3);
//    res = sum_big_num(res, C2);
//    res = sum_big_num(res, C1);
//    res = sum_big_num(res, C0);
    res = karatsuba_algorithm_multiplication("65536", C4);
    res = sum_big_num(res, karatsuba_algorithm_multiplication("4096", C3));
    res = sum_big_num(res, karatsuba_algorithm_multiplication("256", C2));
    res = sum_big_num(res, karatsuba_algorithm_multiplication("16", C1));
    res = sum_big_num(res, C0);

    return res;
}


int Big_num::shenhage_method_multiplication(std::string first_num, std::string second_num) {
    return 0;
}

int Big_num::shtrassen_shenhage_method_multiplication(std::string first_num, std::string second_num) {
    return 0;
}

//std::basic_string<char> karatsuba_algorithm_multiplication(Big_num first_n, Big_num second_n) {
std::string karatsuba_algorithm_multiplication(std::string first_n, std::string second_n) {

//    std::string first_num =  first_n.num_decimal;
//    std::string second_num = second_n.num_decimal;
    std::string first_num =  first_n;
    std::string second_num = second_n;

    if (first_num.length() > second_num.length())
        swap(first_num, second_num);

    // Make both numbers to have
    // same digits
    int len_first_num = first_num.length();
    int len_second_num = second_num.length();

    first_num = std::string(len_second_num - len_first_num, '0') + first_num;
    len_first_num += len_second_num - len_first_num;
//    while (len_second_num > len_first_num) {
//        //first_num += "0";
//        first_num = "0" + first_num;
//        len_first_num++;
//    }

    // Base case
    if (len_first_num == 1) {

        int ans = stoi(first_num) * stoi(second_num);
        std::string ans_str = std::to_string(ans);
        return ans_str;
    }

    // Add zeros in the beginning of
    // the strings when length is odd
    if (len_first_num % 2 == 1) {
        len_first_num++;
        first_num = "0" + first_num;
        second_num = "0" + second_num;
    }

    std::string Al, Ar, Bl, Br;

    // Find the values of Al, Ar,
    // Bl, and Br.
    for (int i = 0; i < len_first_num / 2; ++i) {
        Al += first_num[i];
        Bl += second_num[i];
        Ar += first_num[len_first_num / 2 + i];
        Br += second_num[len_first_num / 2 + i];
    }

    // Stores the value of Al * Bl
    std::string Al_multiply_Bl = karatsuba_algorithm_multiplication(Al, Bl);

    // Stores the value of Ar * Br
    std::string Ar_multiply_Br = karatsuba_algorithm_multiplication(Ar, Br);

    // Stores value of ((Al + Ar)*(Bl + Br) - Al*Bl - Ar*Br)
    std::string A_multiply_B_with_leading_zeros = subtract_big_num(
            karatsuba_algorithm_multiplication(sum_big_num(Al, Ar),
                     sum_big_num(Bl, Br)),
            sum_big_num(Al_multiply_Bl, Ar_multiply_Br));

    // Multiply Al_multiply_Bl by 10^n
    for (int i = 0; i < len_first_num; ++i)
        Al_multiply_Bl +="0";

    // Multiply s by 10^(n/2)
    for (int i = 0; i < len_first_num / 2; ++i)
        A_multiply_B_with_leading_zeros = A_multiply_B_with_leading_zeros + "0";

    // Calculate final answer Al_multiply_Bl + A_multiply_B_with_leading_zeros + s
    std::string ans = sum_big_num(Al_multiply_Bl, sum_big_num(Ar_multiply_Br, A_multiply_B_with_leading_zeros));

    // Remove leading zeroes from ans
    ans = Big_num::remove_leading_zeros(ans);

    // Return Answer
    return ans;


}

Big_num Big_num::operator%(const Big_num &second_term) const {

    return Big_num();
}
std::string remainder(std::string number, std::string modulo){
    //number%modulo
    int a = number.length() - modulo.length();
    std::string m = std::string(std::max(0,a), '0') + modulo;
    if (number == modulo){
        return "0";
    } else if (compare_nums(number, modulo)) { //number.compare(modulo)
        while ( (number.length() > modulo.length()) or (compare_nums(number , modulo)) ) {
            std::string n1_copy = number;
            std::string n2_copy = modulo;

            n2_copy = n2_copy + std::string(number.length() - modulo.length() - (number.length() != modulo.length()), '0');
            n1_copy = subtract_big_num(number, n2_copy);
            number = n1_copy;
        }

    }
    return number;
}










std::string schonhageStrassenMultiplication(std::string x, std::string y)
{
    int n = x.length();
    int m = y.length();
    int linearConvolution[n + m - 1];
    for (int i = 0; i < (n + m - 1); i++)
        linearConvolution[i] = 0;

    std::string p = x;
    for (int i = 0; i < m; i++)
    {
        x = p;
        for (int j = 0; j < n; j++)
        {
            linearConvolution[i + j] += (y.back()-'0') * (x.back()-'0');
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
        linearConvolution[i] += nextCarry;
        //product = sum_big_num(product , std::to_string(base * (linearConvolution[i] % 10) ) );
        product = sum_big_num(product , std::to_string((linearConvolution[i] % 10) ) + std::string(b,'0'));
        nextCarry = linearConvolution[i] / 10;
        //base = karatsuba_algorithm_multiplication(base, "10");
        b++;
    }
    return product;

}




std::string inverse(const std::string& num){
    int base = num.length();
//    if (base <= 19){
//        unsigned long long approx_num = stoi(num.substr(0,base));
//        long double x = 1.0/approx_num;
//        return std::to_string(x);
//    }
    unsigned long long approx_num = stoi(num.substr(0,std::min(19, base-1)));
    long double x = 1.0/approx_num;

    std::string x_str = std::to_string(x);
    long double x_square = x*x;
    std::string x_square_str = std::to_string(x_square);
    if (base <= 19) {
        return x_str;
    }


    x_str = subtract_big_num(
            karatsuba_algorithm_multiplication("2",x_str)
            ,
            karatsuba_algorithm_multiplication(num, x_square_str)
            );

    return x_str;
}


std::string inverse_1(const std::string& num){
    int base = num.length();
    unsigned long long approx_num = stoll(num.substr(0,std::min(19, base)));
    long double x = 1.0/approx_num;

    //std::string z_str = boost::lexical_cast<std::string>(x);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(base + 2) << x;
    std::string x_str = stream.str();

    return x_str;
}



std::string mult_float(const std::string& num1, const std::string& num2){
    if (num2 == "1"){
        return num1;
    }
    int base1 = num1.length();
    int base2 = num2.length();
    //int pow_of_ten_1 = base1 - 2;
    int pow_of_ten_2 = base2 - 2;
    //std::string n1 = num1.substr(2,base1 +1 );
    std::string n1 = num1;
    std::string n2 = num2.substr(2,base2 +1 );
    n2 = Big_num::remove_leading_zeros(n2);
    //pow_of_ten_2 = pow_of_ten_2 - ()


//    if (num1.find(',') == std::string::npos){
//        n1 = num1;
//        pow_of_ten_1 = 0;
    //}
//    if (num1.find(',') == std::string::npos){
//        n2 = num2;
//        pow_of_ten_2 = 0;
//    }
    std::string mult = karatsuba_algorithm_multiplication(n1, n2);
    int mult_len = mult.length();
    std::string res =std::string( "0",std::max(pow_of_ten_2-mult_len,0)) + mult;
    res.insert(mult_len-pow_of_ten_2, ".");

    if (res[0] == '.' )
        res = std::string(1, '0')+".";


    //res = res + std::string( "0",pow_of_ten_1+pow_of_ten_2-mult_len) + mult;
   // res = res + std::string( "0",pow_of_ten_2-mult_len) + mult;
    return res;
}

std::string division(std::string num, std::string divisor){
    std::string divisor_inverse = inverse_1(divisor);
    return mult_float(num, divisor_inverse);
}


std::string modular_mult(std::string num1, std::string num2){
    std::string res = "";
    std::string m1 = "9999";
    std::string m2 = "999999";
    std::string m3 = "9999999";
    std::string m4 = "99999999";
    std::string m5 = "9999999999";
    std::string m6 = "999999999999";


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

//    w_1 = w1 mod m1
//                    1       2  3      4   ... operations // M_j_k, k = 1...n
// w_j = ( ... ( ( wj - w_1) C1j - w_2) C2j - · · · - w_j_1) C(j-1)j mod mj
    std::string w_1 = remainder(w1, m1);
    std::string w_2 = remainder(karatsuba_algorithm_multiplication(subtract_big_num(w2 , w_1), "1000000"), m2);
    std::string w_3 = remainder(
            karatsuba_algorithm_multiplication(
                subtract_big_num(

                karatsuba_algorithm_multiplication(
                        subtract_big_num(w3, w_1), "10000000"
                          ),

                          w_2
                        ),

                    "19999999"
            )
            ,
            m3
            );
    std::string c_1_4 = "100000000";
    std::string c_2_4 = "199999999";
    std::string c_3_4 = "299999998";
    std::string M_4_1 = subtract_big_num(w4, w_1);
    std::string M_4_2 = karatsuba_algorithm_multiplication(M_4_1, c_1_4);
    std::string M_4_3 = subtract_big_num(M_4_2, w_2);
    std::string M_4_4 = karatsuba_algorithm_multiplication(M_4_3, c_2_4);
    std::string M_4_5 = subtract_big_num(M_4_4, w_3);
    std::string M_4_6 = karatsuba_algorithm_multiplication(M_4_5, c_3_4);
    std::string w_4 = remainder(M_4_6, m4);


    std::string c_1_5 = "10000000000";
    std::string c_2_5 = "19999999999";
    std::string c_3_5 = "29999999998";
    std::string c_4_5 = "39999999997";
    std::string M_5_1 = subtract_big_num(w5, w_1);
    std::string M_5_2 = karatsuba_algorithm_multiplication(M_5_1, c_1_5);
    std::string M_5_3 = subtract_big_num(M_5_2, w_2);
    std::string M_5_4 = karatsuba_algorithm_multiplication(M_5_3, c_2_5);
    std::string M_5_5 = subtract_big_num(M_5_4, w_3);
    std::string M_5_6 = karatsuba_algorithm_multiplication(M_5_5, c_3_5);
    std::string M_5_7 = subtract_big_num(M_5_6, w_4);
    std::string M_5_8 = karatsuba_algorithm_multiplication(M_5_7, c_4_5);
    std::string w_5 = remainder(M_5_8, m5);


    std::string c_1_6 = "1000000000000";
    std::string c_2_6 = "1999999999999";
    std::string c_3_6 = "2999999999998";
    std::string c_4_6 = "3999999999997";
    std::string c_5_6 = "4999999999996";
    std::string M_6_1 = subtract_big_num(w6, w_1);
    std::string M_6_2 = karatsuba_algorithm_multiplication(M_6_1, c_1_6);
    std::string M_6_3 = subtract_big_num(M_6_2, w_2);
    std::string M_6_4 = karatsuba_algorithm_multiplication(M_6_3, c_2_6);
    std::string M_6_5 = subtract_big_num(M_6_4, w_3);
    std::string M_6_6 = karatsuba_algorithm_multiplication(M_6_5, c_3_6);
    std::string M_6_7 = subtract_big_num(M_6_6, w_4);
    std::string M_6_8 = karatsuba_algorithm_multiplication(M_6_7, c_4_6);
    std::string M_6_9 = subtract_big_num(M_6_8, w_5);
    std::string M_6_10 = karatsuba_algorithm_multiplication(M_6_9, c_5_6);
    std::string w_6 = remainder(M_6_10, m6);

    //w = ( ... (w_r * m_r-1 + w_r-1 ) m_r-2 + · · · + w_2) m1 + w_1.
    // w_6 * m5 + w4
    std::string w = karatsuba_algorithm_multiplication(w_6, m5);
    w = sum_big_num(w, w_5);
    w = karatsuba_algorithm_multiplication(w, m4);
    w = sum_big_num(w, w_4);
    w = karatsuba_algorithm_multiplication(w, m3);
    w = sum_big_num(w, w_3);
    w = karatsuba_algorithm_multiplication(w, m2);
    w = sum_big_num(w, w_2);
    w = karatsuba_algorithm_multiplication(w, m1);
    w = sum_big_num(w, w_1);
    return w;









    return res;
}









