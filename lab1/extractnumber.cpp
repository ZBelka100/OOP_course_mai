#include "extractnumber.h"

std::string extractnumber(std::string s) {
    std::string result = "";
    for (int i = 0; i < sizeof(s)/sizeof(s[0]); ++i) {
        if  (((s[i]) == '0') || ((s[i]) == '1') || ((s[i]) == '2') || ((s[i]) == '3') || ((s[i]) == '4') ||
             ((s[i]) == '5') || ((s[i]) == '6') || ((s[i]) == '7') || ((s[i]) == '8') || ((s[i]) == '9')) {
                result += s[i];
            }
    }
    return result;
}
