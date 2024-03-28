#ifndef DATETIME_H
#define DATETIME_H

typedef int Key;

typedef struct{
    int year, month, day;
} datetime;
int KEYcmp(Key k1, Key k2);
Key KEYget(datetime val);

#endif