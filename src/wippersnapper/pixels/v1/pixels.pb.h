/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5-dev at Wed Sep  6 18:22:09 2023. */

#ifndef PB_WIPPERSNAPPER_PIXELS_V1_WIPPERSNAPPER_PIXELS_V1_PIXELS_PB_H_INCLUDED
#define PB_WIPPERSNAPPER_PIXELS_V1_WIPPERSNAPPER_PIXELS_V1_PIXELS_PB_H_INCLUDED
#include <pb.h>
#include "nanopb/nanopb.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _wippersnapper_pixels_v1_PixelsType {
    wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_UNSPECIFIED = 0,
    wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_NEOPIXEL = 1,
    wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_DOTSTAR = 2
} wippersnapper_pixels_v1_PixelsType;

typedef enum _wippersnapper_pixels_v1_PixelsOrder {
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_UNSPECIFIED = 0,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_GRB = 1,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_GRBW = 2,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_RGB = 3,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_RGBW = 4,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_BRG = 5,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_RBG = 6,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_GBR = 7,
    wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_BGR = 8
} wippersnapper_pixels_v1_PixelsOrder;

/* Struct definitions */
typedef struct _wippersnapper_pixels_v1_PixelsCreateRequest {
    wippersnapper_pixels_v1_PixelsType pixels_type;
    uint32_t pixels_num;
    wippersnapper_pixels_v1_PixelsOrder pixels_ordering;
    uint32_t pixels_brightness;
    char pixels_pin_neopixel[6];
    char pixels_pin_dotstar_data[6];
    char pixels_pin_dotstar_clock[6];
} wippersnapper_pixels_v1_PixelsCreateRequest;

typedef struct _wippersnapper_pixels_v1_PixelsCreateResponse {
    bool is_success;
    char pixels_pin_data[6];
} wippersnapper_pixels_v1_PixelsCreateResponse;

typedef struct _wippersnapper_pixels_v1_PixelsDeleteRequest {
    wippersnapper_pixels_v1_PixelsType pixels_type;
    char pixels_pin_data[6];
} wippersnapper_pixels_v1_PixelsDeleteRequest;

typedef struct _wippersnapper_pixels_v1_PixelsWriteRequest {
    wippersnapper_pixels_v1_PixelsType pixels_type;
    char pixels_pin_data[6];
    uint32_t pixels_color;
} wippersnapper_pixels_v1_PixelsWriteRequest;


/* Helper constants for enums */
#define _wippersnapper_pixels_v1_PixelsType_MIN wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_UNSPECIFIED
#define _wippersnapper_pixels_v1_PixelsType_MAX wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_DOTSTAR
#define _wippersnapper_pixels_v1_PixelsType_ARRAYSIZE ((wippersnapper_pixels_v1_PixelsType)(wippersnapper_pixels_v1_PixelsType_PIXELS_TYPE_DOTSTAR+1))

#define _wippersnapper_pixels_v1_PixelsOrder_MIN wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_UNSPECIFIED
#define _wippersnapper_pixels_v1_PixelsOrder_MAX wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_BGR
#define _wippersnapper_pixels_v1_PixelsOrder_ARRAYSIZE ((wippersnapper_pixels_v1_PixelsOrder)(wippersnapper_pixels_v1_PixelsOrder_PIXELS_ORDER_BGR+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define wippersnapper_pixels_v1_PixelsCreateRequest_init_default {_wippersnapper_pixels_v1_PixelsType_MIN, 0, _wippersnapper_pixels_v1_PixelsOrder_MIN, 0, "", "", ""}
#define wippersnapper_pixels_v1_PixelsCreateResponse_init_default {0, ""}
#define wippersnapper_pixels_v1_PixelsDeleteRequest_init_default {_wippersnapper_pixels_v1_PixelsType_MIN, ""}
#define wippersnapper_pixels_v1_PixelsWriteRequest_init_default {_wippersnapper_pixels_v1_PixelsType_MIN, "", 0}
#define wippersnapper_pixels_v1_PixelsCreateRequest_init_zero {_wippersnapper_pixels_v1_PixelsType_MIN, 0, _wippersnapper_pixels_v1_PixelsOrder_MIN, 0, "", "", ""}
#define wippersnapper_pixels_v1_PixelsCreateResponse_init_zero {0, ""}
#define wippersnapper_pixels_v1_PixelsDeleteRequest_init_zero {_wippersnapper_pixels_v1_PixelsType_MIN, ""}
#define wippersnapper_pixels_v1_PixelsWriteRequest_init_zero {_wippersnapper_pixels_v1_PixelsType_MIN, "", 0}

/* Field tags (for use in manual encoding/decoding) */
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_type_tag 1
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_num_tag 2
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_ordering_tag 3
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_brightness_tag 4
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_pin_neopixel_tag 5
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_pin_dotstar_data_tag 6
#define wippersnapper_pixels_v1_PixelsCreateRequest_pixels_pin_dotstar_clock_tag 7
#define wippersnapper_pixels_v1_PixelsCreateResponse_is_success_tag 1
#define wippersnapper_pixels_v1_PixelsCreateResponse_pixels_pin_data_tag 2
#define wippersnapper_pixels_v1_PixelsDeleteRequest_pixels_type_tag 1
#define wippersnapper_pixels_v1_PixelsDeleteRequest_pixels_pin_data_tag 2
#define wippersnapper_pixels_v1_PixelsWriteRequest_pixels_type_tag 1
#define wippersnapper_pixels_v1_PixelsWriteRequest_pixels_pin_data_tag 2
#define wippersnapper_pixels_v1_PixelsWriteRequest_pixels_color_tag 3

/* Struct field encoding specification for nanopb */
#define wippersnapper_pixels_v1_PixelsCreateRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    pixels_type,       1) \
X(a, STATIC,   SINGULAR, UINT32,   pixels_num,        2) \
X(a, STATIC,   SINGULAR, UENUM,    pixels_ordering,   3) \
X(a, STATIC,   SINGULAR, UINT32,   pixels_brightness,   4) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_neopixel,   5) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_dotstar_data,   6) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_dotstar_clock,   7)
#define wippersnapper_pixels_v1_PixelsCreateRequest_CALLBACK NULL
#define wippersnapper_pixels_v1_PixelsCreateRequest_DEFAULT NULL

#define wippersnapper_pixels_v1_PixelsCreateResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     is_success,        1) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_data,   2)
#define wippersnapper_pixels_v1_PixelsCreateResponse_CALLBACK NULL
#define wippersnapper_pixels_v1_PixelsCreateResponse_DEFAULT NULL

#define wippersnapper_pixels_v1_PixelsDeleteRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    pixels_type,       1) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_data,   2)
#define wippersnapper_pixels_v1_PixelsDeleteRequest_CALLBACK NULL
#define wippersnapper_pixels_v1_PixelsDeleteRequest_DEFAULT NULL

#define wippersnapper_pixels_v1_PixelsWriteRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    pixels_type,       1) \
X(a, STATIC,   SINGULAR, STRING,   pixels_pin_data,   2) \
X(a, STATIC,   SINGULAR, UINT32,   pixels_color,      3)
#define wippersnapper_pixels_v1_PixelsWriteRequest_CALLBACK NULL
#define wippersnapper_pixels_v1_PixelsWriteRequest_DEFAULT NULL

extern const pb_msgdesc_t wippersnapper_pixels_v1_PixelsCreateRequest_msg;
extern const pb_msgdesc_t wippersnapper_pixels_v1_PixelsCreateResponse_msg;
extern const pb_msgdesc_t wippersnapper_pixels_v1_PixelsDeleteRequest_msg;
extern const pb_msgdesc_t wippersnapper_pixels_v1_PixelsWriteRequest_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define wippersnapper_pixels_v1_PixelsCreateRequest_fields &wippersnapper_pixels_v1_PixelsCreateRequest_msg
#define wippersnapper_pixels_v1_PixelsCreateResponse_fields &wippersnapper_pixels_v1_PixelsCreateResponse_msg
#define wippersnapper_pixels_v1_PixelsDeleteRequest_fields &wippersnapper_pixels_v1_PixelsDeleteRequest_msg
#define wippersnapper_pixels_v1_PixelsWriteRequest_fields &wippersnapper_pixels_v1_PixelsWriteRequest_msg

/* Maximum encoded size of messages (where known) */
#define wippersnapper_pixels_v1_PixelsCreateRequest_size 37
#define wippersnapper_pixels_v1_PixelsCreateResponse_size 9
#define wippersnapper_pixels_v1_PixelsDeleteRequest_size 9
#define wippersnapper_pixels_v1_PixelsWriteRequest_size 15

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
