#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void floatToCharArr(char *buf, float value);
void floatToCharArrEx(char *buf, float value, char lastChar);
void uint16ToCharArr(char *buf, uint16_t value);
void uint16ToCharArrEx(char *buf, uint16_t value, char lastChar);

#endif