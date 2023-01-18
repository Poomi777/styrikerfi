#include <stdio.h>
void update value(char *val) {
    val = "YES";
}
int main() {
    char *answer = "NO";
    update value(answer);
    printf("My answer is %s\n", answer);
}