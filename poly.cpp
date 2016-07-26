// POLY.CPP
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
// - Power exponent is the index of the array
// - Contents of array is the coefficient
// - Assume input (operator>>) is always an integer
// ----------------------------------------------------------------------------

#include <iostream>
#include "poly.h"
using namespace std;

// ----------------------------------------------------------------------------
// default constructor
// Initialize polynomial with largest power of 'power' and coefficient set to
// 'coeff'. Nonnegative power only. If power is negative, create an array
// but do not set a coefficient.
Poly::Poly(const int coeff, const int power) {
	if (power >= 0) {
		size = power + 1;
		arrayPtr = new int[size];
		for (int i = 0; i < size; i++) { // initialize array
			arrayPtr[i] = 0;
		}
		arrayPtr[power] = coeff;
	}
	else {		// power is negative; create an array; set size to be zero
		arrayPtr = new int[1];
		arrayPtr[0] = 0;
		size = 1;
	}
}

// ----------------------------------------------------------------------------
// copy constructor
// Create an exact copy of the 'other' polynomial.
Poly::Poly(const Poly &other) {
	arrayPtr = new int[other.size];
	for (int i = 0; i < other.size; i++) {
		arrayPtr[i] = other.arrayPtr[i];
	}
	size = other.size;
}


// ----------------------------------------------------------------------------
// destructor
// Deallocate all memory.
Poly::~Poly() {
	delete [] arrayPtr;
	arrayPtr = NULL;
	size = 0;
}

// ----------------------------------------------------------------------------
// getCoeff
// Get one term's coefficient.
// Return a coefficient (or 0, if 'power' has a non-existent term).
int Poly::getCoeff(const int power) const {
	if (arrayPtr == NULL || power < 0 || power >= size) return 0;
	return arrayPtr[power];
}

// ----------------------------------------------------------------------------
// setCoeff
// Set one coefficient 'coeff' at 'power' exponent.
void Poly::setCoeff(const int coeff, const int power) {
	if (size <= power) {			// resize to bigger array if needed
		int newSize = power + 1;
		int* tempArray = new int[newSize];
		// copy the old array contents
		for (int i = 0; i < size; i++) {
			tempArray[i] = arrayPtr[i];
		}
		// initialize the rest of array to be 0
		for (int i = size; i < newSize; i++) { 
			tempArray[i] = 0;
		}
		// change array pointer to point to tempArray
		delete [] arrayPtr;
		arrayPtr = tempArray;
		tempArray = NULL;
		size = newSize;
	}
	arrayPtr[power] = coeff; 		// set coefficient at 'power' index
}

// ----------------------------------------------------------------------------
// operator+
// Addition operator. Add two polynomials.
// Return a Poly of the two added polynomials.
Poly Poly::operator+(const Poly& other) const {
	int maxSize = (size < other.size ? other.size : size);
	Poly sum(0, maxSize - 1);
	for (int i = 0; i < maxSize; i++) {
		if (i < size && i < other.size) {	// both Poly array size are equal
			sum.arrayPtr[i] = arrayPtr[i] + other.arrayPtr[i];
		}
		else if (i < size) {				// this Poly array size is >
			sum.arrayPtr[i] = arrayPtr[i];
		} 
		else {								// other Poly array size is >
			sum.arrayPtr[i] = other.arrayPtr[i];
		}
	}
	return sum;
}

// ----------------------------------------------------------------------------
// operator-
// Subtraction operator. Subtract two polynomials. (*this poly - other poly)
// Return a Poly of the two subtracted polynomials.
Poly Poly::operator-(const Poly& other) const {
	int maxSize = (size < other.size ? other.size : size);
	Poly diff(0, maxSize - 1);
	for (int i = 0; i < maxSize; i++) {
		if (i < size && i < other.size) {	// both Poly array size are equal
			diff.arrayPtr[i] = arrayPtr[i] - other.arrayPtr[i];
		}
		else if (i < size) {				// this Poly array size is >
			diff.arrayPtr[i] = arrayPtr[i];
		}
		else {								// other Poly array size is >
			diff.arrayPtr[i] = 0 - other.arrayPtr[i];
		}
	}
	return diff;
}

// ----------------------------------------------------------------------------
// operator*
// Multiplication operator. Multiply two polynomials.
// Return a Poly of the two multiplied polynomials.
Poly Poly::operator*(const Poly& other) const {
	int maxSize = size + other.size;
	Poly multiply(0, maxSize - 2);
	int coeff = 0;
	for (int i = 0; i < size; i++) {	
		if (arrayPtr[i] != 0) {
			for (int j = 0; j < other.size; j++) {
				if (other.arrayPtr[j] != 0) {
					coeff = arrayPtr[i] * other.arrayPtr[j];
					multiply.arrayPtr[i + j] += coeff;
				}
			}
		}
	}
	return multiply;
}

// ----------------------------------------------------------------------------
// operator==
// Equality operator. Check if this poly is equal to the other poly. 
// Return true if both poly are equal. False if both poly are not equal.
bool Poly::operator==(const Poly& other) const {
	if (this == &other) // check if address is the same
		return true;
	for (int i = 0; i < size; i++) { 
		// check other Poly if other.size is within the scope of size
		if (size <= other.size) {
			if (arrayPtr[i] != other.arrayPtr[i])
				return false;
		} 
		else {	// this array is >. return false if values are != 0
			if (arrayPtr[i] != 0) 
				return false;
		}
	}
	// other Poly array is larger
	// check to make sure the rest of the term is zero
	if (size < other.size) {
		for (int i = size; i < other.size; i++) {
			if (other.arrayPtr[i] != 0) 
				return false;
		}
	}
	return true;
}

// ----------------------------------------------------------------------------
// operator!=
// Inequality operator. Check if this poly is not equal to the other poly. 
// Return true if both poly are not equal. False if both poly are equal.
bool Poly::operator!=(const Poly& other) const {
	return !(*this == other);
}

// ----------------------------------------------------------------------------
// operator+=
// Addition assignment operator. Current object = current object + parameter.
// Return this poly with this array pointer to the two added polynomials.
Poly& Poly::operator+=(const Poly& other) {
	int maxSize = (size < other.size ? other.size : size);
	int* tempArray = new int[maxSize];
	for (int i = 0; i < maxSize; i++) {
		if (i < size && i < other.size) {
			tempArray[i] = arrayPtr[i] + other.arrayPtr[i];
		}
		else if (i < size) {
			tempArray[i] = arrayPtr[i];
		} 
		else {
			tempArray[i] = other.arrayPtr[i];
		}
	}
	delete [] arrayPtr;
	size = maxSize;
	arrayPtr = tempArray;
	tempArray = NULL;
	return *this;
}

// ----------------------------------------------------------------------------
// operator-=
// Subtraction assignment operator. 
// Current object = current object - parameter.
// Return this poly with this array pointer to the two subtracted polynomials.
Poly& Poly::operator-=(const Poly& other) {
	int maxSize = (size < other.size ? other.size : size);
	int* tempArray = new int[maxSize];
	for (int i = 0; i < maxSize; i++) {
		if (i < size && i < other.size) {
			tempArray[i] = arrayPtr[i] - other.arrayPtr[i];
		}
		else if (i < size) {
			tempArray[i] = arrayPtr[i];
		}
		else {
			tempArray[i] = 0 - other.arrayPtr[i];
		}
	}
	delete [] arrayPtr;
	size = maxSize;
	arrayPtr = tempArray;
	tempArray= NULL;
	return *this;
}

// ----------------------------------------------------------------------------
// operator*=
// Multiplication assignment operator.
// Current object = (current object) * (parameter).
// Return this poly with this array pointer to the two multiplied polynomials.
Poly& Poly::operator*=(const Poly& other) {
	int maxSize = size + other.size;
	int* tempArray = new int[maxSize];
	int coeff = 0;

	// initialize all values in tempArray to be zero
	for (int i = 0; i < maxSize; i++)
		tempArray[i] = 0;

	for (int i = 0; i < size; i++) {
		if (arrayPtr[i] != 0) {
			for (int j = 0; j < other.size; j++) {
				if (other.arrayPtr[j] != 0) {
					coeff = arrayPtr[i] * other.arrayPtr[j];
					tempArray[i + j] += coeff;
				}
			}
		}
	}
	delete [] arrayPtr;
	size = maxSize;
	arrayPtr = tempArray;
	tempArray = NULL;
	return *this;
}

// ----------------------------------------------------------------------------
// operator=
// Assignment operator. Assign other poly to this polynomial.
// Return this poly with this array set to be the same as the 
// other array contents.
Poly& Poly::operator=(const Poly& other) {
	if (&other != this) {		// check if address is the same
		// cannot make an array smaller (inefficient)
		// check size
		if (size < other.size) {	// size is smaller. make array larger
			delete [] arrayPtr;
			size = other.size;
			arrayPtr = new int[size];
		}
		else // size > other.size
		{
			for (int i = other.size; i < size; i++)
				arrayPtr[i] = 0;
		}
		for (int i = 0; i < other.size; i++) 
			arrayPtr[i] = other.arrayPtr[i];
	}
	return *this;
}

// ----------------------------------------------------------------------------
// operator>>
// Overload input operator for class Poly. Input values for entire array.
// Maximum size of array is the largest power (+1). Non-negative powers only.
// Terminates if input is -1 -1. Assume input are integers. Return input.
istream& operator>>(istream &input, Poly &other) {
	int coeff;
	int power;
	input >> coeff >> power;
	while (coeff != -1 && power != -1) {
		// add to array if power is a nonnegative number
		if (power >= 0) {
			other.setCoeff(coeff, power);
		}
		input >> coeff >> power;
	}
	return input;
}

// ----------------------------------------------------------------------------
// operator<<
// Overload output operator for class Poly. Output values for array with a 
// coefficient, except if all term is zero then print out just " 0".
// Use lowercase x. A nonzero coefficient and its sign are always displayed
// (exactly one blank before every sign). A power of 1 is not displayed
// and x is not shown at all for a power of 0. Return output.
ostream& operator<<(ostream &output, const Poly &other) {
	bool isAllZero = true;	// check if all term is 0
	for (int i = other.size - 1; i >= 0; i--) {
		int coeff = other.arrayPtr[i];
		if (coeff != 0) {
			isAllZero = false; 			// FALSE; all term is not 0
			output << " "; 				// output one space before every sign
			if (coeff > 0)				// output positive sign
				output << "+";
			output << coeff;			// output coefficient
			if (i > 0)				// output 'x' for all power (besides 0)
				output << "x";
			if (i > 1)				// output power for all power > 1
				output << "^" << i;
		}
	}
	if (isAllZero) // all term is 0
		output << " 0";
	return output;
}
// ----------------------------------------------------------------------------