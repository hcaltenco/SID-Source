/* Simple USB Keyboard Example
 Teensy becomes a USB to Serial converter
 http://dorkbotpdx.org/blog/paul/teensy_as_benito_at_57600_baud
 
 You must select Serial from the "Tools > USB Type" menu
 
 This example code is in the public domain.
 */

unsigned long midi_baud = 31250;  // MIDI is UART @ 31.250kHz, 1 start, 8 data, 1 stop, 0 parity bits

unsigned long usb_baud = 57600;
HardwareSerial Uart = HardwareSerial();
const int reset_pin = 4;
const int led_pin = 11;  // 11=Teensy 2.0, 6=Teensy 1.0, 16=Benito
const int led_on = HIGH;
const int led_off = LOW;

#include <NewSoftSerial.h>

#define rxPin 2
#define txPin 3
NewSoftSerial mySerial(rxPin, txPin);

unsigned long last_cmd_to_midi = 0;

void setup()
{ 
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, led_off);
    digitalWrite(reset_pin, HIGH);
    pinMode(reset_pin, OUTPUT);

    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    Serial.begin(usb_baud);	// USB, communication to PC or Mac
    mySerial.begin(midi_baud);
    
    Uart.begin(midi_baud);	// UART, communication to MIDI
}

long led_on_time=0;

static unsigned char hex_digit[] = { 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

void writeAsHexToSerial(unsigned char prefix, unsigned char c)
{
    Serial.write( prefix );
    Serial.write( hex_digit[(c & 0xF0) >> 4]);
    Serial.write( hex_digit[(c & 0x0F)]);
}

void sendToUart(uint8_t *data, unsigned int len)
    {
    for (unsigned int i = 0; i < len; i++)
    {
        mySerial.write(data[i]);
    }
    }

// Startup procedure
uint8_t startupFfbData_0[] =
    {
    0xc5, 0x01        // <ProgramChange> 0x01
    };
// Wait for 10-20 ms
uint8_t startupFfbData_1[] =
    {
    0xf0,
    	0x00, 0x01, 0x0a, 0x01, 0x10, 0x05, 0x6b,  // ???? - reset all?
    0xf7
    };
// Wait for 56 ms
uint8_t startupFfbData_2[] =
    {
    0xb5, 0x40, 0x7f,  // <ControlChange>(Modify, 0x7f)
    0xa5, 0x72, 0x57,  // offset 0x72 := 0x57
    0xb5, 0x44, 0x7f,
    0xa5, 0x3c, 0x43,
    0xb5, 0x48, 0x7f,
    0xa5, 0x7e, 0x00,
    0xb5, 0x4c, 0x7f,
    0xa5, 0x04, 0x00,
    0xb5, 0x50, 0x7f,
    0xa5, 0x02, 0x00,
    0xb5, 0x54, 0x7f,
    0xa5, 0x02, 0x00,
    0xb5, 0x58, 0x7f,
    0xa5, 0x00, 0x7e,
    0xb5, 0x5c, 0x7f,
    0xa5, 0x3c, 0x00,
    0xb5, 0x60, 0x7f
    };
    
uint8_t startupFfbData_3[] =
    {
    0xa5, 0x14, 0x65,
    0xb5, 0x64, 0x7f,
    0xa5, 0x7e, 0x6b,
    0xb5, 0x68, 0x7f,
    0xa5, 0x36, 0x00,
    0xb5, 0x6c, 0x7f,
    0xa5, 0x28, 0x00,
    0xb5, 0x70, 0x7f,
    0xa5, 0x66, 0x4c,
    0xb5, 0x74, 0x7f,
    0xa5, 0x7e, 0x01,
    0xc5, 0x01
    };
// Wait for 69 ms
uint8_t startupFfbData_4[] =
    {
    0xb5, 0x7c, 0x7f,
    0xa5, 0x7f, 0x00,
    0xc5, 0x06
    };
    
uint8_t stopFfbData_0[] =
    {
    0xc5, 0x01        // <ProgramChange> 0x01
    };
// wait 72 ms
uint8_t stopFfbData_1[] =
    {
    0xc5, 0x07        // <ProgramChange> 0x07
    };
// wait 6 ms
uint8_t stopFfbData_2[] =
    {
    0xb0, 0x40, 0x00,  // Looks like all 16 channels get <Modify>(0x00)
    0xb1, 0x40, 0x00,  // ...
    0xb2, 0x40, 0x00,
    0xb3, 0x40, 0x00,
    0xb4, 0x40, 0x00,
    0xb5, 0x40, 0x00,
    0xb6, 0x40, 0x00,
    0xb7, 0x40, 0x00,
    0xb8, 0x40, 0x00,
    0xb9, 0x40, 0x00,
    0xba, 0x40, 0x00,
    0xbb, 0x40, 0x00,
    0xbc, 0x40, 0x00,
    0xbd, 0x40, 0x00,
    0xbe, 0x40, 0x00,
    0xbf, 0x40, 0x00,
    0xb0, 0x40, 0x00,
    0xb1, 0x40, 0x00,
    0xb2, 0x40, 0x00,
    0xb3, 0x40, 0x00,
    0xb4, 0x40, 0x00,
    0xb5, 0x40, 0x00,
    0xb6, 0x40, 0x00,
    0xb7, 0x40, 0x00,
    0xb8, 0x40, 0x00,
    0xb9, 0x40, 0x00,
    0xba, 0x40, 0x00,
    0xbb, 0x40, 0x00,
    0xbc, 0x40, 0x00,
    0xbd, 0x40, 0x00,
    0xbe, 0x40, 0x00,
    0xbf, 0x40, 0x00
    };
uint8_t stopFfbData_3[] =
    {
    };

// Define startup stuff for the FFP
uint8_t enableFfbData[] =
	{
		0xc5, 0x01,
		0xb5, 0x7c, 0x7f,
		0xa5, 0x7f, 0x00,
		0xc5, 0x06
	};


// Define disable stuff for the FFP
uint8_t disableFfbData[] =
	{
		0xc5, 0x01
	};


// Define and play constant force to left
uint8_t constantLeftFfbData[] =
	{
		0xf0,	// define
			0x00, 0x01, 0x0a, 0x01, 0x23, 0x12, 0x7f, 0x5a, 0x19, 0x00, 0x00, 0x0e, 0x02, 0x7f, 0x64, 0x00, 0x10, 0x4e, 0x7f, 0x00, 0x00, 0x7f, 0x5a, 0x19, 0x7f, 0x01, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x18,
		0xf7,
		0xb5, 0x20, 0x02	// play
	};

// Define and play constant force to right
uint8_t constantRightFfbData[] =
	{
		0xf0,	// define
                        0x00, 0x01, 0x0a, 0x01, 0x23, 0x12, 0x7f, 0x5a, 0x19, 0x00, 0x00, 0x5a, 0x00, 0x7f, 0x64, 0x00, 0x10, 0x4e, 0x7f, 0x00, 0x00, 0x7f, 0x5a, 0x19, 0x7f, 0x01, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x4e,
		0xf7,
		0xb5, 0x20, 0x02	// play
	};

uint8_t pauseEffect2FfbData[] =
	{
		0xb5, 0x30, 0x02	// pause/stop
	};

uint8_t removeEffect2FfbData[] =
	{
		0xb5, 0x10, 0x02	// remove
	};

uint8_t *startupSend = NULL;
unsigned long holdStartupSendTil = 0;

void loop()
{
    unsigned char c, dtr;
    static unsigned char prev_dtr = 0;
   
    unsigned long read_time = micros();
    boolean still_reading = false;

    if (Serial.available())
    {
        still_reading = true;
        c = Serial.read();
        if (c == 's')
        {
            startupSend = startupFfbData_0;
        }
        else if (c == 'p')
        {
            startupSend = stopFfbData_0;
        }
        else if (c == 'e')
        {
            sendToUart(enableFfbData, sizeof(enableFfbData));
        }
        else if (c == 'l')
        {
            sendToUart(constantLeftFfbData, sizeof(constantLeftFfbData));
        }
        else if (c == 'r')
        {
            sendToUart(constantRightFfbData, sizeof(constantRightFfbData));
        }
        else if (c == 'R')
        {
            sendToUart(removeEffect2FfbData, sizeof(removeEffect2FfbData));
        }
        else if (c == 'c')
        {
            sendToUart(pauseEffect2FfbData, sizeof(pauseEffect2FfbData));
        }
        else if (c == 'd')
        {
            sendToUart(disableFfbData, sizeof(disableFfbData));
        }
        
        digitalWrite(led_pin, led_on);
        led_on_time = millis();
        writeAsHexToSerial('>', c );
        return;
    }

    if (Uart.available())
    {
        still_reading = true;
        c = Uart.read();
        if (c >= 0x80)
        {  // start a new line - this is a command byte
            unsigned long delta_time = read_time - last_cmd_to_midi + 1000000000ul;
            last_cmd_to_midi = read_time;
            Serial.write("\n\r");
            Serial.print(delta_time);
            Serial.print(": ");
//          Serial.write('c');
//          writeAsHexToSerial('=', (c & 0x40+0x20+0x10) >> 4 );
//          Serial.write('#');
//          writeAsHexToSerial('=', (c & 0x0F) );
        }
        writeAsHexToSerial(' ', c );
        if (c == 0xf0)
        {
            Serial.write('\n');
            Serial.write('\r');
            Serial.write('\t');
        }
        
        digitalWrite(led_pin, led_on);
        led_on_time = millis();

        // Copy to UART output i.e. MIDI THRU
        Uart.write(c);
        return;
    }
    
    if (millis() - led_on_time > 3)
    {
        digitalWrite(led_pin, led_off);
    }
    
    if (startupSend && holdStartupSendTil < read_time && !still_reading)
    {
        if (startupSend == startupFfbData_0)
        {
          sendToUart(startupFfbData_0, sizeof(startupFfbData_0));
          startupSend = startupFfbData_1;
          holdStartupSendTil = micros() + 20*1000;
        }
        else if (startupSend == startupFfbData_1)
        {
          sendToUart(startupFfbData_1, sizeof(startupFfbData_1));
          startupSend = startupFfbData_2;
          holdStartupSendTil = micros() + 56000ul;
        }
        else if (startupSend == startupFfbData_2)
        {
          sendToUart(startupFfbData_2, sizeof(startupFfbData_2));
          startupSend = startupFfbData_3;
        }
        else if (startupSend == startupFfbData_3)
        {
          sendToUart(startupFfbData_3, sizeof(startupFfbData_3));
          startupSend = startupFfbData_4;
          holdStartupSendTil = micros() + 79000ul;
        }
        else if (startupSend == startupFfbData_4)
        {
          sendToUart(startupFfbData_4, sizeof(startupFfbData_4));
          startupSend = NULL;
        }
        else if (startupSend == stopFfbData_0)
        {
          sendToUart(stopFfbData_0, sizeof(stopFfbData_0));
          holdStartupSendTil = micros() + 20000ul;
          startupSend = stopFfbData_1;
        }
        else if (startupSend == stopFfbData_1)
        {
          sendToUart(stopFfbData_1, sizeof(stopFfbData_1));
          holdStartupSendTil = micros() + 6000ul;
          startupSend = stopFfbData_2;
        }
        else if (startupSend == stopFfbData_2)
        {
          sendToUart(stopFfbData_2, sizeof(stopFfbData_2));
          startupSend = NULL;
        }
        else if (startupSend == stopFfbData_3)
        {
          sendToUart(stopFfbData_3, sizeof(stopFfbData_3));
          startupSend = NULL;
        }
    }    
}


