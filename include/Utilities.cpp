#include "Utilities.h"
using namespace std;

string TrimString(const string& toTrim) {
    string trimmed = toTrim;
    trimmed.erase(trimmed.begin(), find_if(trimmed.begin(), trimmed.end(),
                                           [](char c) { return !isspace(c); }));
    trimmed.erase(find_if(trimmed.rbegin(), trimmed.rend(),
                          [](char c) { return !isspace(c); }).base(), trimmed.end());
    return trimmed;
}