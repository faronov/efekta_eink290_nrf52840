
#include <device.h>
#include <devicetree.h>
#include <drivers/sensor.h>

uint32_t lum = 0U;

struct sensor_value temp, press, humidity;
struct sensor_value lum_val;

static const struct device *get_bme280_device(void)
{
	const struct device *dev = device_get_binding("BME280_I2C");

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}

static const struct device *get_max44009_device(void)
{
	const struct device *dev = device_get_binding("MAX44009");

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}
