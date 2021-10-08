/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS_H__
#define ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS_H__

#include "zboss_api.h"

/*! \addtogroup zb_zcl_rel_humidity_measurement_addons */
/*! @{ */

/**@brief Humidity Measurement cluster attributes according to ZCL Spec 4.4.2.1.1. */
typedef struct
{
    zb_int16_t  measure_value;
    zb_int16_t  min_measure_value;
    zb_int16_t  max_measure_value;
} zb_zcl_rel_humidity_measurement_attrs_t;

/** @} */

#endif /* ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS_H__ */