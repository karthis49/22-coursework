/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA6
 *  * * BigInteger.cpp 
 *  * * BigInteger ADT 
 *  * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

#define BASE 1000000000
#define POWER 9


    // Class Constructors & Destructors ----------------------------------------

    // BigInteger()
    // Constructor that creates a new BigInteger in the zero state: 
    // signum=0, digits=().
    BigInteger::BigInteger() {
        signum = 0;
        digits.clear();
    }

    // BigInteger()
    // Constructor that creates a new BigInteger from the string s.
    // Pre: s is a non-empty string consisting of (at least one) base 10 digit
    // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
    BigInteger::BigInteger(std::string s) {
        if (s.substr(1, 0) == "-") {
            signum = -1;
            s.erase(0, 1);
        }
        else if (s.substr(1, 0) == "+") {
            signum = 1;
            s.erase(0, 1);
        }
        else {
            signum = 1;
        }
        std::size_t found = s.find_first_not_of("0123456789");
        if (found == std::string::npos) {
            throw std::invalid_argument("BigInt(std:: string s): invalid input");
        }
        digits.moveBack();
        long digit;
        int str_pos = s.length();
        int val = s.length() % POWER;
        int count = 0;
        int str_curr = s.length();
        while (str_pos > 0) {
            if (count == 0) {
                str_curr -= val;
                digit = stol(s.substr(val, str_curr), nullptr, BASE);
                digits.insertBefore(digit);
                digits.movePrev();
                str_pos -= val;
                count += 1;
            }
            str_curr -= POWER;
            digit = stol(s.substr(val, str_curr), nullptr, BASE);
            digits.insertBefore(digit);
            digits.movePrev();
            str_pos -= POWER;
            
        }
        //signum = 1;
        //long val = stol(s.substr(2,2), nullptr, 10);
        //long val = 2;
        //digits.insertBefore(val);
        
    }

    // BigInteger()
    // Constructor that creates a copy of N.
    BigInteger::BigInteger(const BigInteger& N) {
        signum = N.signum;
        digits = N.digits;
    }

    // Optional Destuctor
    // ~BigInteger()
    // ~BigInteger();


    // Access functions --------------------------------------------------------

    // sign()
    // Returns -1, 1 or 0 according to whether this->BigInteger is positive, 
    // negative or 0, respectively.
    int BigInteger::sign() const {
        return signum;
    }

    // compare()
    // Returns -1, 1 or 0 according to whether this->BigInteger is less than N,
    // greater than N or equal to N, respectively.
    int BigInteger::compare(const BigInteger& N) const {
        //if (this->signum < N.signum) {
        //    return -1;
        //}
        //if (this->signum > N.signum) {
        //    return 1;
        //}
        //if (this->digits.length() < N.digits.length()) {
        //    return -1;
        //}
        //if (this->digits.length() > N.digits.length()) {
        //    return 1;
        //}
        //this->digits.moveFront();
        //N.digits.moveFront();
        //long this_val, N_val;
        //while (this->digits.position() != this->digits.length()) {
        //    this_val = this->digits.moveNext();
        //    N_val = N.digits.moveNext();
        //    if (this_val > N_val) {
        //        return 1;
        //    }
        //    if (this_val < N_val) {
        //        return -1;
        //    }
        //}
        //
        int sign = N.signum;
        return sign;
    }

    // Helper functions -------------------------------------------------
   
    // negateList()
    // Changes the sign of each integer in List L. Used by sub().
    void negateList(List& L) {
        for(int i = 0; i < L.length(); i++) {
            long val = L.peekNext() * -1;
            L.setAfter(val);
        }
    }

    // sumList()
    // Overwrites the state of S with A + sgn*B (considered as vectors).
    // Used by both sum() and sub().
    void sumList(List& S, List A, List B, int sgn) {
        A.moveFront();
        B.moveFront();
        int i;
        long val;
        if (sgn == 1) {
            if (A.length() > B.length()) {
                for(i = 0; i < B.length(); i++) {
                    val = A.peekNext() + B.peekNext();
                    S.insertBefore(val);
                }
                for(i = B.length(); i < A.length(); i++) {
                    S.insertBefore(A.peekNext());
                }
            }
            else if (A.length() < B.length()) {
                for(i = 0; i < A.length(); i++) {
                    val = A.peekNext() + B.peekNext();
                    S.insertBefore(val);
                }
                for(i = A.length(); i < B.length(); i++) {
                    S.insertBefore(B.peekNext());
                }
            }
        }
        else if (sgn == -1) {
            if (A.length() > B.length()) {
                for(i = 0; i < B.length(); i++) {
                    val = A.peekNext() - B.peekNext();
                    S.insertBefore(val);
                }
                for(i = B.length(); i < A.length(); i++) {
                    S.insertBefore(A.peekNext());
                }
            }
             else if (A.length() < B.length()) {
                for(i = 0; i < A.length(); i++) {
                    val = A.peekNext() - B.peekNext();
                    S.insertBefore(val);
                }
                for(i = A.length(); i < B.length(); i++) {
                    S.insertBefore(B.peekNext());
                }
            }
        }   
    }

    // normalizeList()
    // Performs carries from right to left (least to most significant
    // digits), then returns the sign of the resulting integer. Used
    // by add(), sub() and mult().
    int normalizeList(List& L) {
        L.moveFront();
        return 1;
    }

    // shiftList()
    // Prepends p zero digits to L, multiplying L by base^p. Used by mult().
    void shiftList(List& L, int p) {
        L.moveBack();
        for(int i = 0; i < p; i++) {
            L.insertBefore(0);
        }
    }

    // scalarMultList()
    // Multiplies L (considered as a vector) by m. Used by mult().
    void scalarMultList(List& L, ListElement m) {
        for(int i = 0; i < L.length(); i++) {
            long val = L.peekNext() * m;
            L.setAfter(val);
        }
    }


    // Manipulation procedures -------------------------------------------------

    // makeZero()
    // Re-sets this->BigInteger to the zero state.
    void BigInteger::makeZero() {
        signum = 0;
        digits.clear();
    }

    // negate()
    // If this->BigInteger is zero, does nothing, otherwise reverses the sign of 
    // this->BigInteger positive <--> negative. 
    void BigInteger::negate() {
        if (signum == 1) {
            signum = -1;
        }
        if (signum == -1) {
            signum = 1;
        }
    }


    // BigInteger Arithmetic operations ----------------------------------------

    // add()
    // Returns a BigInteger representing the sum of this->and N.
    BigInteger BigInteger::add(const BigInteger& N) const {
        BigInteger S;
        sumList(S.digits, this->digits, N.digits, 1);
        return S;
    }

    // sub()
    // Returns a BigInteger representing the difference of this->and N.
    BigInteger BigInteger::sub(const BigInteger& N) const {
        BigInteger S;
        sumList(S.digits, this->digits, N.digits, -1);
        return S;

    }

    // mult()
    // Returns a BigInteger representing the product of this->and N. 
    BigInteger BigInteger::mult(const BigInteger& N) const {
        BigInteger S; 
        S.signum = N.signum;
        return S;
    }


    // Other Functions ---------------------------------------------------------

    // to_string()
    // Returns a string representation of this->BigInteger consisting of its
    // base 10 digits. If this->BigInteger is negative, the returned string 
    // will begin with a negative sign '-'. If this->BigInteger is zero, the
    // returned string will consist of the character '0' only.
    std::string BigInteger::to_string() {
        long x = 0;
        std::string s = "";

        if(signum == -1) {
            s.append("-");
        }

        if(signum == 0) {
            s.append("0");
        }
        else {
            digits.moveBack();
            while (digits.position() > 1) {
                x = digits.movePrev();
                s.append(std::to_string(x));
            }
        }
        return s;
    }

    // Overriden Operators -----------------------------------------------------
   
    // operator<<()
    // Inserts string representation of N into stream.
    std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
        return stream << N.BigInteger::to_string();
    }

    // operator==()
    // Returns true if and only if A equals B. 
    bool operator==( const BigInteger& A, const BigInteger& B ) {
        if (A.compare(B) == 0) {
            return true;
        }
        return false;
    }

    // operator<()
    // Returns true if and only if A is less than B. 
    bool operator<( const BigInteger& A, const BigInteger& B ) {
        if (A.compare(B) < 0) {
            return true;
        }
        return false;
    }

    // operator<=()
    // Returns true if and only if A is less than or equal to B. 
    bool operator<=( const BigInteger& A, const BigInteger& B ) {
        if (A.compare(B) < 0 || A.compare(B) == 0) {
            return true;
        }
        return false;
    }

    // operator>()
    // Returns true if and only if A is greater than B. 
    bool operator>( const BigInteger& A, const BigInteger& B ) {
        if (A.compare(B) > 0) {
            return true;
        }
        return false;
    }

    // operator>=()
    // Returns true if and only if A is greater than or equal to B. 
    bool operator>=( const BigInteger& A, const BigInteger& B ) {
        if (A.compare(B) > 0 || A.compare(B) == 0) {
            return true;
        }
        return false;
    }

    // operator+()
    // Returns the sum A+B. 
    BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
        return A.add(B);
    }

    // operator+=()
    // Overwrites A with the sum A+B. 
    BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
        //A = A.add(B);
        A.signum = B.signum;
        return A;
    }

    // operator-()
    // Returns the difference A-B. 
    BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
        return A.sub(B);
    }

    // operator-=()
    // Overwrites A with the difference A-B. 
    BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
        //A = A.sub(B);
        A.signum = B.signum;
        return A;
    }

    // operator*()
    // Returns the product A*B. 
    BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
        return A.mult(B);
    }

    // operator*=()
    // Overwrites A with the product A*B. 
    BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
         //A = A.mult(B);
         A.signum = B.signum;
        return A;
    }

