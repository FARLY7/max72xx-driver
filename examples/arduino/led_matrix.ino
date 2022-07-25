#include "max72xx.h"


#define MAX72XX_DIN     8
#define MAX72XX_LOAD    9
#define MAX72XX_CLK     10

#define MAX72XX_MAX_DEVICE_COUNT    1

static max72xx_t max72xx;

/**
 * @brief MAX72xx library write handler
 */
int max72xx_write(max72xx_t *dev, uint8_t *buf, size_t len);
{
    /* Enable the MAX72xx's CS (LOAD) */
    digitalWrite(MAX72XX_LOAD, LOW);

    /* Shift out the bytes (SW implementation */
    for(int i = maxbytes ; i > 0 ; i--) {
        shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, spidata[i - 1]);
    }
    
    /* Disable the MAX72xx's CS (LOAD), thereby latching the data */
    digitalWrite(SPI_CS,HIGH);
    return 0;
}

void setup()
{
    pinMode(MAX72XX_DIN, OUTPUT);
    pinMode(MAX72XX_LOAD, OUTPUT);
    pinMode(MAX72XX_CLK, OUTPUT);

    max72xx_init(&max72xx, max72xx_write);

    /* Put all MAX72xx devices in normal operating mode */
    for(int i = 0 ; i < MAX72XX_MAX_DEVICE_COUNT ; i++) {
        max72xx_shutdown(&max72xx, i, false);
    }
    
    /* Set intensity (brightness) to half on all MAX72xx devices */
    for(int i = 0 ; i < MAX72XX_MAX_DEVICE_COUNT ; i++) {
        max72xx_set_intensity(&max72xx, i, 8);
    }

    /* Clear the display output on all MAX72xx devices */
    for(int i = 0 ; i < MAX72XX_MAX_DEVICE_COUNT ; i++) {
        max72xx_clear(&max72xx, i);
    }
}


void loop()
{
    /* Loop through all MAX72xx devices and sequentially blink every
       single LED */
    for(int i = 0 ; i < MAX72XX_MAX_DEVICE_COUNT ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            for(int k = 0 ; k < 8 ; k++)
            {
                max72xx_set_led(&dev, i, j, k, true);
                delay(100);
                max72xx_set_led(&dev, i, j, k, false);
            }
        }
    }
}