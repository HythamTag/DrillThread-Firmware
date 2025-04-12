void moveStepper(SpeedyStepper &stepper, float distance, bool isRelative = true);
void setStepperParameters(SpeedyStepper &stepper, float speed, float acceleration, bool isRev = false);
void screwHole(float diameter, float depth, float safeDistance, float stepDownTimes, float rotationalAcceleration, float rotationalSpeed);
bool Stop_Flag = false;

#if defined(DRILLING_MACHINE)
void drillSingleHole() {
  // Logic to drill a single hole
  float drillDistance = safeHeight + zDepth;
  moveStepper(speedyStepperZ, -drillDistance);
  moveStepper(speedyStepperZ, drillDistance);
}

void Drill_holes_loop(int part) {
  int offset = (part == 0) ? 0 : int(numOfHoles);
  for (int i = 0; i < numOfHoles; i++) {
    drillSingleHole();
    lcd.setCursor(7, 0);
    lcd.print(i + 1 + offset);
    if (i != numOfHoles - 1) {
      moveStepper(speedyStepperY, yStep);
    }
  }
}

#elif defined(THREADING_MACHINE)
void threadSingleHole() {
  // Logic to thread a single hole
  float threadingStartDistance = safeHeight - tolHeight;
  moveStepper(speedyStepperZ, -threadingStartDistance);
  screwHole(pgm_read_word(&isoDiameters[diameterSelection]), zDepth, tolHeight, stepDown, acceleration_R_Axis_MMPerSecSq, velocity_R_Axis_MMPerSec);
  moveStepper(speedyStepperZ, threadingStartDistance);
}

void Thread_holes_loop(int part) {
  int offset = (part == 0) ? 0 : int(numOfHoles);
  for (int i = 0; i < numOfHoles; i++) {
    threadSingleHole();
    lcd.setCursor(7, 0);
    lcd.print(i + 1 + offset);
    if (i != numOfHoles - 1) {
      moveStepper(speedyStepperY, yStep);
    }
  }
}
#endif


void Move_gap() {
  moveStepper(speedyStepperY, mGap);
}

void moveByDistance(float distance) {
  moveStepper(speedyStepperY, distance);
}

void Start_process(float Y_abs, float Z_abs, bool prev) {
  uint16_t start_seconds = millis() / 1000;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Holes: ");
  lcd.setCursor(7, 0);
  lcd.print(0);
  lcd.setCursor(10, 0);
  lcd.print("|||");
  lcd.setCursor(15, 0);
  lcd.print(int(numOfHoles) * 2);

  digitalWrite(SPINDLE_CONTROL_PIN, 1);
#ifdef DRILLING_MACHINE
  delay(6000);
#endif

  if (prev) {
    setStepperParameters(speedyStepperY, manualSpeed_Y_Axis_MMPerSec, manualAcceleration_Y_Axis_MMPerSecSq);
    setStepperParameters(speedyStepperZ, manualSpeed_Z_Axis_MMPerSec, manualAcceleration_Z_Axis_MMPerSecSq);
    moveStepper(speedyStepperY, Y_abs, false);
    moveStepper(speedyStepperZ, Z_abs + safeHeight, false);
  } else {
    setStepperParameters(speedyStepperY, manualSpeed_Y_Axis_MMPerSec, manualAcceleration_Y_Axis_MMPerSecSq);
    setStepperParameters(speedyStepperZ, manualSpeed_Z_Axis_MMPerSec, manualAcceleration_Z_Axis_MMPerSecSq);
    moveStepper(speedyStepperZ, safeHeight);
  }

  delay(100);

  setStepperParameters(speedyStepperY, velocity_Y_Axis_MMPerSec, acceleration_Y_Axis_MMPerSecSq);
  setStepperParameters(speedyStepperZ, velocity_Z_Axis_MMPerSec, acceleration_Z_Axis_MMPerSecSq);

#if defined(DRILLING_MACHINE)
  // Sequence starts here
  drillSingleHole();
  moveByDistance(firstDis);

  Drill_holes_loop(0);

  moveByDistance(secDis);

  drillSingleHole();
  moveByDistance(mGap);
  drillSingleHole();

  moveByDistance(secDis);

  Drill_holes_loop(1);

  moveByDistance(firstDis);
  drillSingleHole();

#elif defined(THREADING_MACHINE)
  // Sequence starts here
  // threadSingleHole();
  // moveByDistance(firstDis);

  Thread_holes_loop(0);

  // moveByDistance(secDis);

  // threadSingleHole();
  moveByDistance(mGap);
  // threadSingleHole();

  // moveByDistance(secDis);

  Thread_holes_loop(1);

  // moveByDistance(firstDis);
  // threadSingleHole();
#endif

  //  moveStepper(speedyStepperZ, Z_abs + safeHeight, false);
  //  moveStepper(speedyStepperY, Y_abs, false);

  delay(1000);
  digitalWrite(SPINDLE_CONTROL_PIN, 0);

  Home_ZY();


  uint16_t current_seconds = millis() / 1000;
  uint16_t elapsed_seconds = current_seconds - start_seconds;
  uint16_t milliseconds_part = millis() % 1000;



  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Stop_Flag ? "#### FAILED ####" : "##### DONE #####");
  lcd.setCursor(0, 1);
  lcd.print("Time : ");
  lcd.setCursor(7, 1);
  lcd.print(elapsed_seconds);
  lcd.print(".");
  lcd.print(milliseconds_part);
  delay(1000);

  // reset_menu();

  delay(100);
}
