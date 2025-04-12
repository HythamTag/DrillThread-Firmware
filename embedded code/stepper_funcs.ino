void motorInit() {
  // Connect and configure the stepper motors to their IO pins
  speedyStepperY.connectToPins(Y_AXIS_MOTOR_STEP_PIN, Y_AXIS_MOTOR_DIRECTION_PIN);
  speedyStepperZ.connectToPins(Z_AXIS_MOTOR_STEP_PIN, Z_AXIS_MOTOR_DIRECTION_PIN);
  speedyStepperR.connectToPins(R_AXIS_MOTOR_STEP_PIN, R_AXIS_MOTOR_DIRECTION_PIN);  // Added for R-axis

  // Define number of steps required to move 1 mm (1x microstepping)
  speedyStepperY.setStepsPerMillimeter(microstepsPerRev_Y_Axis / mmPerRev_Y_Axis_BallScrew);
  speedyStepperZ.setStepsPerMillimeter(microstepsPerRev_Z_Axis / mmPerRev_Z_Axis_BallScrew);
  speedyStepperR.setStepsPerRevolution(microstepsPerRev_R_Axis);  // Added for R-axis

  // Set linear movement speeds
  speedyStepperY.setSpeedInMillimetersPerSecond(velocity_Y_Axis_MMPerSec );
  speedyStepperZ.setSpeedInMillimetersPerSecond(velocity_Z_Axis_MMPerSec );
  speedyStepperR.setSpeedInRevolutionsPerSecond(velocity_R_Axis_MMPerSec );

  // Set linear movement accelerations
  speedyStepperY.setAccelerationInMillimetersPerSecondPerSecond(acceleration_Y_Axis_MMPerSecSq);
  speedyStepperZ.setAccelerationInMillimetersPerSecondPerSecond(acceleration_Z_Axis_MMPerSecSq );
  speedyStepperR.setAccelerationInRevolutionsPerSecondPerSecond(acceleration_R_Axis_MMPerSecSq );

  // Optional: Load last motor position
  speedyStepperY.setCurrentPositionInMillimeters(position_Y_Axis_MM);
  speedyStepperZ.setCurrentPositionInMillimeters(position_Z_Axis_MM);
}

void moveStepper(SpeedyStepper &stepper, float distance, bool isRelative = true) {
  if (isRelative) {
    stepper.setupRelativeMoveInMillimeters(distance );
  } else {
    stepper.setupMoveInMillimeters(distance );
  }
  while (!stepper.motionComplete() && !Stop_Flag) {
    stepper.processMovement();
    if (Stop_Flag) {
      break;
    }
  }
}

void setStepperParameters(SpeedyStepper &stepper, float speed, float acceleration, bool isRev = false) {
  if (!isRev) {
    stepper.setSpeedInMillimetersPerSecond(speed);
    stepper.setAccelerationInMillimetersPerSecondPerSecond(acceleration );
  } else {
    stepper.setSpeedInRevolutionsPerSecond(speed );
    stepper.setAccelerationInRevolutionsPerSecondPerSecond(acceleration );
  }
}

void handleManualStepperMovement(SpeedyStepper &stepper, int direction, bool &Stop_Flag) {
    stepper.setupRelativeMoveInMillimeters(-direction * 999);
    int buttonPin = (direction == 1) ? DECREMENT_BUTTON_PIN :INCREMENT_BUTTON_PIN;
    while (!stepper.motionComplete()) {
        stepper.processMovement();
        if (digitalRead(buttonPin) != Button_Condition && !Stop_Flag) {
            stepper.setupStop();
            Stop_Flag = true;
            break;
        }
    }
}
