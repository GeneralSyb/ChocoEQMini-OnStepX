// -------------------------------------------------------------------------------------------------
// Pin map for OnStep MaxESP4 (ESP32S)
#pragma once

#if defined(ESP32)

// Serial0: USB to Serial
// Serial1: RX18 Pin GPIO17, TX1 Pin GPIO9. Is for motor drivers
// Serial2: unused

#if SERIAL_A_BAUD_DEFAULT != OFF
  #define SERIAL_A              Serial
#endif
#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial2
#endif

// Use the following settings for any TMC UART driver (TMC2209) that may be present
#if defined(STEP_DIR_TMC_UART_PRESENT) || defined(SERVO_TMC2209_PRESENT)
  #define SERIAL_TMC_HARDWARE_UART
  #define SERIAL_TMC            Serial1          // Use a single hardware serial port to up to four drivers
  #define SERIAL_TMC_BAUD       115200           // Baud rate
  #define SERIAL_TMC_RX         18               // Recieving data
  #define SERIAL_TMC_TX         17                // Transmit data
  #define SERIAL_TMC_ADDRESS_MAP(x) ((x==4)?2 : x) // Axis1(0) is 0, Axis2(1) is 1, Axis3(2) is 2, Axis4(3) is 3, Axis5(4) is 2
#endif

// Specify the ESP32 I2C pins
#define I2C_SDA_PIN             35
#define I2C_SCL_PIN             36

// The multi-purpose pins (Aux3..Aux8 can be analog pwm/dac if supported)
#define AUX2_PIN                OFF               // M3 pin TMC UART RX
#define AUX3_PIN                OFF               // Home SW for Axis1
#define AUX4_PIN                OFF               // Home SW for Axis2
#define AUX5_PIN                OFF                // TX0 main USB, etc.
#define AUX6_PIN                OFF                // RX0 main USB, etc.
#define AUX7_PIN                OFF               // Limit SW, PPS, etc.
#define AUX8_PIN                OFF               // 1-Wire, Status LED, Reticle LED, Tone, etc.

// Misc. pins
#ifndef ONE_WIRE_PIN
  #define ONE_WIRE_PIN          AUX8_PIN         // Default Pin for OneWire bus
#endif

// The PEC index sense is a logic level input, resets the PEC index on rising edge then waits for 60 seconds before allowing another reset
#ifndef PEC_SENSE_PIN
  #define PEC_SENSE_PIN         OFF               // [input only 36] PEC Sense, analog (A0) or digital (GPIO36)
#endif

// The status LED w/ 4.7k resistor in series to limit the current to the LED
#ifdef STATUS_LED_ON_STATE
  #undef STATUS_LED_ON_STATE
#endif
#define STATUS_LED_ON_STATE HIGH
#ifndef STATUS_LED_PIN
  #define STATUS_LED_PIN        47               // Default LED Anode (+)
#endif
#ifdef MOUNT_LED_ON_STATE
  #undef MOUNT_LED_ON_STATE
#endif
#define MOUNT_LED_ON_STATE      HIGH
#define MOUNT_LED_PIN           STATUS_LED_PIN   // Default LED Anode (+)
#ifndef RETICLE_LED_PIN
  #define RETICLE_LED_PIN       AUX8_PIN         // Default LED Cathode (-)
#endif

// For a piezo buzzer
#ifndef STATUS_BUZZER_PIN
  #define STATUS_BUZZER_PIN     OFF               // [must be low at boot 12] Tone
#endif

// The PPS pin is a 3.3V logic input, OnStep measures time between rising edges and adjusts the internal sidereal clock frequency
#ifndef PPS_SENSE_PIN
  #define PPS_SENSE_PIN         AUX7_PIN         // PPS time source, GPS for example
#endif

// The limit switch sense is a logic level input normally pull high (2k resistor,) shorted to ground it stops gotos/tracking
#ifndef LIMIT_SENSE_PIN
  #define LIMIT_SENSE_PIN       AUX7_PIN
#endif

#define SHARED_DIRECTION_PINS                    // Hint that the direction pins are shared
#define SHARED_ENABLE_PIN       5                // Hint that the enable pins are shared

// Axis1 RA/Azm step/dir driver
#define AXIS1_ENABLE_PIN        SHARED           // Enable pin control
#define AXIS1_M0_PIN            OFF              // hardwired for TMC UART address 0
#define AXIS1_M1_PIN            OFF              // hardwired for TMC UART address 0
#define AXIS1_M2_PIN            OFF              // UART TX
#define AXIS1_M3_PIN            OFF              // UART RX
#define AXIS1_STEP_PIN          6
#define AXIS1_DIR_PIN           7                // [must be high at boot 0]
#ifndef AXIS1_SENSE_HOME_PIN
  #define AXIS1_SENSE_HOME_PIN  AUX3_PIN
#endif

// Axis2 Dec/Alt step/dir driver
#define AXIS2_ENABLE_PIN        SHARED
#define AXIS2_M0_PIN            OFF              // hardwired for TMC UART address 1
#define AXIS2_M1_PIN            OFF              // hardwired for TMC UART address 1
#define AXIS2_M2_PIN            OFF              // N/C
#define AXIS2_M3_PIN            OFF              // UART RX
#define AXIS2_STEP_PIN          8
#define AXIS2_DIR_PIN           9
#ifndef AXIS2_SENSE_HOME_PIN
  #define AXIS2_SENSE_HOME_PIN  AUX4_PIN
#endif
#ifndef AXIS2_ENCODER_B_PIN
  #define AXIS2_ENCODER_B_PIN   AUX2_PIN
#endif

// For rotator stepper driver
#define AXIS3_ENABLE_PIN        SHARED
#define AXIS3_M0_PIN            OFF              // hardwired for TMC UART address 2
#define AXIS3_M1_PIN            OFF              // hardwired for TMC UART address 2
#define AXIS3_M2_PIN            OFF              // N/C
#define AXIS3_M3_PIN            OFF              // UART RX
#define AXIS3_STEP_PIN          OFF                // [must be low at boot 2]
#define AXIS3_DIR_PIN           OFF

// For focuser1 stepper driver
#define AXIS4_ENABLE_PIN        SHARED
#define AXIS4_M0_PIN            OFF              // hardwired for TMC UART address 3
#define AXIS4_M1_PIN            OFF              // hardwired for TMC UART address 3
#define AXIS4_M2_PIN            OFF              // N/C
#define AXIS4_M3_PIN            OFF              // UART RX
#define AXIS4_STEP_PIN          OFF
#define AXIS4_DIR_PIN           OFF

// For focuser2 stepper driver
#define AXIS5_ENABLE_PIN        SHARED
#define AXIS5_M0_PIN            OFF              // hardwired for TMC UART address 2
#define AXIS5_M1_PIN            OFF              // hardwired for TMC UART address 2
#define AXIS5_M2_PIN            OFF              // N/C
#define AXIS5_M3_PIN            OFF              // UART RX
#define AXIS5_STEP_PIN          OFF
#define AXIS5_DIR_PIN           OFF

// ST4 interface
#define ST4_RA_W_PIN            OFF               // [input only 34] ST4 RA- West
#define ST4_DEC_S_PIN           OFF               // ST4 DE- South
#define ST4_DEC_N_PIN           OFF               // ST4 DE+ North
#define ST4_RA_E_PIN            OFF               // [input only 35] ST4 RA+ East

#else
#error "Wrong processor for this configuration!"

#endif
