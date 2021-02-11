/*!
 * @file Wippersnapper_Checkin.h
 *
 * This file provides protocol buffer decoders for the Wippersnapper
 * protocol API.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Brent Rubell for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef WIPPERSNAPPER_REGISTRATION_H
#define WIPPERSNAPPER_REGISTRATION_H

#include <Wippersnapper.h>

// forward declaration
class Wippersnapper;

class Wippersnapper_Registration {
    public:
        Wippersnapper_Registration(Wippersnapper *ws);
        ~Wippersnapper_Registration();

        void set_machine_name(const char *machine_name);
        void set_uid(int32_t uid);

        bool encode_description();
        void publish_description();
        bool validate_description(int retries);

    private:
        uint8_t _message_buffer[128];
        size_t _message_len;
        bool _status;

        pb_ostream_t _msg_stream;

        // struct for description msg.
        //wippersnapper_description_v1_CreateDescriptionRequest _message;

        // Description message contents
        const char * _machine_name;
        int32_t _uid;

        Wippersnapper *_ws; // instance of Wippersnapper
};

#endif // WIPPERSNAPPER_REGISTRATION_H