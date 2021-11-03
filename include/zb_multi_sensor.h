
/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ZB_MULTI_SENSOR_H__
#define ZB_MULTI_SENSOR_H__

#define ZB_HA_DEFINE_DEVICE_MULTI_SENSOR

#ifdef ZB_HA_DEFINE_DEVICE_MULTI_SENSOR
#define ZB_ZCL_SUPPORT_CLUSTER_BASIC        1
#define ZB_ZCL_SUPPORT_CLUSTER_IDENTIFY     1
#define ZB_ZCL_SUPPORT_CLUSTER_POWER_CONFIG 1
#define ZB_ZCL_SUPPORT_CLUSTER_TEMP_MEASUREMENT 1
#define ZB_ZCL_SUPPORT_CLUSTER_REL_HUMIDITY_MEASUREMENT 1
#define ZB_ZCL_SUPPORT_CLUSTER_ILLUMINANCE_MEASUREMENT  1
#define ZB_ZCL_SUPPORT_CLUSTER_PRESSURE_MEASUREMENT 1
#endif /* ZB_HA_DEFINE_DEVICE_MULTI_SENSOR  */

#define ZB_MULTI_SENSOR_REPORT_ATTR_COUNT  6
#define ZB_DEVICE_VER_MULTI_SENSOR         0                                    /**< Multisensor device version. */
#define ZB_MULTI_SENSOR_IN_CLUSTER_NUM     7                                    /**< Number of the input (server) clusters in the multisensor device. */
#define ZB_MULTI_SENSOR_OUT_CLUSTER_NUM    1                                    /**< Number of the output (client) clusters in the multisensor device. */

/** @brief Declares cluster list for the multisensor device.
 *
 *  @param cluster_list_name            Cluster list variable name.
 *  @param basic_attr_list              Attribute list for the Basic cluster.
 *  @param identify_attr_list           Attribute list for the Identify cluster.
 *  @param temp_measure_attr_list       Attribute list for the Temperature Measurement cluster.
 *  @param pressure_measure_attr_list   Attribute list for the Pressure Measurement cluster.
 */
#define ZB_DECLARE_MULTI_SENSOR_CLUSTER_LIST(                       \
      cluster_list_name,                                            \
      basic_attr_list,                                              \
      identify_attr_list,                                           \
      temp_measure_attr_list,                                       \
      humm_measure_attr_list,                                       \
      pres_measure_attr_list,                                       \
      power_measure_attr_list)                                      \
      zb_zcl_cluster_desc_t cluster_list_name[] =                   \
      {                                                             \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_IDENTIFY,                               \
          ZB_ZCL_ARRAY_SIZE(identify_attr_list, zb_zcl_attr_t),     \
          (identify_attr_list),                                     \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_BASIC,                                  \
          ZB_ZCL_ARRAY_SIZE(basic_attr_list, zb_zcl_attr_t),        \
          (basic_attr_list),                                        \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,                       \
          ZB_ZCL_ARRAY_SIZE(temp_measure_attr_list, zb_zcl_attr_t), \
          (temp_measure_attr_list),                                 \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,               \
          ZB_ZCL_ARRAY_SIZE(humm_measure_attr_list, zb_zcl_attr_t), \
          (humm_measure_attr_list),                                 \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT,                   \
          ZB_ZCL_ARRAY_SIZE(pres_measure_attr_list, zb_zcl_attr_t), \
          (pres_measure_attr_list),                                 \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_POWER_CONFIG,                           \
          ZB_ZCL_ARRAY_SIZE(power_measure_attr_list, zb_zcl_attr_t),\
          (power_measure_attr_list),                                \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT,                \
          ZB_ZCL_ARRAY_SIZE(illuminance_measure_attr_list, zb_zcl_attr_t),\
          (illuminance_measure_attr_list),                                \
          ZB_ZCL_CLUSTER_SERVER_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        ),                                                          \
        ZB_ZCL_CLUSTER_DESC(                                        \
          ZB_ZCL_CLUSTER_ID_IDENTIFY,                               \
          0,                                                        \
          NULL,                                                     \
          ZB_ZCL_CLUSTER_CLIENT_ROLE,                               \
          ZB_ZCL_MANUF_CODE_INVALID                                 \
        )                                                           \
      }

/** @brief Declares simple descriptor for the "Device_name" device.
 *  
 *  @param ep_name          Endpoint variable name.
 *  @param ep_id            Endpoint ID.
 *  @param in_clust_num     Number of the supported input clusters.
 *  @param out_clust_num    Number of the supported output clusters.
 */
#define ZB_ZCL_DECLARE_MULTI_SENSOR_DESC(ep_name, ep_id, in_clust_num, out_clust_num) \
  ZB_DECLARE_SIMPLE_DESC(in_clust_num, out_clust_num);                                \
  ZB_AF_SIMPLE_DESC_TYPE(in_clust_num, out_clust_num) simple_desc_##ep_name =         \
  {                                                                                   \
    ep_id,                                                                            \
    ZB_AF_HA_PROFILE_ID,                                                              \
    ZB_HA_TEMPERATURE_SENSOR_DEVICE_ID,                                               \
    ZB_DEVICE_VER_MULTI_SENSOR,                                                       \
    0,                                                                                \
    in_clust_num,                                                                     \
    out_clust_num,                                                                    \
    {                                                                                 \
      ZB_ZCL_CLUSTER_ID_BASIC,                                                        \
      ZB_ZCL_CLUSTER_ID_IDENTIFY,                                                     \
      ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT,                                             \
      ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT,                                     \
      ZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT,                                         \
      ZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT,                                      \
      ZB_ZCL_CLUSTER_ID_POWER_CONFIG,                                                 \
      ZB_ZCL_CLUSTER_ID_IDENTIFY,                                                     \
    }                                                                                 \
  }

/** @brief Declares endpoint for the multisensor device.
 *   
 *  @param ep_name          Endpoint variable name.
 *  @param ep_id            Endpoint ID.
 *  @param cluster_list     Endpoint cluster list.
 */
#define ZB_ZCL_DECLARE_MULTI_SENSOR_EP(ep_name, ep_id, cluster_list)              \
  ZB_ZCL_DECLARE_MULTI_SENSOR_DESC(ep_name,                                       \
      ep_id,                                                                      \
      ZB_MULTI_SENSOR_IN_CLUSTER_NUM,                                             \
      ZB_MULTI_SENSOR_OUT_CLUSTER_NUM);                                           \
  ZBOSS_DEVICE_DECLARE_REPORTING_CTX(reporting_info## device_ctx_name,            \
                                     ZB_MULTI_SENSOR_REPORT_ATTR_COUNT);          \
  ZB_AF_DECLARE_ENDPOINT_DESC(ep_name, ep_id,                                     \
      ZB_AF_HA_PROFILE_ID,                                                        \
      0,                                                                          \
      NULL,                                                                       \
      ZB_ZCL_ARRAY_SIZE(cluster_list, zb_zcl_cluster_desc_t),                     \
      cluster_list,                                                               \
      (zb_af_simple_desc_1_1_t*)&simple_desc_##ep_name,                           \
      ZB_MULTI_SENSOR_REPORT_ATTR_COUNT, reporting_info## device_ctx_name, 0, NULL)




#endif /*  ZB_MULTI_SENSOR_H__ */