/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *
 * @brief Zigbee application template.
 */

#include <zephyr.h>
#include <logging/log.h>
#include <dk_buttons_and_leds.h>

#include <zboss_api.h>
#include <zigbee/zigbee_error_handler.h>
#include <zigbee/zigbee_app_utils.h>
#include <zb_nrf_platform.h>
#include <zboss_api_zcl_addons.h>
#include "zb_zcl_rel_humidity_measurement_addons.h"
#include "zb_zcl_illuminance_measurement_addons.h"
#include "zb_zcl_pressure_measurement_addons.h"
#include "zb_zcl_power_config_addons.h"

/* Device endpoint, used to receive ZCL commands. */
#define SENSOR_ENDPOINT           1

/* Version of the application software (1 byte). */
#define SENSOR_INIT_BASIC_APP_VERSION     01

/* Version of the implementation of the Zigbee stack (1 byte). */
#define SENSOR_INIT_BASIC_STACK_VERSION   10

/* Version of the hardware of the device (1 byte). */
#define SENSOR_INIT_BASIC_HW_VERSION      02

/* Manufacturer name (32 bytes). */
#define SENSOR_INIT_BASIC_MANUF_NAME      "Nordic"

/* Model number assigned by manufacturer (32-bytes long string). */
#define SENSOR_INIT_BASIC_MODEL_ID        "Efekta_EINK290"

/* First 8 bytes specify the date of manufacturer of the device
 * in ISO 8601 format (YYYYMMDD). The rest (8 bytes) are manufacturer specific.
 */
#define  SENSOR_INIT_BASIC_DATE_CODE       "20211005"

/* Type of power sources available for the device.
 * For possible values see section 3.2.2.2.8 of ZCL specification.
 */
#define SENSOR_INIT_BASIC_POWER_SOURCE    ZB_ZCL_BASIC_POWER_SOURCE_BATTERY

/* Describes the physical location of the device (16 bytes).
 * May be modified during commisioning process.
 */
#define SENSOR_INIT_BASIC_LOCATION_DESC   "Office desk"

/* Describes the type of physical environment.
 * For possible values see section 3.2.2.2.10 of ZCL specification.
 */
#define SENSOR_INIT_BASIC_PH_ENV          ZB_ZCL_BASIC_ENV_UNSPECIFIED


/* LED indicating that device successfully joined Zigbee network. */
#define ZIGBEE_NETWORK_STATE_LED        DK_LED3

/* LED used for device identification. */
#define IDENTIFY_LED                    DK_LED4

/* Button used to enter the Identify mode. */
#define IDENTIFY_MODE_BUTTON            DK_BTN4_MSK


LOG_MODULE_REGISTER(app);

/* Main application customizable context.
 * Stores all settings and static values.
 */
struct zb_device_ctx {
	zb_zcl_basic_attrs_ext_t     basic_attr;
	zb_zcl_identify_attrs_t  identify_attr;
	zb_zcl_power_config_attrs_t power_config_attr;
	zb_zcl_temp_measurement_attrs_t temperature_measure_attr;
	zb_zcl_rel_humidity_measurement_attrs_t real_humidity_measure_attr;
	zb_zcl_illuminance_measurement_attrs_t illuminance_measure_attr;
	zb_zcl_pressure_measurement_attrs_t pressure_measure_attr;
};

/* Zigbee device application context storage. */
static struct zb_device_ctx dev_ctx;

ZB_ZCL_DECLARE_IDENTIFY_ATTRIB_LIST(
	identify_attr_list,
	&dev_ctx.identify_attr.identify_time);

ZB_ZCL_DECLARE_BASIC_ATTRIB_LIST_EXT(
	basic_attr_list,
	&dev_ctx.basic_attr.zcl_version,
	&dev_ctx.basic_attr.app_version,
	&dev_ctx.basic_attr.stack_version,
	&dev_ctx.basic_attr.hw_version,
	dev_ctx.basic_attr.mf_name,
	dev_ctx.basic_attr.model_id,
	dev_ctx.basic_attr.date_code,
	&dev_ctx.basic_attr.power_source,
	dev_ctx.basic_attr.location_id,
	&dev_ctx.basic_attr.ph_env,
	dev_ctx.basic_attr.sw_ver);

ZB_ZCL_DECLARE_POWER_CONFIG_ATTRIB_LIST(
	power_config_attr_list,
	&dev_ctx.power_config_attr.battery_voltage,
	&dev_ctx.power_config_attr.battery_size,
	&dev_ctx.power_config_attr.battery_quantity,
	&dev_ctx.power_config_attr.battery_rated_voltage,
	&dev_ctx.power_config_attr.battery_alarm_mask,
	&dev_ctx.power_config_attr.battery_voltage_min_threshold);

ZB_ZCL_DECLARE_TEMP_MEASUREMENT_ATTRIB_LIST(
	temperature_measure_attr_list,
	&dev_ctx.temperature_measure_attr.measure_value,
	&dev_ctx.temperature_measure_attr.min_measure_value,
	&dev_ctx.temperature_measure_attr.max_measure_value,
	&dev_ctx.temperature_measure_attr.tolerance);

ZB_ZCL_DECLARE_REL_HUMIDITY_MEASUREMENT_ATTRIB_LIST(
	real_humidity_measure_attr_list,
	&dev_ctx.real_humidity_measure_attr.measure_value,
	&dev_ctx.real_humidity_measure_attr.min_measure_value,
	&dev_ctx.real_humidity_measure_attr.max_measure_value);

ZB_ZCL_DECLARE_ILLUMINANCE_MEASUREMENT_ATTRIB_LIST(
	illuminance_measure_attr_list,
	&dev_ctx.illuminance_measure_attr.measure_value,
	&dev_ctx.illuminance_measure_attr.min_measure_value,
	&dev_ctx.illuminance_measure_attr.max_measure_value);

ZB_ZCL_DECLARE_PRESSURE_MEASUREMENT_ATTRIB_LIST(
	pressure_measure_attr_list,
	&dev_ctx.pressure_measure_attr.measure_value,
	&dev_ctx.pressure_measure_attr.min_measure_value,
	&dev_ctx.pressure_measure_attr.max_measure_value,
	&dev_ctx.pressure_measure_attr.tolerance);


ZB_HA_DECLARE_RANGE_EXTENDER_CLUSTER_LIST(
	sensor_clusters,
	identify_attr_list,
	basic_attr_list);

ZB_HA_DECLARE_RANGE_EXTENDER_EP(
	sensor_ep,
	SENSOR_ENDPOINT,
	sensor_clusters);

ZBOSS_DECLARE_DEVICE_CTX_1_EP(
	sensor_ctx,
	sensor_ep);


/**@brief Function for initializing all clusters attributes. */
static void app_clusters_attr_init(void)
{
	/* Basic cluster attributes data */
	dev_ctx.basic_attr.zcl_version = ZB_ZCL_VERSION;
	dev_ctx.basic_attr.power_source = SENSOR_INIT_BASIC_POWER_SOURCE;

	/* Identify cluster attributes data. */
	dev_ctx.identify_attr.identify_time =
		ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE;
}

/**@brief Function to toggle the identify LED
 *
 * @param  bufid  Unused parameter, required by ZBOSS scheduler API.
 */
static void toggle_identify_led(zb_bufid_t bufid)
{
	static int blink_status;

	dk_set_led(IDENTIFY_LED, (++blink_status) % 2);
	ZB_SCHEDULE_APP_ALARM(toggle_identify_led, bufid, ZB_MILLISECONDS_TO_BEACON_INTERVAL(100));
}

/**@brief Function to handle identify notification events on the first endpoint.
 *
 * @param  bufid  Unused parameter, required by ZBOSS scheduler API.
 */
static void identify_cb(zb_bufid_t bufid)
{
	zb_ret_t zb_err_code;

	if (bufid) {
		/* Schedule a self-scheduling function that will toggle the LED */
		ZB_SCHEDULE_APP_CALLBACK(toggle_identify_led, bufid);
	} else {
		/* Cancel the toggling function alarm and turn off LED */
		zb_err_code = ZB_SCHEDULE_APP_ALARM_CANCEL(toggle_identify_led, ZB_ALARM_ANY_PARAM);
		ZVUNUSED(zb_err_code);

		dk_set_led(IDENTIFY_LED, 0);
	}
}

/**@breif Starts identifying the device.
 *
 * @param  bufid  Unused parameter, required by ZBOSS scheduler API.
 */
static void start_identifying(zb_bufid_t bufid)
{
	zb_ret_t zb_err_code;

	ZVUNUSED(bufid);

	/* Check if endpoint is in identifying mode,
	 * if not put desired endpoint in identifying mode.
	 */
	if (dev_ctx.identify_attr.identify_time ==
	    ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE) {
		LOG_INF("Enter identify mode");
		zb_err_code = zb_bdb_finding_binding_target(
			SENSOR_ENDPOINT);
		ZB_ERROR_CHECK(zb_err_code);
	} else {
		LOG_INF("Cancel identify mode");
		zb_bdb_finding_binding_target_cancel();
	}
}

/**@brief Callback for button events.
 *
 * @param[in]   button_state  Bitmask containing buttons state.
 * @param[in]   has_changed   Bitmask containing buttons
 *                            that have changed their state.
 */
static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	/* Calculate bitmask of buttons that are pressed
	 * and have changed their state.
	 */
	uint32_t buttons = button_state & has_changed;

	if (buttons & IDENTIFY_MODE_BUTTON) {
		ZB_SCHEDULE_APP_CALLBACK(start_identifying, 0);
	}
}

/**@brief Function for initializing LEDs and Buttons. */
static void configure_gpio(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		LOG_ERR("Cannot init buttons (err: %d)", err);
	}

	err = dk_leds_init();
	if (err) {
		LOG_ERR("Cannot init LEDs (err: %d)", err);
	}
}

/**@brief Zigbee stack event handler.
 *
 * @param[in]   bufid   Reference to the Zigbee stack buffer
 *                      used to pass signal.
 */
void zboss_signal_handler(zb_bufid_t bufid)
{
	/* Update network status LED. */
	zigbee_led_status_update(bufid, ZIGBEE_NETWORK_STATE_LED);

	/* No application-specific behavior is required.
	 * Call default signal handler.
	 */
	ZB_ERROR_CHECK(zigbee_default_signal_handler(bufid));

	/* All callbacks should either reuse or free passed buffers.
	 * If bufid == 0, the buffer is invalid (not passed).
	 */
	if (bufid) {
		zb_buf_free(bufid);
	}
}

void error(void)
{
	dk_set_leds_state(DK_ALL_LEDS_MSK, DK_NO_LEDS_MSK);

	while (true) {
		/* Spin forever */
		k_sleep(K_MSEC(1000));
	}
}

void main(void)
{
	LOG_INF("Starting Zigbee application template example");

	/* Initialize */
	configure_gpio();

	/* Register device context (endpoints). */
	ZB_AF_REGISTER_DEVICE_CTX(&sensor_ctx);

	app_clusters_attr_init();

	/* Register handlers to identify notifications */
	ZB_AF_SET_IDENTIFY_NOTIFICATION_HANDLER(SENSOR_ENDPOINT, identify_cb);

	/* Start Zigbee default thread */
	zigbee_enable();

	LOG_INF("Zigbee application template started");
}
