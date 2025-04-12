void handleManualStepperMovement(SpeedyStepper &stepper, int direction, bool &Stop_Flag);
void setStepperParameters(SpeedyStepper &stepper, float speed, float acceleration, bool isRev = false);


void startAction(int subMenuIndex) {
  origin_Y_Axis_MM_raw = speedyStepperY.getCurrentPositionInMillimeters() * 10;
  origin_Z_Axis_MM_raw = speedyStepperZ.getCurrentPositionInMillimeters() * 10;
  saveOrigin();
  Start_process(origin_Y_Axis_MM, origin_Z_Axis_MM, false);
}

void goPrevAction(int subMenuIndex) {
  setStepperParameters(speedyStepperY, manualSpeed_Y_Axis_MMPerSec, manualAcceleration_Y_Axis_MMPerSecSq);
  setStepperParameters(speedyStepperZ, manualSpeed_Z_Axis_MMPerSec, manualAcceleration_Z_Axis_MMPerSecSq);
  speedyStepperY.moveToPositionInMillimeters(origin_Y_Axis_MM);
  speedyStepperZ.moveToPositionInMillimeters(origin_Z_Axis_MM);
}

void moveToHome(bool isZ, bool isY) {
  setStepperParameters(speedyStepperY, homingSpeed_Y_Axis_MMPerSec, homingAcceleration_Y_Axis_MMPerSecSq);
  setStepperParameters(speedyStepperZ, homingSpeed_Z_Axis_MMPerSec, homingAcceleration_Z_Axis_MMPerSecSq);
  if (isZ && !speedyStepperZ.moveToHomeInMillimeters(directionTowardHome_Z_Axis, homingSpeed_Z_Axis_MMPerSec, maxHomingDistance_Z_Axis_MM, Z_AXIS_LIMIT_SWITCH_PIN)) {
    while (true) {}
  }
  if (isY && !speedyStepperY.moveToHomeInMillimeters(directionTowardHome_Y_Axis, homingSpeed_Y_Axis_MMPerSec, maxHomingDistance_Y_Axis_MM, Y_AXIS_LIMIT_SWITCH_PIN)) {
    while (true) {}
  }
}

void Home_ZY() {
  moveToHome(true, true);
  //    saveCurrentPositon();
  position_Y_Axis_MM = speedyStepperY.getCurrentPositionInMillimeters() * 10;
  position_Z_Axis_MM = speedyStepperZ.getCurrentPositionInMillimeters() * 10;

}

void Home_Z() {
  moveToHome(true, false);
  //    saveCurrentPositon();
  position_Z_Axis_MM = speedyStepperZ.getCurrentPositionInMillimeters() * 10;
}

void moveStepper(SpeedyStepper &stepper, int dir, int &pos, float manualSpeed, float manualAcceleration, bool isRev = false) {
  bool Stop_Flag = false;
  setStepperParameters(stepper, manualSpeed, manualAcceleration, isRev);
  handleManualStepperMovement(stepper, dir, Stop_Flag);
  if (not isRev)
    pos = stepper.getCurrentPositionInMillimeters() * 10;
  else
    pos = stepper.getCurrentPositionInRevolutions() * 10;
  displayMenu();
}

void moveY(int dir) {
  //  Serial.println("move ");
  moveStepper(speedyStepperY, dir, position_Y_Axis_MM, manualSpeed_Y_Axis_MMPerSec, manualAcceleration_Y_Axis_MMPerSecSq);
  //  saveCurrentPositon();
  //  position_Y_Axis_MM = int(speedyStepperR.getCurrentPositionInMillimeters());
  //    Serial.println(position_Y_Axis_MM);
}

void moveZ(int dir) {
  moveStepper(speedyStepperZ, dir, position_Z_Axis_MM, manualSpeed_Z_Axis_MMPerSec, manualAcceleration_Z_Axis_MMPerSecSq);
  //  saveCurrentPositon();
  //  position_Z_Axis_MM = int(speedyStepperR.getCurrentPositionInMillimeters());
  //    Serial.println(position_Z_Axis_MM);
}
#ifdef THREADING_MACHINE
void moveR(int dir) {
  moveStepper(speedyStepperR, dir, position_R_Axis_REV, manualSpeed_R_Axis_MMPerSec, manualAcceleration_R_Axis_MMPerSecSq, true);
  //  position_R_Axis_MM = speedyStepperR.getCurrentPositionInRevolutions();
}
#endif

void displayMessage(const char *title, const char *message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(1000);
}

void saveDataAction() {
  displayMessage("####### SAVE #######", "! Data Saved !");
  saveAllParameters();
}

void loadDataAction() {
  displayMessage("####### LOAD #######", "! Data LOADE !");
  loadAllParameters();
}

void longPressHome() {
  if (millis() - buttonPressTime > longPressTime) {
    Home_ZY();
  }
}

void longPressStart() {
  if (millis() - buttonPressTime > longPressTime) {
    Start_process(origin_Y_Axis_MM, origin_Z_Axis_MM, true);
  }
}
