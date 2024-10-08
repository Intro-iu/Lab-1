#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct PolynomialTerm {
    int coefficient;
    int exponent;
    struct PolynomialTerm *next;
} PolynomialTerm;


typedef struct Polynomial {
    PolynomialTerm *head;
} Polynomial;

Polynomial* initPolynomial() {
    Polynomial *poly = (Polynomial*) malloc(sizeof(Polynomial));
    poly->head = NULL;
    return poly;
}

void addTerm(Polynomial *poly, int coefficient, int exponent) {
    PolynomialTerm *newTerm = (PolynomialTerm*) malloc(sizeof(PolynomialTerm));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;

    if (!poly->head || poly->head->exponent < exponent) {
        newTerm->next = poly->head;
        poly->head = newTerm;
    } else {
        PolynomialTerm *current = poly->head;
        while (current->next && current->next->exponent > exponent) {
            current = current->next;
        }
        if (current->exponent == exponent) {
            current->coefficient += coefficient;
        } else {
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }
}

void printPolynomial(Polynomial *poly) {
    PolynomialTerm *current = poly->head;
    while (current) {
        if (current->coefficient > 0 && current != poly->head) {
            printf("+");
        }
        printf("%dx^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

Polynomial* addPolynomials(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *result = initPolynomial();
    PolynomialTerm *p1 = poly1->head;
    PolynomialTerm *p2 = poly2->head;

    while (p1 && p2) {
        if (p1->exponent > p2->exponent) {
            addTerm(result, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p1->exponent < p2->exponent) {
            addTerm(result, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else {
            addTerm(result, p1->coefficient + p2->coefficient, p1->exponent);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1) {
        addTerm(result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }
    while (p2) {
        addTerm(result, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }

    return result;
}

Polynomial* subtractPolynomials(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *result = initPolynomial();
    PolynomialTerm *p2 = poly2->head;

    while (p2) {
        addTerm(result, -p2->coefficient, p2->exponent);
        p2 = p2->next;
    }

    return addPolynomials(poly1, result);
}

Polynomial* multiplyPolynomials(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *result = initPolynomial();
    PolynomialTerm *p1 = poly1->head;
    PolynomialTerm *p2;

    while (p1) {
        p2 = poly2->head;
        while (p2) {
            int coefficient = p1->coefficient * p2->coefficient;
            int exponent = p1->exponent + p2->exponent;
            addTerm(result, coefficient, exponent);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return result;
}

int main() {
    Polynomial *poly1 = initPolynomial();
    Polynomial *poly2 = initPolynomial();
    
    addTerm(poly1, 3, 4);  
    addTerm(poly1, 2, 3);  
    addTerm(poly1, 1, 2);  

    addTerm(poly2, 5, 4);  
    addTerm(poly2, 1, 1);  
    addTerm(poly2, 2, 0);  

    printf("多项式1: ");
    printPolynomial(poly1);

    printf("多项式2: ");
    printPolynomial(poly2);

    Polynomial *sum = addPolynomials(poly1, poly2);
    printf("多项式加法结果: ");
    printPolynomial(sum);

    Polynomial *diff = subtractPolynomials(poly1, poly2);
    printf("多项式减法结果: ");
    printPolynomial(diff);
    
    Polynomial *prod = multiplyPolynomials(poly1, poly2);
    printf("多项式乘法结果: ");
    printPolynomial(prod);

    return 0;
}
