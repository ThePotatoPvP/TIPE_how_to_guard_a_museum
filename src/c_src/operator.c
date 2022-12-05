#include "operator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Returns the absolute value of the greatest common divisor
 * between two given integers.
 *
 * @param a an integer
 * @param b an integer
 * @return The absolute value of the gcd
 */
int gcd(int a, int b){
    int c = abs(a), d = b;

    if (c < d){
        c = d;
        d = abs(a);
    }

    while(d != 0){
        int tmp = c;
        c = d;
        d = tmp % d;
    }

    return c;
}

Rational simplify_Rational(Rational r) {
    int cd = gcd(r._numerator, (int) r._denominator);
    return (Rational) {r._numerator / cd, r._denominator / cd};
}

Rational add_Rational(Rational a, Rational b) {
    int num = a._numerator * (int) b._denominator + (int) a._denominator * b._numerator;
    unsigned int den = a._denominator * b._denominator;
    return simplify_Rational((Rational) {num, den});
}

Rational opposite_Rational(Rational a) {
    return (Rational) {-a._numerator, a._denominator};
}

Rational sub_Rational(Rational a, Rational b){
    return add_Rational(a, opposite_Rational(b));
}

Rational multiply_Rational(Rational a, Rational b) {
    return simplify_Rational((Rational) {a._numerator * b._numerator,
                                         a._denominator * b._denominator});
}

Rational inverse_Rational(Rational a) {

    if(a._numerator == 0){
        printf("Error: Rational trying to inverse 0\n");
        exit(2);
    }

    int sign = a._numerator >= 0 ? 1: -1;
    return (Rational) {(int) a._denominator * sign, abs(a._numerator)};
}

Rational divide_Rational(Rational a, Rational b){
    return multiply_Rational(a, inverse_Rational(b));
}

double as_double_Rational(Rational a){
    return (double) a._numerator/ (double) a._denominator;
}

Rational int_to_Rational(int n){
    return (Rational) {n, 1};
}

int Rational_to_int(Rational r){
    Rational n = simplify_Rational(r);
    if(n._denominator != 1){
        exit(1); // bruh
    }
    return n._numerator;
}

void print_Rational(Rational r){
    printf("R[%d/%d]", r._numerator, r._denominator);
}

char* as_str_Rational(Rational r){
    int numerator_len = snprintf(NULL, 0,"%d", r._numerator);
    int denominator_len = snprintf(NULL, 0,"%d", r._denominator);

    char* rational = malloc(sizeof (char) * (numerator_len + denominator_len + 4 + 1)); // + 1 for \0

    sprintf(rational, "R[%d;%d]", r._numerator, r._denominator);

    return rational;
}

int pow10(int n){
    int result = 1;
    while(n--)
        result *= 10;
    return result;
}

Rational str_to_Rational(char* rational){
    //R[_num;_den]
    Rational r = {0, 0};
    int n = strlen(rational);
    int i = 2;
    int power = 0;
    while(rational[n-i] != ';'){
        r._denominator += pow10(power++) * (rational[n-i++] - '0');
    }
    i++;
    power = 0;
    while(rational[n-i] != '['){
        r._numerator += pow10(power++) * (rational[n-i++] - '0');
    }
    return r;
}