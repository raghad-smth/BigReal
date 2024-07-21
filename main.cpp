#include "BigReal.h"

using namespace std;
int main() {

    //Testing the constructor to take valid real numbers and set the not real number to "0.0"
    BigReal b0("+.777777777777777777777777777777911");
    BigReal b1("-55.888888888888888888888888888888888888888888888888888888888");
    BigReal b2("++++0.239990");
    BigReal b3("undun.2399902");
    BigReal b4("-084.99x");
    cout << b0 << endl;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;

    //Testing the + and << operator
    BigReal b5 = b0+b4;
    cout << b5 << endl;

    //Testing the < operator
    if (b1< b3){
        cout << "b1 is less than b3" << endl;
    }
    else {
        cout << "b1 is greater than b3" << endl;
    }

    // Testing the = operator && ==
    BigReal b6("1.684999999999999999999999999999");
    BigReal b7 = b6;
    cout << b6 << endl;
    if (b6 == b7){
        cout << "Ecual" << endl;
    }
    else {
        cout << "Not ecual" << endl;
    }


    return 0;
}