// POLY.H
// ----------------------------------------------------------------------------
// Bonnie Vo
// Fall 2014
// CSS343 Programming Assignment #1
// Professor Min Chen
// ----------------------------------------------------------------------------
// Polynomial class called Poly that represents a polynomial as an
// an array of terms. The array element subscript is the exponent 
// and the content of the element is the coefficient value. 
// Coefficient may be changed later. May make array larger but not 
// smaller (inefficient).
// 
// Implemntation and assumptions:
// - Polynomial of nonnegative exponents
// - Power (exponent) is the index of the array
// - Contents of array is the coefficient
// - Assume input (operator>>) is always an integer
// ----------------------------------------------------------------------------

#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;

class Poly {
	// operator << (output)
	friend ostream& operator<<(ostream&, const Poly &);
	// operator >> (input)
	friend istream& operator>>(istream &, Poly &);

// function prototypes
public:
	Poly(const int = 0, const int = 0);	// default constructor
	Poly(const Poly &);					// copy constructor
	~Poly();							// destructor

	int getCoeff(const int) const;			// get one term's coefficient
	void setCoeff(const int, const int); 	// set one coefficient
		
	// OVERLOAD OPERATORS:
	// arithmetic operators
	Poly operator+(const Poly &) const;			// add 2 polynomials
	Poly operator-(const Poly &) const;			// subtract 2 polynomials
	Poly operator*(const Poly &) const;			// multiply 2 polynomials

	// boolean comparison operators
	bool operator==(const Poly&) const;			// is object ==
	bool operator!=(const Poly&) const;			// is object !=

	// assignment operators
	Poly& operator+=(const Poly &); 	// addition assignment operator
	Poly& operator-=(const Poly &);		// subtraction assignment operator
	Poly& operator*=(const Poly &);		// multiplication assignment operator
	Poly& operator=(const Poly &);		// assignment operator


private:
	int* arrayPtr;			// pointer to first element of array
	int size;				// size of the array
};
#endif