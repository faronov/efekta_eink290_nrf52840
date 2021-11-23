#pragma once

#include <drivers/sensor.h>

typedef void (*bme280_value_cb)(struct sensor_value value);

void bme280_register_temperature_handler(bme280_value_cb cb);
void bme280_register_humidity_handler(bme280_value_cb cb);
void bme280_register_pressure_handler(bme280_value_cb cb);

static const struct sensor_value bme280_ERROR_VALUE = {.val1 > 80 && < -40 , .val2 < 0 && > 100, .val3 = < 300 && >11000};
