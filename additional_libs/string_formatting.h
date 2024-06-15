#ifndef __STRING_FORMATTING_
#define __STRING_FORMATTING_

unsigned int GetStrLen(const char* str) {
    unsigned int index = 0;

    while(str[index] != 0) {
        index++;
    }

    return index;
}

char gFormattedString[10]; 

const char* IntToStr(unsigned int i) {
    gFormattedString[0] = 0;
    gFormattedString[1] = 0;
    gFormattedString[2] = (i & 0xf0000000) >> 28;
    gFormattedString[3] = (i & 0xf000000) >> 24;
    gFormattedString[4] = (i & 0xf00000) >> 20;
    gFormattedString[5] = (i & 0xf0000) >> 16;
    gFormattedString[6] = (i & 0xf000) >> 12;
    gFormattedString[7] = (i & 0xf00) >> 8;
    gFormattedString[8] = (i & 0xf0) >> 4;
    gFormattedString[9] = i & 0xf;

    for(int i = 0; i < 10; i++) {
        if(gFormattedString[9 - i] >= 10 && i < 9) {
            gFormattedString[8 - i] += 1;
            gFormattedString[9 - i] -= 10;
        }

        gFormattedString[i] += '0';
        
        /*if(gFormattedString[i] < 10) {
            gFormattedString[i] += '0';
        }
        else {
            gFormattedString[i] += 'A' - 10;
        }*/
    }

    return gFormattedString;
}

unsigned char ToUpper(unsigned char c) {
    if(c >= 'a' && c <= 'z') {
        return (c - 'a') + 'A';
    }

    return c;
}

#endif