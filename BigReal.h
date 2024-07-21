#include<iostream>
using namespace std;

class BigReal{
private :
    char sign;
    string integer;
    string fraction;
public:
    BigReal();
    BigReal(std:: string real);
    BigReal(BigReal& other);
    BigReal& operator=(BigReal &other);
    BigReal operator +(BigReal &real);
    bool operator <(BigReal &real);
    bool operator ==(BigReal &real);
    BigReal addBigReals(BigReal &big, BigReal &otherBig);
    friend ostream& operator<< (ostream& out, BigReal& big);

};

