#include "max72xx.h"

#include <string.h>

/* MAX72XX Registers */
#define MAX72XX_REG_ADDR_NOOP               0x00
#define MAX72XX_REG_ADDR_DIGIT_0            0x01
#define MAX72XX_REG_ADDR_DIGIT_1            0x02
#define MAX72XX_REG_ADDR_DIGIT_2            0x03
#define MAX72XX_REG_ADDR_DIGIT_3            0x04
#define MAX72XX_REG_ADDR_DIGIT_4            0x05
#define MAX72XX_REG_ADDR_DIGIT_5            0x06
#define MAX72XX_REG_ADDR_DIGIT_6            0x07
#define MAX72XX_REG_ADDR_DIGIT_7            0x08
#define MAX72XX_REG_ADDR_DECODE_MODE        0x09
#define MAX72XX_REG_ADDR_INTENSITY          0x0A
#define MAX72XX_REG_ADDR_SCAN_LIMIT         0x0B
#define MAX72XX_REG_ADDR_SHUTDOWN           0x0C
#define MAX72XX_REG_ADDR_DISPLAY_TEST       0x0F
#define MAX72XX_REG_MAX_ADDRESS             0x0F

#define MAX72XX_MAX_X_COORD         7
#define MAX72XX_MAX_Y_COORD         7
#define MAX72XX_MAX_COLUMN          MAX72XX_MAX_X_COORD
#define MAX72XX_MAX_ROW             MAX72XX_MAX_Y_COORD

#define MAX72XX_MAX_INTENSITY       15


/**
 * @brief Write to MAX72XX register
 * 
 * @param dev 
 * @param addr 
 * @param val 
 * @return int 
 */
static int max72xx_write_reg(max72xx_t *dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t val)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }

    if(reg_addr >= MAX72XX_REG_MAX_ADDRESS) {
        /* Device register address out of bounds */
        return 1;
    }

    /**
     * SPI data buffer.
     * Each device requires two bytes, one of the register address,
     * and another for the register value.
     */
    uint8_t buf[MAX72XX_MAX_DEVICE_COUNT*2];

    memset(buf, 0, sizeof(buf));

    /* Calculate buffer address for device in chain */
    uint8_t offset = dev_addr * 2;
    
    buf[offset] = reg_addr;
    buf[offset+1] = val;

    return dev->write(dev, buf, sizeof(buf));
}

/**
 * @brief Initialise MAX72XX device(s)
 * 
 * @param dev 
 * @param api 
 * @return int 
 */
int max72xx_init(max72xx_t *dev, max72xx_api_t *api)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    memset(dev->frame, 0, sizeof(dev->frame));
}

/**
 * @brief Change operation mode (SHUTDOWN or NORMAL)
 * 
 * @param dev 
 * @param status If true, device goes into power-down mode. Set to
 *               false for normal operation. 
 * @return int
 */
int max72xx_shutdown(max72xx_t *dev, uint8_t addr, bool status)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }

    return max72xx_write_reg(dev, i, MAX72XX_REG_ADDR_SHUTDOWN, !status);
}

/**
 * @brief Set the brightness intensity.
 * 
 * @param intensity Between 0-15
 * @return int 
 */
int max72xx_set_intensity(max72xx_t *dev, uint8_t addr, int intensity)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }

    if(intensity > MAX72XX_MAX_INTENSITY) {
        return 1;
    }

    return max72xx_write_reg(dev, i, MAX72XX_REG_ADDR_INTENSITY, intensity);
}

/**
 * @brief Turn on display test
 * 
 * @param on Turn display test on or off 
 * @return int 
 */
int max72xx_display_test(max72xx_t *dev, uint8_t addr, bool on)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }


    return max72xx_write_reg(dev, i, MAX72XX_REG_ADDR_DISPLAY_TEST, on);
}

/**
 * @brief Clear the display
 * 
 * @param dev 
 * @return int 
 */
int max72xx_clear(max72xx_t *dev, uint8_t addr)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }

    int err;
    for(int i = 0 ; i < MAX72XX_MAX_COLUMN ; i++) {
        err = max72xx_set_column(dev, addr, i, 0);
        if(err) {
            return err;
        }
    }
}

/**
 * @brief Set LED on or off.
 * 
 * @param addr Device address
 * @param x 
 * @param y 
 * @param state State of LED (true = ON, false = OFF)
 * @return int OUT_OF_BOUNDS
 */
int max72xx_set_led(max72xx_t *dev, uint8_t addr, uint8_t x, uint8_t y, bool state)
{
    if(!dev) {
        /* Device instance null */
        return 1;
    }

    if(addr >= MAX72XX_MAX_DEVICE_COUNT) {
        /* Device address out of bounds */
        return 1;
    }

    if(x > MAX72XX_MAX_X_COORD || y > MAX72XX_MAX_Y_COORD) {
        /* LED coordinates out of bounds */
        return 1;
    }

    /*
        Register Data
                        D7 D6 D5 D4 D3 D2 D1 D0
        Corresponding
        Segment Line    DP A  B  C  D  E  F  G

        X coordinates are Digits
        Y coordinates are Segments

        Digits 0-7 are mapped to X 0-7
        Segments DP-G are mapped to Y 0-7
    */

    /*
    Example:
        Set LED with coordinates (4,5).

        Digit Register = DIGIT_4
        Segment Register = 

    */

    uint8_t frame_idx = 

    uint8_t digit = MAX72XX_REG_ADDR_DIGIT_0 + x;
    uint8_t segment = 1 << (7-y);

    return max72xx_write_reg(dev, addr, digit, segment);
}