/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


//Servo Setup
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  220 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  440 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
int servoMid = (SERVOMAX+SERVOMIN)/2; 
// our servo # counter
uint8_t servonum = 0;


//Display Setup
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define WHITE 0x7 //color constant for backlight



void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);

  //welcome screen
//  String welcome = "Welcome to the Eye Mech!";
//  lcd.setCursor(0, 1);
//  lcd.print("by anish & kito");
//  lcd.setCursor(0, 0);
//  displayScroll(welcome);
  

  //delay(10);   
  //centerAll(); 
  //delay(800); 
  orbit(1, 3);

  homeScreen();
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {

  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void backAndForth(int startPulse, int endPulse, int ms, int servoNum) {
   for(int curr = startPulse; curr < endPulse; curr++) {
      pwm.setPWM(servoNum, 0, curr);     
      delay(ms); 
    }

    for(int curr = endPulse; curr > startPulse; curr--) {
      pwm.setPWM(servoNum, 0, curr);       
      delay(ms); 
    }
}

void oscillate(int ms, int oscillations, int axis) {
    
    //assign input to axis
    int xServo = 0; 
    int yServo = 1;

    
    int currPos = servoMid;
    int currAxis = 0;
    boolean phase = true;

    //set both axes to center
    pwm.setPWM(xServo, 0, currPos); 
    pwm.setPWM(yServo, 0, currPos);

    //establish steps that represent a single oscillation
    int steps = (SERVOMAX - SERVOMIN) * 2;
    int currSteps = 0;

//    Possible logic if input is boolean
//    if (input) {
//      currAxis = xServo;
//    } else {
//      currAxis = yServo;
//    }

//  loop to handle updating in 1 step increments
    while(currSteps < steps * oscillations) {
      if (phase) {
        pwm.setPWM(axis, 0, currPos++);
      } else {
        pwm.setPWM(axis, 0, currPos--);
      }

      if (currPos == SERVOMAX || currPos == SERVOMIN) {
        phase = !phase; 
      }
      
      delay(ms);
      currSteps++;      
    }
    
  
}

void orbit(int ms, int rotations) {
    int xServo = 0; 
    int yServo = 1; 
    
    pwm.setPWM(xServo, 0, servoMid); 
    pwm.setPWM(yServo, 0, SERVOMAX);

    int currX = servoMid;
    int currY = SERVOMAX;

    int trying = pwm.getPWM(xServo);

    boolean phaseX = true;
    boolean phaseY = false;

    int steps = (SERVOMAX - SERVOMIN) * 2;
    int currSteps = 0;

    while(currSteps < steps * rotations) {
      if (phaseX) {
        pwm.setPWM(xServo, 0, currX++); 
      }
  
      if (phaseY) {
        pwm.setPWM(yServo, 0, currY++); 
      }
  
      if (!phaseX) {
        pwm.setPWM(xServo, 0, currX--); 
      }
  
      if (!phaseY) {
        pwm.setPWM(yServo, 0, currY--); 
      }
  
      if (currX == SERVOMAX || currX == SERVOMIN) {
        phaseX = !phaseX; 
      }
  
      if (currY == SERVOMAX || currY == SERVOMIN) {
        phaseY = !phaseY; 
      }

      currSteps++;
      delay(ms); 
    }
    
}


void centerAll() {
  for(int i = 0; i < 6; i++) {
     pwm.setPWM(i, 0, servoMid);
     Serial.println(servoMid); 
  }
}

void displayScroll(String text) {
  lcd.print(text);
  delay(1000);
  for (int i = 0; i < text.length() - 16; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

void homeScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("< Orbit");
  lcd.setCursor(0, 1);
  lcd.print("^ Oscillate");
  lcd.setCursor(11, 0);
  lcd.print("> Pos");
}

void orbitScreen() {
  lcd.clear();
  lcd.print("orbit!");
}

void oscScreen() {
  lcd.clear();
  lcd.print("oscillate!");
}

void posScreen() {
  lcd.clear();
  lcd.print("position!");
}


uint8_t i=0;

void loop() {
  int horizontalServo = 0; 
  int verticalServo = 1; 
  
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      oscScreen();
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
    }
    if (buttons & BUTTON_LEFT) {
      orbitScreen();
    }
    if (buttons & BUTTON_RIGHT) {
      posScreen();
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
    }
  }

}
