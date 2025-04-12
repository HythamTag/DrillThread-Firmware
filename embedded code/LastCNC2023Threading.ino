#include "SpeedyStepper.h"
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>  // Required for PROGMEM
#include "EEPROMManager.h"

// #define DRILLING_MACHINE
#define THREADING_MACHINE

#define ENTER_BUTTON_PIN A0
#define BACK_BUTTON_PIN A3
#define INCREMENT_BUTTON_PIN A2
#define DECREMENT_BUTTON_PIN A1

#define START_PIN 9
#define STOP_BUTTON_PIN 13
#define HOME_PIN 10
#define SPINDLE_CONTROL_PIN 8

#define NUM_ROWS 4
#define Button_Condition false

#define maxHomingDistance_Y_Axis_MM 9999  // Maximum homing distance for Y-axis in mm
#define maxHomingDistance_Z_Axis_MM 9999  // Maximum homing distance for Z-axis in mm

#define directionTowardHome_Y_Axis -1  // Direction to move Y-axis toward limit switch: 1 for positive, -1 for negative
#define directionTowardHome_Z_Axis 1   // Direction to move Z-axis toward limit switch: 1 for positive, -1 for negative

// Motor Pin Assignments
#define Z_AXIS_MOTOR_STEP_PIN 6
#define Z_AXIS_MOTOR_DIRECTION_PIN 7
#define Y_AXIS_MOTOR_STEP_PIN 4
#define Y_AXIS_MOTOR_DIRECTION_PIN 5
#define R_AXIS_MOTOR_STEP_PIN 2
#define R_AXIS_MOTOR_DIRECTION_PIN 3

// Limit Switch Pin Assignments
#define Y_AXIS_LIMIT_SWITCH_PIN 11
#define Z_AXIS_LIMIT_SWITCH_PIN 12

// Motor Drivers Configuration
#define microstepsPerRev_Y_Axis 400  // Number of microsteps per revolution for Y-axis motor
#define microstepsPerRev_Z_Axis 400  // Number of microsteps per revolution for Z-axis motor
#define microstepsPerRev_R_Axis 400  // Number of microsteps per revolution for R-axis motor

// Ball Screw Configuration
#define mmPerRev_Y_Axis_BallScrew 10  // Millimeters per revolution for Y-axis ball screw
#define mmPerRev_Z_Axis_BallScrew 10  // Millimeters per revolution for Z-axis ball screw

// dev value to fix int problem
// #define div_value 10


// create two stepper motor objects, one for each motor
SpeedyStepper speedyStepperY;
SpeedyStepper speedyStepperZ;
SpeedyStepper speedyStepperR;
EEPROMManager manager;
// Motors Configuration for Y and Z Axes
// Raw values
int position_Y_Axis_MM = 0;
int position_Z_Axis_MM = 0;
int position_R_Axis_REV = 0;

int origin_Y_Axis_MM_raw = 0.0;  // Current position of Y-axis in millimeters
int origin_Z_Axis_MM_raw = 0.0;  // Current position of Z-axis in millimeters

int velocity_Y_Axis_MMPerSec_raw = 1500;
int velocity_Z_Axis_MMPerSec_raw = 1500;
int velocity_R_Axis_MMPerSec_raw = 600;

int acceleration_Y_Axis_MMPerSecSq_raw = 2000;
int acceleration_Z_Axis_MMPerSecSq_raw = 2000;
int acceleration_R_Axis_MMPerSecSq_raw = 600;

int manualSpeed_Y_Axis_MMPerSec_raw = 500;
int manualSpeed_Z_Axis_MMPerSec_raw = 500;
int manualSpeed_R_Axis_MMPerSec_raw = 10;

int manualAcceleration_Y_Axis_MMPerSecSq_raw = 1000;
int manualAcceleration_Z_Axis_MMPerSecSq_raw = 1000;
int manualAcceleration_R_Axis_MMPerSecSq_raw = 10;

int homingSpeed_Y_Axis_MMPerSec_raw = 300;
int homingSpeed_Z_Axis_MMPerSec_raw = 300;

int homingAcceleration_Y_Axis_MMPerSecSq_raw = 300;
int homingAcceleration_Z_Axis_MMPerSecSq_raw = 300;

int numOfHoles_raw = 50;
int yStep_raw = 50;
int mGap_raw = 300;
int zDepth_raw = 150;
int safeHeight_raw = 50;
int tolHeight_raw = 10;
int diameterSelection = 1;
int stepDown_raw = 1000;

int firstDis_raw = 100;
int secDis_raw = 200;

#define origin_Y_Axis_MM (origin_Y_Axis_MM_raw / 10.0)
#define origin_Z_Axis_MM (origin_Z_Axis_MM_raw / 10.0)


// #define position_Y_Axis_MM (position_Y_Axis_MM_raw / 10.0)
// #define position_Z_Axis_MM (position_Z_Axis_MM_raw / 10.0)
// #define position_R_Axis_REV (position_R_Axis_REV_raw / 10.0)

#define velocity_Y_Axis_MMPerSec (velocity_Y_Axis_MMPerSec_raw / 10.0)
#define velocity_Z_Axis_MMPerSec (velocity_Z_Axis_MMPerSec_raw / 10.0)
#define velocity_R_Axis_MMPerSec (velocity_R_Axis_MMPerSec_raw / 10.0)

#define acceleration_Y_Axis_MMPerSecSq (acceleration_Y_Axis_MMPerSecSq_raw / 10.0)
#define acceleration_Z_Axis_MMPerSecSq (acceleration_Z_Axis_MMPerSecSq_raw / 10.0)
#define acceleration_R_Axis_MMPerSecSq (acceleration_R_Axis_MMPerSecSq_raw / 10.0)

#define manualSpeed_Y_Axis_MMPerSec (manualSpeed_Y_Axis_MMPerSec_raw / 10.0)
#define manualSpeed_Z_Axis_MMPerSec (manualSpeed_Z_Axis_MMPerSec_raw / 10.0)
#define manualSpeed_R_Axis_MMPerSec (manualSpeed_R_Axis_MMPerSec_raw / 10.0)

#define manualAcceleration_Y_Axis_MMPerSecSq (manualAcceleration_Y_Axis_MMPerSecSq_raw / 10.0)
#define manualAcceleration_Z_Axis_MMPerSecSq (manualAcceleration_Z_Axis_MMPerSecSq_raw / 10.0)
#define manualAcceleration_R_Axis_MMPerSecSq (manualAcceleration_R_Axis_MMPerSecSq_raw / 10.0)

#define homingSpeed_Y_Axis_MMPerSec (homingSpeed_Y_Axis_MMPerSec_raw / 10.0)
#define homingSpeed_Z_Axis_MMPerSec (homingSpeed_Z_Axis_MMPerSec_raw / 10.0)

#define homingAcceleration_Y_Axis_MMPerSecSq (homingAcceleration_Y_Axis_MMPerSecSq_raw / 10.0)
#define homingAcceleration_Z_Axis_MMPerSecSq (homingAcceleration_Z_Axis_MMPerSecSq_raw / 10.0)

#define numOfHoles (numOfHoles_raw / 10.0)
#define yStep (yStep_raw / 10.0)
#define mGap (mGap_raw / 10.0)
#define zDepth (zDepth_raw / 10.0)
#define safeHeight (safeHeight_raw / 10.0)
#define tolHeight (tolHeight_raw / 10.0)
// #define diameterSelection (diameterSelection_raw / 10.0)
#define stepDown (stepDown_raw / 10.0)

#define firstDis (firstDis_raw / 10.0)
#define secDis (secDis_raw / 10.0)


// Move constant arrays to PROGMEM
const int isoDiameters[] PROGMEM = { 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 24, 30, 36, 42, 48 };
const float isoPitches[] PROGMEM = { 0.5, 0.7, 0.8, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0 };

LiquidCrystal_I2C lcd(0x27, 20, NUM_ROWS);  // Assuming you're using a 16x2 LCD with I2C address 0x27

class MenuItem {
public:
  const char* displayName;
  void (*actionFunction)(int value);
  void (*adjustFunction)(int direction);
  int* itemValue;
  int changeValue;
  int lowerLimit;
  int upperLimit;
  int* targetArray;  // Change this to a pointer

  MenuItem(const char* name, void (*action)(int) = NULL, void (*adjust)(int) = NULL, int* value = NULL, int change = NULL, int lowerLimitValue = NULL, int upperLimitValue = NULL, int* array = NULL)  // Change the type of the last parameter to float*
    : displayName(name), actionFunction(action), adjustFunction(adjust), itemValue(value), changeValue(change), lowerLimit(lowerLimitValue), upperLimit(upperLimitValue), targetArray(array) {}
};

// Global variables for menu navigation
int firstVisibleItem = 0;
int firstVisibleSubItem = 0;
bool adjustingValue = false;

// Global state variables
bool isButtonPressed = false;
const unsigned int longPressTime = 1000;  // 1 second for example
unsigned int buttonPressTime = 0;         // Time when the button was first pressed
int currentDelay = 200;                   // Initial delay


// Placeholder functions for menu and submenu items
void defaultAction() {
  // Serial.println("Default action triggered");
}

// Submenu items
MenuItem startSubMenu[] = {
  MenuItem("Return to Origin", goPrevAction),
  MenuItem("Start current Pos", startAction)
};

MenuItem moveSubMenu[] = {
  MenuItem("Move Y", moveY, defaultAdjust, &position_Y_Axis_MM),
  MenuItem("Move Z", moveZ, defaultAdjust, &position_Z_Axis_MM),
#ifdef THREADING_MACHINE
  MenuItem("Move R", moveR, defaultAdjust, &position_R_Axis_REV)
#endif
};

MenuItem homeSubMenu[] = {
  MenuItem("Home Z", Home_Z),
  MenuItem("Home ZY", Home_ZY)
};

// dont put zero in upper or lower limits because NULL is ZERO

MenuItem drillParametersSubMenu[] = {
  MenuItem("NO HOLES", NULL, defaultAdjust, &numOfHoles_raw, 10, 10, NULL, NULL),
  MenuItem("Y STEP", NULL, defaultAdjust, &yStep_raw, 1, 1, NULL, NULL),
  MenuItem("Mid GAP", NULL, defaultAdjust, &mGap_raw, 1, 1, NULL, NULL),
#ifdef DRILLING_MACHINE
  MenuItem("1ST DIS", NULL, defaultAdjust, &firstDis_raw, 1, 1, NULL, NULL),
  MenuItem("2ND DIS", NULL, defaultAdjust, &secDis_raw, 1, 1, NULL, NULL),
#endif
  MenuItem("Z DEPTH", NULL, defaultAdjust, &zDepth_raw, 1, 1, NULL, NULL),
  MenuItem("SAFE HEIGHT", NULL, defaultAdjust, &safeHeight_raw, 1, 1, NULL, NULL),
};

MenuItem threadParametersSubMenu[] = {
  MenuItem("THREAD DIA", NULL, defaultAdjust, &diameterSelection, 1, 1, 14, isoDiameters),
  MenuItem("STEPDOWN", NULL, defaultAdjust, &stepDown_raw, 10, 10, NULL, NULL),
  MenuItem("TOL HEIGHT", NULL, defaultAdjust, &tolHeight_raw, 1, 1, NULL, NULL),
};


MenuItem velocitySubMenu[] = {
  MenuItem("WORK VEL Y", NULL, defaultAdjust, &velocity_Y_Axis_MMPerSec_raw, 100, 100, 5000),
  MenuItem("WORK VEL Z", NULL, defaultAdjust, &velocity_Z_Axis_MMPerSec_raw, 100, 100, 5000),
#ifdef THREADING_MACHINE
  MenuItem("WORK VEL R", NULL, defaultAdjust, &velocity_R_Axis_MMPerSec_raw, 10, 10, 300),
#endif
  MenuItem("MAN VEL Y", NULL, defaultAdjust, &manualSpeed_Y_Axis_MMPerSec_raw, 100, 100, 5000),
  MenuItem("MAN VEL Z", NULL, defaultAdjust, &manualSpeed_Z_Axis_MMPerSec_raw, 100, 100, 5000),
#ifdef THREADING_MACHINE
  MenuItem("MAN VEL R", NULL, defaultAdjust, &manualSpeed_R_Axis_MMPerSec_raw, 10, 10, 300),
#endif
  MenuItem("HME VEL Y", NULL, defaultAdjust, &homingSpeed_Y_Axis_MMPerSec_raw, 100, 100, 5000),
  MenuItem("HME VEL Z", NULL, defaultAdjust, &homingSpeed_Z_Axis_MMPerSec_raw, 100, 100, 5000),
};

MenuItem accelerationSubMenu[] = {
  MenuItem("WORK ACC Y", NULL, defaultAdjust, &acceleration_Y_Axis_MMPerSecSq_raw, 100, 100, 5000),
  MenuItem("WORK ACC Z", NULL, defaultAdjust, &acceleration_Z_Axis_MMPerSecSq_raw, 100, 100, 5000),
#ifdef THREADING_MACHINE
  MenuItem("WORK ACC R", NULL, defaultAdjust, &acceleration_R_Axis_MMPerSecSq_raw, 10, 10, 300),
#endif
  MenuItem("MAN ACC Y", NULL, defaultAdjust, &manualAcceleration_Y_Axis_MMPerSecSq_raw, 100, 100, 5000),
  MenuItem("MAN ACC Z", NULL, defaultAdjust, &manualAcceleration_Z_Axis_MMPerSecSq_raw, 100, 100, 5000),
#ifdef THREADING_MACHINE
  MenuItem("MAN ACC R", NULL, defaultAdjust, &manualAcceleration_R_Axis_MMPerSecSq_raw, 10, 10, 300),
#endif
  MenuItem("HME VEL Y", NULL, defaultAdjust, &homingAcceleration_Y_Axis_MMPerSecSq_raw, 100, 100, 5000),
  MenuItem("HME VEL Z", NULL, defaultAdjust, &homingAcceleration_Z_Axis_MMPerSecSq_raw, 100, 100, 5000),
};

// Define a structure to hold both the main menu item and its corresponding submenu
struct MenuWithSub {
  MenuItem mainItem;
  MenuItem* subItems;
  int subItemCount;
};

// Main menu items with their corresponding submenus
MenuWithSub menusWithSubs[] = {
  { MenuItem("START", NULL), startSubMenu, sizeof(startSubMenu) / sizeof(startSubMenu[0]) },
  { MenuItem("MOVE", NULL), moveSubMenu, sizeof(moveSubMenu) / sizeof(moveSubMenu[0]) },
  { MenuItem("HOME", NULL), homeSubMenu, sizeof(homeSubMenu) / sizeof(homeSubMenu[0]) },
  { MenuItem("DRILL PARAM", NULL), drillParametersSubMenu, sizeof(drillParametersSubMenu) / sizeof(drillParametersSubMenu[0]) },
#ifdef THREADING_MACHINE
  { MenuItem("THREAD PARAM", NULL), threadParametersSubMenu, sizeof(threadParametersSubMenu) / sizeof(threadParametersSubMenu[0]) },
#endif
  { MenuItem("VELOCITY", NULL), velocitySubMenu, sizeof(velocitySubMenu) / sizeof(velocitySubMenu[0]) },
  { MenuItem("ACCELERATION", NULL), accelerationSubMenu, sizeof(accelerationSubMenu) / sizeof(accelerationSubMenu[0]) },
  { MenuItem("SAVE DATA", saveDataAction), NULL, 0 },
  { MenuItem("LOAD DATA", loadDataAction), NULL, 0 }
};


// Pointers to keep track of the currently selected menu and submenu
MenuWithSub* currentMenu = &menusWithSubs[0];
MenuItem* currentSubMenu = NULL;




void setup() {
  //  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  //    saveAllData();

  //Serial.println(velocity_Y_Axis_MMPerSec_raw);
  //Serial.println(acceleration_Y_Axis_MMPerSecSq_raw);
  //Serial.println(velocity_Z_Axis_MMPerSec_raw);
  //Serial.println(acceleration_Z_Axis_MMPerSecSq_raw);
  //Serial.println("################");

  loadAllData();

  //Serial.println(velocity_Y_Axis_MMPerSec_raw);
  //Serial.println(acceleration_Y_Axis_MMPerSecSq_raw);
  //Serial.println(velocity_Z_Axis_MMPerSec_raw);
  //Serial.println(acceleration_Z_Axis_MMPerSecSq_raw);


  motorInit();
  pinMode(ENTER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BACK_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(HOME_PIN, INPUT_PULLUP);
  pinMode(SPINDLE_CONTROL_PIN, OUTPUT);
  displayMenu();
}

void loop() {

  if (digitalRead(START_PIN) == LOW) {
    if (!isButtonPressed) {
      buttonPressTime = millis();
      isButtonPressed = true;
    } else if (millis() - buttonPressTime > longPressTime) {
      longPressStart();
      isButtonPressed = false;  // Reset after detecting a long press
    }
  } else if (digitalRead(HOME_PIN) == LOW) {
    if (!isButtonPressed) {
      buttonPressTime = millis();
      isButtonPressed = true;
    } else if (millis() - buttonPressTime > longPressTime) {
      longPressHome();
      isButtonPressed = false;  // Reset after detecting a long press
    }
  } else {
    isButtonPressed = false;  // Reset when the button is released
  }

  checkButtons();
}
