/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5-dev at Tue Oct 11 14:47:09 2022. */

#ifndef PB_WIPPERSNAPPER_I2C_V1_WIPPERSNAPPER_I2C_V1_I2C_PB_H_INCLUDED
#define PB_WIPPERSNAPPER_I2C_V1_WIPPERSNAPPER_I2C_V1_I2C_PB_H_INCLUDED
#include <pb.h>
#include "nanopb/nanopb.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _wippersnapper_i2c_v1_BusResponse {
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_UNSPECIFIED = 0,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_SUCCESS = 1,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_ERROR_HANG = 2,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_ERROR_PULLUPS = 3,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_ERROR_WIRING = 4,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_UNSUPPORTED_SENSOR = 5,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_DEVICE_INIT_FAIL = 6,
    wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_DEVICE_DEINIT_FAIL = 7
} wippersnapper_i2c_v1_BusResponse;

typedef enum _wippersnapper_i2c_v1_SensorType {
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_UNSPECIFIED = 0,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_ACCELEROMETER = 1,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_MAGNETIC_FIELD = 2,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_ORIENTATION = 3,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_GYROSCOPE = 4,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_LIGHT = 5,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PRESSURE = 6,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PROXIMITY = 8,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_GRAVITY = 9,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_LINEAR_ACCELERATION = 10,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_ROTATION_VECTOR = 11,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_RELATIVE_HUMIDITY = 12,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_AMBIENT_TEMPERATURE = 13,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_OBJECT_TEMPERATURE = 14,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_VOLTAGE = 15,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_CURRENT = 16,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_COLOR = 17,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_RAW = 18,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM10_STD = 19,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM25_STD = 20,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM100_STD = 21,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM10_ENV = 22,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM25_ENV = 23,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_PM100_ENV = 24,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_CO2 = 25,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_GAS_RESISTANCE = 26,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_ALTITUDE = 27,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_LUX = 28,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_ECO2 = 29,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_UNITLESS_PERCENT = 30,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_AMBIENT_TEMPERATURE_FAHRENHEIT = 31,
    wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_OBJECT_TEMPERATURE_FAHRENHEIT = 32
} wippersnapper_i2c_v1_SensorType;

/* Struct definitions */
typedef struct _wippersnapper_i2c_v1_I2CDeviceInitRequests {
    pb_callback_t list;
} wippersnapper_i2c_v1_I2CDeviceInitRequests;

typedef struct _wippersnapper_i2c_v1_I2CBusInitRequest {
    int32_t i2c_pin_scl;
    int32_t i2c_pin_sda;
    uint32_t i2c_frequency;
    int32_t i2c_port_number;
} wippersnapper_i2c_v1_I2CBusInitRequest;

typedef struct _wippersnapper_i2c_v1_I2CBusInitResponse {
    wippersnapper_i2c_v1_BusResponse bus_response;
} wippersnapper_i2c_v1_I2CBusInitResponse;

typedef struct _wippersnapper_i2c_v1_I2CBusScanResponse {
    pb_size_t addresses_found_count;
    uint32_t addresses_found[120];
    wippersnapper_i2c_v1_BusResponse bus_response;
} wippersnapper_i2c_v1_I2CBusScanResponse;

typedef struct _wippersnapper_i2c_v1_I2CBusSetFrequency {
    uint32_t frequency;
    int32_t bus_id;
} wippersnapper_i2c_v1_I2CBusSetFrequency;

typedef struct _wippersnapper_i2c_v1_I2CDeviceDeinitRequest {
    int32_t i2c_port_number;
    uint32_t i2c_device_address;
} wippersnapper_i2c_v1_I2CDeviceDeinitRequest;

typedef struct _wippersnapper_i2c_v1_I2CDeviceDeinitResponse {
    uint32_t i2c_device_address;
    wippersnapper_i2c_v1_BusResponse bus_response;
} wippersnapper_i2c_v1_I2CDeviceDeinitResponse;

typedef struct _wippersnapper_i2c_v1_I2CDeviceInitResponse {
    uint32_t i2c_device_address;
    wippersnapper_i2c_v1_BusResponse bus_response;
} wippersnapper_i2c_v1_I2CDeviceInitResponse;

typedef struct _wippersnapper_i2c_v1_I2CDeviceSensorProperties {
    wippersnapper_i2c_v1_SensorType sensor_type;
    uint32_t sensor_period;
} wippersnapper_i2c_v1_I2CDeviceSensorProperties;

typedef struct _wippersnapper_i2c_v1_I2CDeviceUpdateResponse {
    uint32_t i2c_device_address;
    wippersnapper_i2c_v1_BusResponse bus_response;
} wippersnapper_i2c_v1_I2CDeviceUpdateResponse;

typedef struct _wippersnapper_i2c_v1_SensorEvent {
    wippersnapper_i2c_v1_SensorType type;
    float value;
} wippersnapper_i2c_v1_SensorEvent;

typedef struct _wippersnapper_i2c_v1_I2CBusScanRequest {
    int32_t i2c_port_number;
    bool has_bus_init_request;
    wippersnapper_i2c_v1_I2CBusInitRequest bus_init_request;
} wippersnapper_i2c_v1_I2CBusScanRequest;

typedef struct _wippersnapper_i2c_v1_I2CDeviceEvent {
    uint32_t sensor_address;
    pb_size_t sensor_event_count;
    wippersnapper_i2c_v1_SensorEvent sensor_event[15];
} wippersnapper_i2c_v1_I2CDeviceEvent;

typedef struct _wippersnapper_i2c_v1_I2CDeviceInitRequest {
    int32_t i2c_port_number;
    bool has_i2c_bus_init_req;
    wippersnapper_i2c_v1_I2CBusInitRequest i2c_bus_init_req;
    uint32_t i2c_device_address;
    char i2c_device_name[15];
    pb_size_t i2c_device_properties_count;
    wippersnapper_i2c_v1_I2CDeviceSensorProperties i2c_device_properties[15];
} wippersnapper_i2c_v1_I2CDeviceInitRequest;

typedef struct _wippersnapper_i2c_v1_I2CDeviceUpdateRequest {
    int32_t i2c_port_number;
    uint32_t i2c_device_address;
    char i2c_device_name[15];
    pb_size_t i2c_device_properties_count;
    wippersnapper_i2c_v1_I2CDeviceSensorProperties i2c_device_properties[15];
} wippersnapper_i2c_v1_I2CDeviceUpdateRequest;


/* Helper constants for enums */
#define _wippersnapper_i2c_v1_BusResponse_MIN wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_UNSPECIFIED
#define _wippersnapper_i2c_v1_BusResponse_MAX wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_DEVICE_DEINIT_FAIL
#define _wippersnapper_i2c_v1_BusResponse_ARRAYSIZE ((wippersnapper_i2c_v1_BusResponse)(wippersnapper_i2c_v1_BusResponse_BUS_RESPONSE_DEVICE_DEINIT_FAIL+1))

#define _wippersnapper_i2c_v1_SensorType_MIN wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_UNSPECIFIED
#define _wippersnapper_i2c_v1_SensorType_MAX wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_OBJECT_TEMPERATURE_FAHRENHEIT
#define _wippersnapper_i2c_v1_SensorType_ARRAYSIZE ((wippersnapper_i2c_v1_SensorType)(wippersnapper_i2c_v1_SensorType_SENSOR_TYPE_OBJECT_TEMPERATURE_FAHRENHEIT+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define wippersnapper_i2c_v1_I2CBusInitRequest_init_default {0, 0, 0, 0}
#define wippersnapper_i2c_v1_I2CBusInitResponse_init_default {_wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CBusSetFrequency_init_default {0, 0}
#define wippersnapper_i2c_v1_I2CBusScanRequest_init_default {0, false, wippersnapper_i2c_v1_I2CBusInitRequest_init_default}
#define wippersnapper_i2c_v1_I2CBusScanResponse_init_default {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default {_wippersnapper_i2c_v1_SensorType_MIN, 0}
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_init_default {{{NULL}, NULL}}
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_init_default {0, false, wippersnapper_i2c_v1_I2CBusInitRequest_init_default, 0, "", 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default}}
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_init_default {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_init_default {0, 0, "", 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_default}}
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_init_default {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_init_default {0, 0}
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_init_default {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_SensorEvent_init_default {_wippersnapper_i2c_v1_SensorType_MIN, 0}
#define wippersnapper_i2c_v1_I2CDeviceEvent_init_default {0, 0, {wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default, wippersnapper_i2c_v1_SensorEvent_init_default}}
#define wippersnapper_i2c_v1_I2CBusInitRequest_init_zero {0, 0, 0, 0}
#define wippersnapper_i2c_v1_I2CBusInitResponse_init_zero {_wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CBusSetFrequency_init_zero {0, 0}
#define wippersnapper_i2c_v1_I2CBusScanRequest_init_zero {0, false, wippersnapper_i2c_v1_I2CBusInitRequest_init_zero}
#define wippersnapper_i2c_v1_I2CBusScanResponse_init_zero {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero {_wippersnapper_i2c_v1_SensorType_MIN, 0}
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_init_zero {{{NULL}, NULL}}
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_init_zero {0, false, wippersnapper_i2c_v1_I2CBusInitRequest_init_zero, 0, "", 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero}}
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_init_zero {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_init_zero {0, 0, "", 0, {wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero, wippersnapper_i2c_v1_I2CDeviceSensorProperties_init_zero}}
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_init_zero {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_init_zero {0, 0}
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_init_zero {0, _wippersnapper_i2c_v1_BusResponse_MIN}
#define wippersnapper_i2c_v1_SensorEvent_init_zero {_wippersnapper_i2c_v1_SensorType_MIN, 0}
#define wippersnapper_i2c_v1_I2CDeviceEvent_init_zero {0, 0, {wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero, wippersnapper_i2c_v1_SensorEvent_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_list_tag 1
#define wippersnapper_i2c_v1_I2CBusInitRequest_i2c_pin_scl_tag 1
#define wippersnapper_i2c_v1_I2CBusInitRequest_i2c_pin_sda_tag 2
#define wippersnapper_i2c_v1_I2CBusInitRequest_i2c_frequency_tag 3
#define wippersnapper_i2c_v1_I2CBusInitRequest_i2c_port_number_tag 4
#define wippersnapper_i2c_v1_I2CBusInitResponse_bus_response_tag 2
#define wippersnapper_i2c_v1_I2CBusScanResponse_addresses_found_tag 1
#define wippersnapper_i2c_v1_I2CBusScanResponse_bus_response_tag 2
#define wippersnapper_i2c_v1_I2CBusSetFrequency_frequency_tag 1
#define wippersnapper_i2c_v1_I2CBusSetFrequency_bus_id_tag 2
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_i2c_port_number_tag 1
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_i2c_device_address_tag 2
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_i2c_device_address_tag 2
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_bus_response_tag 3
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_i2c_device_address_tag 2
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_bus_response_tag 3
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_sensor_type_tag 1
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_sensor_period_tag 2
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_i2c_device_address_tag 1
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_bus_response_tag 3
#define wippersnapper_i2c_v1_SensorEvent_type_tag 1
#define wippersnapper_i2c_v1_SensorEvent_value_tag 2
#define wippersnapper_i2c_v1_I2CBusScanRequest_i2c_port_number_tag 1
#define wippersnapper_i2c_v1_I2CBusScanRequest_bus_init_request_tag 2
#define wippersnapper_i2c_v1_I2CDeviceEvent_sensor_address_tag 1
#define wippersnapper_i2c_v1_I2CDeviceEvent_sensor_event_tag 2
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_port_number_tag 1
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_bus_init_req_tag 2
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_device_address_tag 3
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_device_name_tag 4
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_device_properties_tag 5
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_i2c_port_number_tag 1
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_i2c_device_address_tag 2
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_i2c_device_name_tag 3
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_i2c_device_properties_tag 4

/* Struct field encoding specification for nanopb */
#define wippersnapper_i2c_v1_I2CBusInitRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    i2c_pin_scl,       1) \
X(a, STATIC,   SINGULAR, INT32,    i2c_pin_sda,       2) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_frequency,     3) \
X(a, STATIC,   SINGULAR, INT32,    i2c_port_number,   4)
#define wippersnapper_i2c_v1_I2CBusInitRequest_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CBusInitRequest_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CBusInitResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    bus_response,      2)
#define wippersnapper_i2c_v1_I2CBusInitResponse_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CBusInitResponse_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CBusSetFrequency_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   frequency,         1) \
X(a, STATIC,   SINGULAR, INT32,    bus_id,            2)
#define wippersnapper_i2c_v1_I2CBusSetFrequency_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CBusSetFrequency_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CBusScanRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    i2c_port_number,   1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  bus_init_request,   2)
#define wippersnapper_i2c_v1_I2CBusScanRequest_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CBusScanRequest_DEFAULT NULL
#define wippersnapper_i2c_v1_I2CBusScanRequest_bus_init_request_MSGTYPE wippersnapper_i2c_v1_I2CBusInitRequest

#define wippersnapper_i2c_v1_I2CBusScanResponse_FIELDLIST(X, a) \
X(a, STATIC,   REPEATED, UINT32,   addresses_found,   1) \
X(a, STATIC,   SINGULAR, UENUM,    bus_response,      2)
#define wippersnapper_i2c_v1_I2CBusScanResponse_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CBusScanResponse_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    sensor_type,       1) \
X(a, STATIC,   SINGULAR, UINT32,   sensor_period,     2)
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceInitRequests_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  list,              1)
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_CALLBACK pb_default_field_callback
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_DEFAULT NULL
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_list_MSGTYPE wippersnapper_i2c_v1_I2CDeviceInitRequest

#define wippersnapper_i2c_v1_I2CDeviceInitRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    i2c_port_number,   1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  i2c_bus_init_req,   2) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   3) \
X(a, STATIC,   SINGULAR, STRING,   i2c_device_name,   4) \
X(a, STATIC,   REPEATED, MESSAGE,  i2c_device_properties,   5)
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_DEFAULT NULL
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_bus_init_req_MSGTYPE wippersnapper_i2c_v1_I2CBusInitRequest
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_i2c_device_properties_MSGTYPE wippersnapper_i2c_v1_I2CDeviceSensorProperties

#define wippersnapper_i2c_v1_I2CDeviceInitResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   2) \
X(a, STATIC,   SINGULAR, UENUM,    bus_response,      3)
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    i2c_port_number,   1) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   2) \
X(a, STATIC,   SINGULAR, STRING,   i2c_device_name,   3) \
X(a, STATIC,   REPEATED, MESSAGE,  i2c_device_properties,   4)
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_DEFAULT NULL
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_i2c_device_properties_MSGTYPE wippersnapper_i2c_v1_I2CDeviceSensorProperties

#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   1) \
X(a, STATIC,   SINGULAR, UENUM,    bus_response,      3)
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    i2c_port_number,   1) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   2)
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   i2c_device_address,   2) \
X(a, STATIC,   SINGULAR, UENUM,    bus_response,      3)
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_DEFAULT NULL

#define wippersnapper_i2c_v1_SensorEvent_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    type,              1) \
X(a, STATIC,   SINGULAR, FLOAT,    value,             2)
#define wippersnapper_i2c_v1_SensorEvent_CALLBACK NULL
#define wippersnapper_i2c_v1_SensorEvent_DEFAULT NULL

#define wippersnapper_i2c_v1_I2CDeviceEvent_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   sensor_address,    1) \
X(a, STATIC,   REPEATED, MESSAGE,  sensor_event,      2)
#define wippersnapper_i2c_v1_I2CDeviceEvent_CALLBACK NULL
#define wippersnapper_i2c_v1_I2CDeviceEvent_DEFAULT NULL
#define wippersnapper_i2c_v1_I2CDeviceEvent_sensor_event_MSGTYPE wippersnapper_i2c_v1_SensorEvent

extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CBusInitRequest_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CBusInitResponse_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CBusSetFrequency_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CBusScanRequest_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CBusScanResponse_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceSensorProperties_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceInitRequests_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceInitRequest_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceInitResponse_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceUpdateRequest_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceUpdateResponse_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceDeinitRequest_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceDeinitResponse_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_SensorEvent_msg;
extern const pb_msgdesc_t wippersnapper_i2c_v1_I2CDeviceEvent_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define wippersnapper_i2c_v1_I2CBusInitRequest_fields &wippersnapper_i2c_v1_I2CBusInitRequest_msg
#define wippersnapper_i2c_v1_I2CBusInitResponse_fields &wippersnapper_i2c_v1_I2CBusInitResponse_msg
#define wippersnapper_i2c_v1_I2CBusSetFrequency_fields &wippersnapper_i2c_v1_I2CBusSetFrequency_msg
#define wippersnapper_i2c_v1_I2CBusScanRequest_fields &wippersnapper_i2c_v1_I2CBusScanRequest_msg
#define wippersnapper_i2c_v1_I2CBusScanResponse_fields &wippersnapper_i2c_v1_I2CBusScanResponse_msg
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_fields &wippersnapper_i2c_v1_I2CDeviceSensorProperties_msg
#define wippersnapper_i2c_v1_I2CDeviceInitRequests_fields &wippersnapper_i2c_v1_I2CDeviceInitRequests_msg
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_fields &wippersnapper_i2c_v1_I2CDeviceInitRequest_msg
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_fields &wippersnapper_i2c_v1_I2CDeviceInitResponse_msg
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_fields &wippersnapper_i2c_v1_I2CDeviceUpdateRequest_msg
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_fields &wippersnapper_i2c_v1_I2CDeviceUpdateResponse_msg
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_fields &wippersnapper_i2c_v1_I2CDeviceDeinitRequest_msg
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_fields &wippersnapper_i2c_v1_I2CDeviceDeinitResponse_msg
#define wippersnapper_i2c_v1_SensorEvent_fields &wippersnapper_i2c_v1_SensorEvent_msg
#define wippersnapper_i2c_v1_I2CDeviceEvent_fields &wippersnapper_i2c_v1_I2CDeviceEvent_msg

/* Maximum encoded size of messages (where known) */
#define wippersnapper_i2c_v1_I2CBusInitRequest_size 39
#define wippersnapper_i2c_v1_I2CBusInitResponse_size 2
#define wippersnapper_i2c_v1_I2CBusSetFrequency_size 17
#define wippersnapper_i2c_v1_I2CBusScanRequest_size 52
#define wippersnapper_i2c_v1_I2CBusScanResponse_size 722
#define wippersnapper_i2c_v1_I2CDeviceSensorProperties_size 8
/* wippersnapper_i2c_v1_I2CDeviceInitRequests_size depends on runtime parameters */
#define wippersnapper_i2c_v1_I2CDeviceInitRequest_size 224
#define wippersnapper_i2c_v1_I2CDeviceInitResponse_size 8
#define wippersnapper_i2c_v1_I2CDeviceUpdateRequest_size 183
#define wippersnapper_i2c_v1_I2CDeviceUpdateResponse_size 8
#define wippersnapper_i2c_v1_I2CDeviceDeinitRequest_size 17
#define wippersnapper_i2c_v1_I2CDeviceDeinitResponse_size 8
#define wippersnapper_i2c_v1_SensorEvent_size    7
#define wippersnapper_i2c_v1_I2CDeviceEvent_size 141

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
