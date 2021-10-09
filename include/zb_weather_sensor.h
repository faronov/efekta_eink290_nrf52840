
/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR_H__
#define ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR_H__

#define ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR

#ifdef ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR
#define ZB_ZCL_SUPPORT_CLUSTER_BASIC        1
#define ZB_ZCL_SUPPORT_CLUSTER_IDENTIFY     1
#define ZB_ZCL_SUPPORT_CLUSTER_POWER_CONFIG 1
#define ZB_ZCL_SUPPORT_CLUSTER_TEMP_MEASUREMENT 1
#define ZB_ZCL_SUPPORT_CLUSTER_REL_HUMIDITY_MEASUREMENT 1
#define ZB_ZCL_SUPPORT_CLUSTER_ILLUMINANCE_MEASUREMENT  1
#define ZB_ZCL_SUPPORT_CLUSTER_PRESSURE_MEASUREMENT 1
#endif /* ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR  */


#endif /*ZB_HA_DEFINE_DEVICE_WEATHER_SENSOR_H__ */