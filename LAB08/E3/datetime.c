#include "datetime.h"

int KEYcmp(Key k1, Key k2){
    if (k1>k2)
        return 1;
    else if (k1==k2)
        return 0;
    return -1;
}

Key KEYget(datetime val) {
    return val.year*10000 + val.month*100 + val.day;
}