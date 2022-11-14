#include "operator.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

void print_Rational(Rational r){
    printf("R[%d/%d]", r._numerator, r._denominator);
}