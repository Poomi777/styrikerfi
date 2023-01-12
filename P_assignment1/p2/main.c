#include "testlib.h"
#include "parseint.h"

int main()
{
    test_start("parseint.c");

    test_equals_int(parseDecimalChar('0'), 0);
    test_equals_int(parseInt("010"), 8);
    test_equals_int(parseInt("10"), 10);
    test_equals_int(parseInt("?"), -1);
    test_equals_int(parseInt("8"), 8);
    test_equals_int(parseInt("6"), 6);

    return test_end();
}
