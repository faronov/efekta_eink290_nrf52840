#include <zephyr/types.h>
#include <zephyr.h>
#include <logging/log.h>
#include <dk_buttons_and_leds.h>
#include <drivers/sensor.h>

#if CONFIG_SUBSYS_ZIGBEE_DEVICE
#include "zigbee_device.h"
#endif

#if CONFIG_SUBSYS_BME280
#include "bme280.h"
#endif

#if CONFIG_SUBSYS_MAX44009
#include "max44009.h"
#endif


LOG_MODULE_REGISTER(main);

#if CONFIG_SUBSYS_BME280
static void handle_temperature_value(struct sensor_value value)
{
    LOG_INF("Temperature: %d.%06d Celsius", value.val1, value.val2);
    if (value.val2 < 0)
    {
        LOG_WRN("Temperature failed.");
    }
}
static void handle_humidity_value(struct sensor_value value)
{
    LOG_INF("Humidity: %d.%06d %%", value.val1, value.val2);
    if (value.val2 < 0)
    {
        LOG_WRN("Humidity failed.");
    }
}
static void handle_pressure_value(struct sensor_value value)
{
    LOG_INF("Pressure: %1d.%06d hPa", value.val1, value.val2);
    if (value.val2 < 0)
    {
        LOG_WRN("Pressure failed.");
    }
}
#endif

#if CONFIG_SUBSYS_MAX44009
static void handle_luminosity_value(struct sensor_value value)
{
    LOG_INF("LUX: %d.%06d", value.val1, value.val2);
    if (value.val2 < 0)
    {
        LOG_WRN("Get LUX failed.");
    }
}
#endif

void main(void)
{
    LOG_INF("Efekta multi Sensor");

    int err = dk_leds_init();
    if (err)
    {
        LOG_ERR("Cannot init LEDs (err: %d)", err);
    } 

#if CONFIG_SUBSYS_ZIGBEE_DEVICE
    // Start zigbee device
    start_zigbee_device();
#endif

#if CONFIG_SUBSYS_BME280
    // Register sensor value handlers
    bme280_register_temperature_handler(handle_temperature_value);
    bme280_register_humidity_handler(handle_humidity_value);
    bme280_register_pressure_handler(handle_pressure_value);
#if CONFIG_SUBSYS_ZIGBEE_DEVICE
    // Forward bme280 measurements to zigbee
    bme280_register_temperature_handler(publish_temperature);
    bme280_register_humidity_handler(publish_humidity);
    bme280_register_pressure_handler(publish_pressure);
#endif
#endif

#if CONFIG_SUBSYS_MAX44009
    // Register sensor value handlers
    max44009_register_luminosity_handler(handle_luminosity_value);
#if CONFIG_SUBSYS_ZIGBEE_DEVICE
    // Forward measurements to zigbee
    max44009_register_luminosity_handler(publish_luminosity_value);
#endif
#endif
    while (1)
    {
        dk_set_led_off(DK_LED1);
        k_sleep(K_MSEC(1000));
        dk_set_led_on(DK_LED1);
        k_sleep(K_FOREVER);
    }
    /* for (;;) {
        dk_set_led_off(DK_LED1);
        k_sleep(K_MSEC(1000));
        dk_set_led_on(DK_LED1);
        k_cpu_idle();
    } */

}