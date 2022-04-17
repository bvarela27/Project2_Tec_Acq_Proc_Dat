

// C substring function definition
void substring(char* s, char* sub, int start, int len) {
    int counter = 0;

    while (counter < len) {
        sub[counter] = s[start+counter];
        counter++;
    }
    sub[counter] = '\0';
}