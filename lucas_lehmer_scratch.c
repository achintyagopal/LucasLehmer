#include <stdio.h>
#include <stdlib.h>

#define BASE 30
#define p 5000
#define MASK (1 << BASE) - 1
#define primeSize p / BASE + 1
#define primeLeftOver p % BASE
#define tmpMask ((1 << primeLeftOver) - 1)

struct BigNum {
    unsigned long *ob_type;
    unsigned long ob_size; 
};

struct BigNum* initializeWithSize(unsigned int size) {
    struct BigNum* a = (struct BigNum*) malloc(sizeof(struct BigNum));

    unsigned long* arr = (unsigned long *) calloc(size, sizeof(unsigned long));
    a->ob_type = arr;
    a->ob_size = size;
    return a;
}

struct BigNum* initializeToFour(unsigned int size) {
    struct BigNum* a = initializeWithSize(size);
    a->ob_type[0] = 4;

    return a;
}

struct BigNum* initializePrime() {

    struct BigNum* a = initializeWithSize(primeSize);

    for (long j = 0; j < primeSize - 1; j++) {
        a->ob_type[j] = MASK;
    }
    a->ob_type[primeSize - 1] = (1 << primeLeftOver) - 1;

    return a;
}

void print(struct BigNum* number) {
    for (unsigned long i = number->ob_size - 1; i > 0; i--) {
        printf("%lu ", number->ob_type[i]);
    }
    printf("%lu\n", number->ob_type[0]);
}

void multiplyAndAdd(struct BigNum* res, unsigned long number, struct BigNum* a, unsigned long offset) {
    unsigned long carry = 0;
    unsigned long tmp;
    for (unsigned long i = 0; i < a->ob_size; i++) {
        tmp = a->ob_type[i] * number + res->ob_type[i+offset] + carry;
        res->ob_type[i + offset] = tmp & MASK;
        carry = tmp >> BASE;
    }
    if (carry != 0) {
        res->ob_type[a->ob_size + offset] = carry;
    }
}

// Implement Karatsuba Algorithm
void multiply(struct BigNum* res, struct BigNum* a, struct BigNum* b) {
    for (unsigned long i = 0; i < res->ob_size; i++) {
        res->ob_type[i] = 0;
    }
    for (unsigned long i = 0; i < a->ob_size; i++) {
        multiplyAndAdd(res, a->ob_type[i], b, i);
    }
}

// Implement Karatsuba Algorithm
void square(struct BigNum* res, struct BigNum* a) {
    multiply(res, a, a);
}

void inPlaceMinusTwo(struct BigNum* a) {
    // assume no actual number less than 2
    if (a->ob_type[0] >= 2) {
        a->ob_type[0] -= 2;
    } else {
        a->ob_type[0] = MASK - 1 + a->ob_type[0];
        for (unsigned long i = 1; i < a->ob_size; i++) {
            if (a->ob_type[i] == 0) {
                a->ob_type[i] = MASK;
            } else {
                a->ob_type[i] -= 1;
                return;
            }
        }
        a->ob_type[a->ob_size-1] = tmpMask;
    }
}

void addWithMask(struct BigNum* a, struct BigNum* number) {

    unsigned long tmp;
    unsigned long carry = 0;
    for (long i = 0; i < primeSize - 1; i++) {
        tmp = a->ob_type[i] + number->ob_type[i] + carry;
        a->ob_type[i] = tmp & MASK;
        carry = tmp >> BASE;
    }
    tmp = a->ob_type[primeSize - 1] + (number->ob_type[primeSize - 1] & ((1 << primeLeftOver) - 1)) + carry;
    a->ob_type[primeSize - 1] = tmp & MASK;
    carry = tmp >> BASE;
}


void addConstWithMask(struct BigNum* res, unsigned long number) {
    unsigned long tmp = number + res->ob_type[0];
    res->ob_type[0] = tmp & MASK;
    unsigned long carry = tmp >> BASE;
    for (unsigned long i = 1; i < res->ob_size - 1 && carry != 0; i++) {

        tmp = res->ob_type[i] + carry;
        res->ob_type[i] = tmp & MASK;
        carry = tmp >> BASE;

    }

    tmp = (res->ob_type[res->ob_size - 1] & tmpMask) + carry;
    res->ob_type[res->ob_size - 1] = tmp & MASK;
    carry = tmp >> BASE;
}

void rightShiftNumberByDigits(struct BigNum* number, struct BigNum* a) {

    for (long j = 0; j < primeSize; j++) {
        a->ob_type[j] = (number->ob_type[j + primeSize - 1] >> primeLeftOver) | ((number->ob_type[j + primeSize] & tmpMask) << (BASE - primeLeftOver));
    }
}

void modByPrime(struct BigNum* number, struct BigNum* a) {
    rightShiftNumberByDigits(number, a);
    addWithMask(a, number);

    unsigned long value = a->ob_type[primeSize - 1] >> primeLeftOver;
    addConstWithMask(a, value);
}

void inPlaceCheckIfNumber(struct BigNum* a, struct BigNum* prime) {

    for (long j = 0; j < a->ob_size; j++) {
        if (a->ob_type[j] != prime->ob_type[j]) {
            return;
        }
    }
    for (long j = 0; j < a->ob_size; j++) {
        a->ob_type[j] = 0;
    }

}

void printIsZero(struct BigNum* a) {
    for (long j = 0; j < a->ob_size; j++) {
        if (a->ob_type[j] != 0) {
            printf("False\n");
            return;
        }
    }
    printf("True\n");
}

int main(int argc, char const *argv[])
{
    struct BigNum* prime = initializePrime();

    struct BigNum* a = initializeToFour(primeSize);
    struct BigNum* res = initializeWithSize(2 * primeSize);

    for (int k = 3; k <= p; k++) {
        square(res, a);
        modByPrime(res, a);
        inPlaceMinusTwo(a);
    }

    inPlaceCheckIfNumber(a, prime);
    printIsZero(a);
    return 0;
}
