/** @brief Declare attribute list for Power Configuration cluster - server side
    @param attr_list - attribute list name
    @param voltage - pointer to variable to store BatteryVoltage attribute
    @param size - pointer to variable to store BatterySize attribute
    @param quantity - pointer to variable to store BatteryQuantity attribute
    @param rated_voltage - pointer to variable to store BatteryRatedVoltage attribute
    @param alarm_mask - pointer to variable to store BatteryAlarmMask attribute
    @param voltage_min_threshold - pointer to variable to store BatteryVoltageMinThreshold attribute
*/

/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ZB_ZCL_POWER_CONFIG_ADDONS_H__
#define ZB_ZCL_POWER_CONFIG_ADDONS_H__

#include "zboss_api.h"

/*! \addtogroup zb_zcl_power_config_addons */
/*! @{ */

/**@brief power config cluster attributes according to ZCL Spec 4.4.2.1.1. */
typedef struct
{
    zb_uint8_t battery_voltage;
    zb_uint8_t battery_size;
    zb_uint8_t battery_quantity;
    zb_uint8_t battery_rated_voltage;
    zb_uint8_t battery_alarm_mask;
    zb_uint8_t battery_voltage_min_threshold;

} zb_zcl_power_config_attrs_t;

/** @} */

#endif /* ZB_ZCL_POWER_CONFIG_ADDONS_H__ */