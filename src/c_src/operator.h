#ifndef OPERATOR
#define OPERATOR

typedef struct Rational{
    int _numerator;
    unsigned int _denominator;
} Rational;

/**
 * Returns a simplified rational by dividing both
 * the numerator and denominator by the gcd of both
 * factors.
 *
 * @param r a rational to simplify
 * @return a simplified rational
 */
Rational simplify_Rational(Rational);

/**
 * Returns -a.
 *
 * @param a a rational number to negate
 * @return -a
 */
Rational opposite_Rational(Rational);

/**
 * Returns a + b.
 *
 * @param a a rational number
 * @param b a rational number
 * @return a + b
 */
Rational add_Rational(Rational, Rational);

/**
 * Return a - b.
 *
 * @param a a rational number
 * @param b a rational number
 * @return  a - b
 */
Rational sub_Rational(Rational, Rational);

Rational multiply_Rational(Rational, Rational);

/**
 * Inverse a rational number, raise an error if trying to inverse O.
 *
 * @param a rational number
 * @return the inverse of a
 */
Rational inverse_Rational(Rational);

Rational divide_Rational(Rational, Rational);

double as_double_Rational(Rational);

void print_Rational(Rational);

char* as_str_Rational(Rational);

Rational str_to_Rational(char*);

Rational int_to_Rational(int);

int Rational_to_int(Rational);
#endif
