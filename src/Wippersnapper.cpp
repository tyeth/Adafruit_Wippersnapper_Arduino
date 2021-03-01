/*!
 * @file Wippersnapper.cpp
 *
 * @mainpage Adafruit Wippersnapper Wrapper
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's Wippersnapper wrapper for the
 * Arduino platform.  It is designed specifically to work with the
 * Adafruit IO+ Wippersnapper IoT platform.
 *
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 *
 * This library depends on <a href="https://github.com/adafruit/Adafruit_Sensor">
 * Adafruit_Sensor</a> being present on your system. Please make sure you have
 * installed the latest version before using this library.
 *
 * @section author Author
 *
 * Written by Brent Rubell for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "Wippersnapper.h"

ws_board_status_t Wippersnapper::_boardStatus;
uint16_t Wippersnapper::bufSize;
uint8_t Wippersnapper::_buffer[128];
char Wippersnapper:: _value[45];
timerDigitalInput Wippersnapper::_timersDigital[MAX_DIGITAL_TIMERS];
/**************************************************************************/
/*!
    @brief    Instantiates the Wippersnapper client object.
    @param    aio_username
              Adafruit IO Username.
    @param    aio_key
              Adafruit IO Active Key.
*/
/**************************************************************************/
Wippersnapper::Wippersnapper(const char *aio_username, const char *aio_key) {
    _mqtt = 0;     // MQTT Client object

    _username = aio_username;
    _key = aio_key;

    // TODO: Remove!
    _deviceId = "myDevice"; // Adafruit IO+ device name
    _hw_vid = 0;       // Hardware's usb vendor id
    _hw_pid = 0;       // Hardware's usb product id

    // Reserved MQTT Topics //
    _topic_description = 0;
    _topic_description_status = 0;
    _topic_signal_device = 0;
    _topic_signal_brkr = 0;

    // disable all timers
    for (int i = 0; i < MAX_DIGITAL_TIMERS; i++) {
        _timersDigital[i].timerInterval = -1;
    }

}

/**************************************************************************/
/*!
    @brief    Wippersnapper destructor
*/
/**************************************************************************/
Wippersnapper::~Wippersnapper() {
    // re-allocate topics
    free(_topic_description);
    free(_topic_signal_device);
    free(_topic_signal_brkr);
}

/**************************************************************************/
/*!
    @brief This function is the core of the createSignalRequest encoding process.
          It handles the top-level pb_field_t array manually, in order to encode
          a correct field tag before the message. The pointer to MsgType_fields
          array is used as an unique identifier for the message type.
*/
/**************************************************************************/
bool Wippersnapper::encode_unionmessage(pb_ostream_t *stream, const pb_msgdesc_t *messagetype, void *message)
{
    pb_field_iter_t iter;

    if (!pb_field_iter_begin(&iter, wippersnapper_signal_v1_CreateSignalRequest_fields, message))
        return false;
    do
    {
        if (iter.submsg_desc == messagetype)
        {
            if (!pb_encode_tag_for_field(stream, &iter))
                return false;
            return pb_encode_submessage(stream, messagetype, message);
        }
    } while (pb_field_iter_next(&iter));
    return false;
}


/// PIN API ///
/****************************************************************************/
/*!
    @brief    Configures a digital pin to behave as an input or an output.
*/
/****************************************************************************/
void initDigitalPin(wippersnapper_pin_v1_ConfigurePinRequest_Direction direction, uint8_t pinName) {
     if (direction == wippersnapper_pin_v1_ConfigurePinRequest_Direction_DIRECTION_OUTPUT) {
        WS_DEBUG_PRINT("Configured digital output pin on D"); WS_DEBUG_PRINTLN(pinName);
        pinMode(pinName, OUTPUT);
        digitalWrite(pinName, LOW); // initialize LOW
     }
     else if (direction == wippersnapper_pin_v1_ConfigurePinRequest_Direction_DIRECTION_INPUT) {
        WS_DEBUG_PRINT("Configuring digital input pin on D"); WS_DEBUG_PRINTLN(pinName);
        pinMode(pinName, INPUT);
     }
     else {
         WS_DEBUG_PRINTLN("ERROR: Invalid digital pin direction!");
     }
}

/****************************************************************************/
/*!
    @brief    "Releases" a previously configured digital pin
*/
/****************************************************************************/
void deinitDigitalPin(uint8_t pinName) {
    WS_DEBUG_PRINT("Deinitializing pin ");
    char cstr[16];
    itoa(pinName, cstr, 10);
    WS_DEBUG_PRINTLN(cstr);
    pinMode(pinName, INPUT); // hi-z
}

/**************************************************************************/
/*!
    @brief  High-level service which outputs to a digital pin.
*/
/**************************************************************************/
void digitalWriteSvc(uint8_t pinName, int pinValue) {
    WS_DEBUG_PRINT("Digital Pin Event: Set ");WS_DEBUG_PRINT(pinName);
    WS_DEBUG_PRINT(" to ");WS_DEBUG_PRINTLN(pinValue);
    digitalWrite(pinName, pinValue);
}

/****************************************************************************/
/*!
    @brief    Attaches a timer to a digital pin.
*/
/****************************************************************************/
void Wippersnapper::attachDigitalPinTimer(uint8_t pinName, float interval) {
    WS_DEBUG_PRINT("Attaching timer to pin D");WS_DEBUG_PRINTLN(pinName);
    // Interval is in seconds, cast it to long and convert it to milliseconds
    long interval_ms = (long)interval * 1000;
    WS_DEBUG_PRINT("Interval (ms):"); WS_DEBUG_PRINTLN(interval_ms);

    // attach a free timer to the pin
    for (int timerNum = 0; timerNum <= MAX_DIGITAL_TIMERS; timerNum++) {
        if (_timersDigital[timerNum].timerInterval == -1) {
            WS_DEBUG_PRINT("Allocating timer #");WS_DEBUG_PRINTLN(timerNum);
            // create a digital timer object
            timerDigitalInput timerPin = {pinName, interval_ms};
            // add new timer to array
            _timersDigital[timerNum] = timerPin;
            break;
        } else if (timerNum == MAX_DIGITAL_TIMERS) {
            WS_DEBUG_PRINTLN("ERROR: Unable to assign timer, maximum timers allocated");
        }
    }
}

/****************************************************************************/
/*!
    @brief    Detaches a timer from a digital pin
*/
/****************************************************************************/
void Wippersnapper::detachDigitalPinTimer(uint8_t pinName) {
    WS_DEBUG_PRINT("Freeing timer on pin D"); WS_DEBUG_PRINTLN(pinName);
    // find timer associated with pin
    for (int i; i <= MAX_DIGITAL_TIMERS; i++) {
        if(_timersDigital[i].timerInterval == pinName) {
            _timersDigital[pinName].timerInterval = -1; // reset timer
            _timersDigital[pinName].prvPinVal = 0; // reset prv. value
        }
    }
}

/****************************************************************************/
/*!
    @brief    High-level digitalRead service impl. which performs a
                digitalRead.
    @returns  pinVal
                Value of pin, either HIGH or LOW
*/
/****************************************************************************/
int digitalReadSvc(uint8_t pinName) {
    // Service using arduino `digitalRead`
    int pinVal = digitalRead(pinName);
    return pinVal;
}

/****************************************************************************/
/*!
    @brief    Encodes a PinEvents message, provided pinEvents.
*/
/****************************************************************************/
/* void Wippersnapper::encodePinEvents {
    WS_DEBUG_PRINTLN("Encoding PinEvents message...");
} */

// Thinking:
// could each timer hold a pinevent message that we can write into?
// could we just create pinevent fields within the timer instead?


// Adds a pinEvent to pinevents list
//void Wippersnapper::addPinEvent() {
//    WS_DEBUG_PRINT("Adding event to pinevent list...");
//}

// TODO: Create a signal message

/****************************************************************************/
/*!
    @brief    Encodes signal message into shared buffer.
    signalPayloadType: 
        1 = pin_events
    @returns  True if successful, False otherwise.
*/
/****************************************************************************/
bool Wippersnapper::encodeSignalMsg(uint8_t signalPayloadType){
    bool status;
    size_t message_length;
    pb_ostream_t stream;

    wippersnapper_signal_v1_CreateSignalRequest msg = wippersnapper_signal_v1_CreateSignalRequest_init_zero;

    if (signalPayloadType == 1) {
        msg.which_payload == wippersnapper_signal_v1_CreateSignalRequest_pin_events_tag;
        // todo: execute the callback to encodepineventlistmsg
        // todo: pass it the "msg"
    }
    else {
        WS_DEBUG_PRINTLN("ERROR: Signal payload type not found");
        return -1;
    }

    stream = pb_ostream_from_buffer(_buffer, bufSize);

    // encode the signal message
    status = pb_encode(&stream, wippersnapper_signal_v1_CreateSignalRequest_fields, &msg);
    message_length = stream.bytes_written;
    
    if (!status)
    {
        WS_DEBUG_PRINTLN("ERROR: Unable to encode signal message.");
        //printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        status = -1;
    }

    return status;
}


/****************************************************************************/
/*!
    @brief    Configures a pin according to a 
                wippersnapper_pin_v1_ConfigurePinRequest message.
    @param    pinMsg
              Pointer to a wippersnapper_pin_v1_ConfigurePinRequest message.
*/
/****************************************************************************/
bool Wippersnapper::configPinReq(wippersnapper_pin_v1_ConfigurePinRequest *pinMsg) {
    WS_DEBUG_PRINTLN("configPinReq");
    bool is_create = false;
    bool is_delete = false;

     // Check request type
    if (pinMsg->request_type == wippersnapper_pin_v1_ConfigurePinRequest_RequestType_REQUEST_TYPE_CREATE) {
        WS_DEBUG_PRINT("Initializing new pin ");WS_DEBUG_PRINTLN(pinMsg->pin_name);
        is_create = true;
    } else if (pinMsg->request_type == wippersnapper_pin_v1_ConfigurePinRequest_RequestType_REQUEST_TYPE_DELETE) {
        WS_DEBUG_PRINT("Deleting pin ");WS_DEBUG_PRINTLN(atoi(pinMsg->pin_name));
        is_delete = true;
    }

    char* pinName = pinMsg->pin_name + 1;

    if (is_create == true) { // initialize a new pin
        if (pinMsg->mode == wippersnapper_pin_v1_Mode_MODE_DIGITAL) {
            initDigitalPin(pinMsg->direction, atoi(pinName));
            // Check if direction requires a new timer
            if (pinMsg->direction == wippersnapper_pin_v1_ConfigurePinRequest_Direction_DIRECTION_INPUT) {
                // attach a new timer
                attachDigitalPinTimer(atoi(pinName), pinMsg->period);
            }
        }
        // TODO: else, check for analog pin, setAnalogPinMode() call
    }

    if (is_delete == true) { // delete a prv. initialized pin
        // check if pin has a timer
        if (pinMsg->direction == wippersnapper_pin_v1_ConfigurePinRequest_Direction_DIRECTION_INPUT)
            detachDigitalPinTimer(atoi(pinName));
        // deinitialize the digital pin
        deinitDigitalPin(atoi(pinName));
    }
    return true;
}

/**************************************************************************/
/*!
    @brief  Decodes repeated ConfigurePinRequests messages.
*/
/**************************************************************************/
bool Wippersnapper::cbDecodePinConfigMsg(pb_istream_t *stream, const pb_field_t *field, void **arg) {
    bool is_success = true;
    WS_DEBUG_PRINTLN("cbDecodePinConfigMsg");

    // pb_decode the stream into a pinReqMessage
    wippersnapper_pin_v1_ConfigurePinRequest pinReqMsg = wippersnapper_pin_v1_ConfigurePinRequest_init_zero;
    if (!pb_decode(stream, wippersnapper_pin_v1_ConfigurePinRequest_fields, &pinReqMsg)) {
        WS_DEBUG_PRINTLN("L191 ERROR: Could not decode CreateSignalRequest")
        is_success = false;
    }

    // Configure physical pin
    if (! configPinReq(&pinReqMsg)){
        WS_DEBUG_PRINTLN("Unable to configure pin");
        is_success = false;
    }

    // TODO: Freeup struct members
    return is_success;
}


/**************************************************************************/
/*!
    @brief  Decodes repeated PinEvents messages.
*/
/**************************************************************************/
bool Wippersnapper::cbDecodePinEventMsg(pb_istream_t *stream, const pb_field_t *field, void **arg) {
    bool is_success = true;
    WS_DEBUG_PRINTLN("cbDecodePinEventMsg");

    // Decode stream into a PinEvent
    wippersnapper_pin_v1_PinEvent pinEventMsg = wippersnapper_pin_v1_PinEvent_init_zero;
    if (!pb_decode(stream, wippersnapper_pin_v1_PinEvent_fields, &pinEventMsg)) {
        WS_DEBUG_PRINTLN("ERROR: Could not decode PinEvents")
        is_success = false;
    }

    char* pinName = pinEventMsg.pin_name + 1;
    if (pinEventMsg.pin_name[0] == 'D') { // digital pin event
        digitalWriteSvc(atoi(pinName), atoi(pinEventMsg.pin_value));
    }
    else if (pinEventMsg.pin_name[0] == 'A') { // analog pin event
        // TODO
        WS_DEBUG_PRINTLN("Analog pin event, Unimplemented!");
    }
    else {
        WS_DEBUG_PRINTLN("Unknown pinEvent:pinName!");
        is_success = false;
    }

    return is_success;
}

/**************************************************************************/
/*!
    @brief      Sets payload callbacks inside the signal message's
                submessage.
*/
/**************************************************************************/
bool Wippersnapper::cbSignalMsg(pb_istream_t *stream, const pb_field_t *field, void **arg) {
    bool is_success = true;
    WS_DEBUG_PRINTLN("cbSignalMsg");

    pb_size_t arr_sz = field->array_size;
    WS_DEBUG_PRINT("Sub-messages found: "); WS_DEBUG_PRINTLN(arr_sz);

    if (field->tag == wippersnapper_signal_v1_CreateSignalRequest_pin_configs_tag) {
        WS_DEBUG_PRINTLN("Signal Msg Tag: Pin Configuration");
        // array to store the decoded CreateSignalRequests data
        wippersnapper_pin_v1_ConfigurePinRequests msg = wippersnapper_pin_v1_ConfigurePinRequests_init_zero;
        // set up callback
        msg.list.funcs.decode = &Wippersnapper::cbDecodePinConfigMsg;
        msg.list.arg = field->pData;
        // decode each ConfigurePinRequest sub-message
        if (!pb_decode(stream, wippersnapper_pin_v1_ConfigurePinRequests_fields, &msg)) {
            WS_DEBUG_PRINTLN("ERROR: Could not decode CreateSign2alRequest")
            is_success = false;
        }
    }
    else if (field->tag == wippersnapper_signal_v1_CreateSignalRequest_pin_events_tag) {
        WS_DEBUG_PRINTLN("Signal Msg Tag: Pin Event");
        // array to store the decoded PinEvents data
        wippersnapper_pin_v1_PinEvents msg = wippersnapper_pin_v1_PinEvents_init_zero;
        // set up callback
        msg.list.funcs.decode = &Wippersnapper::cbDecodePinEventMsg;
        msg.list.arg = field->pData;
        // decode each PinEvents sub-message
        if (!pb_decode(stream, wippersnapper_pin_v1_PinEvents_fields, &msg)) {
            WS_DEBUG_PRINTLN("ERROR: Could not decode CreateSign2alRequest")
            is_success = false;
        }
    }
    else {
        WS_DEBUG_PRINTLN("ERROR: Unexpected signal msg tag.");
    }

    // once this is returned, pb_dec_submessage()
    // decodes the submessage contents.
    return is_success;
}

/**************************************************************************/
/*!
    @brief    Decodes a signal buffer protobuf message.
        NOTE: Should be executed in-order after a new _buffer is recieved.
    @param    encodedSignalMsg
              Encoded signal message.
    @return   true if successfully decoded signal message, false otherwise.
*/
/**************************************************************************/
bool Wippersnapper::decodeSignalMsg(wippersnapper_signal_v1_CreateSignalRequest *encodedSignalMsg) {
    bool is_success = true;
    WS_DEBUG_PRINTLN("decodeSignalMsg");

    /* Set up the payload callback, which will set up the callbacks for
    each oneof payload field once the field tag is known */
    encodedSignalMsg->cb_payload.funcs.decode = &Wippersnapper::cbSignalMsg;

    // decode the CreateSignalRequest, calls cbSignalMessage and assoc. callbacks
    pb_istream_t stream = pb_istream_from_buffer(_buffer, bufSize);
    if (!pb_decode(&stream, wippersnapper_signal_v1_CreateSignalRequest_fields, encodedSignalMsg)) {
        WS_DEBUG_PRINTLN("L285 ERROR: Could not decode CreateSignalRequest")
        is_success = false;
    }
    return is_success;
}

/**************************************************************************/
/*!
    @brief    Executes when signal topic receives a new message. Fills
                shared buffer with data from payload.
*/
/**************************************************************************/
void Wippersnapper::cbSignalTopic(char *data, uint16_t len) {
    WS_DEBUG_PRINTLN("* NEW message on signal topic");
    WS_DEBUG_PRINT(len);WS_DEBUG_PRINTLN(" bytes.");
    // zero-out buffer contents
    memset(_buffer, 0, sizeof(_buffer));
    // copy data to buffer
    memcpy(_buffer, data, len);
    bufSize = len;
}

/**************************************************************************/
/*!
    @brief    Provides void decodeRegMsg callback with a
                wippersnapper object
*/
/**************************************************************************/
Wippersnapper* object_which_will_handle_signal;
static void cbDescStatus_Wrapper(char *data, uint16_t len) {
    object_which_will_handle_signal->_registerBoard->decodeRegMsg(data, len);
}

/**************************************************************************/
/*!
    @brief    Generates Wippersnapper feeds.
*/
/**************************************************************************/
void Wippersnapper::generate_feeds() {

    // Check and set network iface UID
    setUID();

    // Move the top 3 bytes from the UID
    for (int i = 5; i > 2; i--) {
        _uid[6-1-i]  = _uid[i];
    }
    
    snprintf(sUID, sizeof(sUID), "%02d%02d%02d",_uid[0], _uid[1], _uid[2]);

    // Assign board type, defined at compile-time
    _boardId = BOARD_ID;
    // Create device UID
    _device_uid = (char *)malloc(sizeof(char) + strlen("io-wipper-") + strlen(_boardId) + strlen(sUID));
    strcpy(_device_uid, "io-wipper-");
    strcat(_device_uid, _boardId);
    strcat(_device_uid, sUID);
    //self._device_uid = "io-wipper-{}{}".format(self._board.name, str(mac_addr))

    // Create MQTT client object
    setupMQTTClient(_device_uid);

    // Assign board type info
    // TODO: Do we still need this?
    _hw_vid = USB_VID;
    _hw_pid = USB_PID;

    // allocate memory for reserved topics
    _topic_description = (char *)malloc(sizeof(char) * strlen(_username) \
    + strlen("/wprsnpr") + strlen(TOPIC_DESCRIPTION) + strlen("status") + 1);

    // Check-in status topic
    _topic_description_status = (char *)malloc(sizeof(char) * strlen(_username) + \
    + strlen("/wprsnpr/") + strlen(_device_uid) + strlen(TOPIC_DESCRIPTION) + \
    strlen("status") + strlen("broker") + 1);

    _topic_signal_device = (char *)malloc(sizeof(char) * strlen(_username) + \
    + strlen("/") + strlen(_device_uid) +  strlen("/wprsnpr/") + \
    strlen(TOPIC_SIGNALS) + strlen("device") + 1);

    _topic_signal_brkr = (char *)malloc(sizeof(char) * strlen(_username) + \
    + strlen("/") + strlen(_device_uid) +  strlen("/wprsnpr/") + \
    strlen(TOPIC_SIGNALS) + strlen("broker") + 1);

    // Build description check-in topic
    if (_topic_description) {
        strcpy(_topic_description, _username);
        strcat(_topic_description, "/wprsnpr");
        strcat(_topic_description, TOPIC_DESCRIPTION);
        strcat(_topic_description, "status");
    } else { // malloc failed
        _topic_description  = 0;
    }


    // build description status topic
    if (_topic_description_status) {
        strcpy(_topic_description_status, _username);
        strcat(_topic_description_status, "/wprsnpr/");
        strcat(_topic_description_status, _device_uid);
        strcat(_topic_description_status, TOPIC_DESCRIPTION);
        strcat(_topic_description_status, "status");
        strcat(_topic_description_status, "/broker");
    } else { // malloc failed
        _topic_description_status = 0;
    }

    // build incoming signal topic
    if (_topic_signal_device) {
        strcpy(_topic_signal_device, _username);
        strcat(_topic_signal_device, "/wprsnpr/");
        strcat(_topic_signal_device, _device_uid);
        strcat(_topic_signal_device, TOPIC_SIGNALS);
        strcat(_topic_signal_device, "device");
    } else { // malloc failed
        _topic_signal_device = 0;
    }

    // build signals outgoing topic
    if (_topic_signal_brkr) {
        strcpy(_topic_signal_brkr, _username);
        strcat(_topic_signal_brkr, "/wprsnpr/");
        strcat(_topic_signal_brkr, _device_uid);
        strcat(_topic_signal_brkr, TOPIC_SIGNALS);
        strcat(_topic_signal_brkr, "broker");
    } else { // malloc failed
        _topic_signal_brkr = 0;
    }

}

/**************************************************************************/
/*!
    @brief    Connects to Adafruit IO+ Wippersnapper broker.
*/
/**************************************************************************/
void Wippersnapper::connect() {
    WS_DEBUG_PRINTLN("connect()");
    _status = WS_IDLE;
    _boardStatus = WS_BOARD_DEF_IDLE;

    WS_DEBUG_PRINTLN("Generating feeds...");
    generate_feeds();

    // Subscription to listen to commands from the server
    _topic_signal_brkr_sub = new Adafruit_MQTT_Subscribe(_mqtt, _topic_signal_brkr);
    _topic_signal_brkr_sub->setCallback(cbSignalTopic);
    _mqtt->subscribe(_topic_signal_brkr_sub);

    // Publish to outgoing commands channel, server listens to this sub-topic
    _topic_signal_device_pub = new Adafruit_MQTT_Publish(_mqtt, _topic_signal_device);

    // Create a subscription to the description status response topic
    _topic_description_sub = new Adafruit_MQTT_Subscribe(_mqtt, _topic_description_status);

    // set callback and subscribe
    _topic_description_sub->setCallback(cbDescStatus_Wrapper);
    _mqtt->subscribe(_topic_description_sub);

    // Connect network interface
    WS_DEBUG_PRINT("Connecting to WiFi...");
    _connect();
    WS_DEBUG_PRINTLN("WiFi Connected!");

    // Wait for connection to broker
    WS_DEBUG_PRINT("Connecting to Wippersnapper MQTT...");
    while (status() < WS_CONNECTED) {
        WS_DEBUG_PRINT(".");
        delay(500);
    }
    WS_DEBUG_PRINTLN("MQTT Connected!");

    WS_DEBUG_PRINTLN("Registering Board...")
    if (!registerBoard(10)) {
        WS_DEBUG_PRINTLN("Unable to register board with Wippersnapper.");
        for(;;);
    }
    WS_DEBUG_PRINTLN("Registered board with Wippersnapper.");

}

/**************************************************************************/
/*!
    @brief    Disconnects from Adafruit IO+ Wippersnapper.
*/
/**************************************************************************/
void Wippersnapper::disconnect() {
    _disconnect();
}

/**************************************************************************/
/*!
    @brief    Checks and handles network interface connection.
*/
/**************************************************************************/
ws_status_t Wippersnapper::checkNetworkConnection(uint32_t timeStart) {
    if (status() < WS_NET_CONNECTED) {
        WS_DEBUG_PRINTLN("connection failed, reconnecting...");
        unsigned long startRetry = millis();
        while (status() < WS_CONNECTED) { // return an error on timeout
            if (millis() - startRetry > 5000) {
                return status();
            }
            delay(500);
        }

        

/*         if (!sendGetHardwareDescription(10)){
            // TODO: get error types back from function instead of bool, verify against resp.
            return status();
        } */
    }
    return status();
}

/**************************************************************************/
/*!
    @brief    Handles MQTT broker connection.
*/
/**************************************************************************/
ws_status_t Wippersnapper::checkMQTTConnection(uint32_t timeStart) {
    // Check network connection
    if (mqttStatus() != WS_CONNECTED) {
        return status();
    }
    // Ping if > keepAlive interval
    if (millis() > (_prv_ping + WS_KEEPALIVE_INTERVAL)) {
        _mqtt->ping();
        _prv_ping = millis();
    }

    return status();
}

/**************************************************************************/
/*!
    @brief    Handles MQTT messages on signal topic until timeout.
    @param    timeout
                timeout in milliseconds.
*/
/**************************************************************************/
bool Wippersnapper::processSignalMessages(int16_t timeout) {
    _mqtt->processPackets(timeout);

    if (_buffer[0] != 0) { // check if buffer set by signal topic callback
        // Empty struct for storing the signal message
        _incomingSignalMsg = wippersnapper_signal_v1_CreateSignalRequest_init_zero;

        // Attempt to decode a signal message
        if (! decodeSignalMsg(&_incomingSignalMsg)) {
            WS_DEBUG_PRINTLN("ERROR: Failed to decode signal message");
            return false;
        }
        memset(_buffer, 0, sizeof(_buffer));
    }

    return true;
}

//bool encodePinEventList(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {
//    WS_DEBUG_PRINTLN("Adding a pinEvent to pinEventList");

//}


/**************************************************************************/
/*!
    @brief    Processes incoming commands and handles network connection.
*/
/**************************************************************************/
ws_status_t Wippersnapper::run() {
    uint32_t curTime = millis();

    //WS_DEBUG_PRINTLN("EXEC: loop'");

    // Check network connection
    checkNetworkConnection(curTime); // TODO: handle this better
    // Check and handle MQTT connection
    checkMQTTConnection(curTime); // TODO: handle this better

    // Create a new signal message
    _outgoingSignalMsg = wippersnapper_signal_v1_CreateSignalRequest_init_zero;
    // Process digital timers
    // todo: move this to header
    wippersnapper_pin_v1_PinEvents pinEventList = wippersnapper_pin_v1_PinEvents_init_zero;
    // TODO: Only check active timers instead of all timers?
    for (int i = 0; i < MAX_DIGITAL_TIMERS; i++) {
        if (_timersDigital[i].timerInterval > -1L) { // validate if timer is enabled
            // Check if timer executes on a time period
            //WS_DEBUG_PRINTLN("Checking timer");
            if (curTime - _timersDigital[i].timerIntervalPrv > _timersDigital[i].timerInterval) {
                // service the timer
                WS_DEBUG_PRINT("Timer executed on digital pin D");WS_DEBUG_PRINTLN(_timersDigital[i].pinName);
                // sample the pin
                int pinVal = digitalReadSvc(_timersDigital[i].pinName);
                // only send on-change
                if (pinVal != _timersDigital[i].prvPinVal) {
                    // Create and fill a new pinEvent msg
                    wippersnapper_pin_v1_PinEvent pinEvent = wippersnapper_pin_v1_PinEvent_init_zero;
                    // We're using a digital timer here, so append "D" onto the numeric pin name
                    // TODO: in the future, this can be optimized within PinEvent's struct
                    sprintf(pinEvent.pin_name , "D%d", _timersDigital[i].pinName);
                    sprintf(pinEvent.pin_value, "%d", pinVal);
                    pinEvent.mode = wippersnapper_pin_v1_Mode_MODE_DIGITAL;
                    // TODO: Start encoding the pinevent list here.
                    //pinEventList.list.funcs.encode = 
                }
                // reset the timer
                _timersDigital[i].timerIntervalPrv = curTime;
            }
            // Check if timer executes on a state change
            else if (_timersDigital[i].timerInterval == 0) {
                // read pin
                int pinVal = digitalReadSvc(_timersDigital[i].pinName);
                // only send on-change
                if (pinVal != _timersDigital[i].prvPinVal) {
                    // Encode the pin's new value
                    // Send the pin's new value
                    // TODO
                    // Set state
                    _timersDigital[i].prvPinVal = pinVal;
                }
            }
        }

    }

    // Process all incoming packets from Wippersnapper MQTT Broker
    processSignalMessages(100);

    return status();
}

/**************************************************************************/
/*!
    @brief    Sends board description message to Wippersnapper
*/
/**************************************************************************/
bool Wippersnapper::registerBoard(uint8_t retries=10) {
    WS_DEBUG_PRINTLN("registerBoard()");
    // Create new board
    _registerBoard = new Wippersnapper_Registration(this);
    // Run the FSM for the registration process
    return _registerBoard->processRegistration();
}

/**************************************************************************/
/*!
    @brief    Returns the network status.
    @return   Wippersnapper network status.
*/
/**************************************************************************/
ws_status_t Wippersnapper::status() {
  ws_status_t net_status = networkStatus();

  // if we aren't connected, return network status
  if (net_status != WS_NET_CONNECTED) {
    _status = net_status;
    return _status;
  }

  // check mqtt status and return
  _status = mqttStatus();
  return _status;
}

/**************************************************************************/
/*!
    @brief    Returns the board definition status
    @return   Wippersnapper board definition status
*/
/**************************************************************************/
ws_board_status_t Wippersnapper::getBoardStatus() {
    return _boardStatus;
}

/**************************************************************************/
/*!
    @brief    Checks connection status with Adafruit IO's MQTT broker.
    @return   True if connected, otherwise False.
*/
/**************************************************************************/
ws_status_t Wippersnapper::mqttStatus() {
  // if the connection failed,
  // return so we don't hammer IO
  if (_status == WS_CONNECT_FAILED) {
    WS_DEBUG_PRINT("mqttStatus() failed to connect");
    WS_DEBUG_PRINTLN(_mqtt->connectErrorString(_status));
    return _status;
  }

  if (_mqtt->connected())
    return WS_CONNECTED;

  // prevent fast reconnect attempts, except for the first time through
  if (_last_mqtt_connect == 0 ||
      millis() - _last_mqtt_connect > WS_KEEPALIVE_INTERVAL) {
    _last_mqtt_connect = millis();
    switch (_mqtt->connect(_username, _key)) {
    case 0:
      return WS_CONNECTED;
    case 1: // invalid mqtt protocol
    case 2: // client id rejected
    case 4: // malformed user/pass
    case 5: // unauthorized
      return WS_CONNECT_FAILED;
    case 3: // mqtt service unavailable
    case 6: // throttled
    case 7: // banned -> all MQTT bans are temporary, so eventual retry is
            // permitted
      // delay to prevent fast reconnects and fast returns (backward
      // compatibility)
        delay(WS_KEEPALIVE_INTERVAL);
      return WS_DISCONNECTED;
    default:
      return WS_DISCONNECTED;
    }
  }
  return WS_DISCONNECTED;
}


/**************************************************************************/
/*!
    @brief    Provide status explanation strings.
    @return   A pointer to the status string, _status. _status is the BC status
   value
*/
/**************************************************************************/
const __FlashStringHelper *Wippersnapper::statusText() {
  switch (_status) {
    // CONNECTING
    case WS_IDLE:
        return F("Idle. Waiting for connect to be called...");
    case WS_NET_DISCONNECTED:
        return F("Network disconnected.");
    case WS_DISCONNECTED:
        return F("Disconnected from Wippersnapper.");
    // FAILURE
    case WS_NET_CONNECT_FAILED:
        return F("Network connection failed.");
    case WS_CONNECT_FAILED:
        return F("Wippersnapper connection failed.");
    case WS_FINGERPRINT_INVALID:
        return F("Wippersnapper SSL fingerprint verification failed.");
    case WS_AUTH_FAILED:
        return F("Wippersnapper authentication failed.");
    // SUCCESS
    case WS_NET_CONNECTED:
        return F("Network connected.");
    case WS_CONNECTED:
        return F("Wippersnapper connected.");
    case WS_CONNECTED_INSECURE:
        return F("Wippersnapper connected. **THIS CONNECTION IS INSECURE** SSL/TLS "
                "not supported for this platform.");
    case WS_FINGERPRINT_UNSUPPORTED:
        return F("Wippersnapper connected over SSL/TLS. Fingerprint verification "
                "unsupported.");
    case WS_FINGERPRINT_VALID:
        return F("Wippersnapper connected over SSL/TLS. Fingerprint valid.");
    default:
        return F("Unknown status code");
  }
}
