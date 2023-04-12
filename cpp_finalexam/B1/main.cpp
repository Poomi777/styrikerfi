#include <iostream>
#include <string.h>

using namespace std;

/**
 * IT IS OK TO GET WARNING SUCH AS
 * warning: ISO C++ forbids converting
 * OR SIMILAR
 */

// Implement is_substring here

bool is_substring(const char* string1, const char* string2) {
    size_t len1 = strlen(string1);
    size_t len2 = strlen(string2);

    if (len1 > len2) {
        return false;
    }

    for (int i = 0; i <= len2 - len1; i++) {
        if (strncmp(string1, &string2[i], len1) == 0) {
            return true;
        }
    }

    return false;
}

int main(){
    cout << "is " << "brat" << " a substring of " << "algebra" << "? " << (is_substring("brat", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "bra" << " a substring of " << "algebra" << "? " << (is_substring("bra", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "bgeb" << " a substring of " << "algebra" << "? " << (is_substring("bgeb", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "geb" << " a substring of " << "algebra" << "? " << (is_substring("geb", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "gebb" << " a substring of " << "algebra" << "? " << (is_substring("gebb", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "algo" << " a substring of " << "algebra" << "? " << (is_substring("algo", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "alg" << " a substring of " << "algebra" << "? " << (is_substring("alg", "algebra") ? "YES" : "NO") << endl;
    cout << "is " << "falg" << " a substring of " << "algebra" << "? " << (is_substring("falg", "algebra") ? "YES" : "NO") << endl;
    return 0;
}
