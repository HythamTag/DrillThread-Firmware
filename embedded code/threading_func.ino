#ifdef THREADING_MACHINE

void screwHole(float diameter, float depth, float safeDistance, float stepDownTimes, float rotationalAcceleration, float rotationalSpeed) {
  float totalDepth = -depth - safeDistance;
  float pitch = getPitchFromDiameter(diameter);
  float translationalAcceleration = rotationalAcceleration * pitch;
  float translationalSpeed = rotationalSpeed * pitch;

  // float PROGMEM totalDepth = -depth - safeDistance;
  // float PROGMEM pitch = getPitchFromDiameter(diameter);
  // float PROGMEM translationalAcceleration = rotationalAcceleration * pitch;
  // float PROGMEM translationalSpeed = rotationalSpeed * pitch;
  // pgm_read_float(&totalDepth);

  setStepperParameters(speedyStepperZ, translationalSpeed, translationalAcceleration);
  setStepperParameters(speedyStepperR, rotationalSpeed, rotationalAcceleration, true);

  delay(500);

  int stages = ceil(-totalDepth / stepDownTimes);
  // Serial.print("pitch : ");
  // Serial.println(pitch);
  // Serial.print("depth : ");
  // Serial.println(depth);
  // Serial.print("safeDistance : ");
  // Serial.println(safeDistance);
  // Serial.print("totalDepth : ");
  // Serial.println(totalDepth);
  // Serial.print("stepDownTimes : ");
  // Serial.println(stepDownTimes);

  // Serial.print("rotationalSpeed : ");
  // Serial.println(rotationalSpeed);
  // Serial.print("rotationalAcceleration : ");
  // Serial.println(rotationalAcceleration);


  // Serial.print("translationalSpeed : ");
  // Serial.println(translationalSpeed);
  // Serial.print("translationalAcceleration : ");
  // Serial.println(translationalAcceleration);


  // Serial.print("Stages : ");
  // Serial.println(stages);

  for (int stage = 1; stage <= stages; stage++) {
    float currentDepth = max(totalDepth, -stepDownTimes * stage);
    // float relativeDepth = currentDepth + stepDownTimes * (stage - 1);
    float currentRotation = -currentDepth / pitch;

    speedyStepperZ.setupRelativeMoveInMillimeters(currentDepth);
    speedyStepperR.setupRelativeMoveInRevolutions(currentRotation);

    processMovements();

    speedyStepperZ.setupRelativeMoveInMillimeters(-currentDepth);
    speedyStepperR.setupRelativeMoveInRevolutions(-currentRotation);

    processMovements();
  }

  setStepperParameters(speedyStepperY, velocity_Y_Axis_MMPerSec, acceleration_Y_Axis_MMPerSecSq);
  setStepperParameters(speedyStepperZ, velocity_Z_Axis_MMPerSec, acceleration_Z_Axis_MMPerSecSq);
  setStepperParameters(speedyStepperR, velocity_R_Axis_MMPerSec, acceleration_R_Axis_MMPerSecSq, true);
}

void processMovements() {
  while (!speedyStepperR.motionComplete() || !speedyStepperZ.motionComplete()) {
    speedyStepperR.processMovement();
    speedyStepperZ.processMovement();
  }
}

float getPitchFromDiameter(float diameter) {
  // static const float isoDiameters[] = { 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 24.0, 30.0, 36.0, 42.0, 48.0 };
  // static const float isoPitches[] = { 0.5, 0.7, 0.8, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0 };

  for (int i = 0; i < sizeof(isoDiameters) / sizeof(isoDiameters[0]); i++) {
    if (diameter == float(pgm_read_word(&isoDiameters[i]))) {
      return pgm_read_float(&isoPitches[i]);
    }
  }
  return 0.0;
}
#endif
