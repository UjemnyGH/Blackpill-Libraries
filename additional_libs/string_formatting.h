#ifndef __STRING_FORMATTING_
#define __STRING_FORMATTING_

unsigned int GetStrLen(const char* str) {
    unsigned int index = 0;

    while(str[index] != 0) {
        index++;
    }

    return index;
}

unsigned char ToUpper(unsigned char c) {
    if(c >= 'a' && c <= 'z') {
        return (c - 'a') + 'A';
    }

    return c;
}

#endif