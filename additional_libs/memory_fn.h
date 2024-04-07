#ifndef __MEMORY_FN_
#define __MEMORY_FN_

/**
 * @brief Sets memory block [p] to desired value [d] of length [len]
 * 
 * @param p pointer to memory block
 * @param d desired value 0x0-0xff
 * @param len memory block length
 * @return void*
 */
void* memset(void* p, unsigned char d, int len) {
    for(int i = 0; i < len; i++) {
        ((int*)p)[i] = d;
    }

    return p;
}

/**
 * @brief Copy source memory block to destination memory block
 * 
 * @param dst destination memory block
 * @param src source memory block
 * @param len length of source memory block
 * @attention length should be equal or greater than destination memory block length
 * @return void* dst
 */
void* memcpy(void* dst, const void* src, int len) {
    for(int i = 0; i < len; i++) {
        ((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
    }

    return dst;
}

/**
 * @brief Move (but really copy) source memory block to destination memory block
 * 
 * @param dst destination memory block
 * @param src source memory block
 * @param len length of source memory block
 * @attention length should be equal or greater than destination memory block length
 * @return void* dst
 */
void* memmove(void* dst, const void* src, int len) {
    return memcpy(dst, src, len);
}

/**
 * @brief Compare 2 memory blocks
 * 
 * @param p1 memory block 1
 * @param p2 memory block 2
 * @param len length of shorter memory block
 * @return int 0 = equal blocks; -x = at x block 2 have grater value than block 1; x = opposite of -x
 */
int memcmp(const void* p1, const void* p2, int len) {
    int first_byte = 0;

    for(int i = 0; i < len; i++) {
        if(((unsigned char*)p1)[i] > ((unsigned char*)p2)[i]) {
            first_byte = i;
            break;
        }
        else if(((unsigned char*)p1)[i] < ((unsigned char*)p2)[i]) {
            first_byte = -i;
            break;
        }
    }

    return first_byte;
}

/**
 * @brief Search in memory block [p] of length [len] desired value [d] and return pointer to it, or NULL if no value was found
 * 
 * @param p searched memory block
 * @param d desired value to find
 * @param len length of memory block
 * @return void* pointer to found value, if value doesn`t exits in given block of memory NULL is returned
 */
void* memchr(void* p, unsigned char d, int len) {
    void* found = (void*)0;
    
    for(int i = 0; i < len; i++) {
        if(((unsigned char*)p)[i] == d) {
            found = ((unsigned int*)p) + i;
            break;
        }
    }

    return found;
}

#endif