/** A utility to get the arduino to print what its receiving from the serial
 * verbatim using hex codes
 */

#define DEBUG 1
#define TERMINAL_SERIAL_BAUD 9600
#define DEVICE_SERIAL_BAUD 9600

#define TOKENS_PER_LINE 18
#define TOKENS_PER_SEPERATOR 9

#define ENDL "\r\n"

#define P(name) static const unsigned char name[] PROGMEM

/* The hardware serial is used for communicating with the computer, a software
 * one will be needed to interface with the device unless you're using a mega.
 */
#include <SoftwareSerial.h>
#include <stdarg.h>

P(TEST_MESSAGE0) = "this is a test or something %d" ENDL;

P(TEST_TOKEN) = "%02X ";
P(TEST_NEW_LINE) = "%08lu ";
P(TEST_END_LINE) = ENDL;
P(TEST_SEPERATOR) = "| ";

// Local definitions
void aprintf( Stream* input, const prog_uint8_t* fmt, ... );

SoftwareSerial device(2, 3);

uint32_t loop_count = 0;
uint8_t line_token_count = 0;

uint8_t grab = '\0';

void setup() {
    Serial.begin(TERMINAL_SERIAL_BAUD);
    Serial.println("Starting program");

    device.begin(DEVICE_SERIAL_BAUD);
    aprintf( &Serial, TEST_NEW_LINE, loop_count++ );
}

void loop() {
    /*aprintf( &Serial, TEST_MESSAGE0, 9 );*/

    if( device.available() ) grab = (uint8_t)device.read();
    if( grab != '\0' ) {

        if( line_token_count == TOKENS_PER_SEPERATOR ) {
            aprintf( &Serial, TEST_SEPERATOR );
        } else if( line_token_count == TOKENS_PER_LINE ) {
            aprintf( &Serial, TEST_END_LINE );
            aprintf( &Serial, TEST_NEW_LINE, (long unsigned)loop_count++ );
            line_token_count = 0;
        }

        aprintf( &Serial, TEST_TOKEN, grab );
        line_token_count++;
        grab = '\0';
    }
}

void aprintf( Stream* input, const prog_uint8_t* fmt, ... ) {
    char tmp[80];

    va_list args;
    va_start( args, fmt );
    vsnprintf_P( tmp, 80, (const prog_char*)fmt, args );
    va_end( args );

    input->print( tmp );
}
