#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
#include <vector>
#include <Wire.h>
#include <SPI.h>

//Initialize Speaker Token encodings
const uint8_t spLEVEL[] PROGMEM = {0x69,0xAB,0xC4,0xB3,0xD8,0x92,0x86,0x2D,0x83,0xEE,0x60,0xCD,0x12,0xD6,0x0C,0x66,0x45,0x2C,0x73,0x58,0x0B,0xA8,0x53,0xD6,0xAC,0x6D,0xE9,0xC0,0x57,0xC5,0xB2,0xAE,0xA1,0xB0,0x49,0x0D,0x7B,0xBD,0x86,0xA2,0x47,0x35,0xE3,0xF5,0xEA,0xB2,0x4B,0x4B,0xCB,0xC7,0xA3,0xCD,0xDE,0x23,0x59,0x1A,0x9A,0x31,0x8B,0xB0,0x54,0x76,0xE3,0xC6,0x26,0x5C,0x2C,0xCC,0x76,0x6B,0x92,0xBC,0x34,0x95,0xC6,0xA3,0xCE,0x74,0xDB,0x85,0x3B,0x8F,0xBA,0x90,0x9C,0x51,0xCC,0xD6,0xEA,0x4C,0x63,0x56,0x30,0x6D,0xA9,0x23,0xCF,0x59,0xD0,0x34,0xB5,0xF9,0x7F};
const uint8_t spONE[] PROGMEM = {0x66,0x4E,0xA8,0x7A,0x8D,0xED,0xC4,0xB5,0xCD,0x89,0xD4,0xBC,0xA2,0xDB,0xD1,0x27,0xBE,0x33,0x4C,0xD9,0x4F,0x9B,0x4D,0x57,0x8A,0x76,0xBE,0xF5,0xA9,0xAA,0x2E,0x4F,0xD5,0xCD,0xB7,0xD9,0x43,0x5B,0x87,0x13,0x4C,0x0D,0xA7,0x75,0xAB,0x7B,0x3E,0xE3,0x19,0x6F,0x7F,0xA7,0xA7,0xF9,0xD0,0x30,0x5B,0x1D,0x9E,0x9A,0x34,0x44,0xBC,0xB6,0x7D,0xFE,0x1F};
const uint8_t spTWO[]  PROGMEM = {0x06,0xB8,0x59,0x34,0x00,0x27,0xD6,0x38,0x60,0x58,0xD3,0x91,0x55,0x2D,0xAA,0x65,0x9D,0x4F,0xD1,0xB8,0x39,0x17,0x67,0xBF,0xC5,0xAE,0x5A,0x1D,0xB5,0x7A,0x06,0xF6,0xA9,0x7D,0x9D,0xD2,0x6C,0x55,0xA5,0x26,0x75,0xC9,0x9B,0xDF,0xFC,0x6E,0x0E,0x63,0x3A,0x34,0x70,0xAF,0x3E,0xFF,0x1F};
const uint8_t spTHREE[] PROGMEM = {0x0C,0xE8,0x2E,0x94,0x01,0x4D,0xBA,0x4A,0x40,0x03,0x16,0x68,0x69,0x36,0x1C,0xE9,0xBA,0xB8,0xE5,0x39,0x70,0x72,0x84,0xDB,0x51,0xA4,0xA8,0x4E,0xA3,0xC9,0x77,0xB1,0xCA,0xD6,0x52,0xA8,0x71,0xED,0x2A,0x7B,0x4B,0xA6,0xE0,0x37,0xB7,0x5A,0xDD,0x48,0x8E,0x94,0xF1,0x64,0xCE,0x6D,0x19,0x55,0x91,0xBC,0x6E,0xD7,0xAD,0x1E,0xF5,0xAA,0x77,0x7A,0xC6,0x70,0x22,0xCD,0xC7,0xF9,0x89,0xCF,0xFF,0x03};
const uint8_t spSTART[] PROGMEM = {0x02,0xF8,0x49,0xCC,0x00,0xBF,0x87,0x3B,0xE0,0xB7,0x60,0x03,0xFC,0x9A,0xAA,0x80,0x3F,0x92,0x11,0x30,0x29,0x9A,0x02,0x86,0x34,0x5F,0x65,0x13,0x69,0xE2,0xDA,0x65,0x35,0x59,0x8F,0x49,0x59,0x97,0xD5,0x65,0x7D,0x29,0xA5,0xDE,0x56,0x97,0xF5,0x85,0x8E,0xE4,0x5D,0x6D,0x0E,0x23,0x39,0xDC,0x79,0xD4,0xA5,0x35,0x75,0x72,0xEF,0x51,0x95,0xE9,0x38,0xE6,0xB9,0x4B,0x5D,0x1A,0x26,0x6B,0x3B,0x46,0xE0,0x14,0xA5,0x2A,0x54,0x03,0x40,0x01,0x43,0xBA,0x31,0x60,0x73,0x35,0x04,0x4E,0x51,0xAA,0x42,0x35,0xFE,0x1F};
const uint8_t spPLAY[] PROGMEM ={0x06,0xC8,0x55,0x54,0x01,0x49,0x69,0x94,0xC4,0xA4,0x1C,0xE3,0x8A,0xD3,0x93,0x19,0xAF,0x24,0xE4,0x68,0xE1,0x4D,0xBC,0x92,0x58,0x22,0x95,0x27,0xF1,0x4A,0x53,0xF5,0x10,0x99,0x26,0xB3,0x68,0x75,0x29,0x12,0xE2,0x53,0xBB,0x74,0x31,0x52,0x64,0x4F,0xD8,0xDA,0xA7,0x3E,0x3A,0xF6,0xAC,0x2C,0x13,0xFA,0xA0,0x39,0xBA,0x33,0x88,0xEB,0x8D,0x92,0xB9,0x70,0xA1,0x0F,0x00,0x00};
const uint8_t spAGAIN[] PROGMEM ={0x08,0xD0,0xD1,0xBD,0x55,0xAE,0xA7,0x73,0x54,0xAD,0x53,0xC5,0x18,0xE1,0xA2,0x4B,0x4F,0x9D,0x42,0xA8,0x89,0x76,0x6D,0xB5,0xB7,0x22,0x21,0xE9,0xAD,0x36,0xB3,0x1D,0x4D,0xB1,0x22,0xAE,0x97,0xA4,0xE7,0x23,0x2B,0x89,0x5D,0x63,0x92,0xEC,0x6C,0xA7,0x23,0x2D,0xD5,0x42,0x74,0x14,0xCF,0x6C,0xE4,0xA9,0x45,0x08,0x8D,0xE3,0x5D,0xEF,0x66,0xB4,0xB1,0x67,0xB2,0x66,0xE2,0xD9,0x8F,0x3E,0x8C,0x08,0xF2,0x8C,0x1B,0x06,0xE9,0xA5,0xCC,0x46,0xB6,0x1F,0xEC,0x20,0x07,0x34,0xD0,0x10,0x99,0xDA,0x92,0x1E,0x00,0x00};
const uint8_t spGAMES[] PROGMEM ={0xAA,0x15,0x24,0x2A,0xD6,0xE4,0xB6,0xB6,0x79,0x13,0xB1,0x5C,0xB2,0xF3,0x93,0x97,0xA4,0x66,0x3E,0x75,0x77,0x3E,0xF2,0x52,0x8D,0xCD,0x26,0xF6,0xCC,0x7B,0xDE,0x8A,0x9A,0x14,0x2D,0xBA,0xD2,0xAC,0x66,0xDD,0xEB,0xDE,0x8E,0xB6,0x7A,0x47,0x0D,0xAF,0x95,0x3A,0x6D,0xB1,0x9A,0xDA,0x8E,0xED,0x6C,0x67,0x3A,0x6E,0xA5,0x46,0x42,0xB1,0xED,0x74,0x27,0x3A,0x62,0x32,0xC2,0x23,0x76,0xEA,0x7F,0x22,0x36,0x11,0xF5,0x06,0x38,0x1C,0xC8,0x00,0xDF,0x29,0x39,0xE0,0x7B,0x56,0x03,0x7C,0xCD,0xCA,0x80,0xCC,0x83,0x1E,0x00,0x00};
const uint8_t spRETURN[] PROGMEM ={0x00,0x60,0x12,0x15,0xC9,0x27,0x9C,0xF1,0xA8,0xBC,0x93,0xD4,0xD2,0x65,0xAB,0x4A,0x51,0x43,0x25,0x7B,0xDF,0x6A,0x54,0x3E,0x98,0x99,0x76,0x2B,0xD3,0x19,0x19,0x91,0x1A,0x4E,0x00,0x12,0xD0,0x4C,0xB8,0x07,0x14,0xE0,0x9D,0x19,0x02,0x78,0xB5,0x5C,0x91,0x4F,0x2E,0x95,0xEA,0x7A,0x27,0x2B,0x0D,0xA5,0xC9,0x8B,0x3C,0xEF,0x74,0x67,0x23,0x0F,0xDB,0x38,0x55,0x32,0xCF,0x6A,0xD4,0x61,0x3A,0x87,0x8B,0xAF,0xD6,0x84,0x6B,0x66,0x4E,0x9D,0x4A,0x1B,0x0F,0xBB,0x86,0xA4,0x09,0x5D,0x58,0x90,0x66,0xE5,0xCA,0x75,0x2C,0x58,0x9B,0xB4,0x69,0xDF,0xF9,0xEE,0x01};
const uint8_t spTO[] PROGMEM ={0x02,0xD8,0x51,0x3C,0x00,0xC7,0x7A,0x18,0x20,0x85,0xE2,0xE5,0x16,0x61,0x45,0x65,0xD9,0x6F,0xBC,0xE3,0x99,0xB4,0x34,0x51,0x6B,0x49,0xC9,0xDE,0xAB,0x56,0x3B,0x11,0xA9,0x2E,0xD9,0x73,0xEB,0x7A,0x69,0x2A,0xCD,0xB5,0x9B,0x1A,0x58,0x2A,0x73,0xF3,0xCD,0x6A,0x90,0x62,0x8A,0xD3,0xD3,0xAA,0x41,0xF1,0x4E,0x77,0x75,0xF2};
const uint8_t spGOODBYE[] PROGMEM ={0xA9,0x49,0xE1,0x54,0x91,0x2D,0xAF,0x22,0x07,0x55,0x29,0x69,0x7B,0xF2,0x18,0x38,0x32,0x3C,0xCB,0x4D,0x52,0xC8,0x4A,0x5A,0x65,0x99,0x52,0x21,0x6A,0x61,0x69,0x2E,0x45,0x46,0x2C,0x43,0xA9,0x3C,0x3D,0x1C,0x87,0x2A,0x3A,0xFB,0x50,0x6E,0x73,0xEB,0xDB,0xEC,0x6E,0x77,0xA3,0xF7,0xD1,0x4E,0x35,0xA2,0xCC,0x7E,0x74,0x3E,0xC6,0xA8,0x79,0x85,0xD1,0x86,0x64,0x65,0x16,0x95,0x5B,0x13,0x52,0xB0,0x65,0x94,0x2E,0xB5,0x4D,0x6A,0x55,0x65,0xF8,0x01,0x00,0x00};

//Initialize start times for each level
unsigned long previous_time1 = 0;
unsigned long previous_time2 = 0;
unsigned long previous_time3 = 0;

//Initialize PIN numbers
const byte buttonA = 4;
const byte buttonB = 5;

//Initialize Interrupt Flags
volatile bool Aflag = false;
volatile bool Bflag = false;

//Initialize correct sequence vector
std::vector<int> correct_sequence;

//Initialize initial level scores
volatile int lvl1_score = 0;
volatile int lvl2_score = 0;
volatile int lvl3_score = 0;

//Initialize current level flag
volatile int current_level = 0;

//Initialize decision flag
volatile int decision;

void setup() {
	
//Initialize Circuit session, initialize pins, and attach pins to interrupts, Speak "GAMES START"
CircuitPlayground.begin();
Serial.begin(9600); //begin Serial Communication
pinMode(buttonA, INPUT_PULLDOWN);
pinMode(buttonB, INPUT_PULLDOWN);
pinMode(switch_, INPUT_PULLUP); 
attachInterrupt(digitalPinToInterrupt(switch_), switch_setter, CHANGE);
attachInterrupt(digitalPinToInterrupt(buttonA), Aflag_setter, CHANGE);
attachInterrupt(digitalPinToInterrupt(buttonB), Bflag_setter, CHANGE);

CircuitPlayground.speaker.say(spGAMES);
CircuitPlayground.speaker.say(spSTART);
}

//Set A-Flag, un-set B flag
void Aflag_setter() {
  Bflag = false;
  Aflag = true;
  //Serial.println("Aflag");
}

//Set B-Flag, un-set A flag
void Bflag_setter() {
  Aflag = false;
  Bflag = true;
  //Serial.println("Bflag");
}

//Create a random pattern of 1s and 0s of length 10, store in vector
//For number in sequence, 1 = Red, 0 = Blue
//Takes int level as argument, increasing level corresponds to shorter time displaying pattern
void generate_pattern(int level) {
  for(int i=0; i<10; ++i) {
    long rand = random(0,2);
    int randd = int(rand);
    correct_sequence.push_back(randd);
    if (randd == 1) {
      CircuitPlayground.setPixelColor(i, 255, 0, 0);
    } else {
      CircuitPlayground.setPixelColor(i, 0, 0, 255);
    }
  }
  switch(level) {
      case 1:
        delay(3000);
      case 2:
        delay(2000);
      case 3:
        delay(1000);
    }
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i,0,0,0);
  }
}

//Level tracks total buttons pressed, the next number/color in the correct sequence vector, number of correct inputs. Level ends after 10 button presses. A input for 1, B input for 0.
void lvl1() {

  volatile int button_presses = 0;
  volatile int next_correct_input = 0;
  volatile int num_correct = 0;

  generate_pattern(1);

  previous_time1 = millis();

  next_correct_input = correct_sequence[0];

  Aflag = false;
  Bflag = false;

  while (button_presses < 10) {
      if (next_correct_input == 1) {
        if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        } else if (Bflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        }
      } else {
        if (Bflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        } else if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        }
      }
  }

  float lvl_time = millis() - previous_time1;

  int lvl1_local_score = floor((num_correct * 0.1) * (20000.0 / lvl_time) * 100); 

  lvl1_score = lvl1_local_score;

  Serial.print("Level one score: ");
  Serial.print(lvl1_local_score);
  Serial.println();
  Serial.print("Total score: ");
  Serial.print(lvl1_score + lvl2_score);
  Serial.println();

}

void lvl2() {

  volatile int button_presses = 0;
  volatile int next_correct_input = 0;
  volatile int num_correct = 0;

  generate_pattern(2);

  previous_time2 = millis();

  next_correct_input = correct_sequence[0];

  Aflag = false;
  Bflag = false;

  while (button_presses < 10) {
      if (next_correct_input == 1) {
        if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        } else if (Bflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        }
      } else {
        if (Bflag) {
          
          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        } else if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        }
      }
  }

  float lvl_time = millis() - previous_time2;

  int lvl2_local_score = floor((num_correct * 0.1) * (20000.0 / lvl_time) * 100);

  lvl2_score = lvl2_local_score; 

  Serial.print("Level two score: ");
  Serial.print(lvl2_local_score);
  Serial.println();
  Serial.print("Total score: ");
  Serial.print(lvl1_score + lvl2_score);
  Serial.println();

}

void lvl3() {

  volatile int button_presses = 0;
  volatile int next_correct_input = 0;
  volatile int num_correct = 0;

  generate_pattern(3);

  previous_time3 = millis();

  next_correct_input = correct_sequence[0];

  Aflag = false;
  Bflag = false;

  while (button_presses < 10) {
      if (next_correct_input == 1) {
        if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        } else if (Bflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        }
      } else {
        if (Bflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          num_correct = ++num_correct;
          next_correct_input = correct_sequence[button_presses];
          Bflag = false;
        } else if (Aflag) {

          Serial.println("Input Registered");

          delay(500);
          button_presses = ++button_presses;
          next_correct_input = correct_sequence[button_presses];
          Aflag = false;
        }
      }
  }

  float lvl_time = millis() - previous_time3;

  int lvl3_local_score = floor((num_correct * 0.1) * (20000.0 / lvl_time) * 100); 

  lvl3_score = lvl3_local_score;

  Serial.print("Level three score: ");
  Serial.print(lvl3_local_score);
  Serial.println();
  Serial.print("Total score: ");
  Serial.print(lvl1_score + lvl2_score + lvl3_score);
  Serial.println();

}

//Main running loop runs all levels, clears out correct sequence vector after each level, ends with menu which prompts user to either exit the program or play again.
void loop() {

  if (current_level == 1 || current_level == 0) {

  current_level = 1;

  CircuitPlayground.speaker.say(spLEVEL);
  CircuitPlayground.speaker.say(spONE);
	CircuitPlayground.speaker.say(spSTART);
  
  lvl1();

  correct_sequence.clear();

  delay(2000);

  current_level = 2;
  }

  if (current_level == 2) {
  CircuitPlayground.speaker.say(spLEVEL);
  CircuitPlayground.speaker.say(spTWO);
	CircuitPlayground.speaker.say(spSTART);

  lvl2();

  correct_sequence.clear();

  delay(2000);

  current_level = 3;
  }

  if (current_level == 3) {
  CircuitPlayground.speaker.say(spLEVEL);
  CircuitPlayground.speaker.say(spTHREE);
	CircuitPlayground.speaker.say(spSTART);

  lvl3();

  correct_sequence.clear();

  current_level = 0;
  }

  lvl1_score = 0;
  lvl2_score = 0;
  lvl3_score = 0;
  decision = 0;

  while(decision == 0) {
    if (Aflag) {
      CircuitPlayground.speaker.say(spPLAY);
      CircuitPlayground.speaker.say(spAGAIN);
      decision = 1;
      break;
    } else if (Bflag) {
      decision = 2;
      CircuitPlayground.speaker.say(spGOODBYE);
      exit(0);
    }
    Serial.println("\nPlay again: A | Exit: B");
    delay(10000);
  }
 }
