#include "console.h"

#include "dac.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"

bool buf_decode(uint8_t *buf, uint16_t size) {
    uint8_t ao[3] = {0};
    uint8_t ch_ao = 5;

    uint8_t voltage[20] = {0};
    double volt = 0;

    for (uint8_t x = 0; x < 3; x++) {
        ao[x] = *(buf + x);
    }
    if (strcmp(ao, "ao0") == 0) ch_ao = 0;
    if (strcmp(ao, "ao1") == 0) ch_ao = 1;
    if (strcmp(ao, "ao2") == 0) ch_ao = 2;
    if (ch_ao == 5) return 1;

    uint8_t x = 0;
    while (1) {
        if (*(buf + 4 + x) != '\n')
            voltage[x] = *(buf + 4 + x);
        else {
            voltage[x] = '\0';
            break;
        }
        x++;
    }

    volt = atof(voltage);
    if ((volt > 10) || (volt < 0)) return 1;
    
    dac_set_voltage(ch_ao, volt);

    return 0;
}