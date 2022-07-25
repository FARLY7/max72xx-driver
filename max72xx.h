#ifndef MAX72XX_H
#define MAX72XX_H

#include <errno.h>
#include <stdint.h>
#include <stddef.h>


/* Defines the maximum number of MAX72XX devices in a chain */
#ifndef MAX72XX_MAX_DEVICE_COUNT
#define MAX72XX_MAX_DEVICE_COUNT            1
#endif

typedef struct {

    uint8_t frame[MAX72XX_MAX_DEVICE_COUNT * 8];

} max72xx_t;


/**
 * @brief Initialise MAX72XX device(s)
 * 
 * @param dev Pointer to MAX27xx instance
 * @param api 
 * @return int 
 */
int max72xx_init(max72xx_t *dev,
                    int (write*)(max72xx_t *dev, uint8_t *buf, size_t len));

/**
 * @brief Change operation mode (SHUTDOWN or NORMAL)
 * 
 * @param dev Pointer to MAX27xx instance
 * @param addr Device address
 * @param status If true, device goes into power-down mode. Set to
 *               false for normal operation. 
 * @return int
 */
int max72xx_shutdown(max72xx_t *dev, uint8_t addr, bool status);

/**
 * @brief Set the brightness intensity.
 * 
 * @param dev Pointer to MAX27xx instance
 * @param intensity Between 0-15
 * @param addr Device address
 * @return int 
 */
int max72xx_set_intensity(max72xx_t *dev, uint8_t addr, int intensity);

/**
 * @brief Turn on display test
 * 
 * @param dev Pointer to MAX27xx instance
 * @param on Turn display test on or off 
 * @param addr Device address
 * @return int 
 */
int max72xx_display_test(max72xx_t *dev, uint8_t addr, bool on);

/**
 * @brief Clear the display
 * 
 * @param dev Pointer to MAX27xx instance
 * @param addr Device address
 * @return int 
 */
int max72xx_clear(max72xx_t *dev, uint8_t addr);

/**
 * @brief Set LED on or off.
 * 
 * @param dev Pointer to MAX27xx instance
 * @param addr Device address
 * @param x 
 * @param y 
 * @param state 
 * @return int OUT_OF_BOUNDS
 */
int max72xx_set_led(max72xx_t *dev, uint8_t addr, uint8_t x, uint8_t y, bool state);

/**
 * @brief Set column of LEDs on or off.
 * 
 * @param dev 
 * @param addr 
 * @param column 
 * @param val 
 * @return int 
 */
int max72xx_set_column(max72xx_t *dev, uint8_t addr, uint8_t column, uint8_t val);

/**
 * @brief Set row of LEDs on or off.
 * 
 * @param dev 
 * @param addr 
 * @param row 
 * @param val 
 * @return int 
 */
int max72xx_set_row(max72xx_t *dev, uint8_t addr, uint8_t row, uint8_t val);

#endif /* MAX27XX_H */