/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5-dev at Fri Jun  6 19:48:16 2025. */

#ifndef PB_WIPPERSNAPPER_DS18X20_V1_WIPPERSNAPPER_DS18X20_V1_DS18X20_PB_H_INCLUDED
#define PB_WIPPERSNAPPER_DS18X20_V1_WIPPERSNAPPER_DS18X20_V1_DS18X20_PB_H_INCLUDED
#include <pb.h>
#include "nanopb/nanopb.pb.h"
#include "wippersnapper/i2c/v1/i2c.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _wippersnapper_ds18x20_v1_Ds18x20DeInitRequest {
    char onewire_pin[5];
} wippersnapper_ds18x20_v1_Ds18x20DeInitRequest;

typedef struct _wippersnapper_ds18x20_v1_Ds18x20DeviceEvent {
    char onewire_pin[5];
    pb_size_t sensor_event_count;
    wippersnapper_i2c_v1_SensorEvent sensor_event[2];
} wippersnapper_ds18x20_v1_Ds18x20DeviceEvent;

typedef struct _wippersnapper_ds18x20_v1_Ds18x20InitRequest {
    char onewire_pin[5];
    int32_t sensor_resolution;
    pb_size_t i2c_device_properties_count;
    wippersnapper_i2c_v1_I2CDeviceSensorProperties i2c_device_properties[2];
} wippersnapper_ds18x20_v1_Ds18x20InitRequest;

typedef struct _wippersnapper_ds18x20_v1_Ds18x20InitResponse {
    bool is_initialized;
    char onewire_pin[5];
} wippersnapper_ds18x20_v1_Ds18x20InitResponse;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_init_default {"", 0, 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default}}
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_init_default {0, ""}
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_init_default {""}
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_init_default {"", 0, {wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default}}
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_init_zero {"", 0, 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero}}
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_init_zero {0, ""}
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_init_zero {""}
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_init_zero {"", 0, {wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_onewire_pin_tag 1
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_onewire_pin_tag 1
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_sensor_event_tag 2
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_onewire_pin_tag 1
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_sensor_resolution_tag 2
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_i2c_device_properties_tag 3
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_is_initialized_tag 1
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_onewire_pin_tag 2

/* Struct field encoding specification for nanopb */
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   onewire_pin,       1) \
X(a, STATIC,   SINGULAR, INT32,    sensor_resolution,   2) \
X(a, STATIC,   REPEATED, MESSAGE,  i2c_device_properties,   3)
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_CALLBACK NULL
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_DEFAULT NULL
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_i2c_device_properties_MSGTYPE wippersnapper_i2c_v1_I2CDeviceSensorProperties

#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     is_initialized,    1) \
X(a, STATIC,   SINGULAR, STRING,   onewire_pin,       2)
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_CALLBACK NULL
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_DEFAULT NULL

#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   onewire_pin,       1)
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_CALLBACK NULL
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_DEFAULT NULL

#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   onewire_pin,       1) \
X(a, STATIC,   REPEATED, MESSAGE,  sensor_event,      2)
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_CALLBACK NULL
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_DEFAULT NULL
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_sensor_event_MSGTYPE wippersnapper_i2c_v1_SensorEvent

extern const pb_msgdesc_t wippersnapper_ds18x20_v1_Ds18x20InitRequest_msg;
extern const pb_msgdesc_t wippersnapper_ds18x20_v1_Ds18x20InitResponse_msg;
extern const pb_msgdesc_t wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_msg;
extern const pb_msgdesc_t wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_fields &wippersnapper_ds18x20_v1_Ds18x20InitRequest_msg
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_fields &wippersnapper_ds18x20_v1_Ds18x20InitResponse_msg
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_fields &wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_msg
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_fields &wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_msg

/* Maximum encoded size of messages (where known) */
#define wippersnapper_ds18x20_v1_Ds18x20InitRequest_size 37
#define wippersnapper_ds18x20_v1_Ds18x20InitResponse_size 8
#define wippersnapper_ds18x20_v1_Ds18x20DeInitRequest_size 6
#define wippersnapper_ds18x20_v1_Ds18x20DeviceEvent_size 24

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
