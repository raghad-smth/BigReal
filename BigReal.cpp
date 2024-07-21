// File: BigReal.cpp
// Purpose: Being able to store and perform operations on  large numbers that exceed the capacity of int and float data type
// Author: Raghad Mohammed Suliman
// Section: S12
// ID: 20220704
// TA: Samar Sabry
// Date: 29 Oct  2023


#include <iostream>
#include <string>
#include <regex>
#include "BigReal.h"
using namespace std;


//Default constructor
 BigReal:: BigReal(){
        sign = '+';
        integer = "0";
          fraction = ".0";
    }

// Copy constructor
BigReal::  BigReal(BigReal& other){
        sign = other.sign;
        integer = other.integer;
        fraction = other.fraction;
    }

 //constructor that take the BigReal as a string and check if it is  valid real number, and if not it sets it to "+0.0"
 BigReal:: BigReal(string real) {
        sign = '+';
        // using regex to creat a rule that needs to be true in order for a match to happen
        regex r("[+-]?[0-9]*.?[0-9]*");
        if (regex_match(real, r)) {
            if (real[0] == '-') {
                sign = '-';
            }
            // erasing the sign part from real if it was there so integer can get all the intger part form real starting from index 0
            if (real[0] == '+' || real[0] == '-') {
                real.erase(0, 1);
            }
            // looping till we reach a decimal point if found : else we keep looping until the end of the string
            for (int i = 0; i < real.size() && real[i] != '.'; i++) {
                integer += real[i];
            }
            // incase the intger part was == 0 and the user didn't insert it
            if (integer == "") {
                integer = '0';
            }
            // If real has a decimal point only then we can start storing the fraction part starting from there
            if (real.find('.') != std::string::npos) {
                for (int j = 0; j < real.size(); j++) {
                    fraction += real[j + real.find('.')];
                }
            }

        }
            //setting real to "+0.0" if it was not valid
        else {
            sign = '+';
            integer = '0';
            fraction = ".0";

        }
    }

// Overloading the operator= to work with Big real numbers
  BigReal& BigReal::operator=(BigReal &other){   //  b = c then am copying from c to b so b
       sign = other.sign;
       integer = other.integer;
       fraction = other.fraction;
        return *this;
    }

 //Overloading the oprator== to compare two big reals
bool BigReal::operator== (BigReal &other){
        return sign == other.sign && integer == other.integer && fraction == other.fraction;
    }

 // Overloading the oprator< to compare two big reals
 bool BigReal::operator< (BigReal &real){
        // comp1 represent Big Real before the <
        // com2 represent Big Real after the >
        string comp1="", comp2="";
        //Setting both numbers to the same size

        comp1.insert(0,this->integer);          // inserting the integer part
        comp2.insert(0,real.integer);
        if (this->integer.size() < real.integer.size()){  // Filling the smaller string in size with '0' to be equal to the larger
            comp1.insert(0, this->integer.size() - real.integer.size(), '0');
        }
        else if(real.integer.size() < this->integer.size()  ){
            comp2.insert(0, this->integer.size() - real.integer.size(), '0');
        }
        comp1+=this->fraction;                           // inserting the fraction part
        comp2+=real.fraction;
        if (this->fraction.size() < real.fraction.size()){ // Filling the smaller string in size with '0' to be equal to the larger
            comp1.insert(comp1.size()-1, this->fraction.size() - real.fraction.size(), '0');
        }
        else if(real.fraction.size() < this->fraction.size()  ){
            comp2.insert(comp2.size()-1, this->fraction.size() - real.fraction.size(), '0');
        }

        // if the number that comes after the < is postive and the one before it is negtive then the one before it is smaller : retrun true
        if(sign == '-' && real.sign == '+'){
            return true;
        }
        // if the number that comes after the < is negtive and the one before it is positve then the one before it is larger : retrun false
        else if(sign == '+' && real.sign == '-'){
            return false;
        }
        // comparing the two strings that now in the same size so that the first char is compared with it's equvelint char in the other big real
        else if(sign == '+' && real.sign == '+'){
            return comp1 < comp2;
        }
        else{
            return comp1 > comp2;
        }

    }


// Function to add two big reals
 BigReal BigReal:: addBigReals(BigReal &big, BigReal &otherBig) {
        if (big.sign == otherBig.sign) {
            BigReal finalRes;
            int temp = 0, carry = 0;
            string fracRes, intRes;
            //if the two reals don't have the same fraction size store the surples part in result right away
            if (big.fraction.size() > otherBig.fraction.size()) {
                fracRes = big.fraction.substr(otherBig.fraction.size() - 1, big.fraction.size() - 1);
                big.fraction.erase(otherBig.fraction.size() - 1,
                                   big.fraction.size() - 1);//erase to make the fractions equals
            } else {
                fracRes = otherBig.fraction.substr(big.fraction.size() - 1, otherBig.fraction.size() - 1);
                otherBig.fraction.erase(big.fraction.size() - 1, otherBig.fraction.size() - 1);
            }


            for (int i = big.fraction.size() - 1; i > 0; i--) {
                temp = carry + big.fraction[i] - '0' + otherBig.fraction[i] - '0';
                if (temp > 9) {
                    carry = 1;
                    temp -= 10;
                } else {
                    carry = 0;
                }
                fracRes.insert(0, to_string(temp));
            }
            fracRes.insert(0, ".");


            temp = 0;
            if (big.integer.size() > otherBig.integer.size()) {
                otherBig.integer.insert(0, big.integer.size() - otherBig.integer.size(), '0');
            } else {
                big.integer.insert(0, otherBig.integer.size() - big.integer.size(), '0');
            }

            for (int i = big.integer.size() - 1; i >= 0; i--) {
                temp = carry + big.integer[i] - '0' + otherBig.integer[i] - '0';
                if (temp > 9) {
                    carry = 1;
                    temp -= 10;
                } else {
                    carry = 0;
                }
                intRes.insert(0, to_string(temp));
            }
         // Setting the finalres that will get returned
            finalRes.sign = big.sign;
            finalRes.integer= intRes ;
            finalRes.fraction =  fracRes;
            return finalRes;

        } else {
            cout << "This program doesn't handel addition of big real with different signs " << endl;
        }

    }

// overloading the '+' to add Big reals by calling the function addBigReals
 BigReal BigReal :: operator+(BigReal& big){
        return addBigReals(*this, big);
    }

// Overloading the << to print Big real into the console
ostream& operator<<(ostream &out, BigReal &big) {
    out << big.sign << big.integer << big.fraction;
    return out;
}



