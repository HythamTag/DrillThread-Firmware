void displayMenu() {
  lcd.clear();
  if (currentSubMenu == NULL) {
    displayMainMenu();
  } else {
    displaySubMenu();
  }
}

void displayMainMenu() {
  int menuCount = sizeof(menusWithSubs) / sizeof(menusWithSubs[0]);

  int lastVisibleItem = min(firstVisibleItem + NUM_ROWS - 1, menuCount - 1);
  for (int i = firstVisibleItem; i <= lastVisibleItem; i++) {
    lcd.setCursor(0, i - firstVisibleItem);
    if (&menusWithSubs[i] == currentMenu) {
      lcd.print(">");
    }
    lcd.print(menusWithSubs[i].mainItem.displayName);
  }
}

void displaySubMenu() {
  int lastVisibleSubItem = min(firstVisibleSubItem + NUM_ROWS - 1, currentMenu->subItemCount - 1);
  for (int i = firstVisibleSubItem; i <= lastVisibleSubItem; i++) {
    lcd.setCursor(0, i - firstVisibleSubItem);
    if (&currentMenu->subItems[i] == currentSubMenu) {
      lcd.print(F(">"));
    }
    lcd.print(currentMenu->subItems[i].displayName);

    if (currentMenu->subItems[i].itemValue != nullptr) {
      if (adjustingValue && &currentMenu->subItems[i] == currentSubMenu) {
        lcd.setCursor(12, i - firstVisibleSubItem);
        lcd.print(F("["));
        lcd.setCursor(19, i - firstVisibleSubItem);
        lcd.print(F("]"));
      }
      lcd.setCursor(13, i - firstVisibleSubItem);
      if (currentMenu->subItems[i].targetArray != NULL) {
        lcd.print(pgm_read_word(&currentMenu->subItems[i].targetArray[(int)(*(currentMenu->subItems[i].itemValue)) - 1]));
      } else {
        lcd.print(float(*(currentMenu->subItems[i].itemValue)) / 10);
      }
    }
  }
}

void scrollMenu(int direction) {
  if (currentSubMenu == NULL) {
    scrollMainMenu(direction);
    // Serial.println("scroll Menu");
  } else {
    // Serial.println("scroll Sub Menu");
    scrollSubMenu(direction);
  }
  displayMenu();
}

void scrollMainMenu(int direction) {
  int menuCount = sizeof(menusWithSubs) / sizeof(menusWithSubs[0]);
  int newIndex = (currentMenu - menusWithSubs) + direction;

  if (newIndex >= 0 && newIndex < menuCount) {
    currentMenu += direction;
    adjustVisibleItems(direction, firstVisibleItem, NUM_ROWS, newIndex);
  }
}

void scrollSubMenu(int direction) {
  if (!adjustingValue) {
    int newIndex = (currentSubMenu - currentMenu->subItems) + direction;
    // Serial.print("newIndex : ");
    // Serial.print(newIndex);
    // Serial.print("  firstVisibleSubItem : ");
    // Serial.print(firstVisibleSubItem);
    // Serial.print("direction : ");
    // Serial.println(direction);
    if (newIndex >= 0 && newIndex < currentMenu->subItemCount) {
      currentSubMenu += direction;
      adjustVisibleItems(direction, firstVisibleSubItem, NUM_ROWS, newIndex);
    }
  } else {
    currentSubMenu->adjustFunction(direction);
  }
}

void adjustVisibleItems(int direction, int &firstVisible, int numRows, int newIndex) {
  // int newIndex = firstVisible + direction;
  // Serial.print("newIndex : ");
  // Serial.print(newIndex);
  // Serial.print("  firstVisible : ");
  // Serial.print(firstVisible);
  // Serial.print("direction : ");
  // Serial.println(direction);
  if (direction > 0 && newIndex >= firstVisible + numRows) {
    firstVisible++;
  } else if (direction < 0 && newIndex < firstVisible) {
    firstVisible--;
  }
}


void adjustValueWithinLimits(float &value, float lowerLimit, float upperLimit) {
  if (upperLimit != NULL ) {
    if (value > upperLimit)
    {
//      Serial.println( "upper");
//      Serial.println( value );
//      Serial.println(upperLimit != NULL);
//      Serial.println( value > upperLimit);
//      Serial.println( upperLimit );
//      Serial.println( "done");
      value = upperLimit;
    }

  }
  if (lowerLimit != NULL)  {
    if (value < lowerLimit)
    {
//      Serial.println( "lower");
//      Serial.println( value );
//      Serial.println(lowerLimit != NULL);
//      Serial.println( value < lowerLimit);
//      Serial.println( "done");
      value = lowerLimit;
    }
  }

}

void defaultAdjust(int direction) {
  if (currentSubMenu->itemValue != NULL) {  // Ensure itemValue is not null
    float changeValue = (currentSubMenu->changeValue);
    float currentValue = *(currentSubMenu->itemValue) - direction * changeValue;
//    Serial.println(*(currentSubMenu->itemValue));
//    Serial.println( currentSubMenu->lowerLimit);
//    Serial.println( currentSubMenu->upperLimit);
//    Serial.println(changeValue);
//    Serial.println(currentValue);


    adjustValueWithinLimits(currentValue, currentSubMenu->lowerLimit, currentSubMenu->upperLimit);
//    Serial.println(currentValue);
    *(currentSubMenu->itemValue) = int(currentValue);
//    Serial.println(currentValue);
//    Serial.println("###############");
    if (currentSubMenu->actionFunction != NULL) {
      currentSubMenu->actionFunction(direction);
    }
  }
}

void enterSubMenu() {
  if (currentSubMenu == NULL) {
    if (currentMenu->subItems != NULL) {
      currentSubMenu = &currentMenu->subItems[0];
      firstVisibleSubItem = 0;
    } else {
      executeMenuAction(currentMenu->mainItem);
    }
  } else {
    executeMenuAction(*currentSubMenu);
  }
  displayMenu();
}

void executeMenuAction(const MenuItem &item) {
  if (item.itemValue != NULL) {
    adjustingValue = true;
  } else {
    item.actionFunction(1);
  }
}

void leaveSubMenu() {
  if (currentSubMenu != NULL) {
    if (currentSubMenu->itemValue != NULL && adjustingValue) {
      adjustingValue = false;
    } else {
      currentSubMenu = NULL;
    }
    displayMenu();
  }
}

void handleButtonPress(int buttonPin, void (*action)()) {
  unsigned long currentTime = millis();
  if (digitalRead(buttonPin) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = currentTime;
    }
    unsigned long elapsedTime = currentTime - buttonPressTime;
    if (elapsedTime > 1000) {
      currentDelay /= 2;
      buttonPressTime = currentTime;
    }
    action();
    delay(currentDelay);
  }
}

void checkButtons() {
  unsigned int currentTime = millis();

  if (digitalRead(INCREMENT_BUTTON_PIN) == LOW) {
    if (buttonPressTime == 0) {  // First time button is pressed
      buttonPressTime = currentTime;
    }

    unsigned int elapsedTime = currentTime - buttonPressTime;
    if (elapsedTime > 1000) {         // If more than 1 second has passed
      currentDelay /= 2;              // Halve the delay
      buttonPressTime = currentTime;  // Reset the button press time
    }

    scrollMenu(-1);
    delay(currentDelay);  // Use the adjusted delay

  } else if (digitalRead(DECREMENT_BUTTON_PIN) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = currentTime;
    }

    unsigned int elapsedTime = currentTime - buttonPressTime;
    if (elapsedTime > 1000) {
      currentDelay /= 2;
      buttonPressTime = currentTime;
    }

    scrollMenu(1);
    delay(currentDelay);

  } else if (digitalRead(ENTER_BUTTON_PIN) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = currentTime;
    }

    unsigned long elapsedTime = currentTime - buttonPressTime;
    if (elapsedTime > 1000) {
      currentDelay /= 2;
      buttonPressTime = currentTime;
    }

    enterSubMenu();
    delay(currentDelay);

  } else if (digitalRead(BACK_BUTTON_PIN) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = currentTime;
    }

    unsigned int elapsedTime = currentTime - buttonPressTime;
    if (elapsedTime > 1000) {
      currentDelay /= 2;
      buttonPressTime = currentTime;
    }

    leaveSubMenu();
    delay(currentDelay);

  } else {
    // If no button is pressed, reset the button press time and delay
    buttonPressTime = 0;
    currentDelay = 200;
  }
}

bool allButtonsReleased() {
  return digitalRead(INCREMENT_BUTTON_PIN) == HIGH && digitalRead(DECREMENT_BUTTON_PIN) == HIGH && digitalRead(ENTER_BUTTON_PIN) == HIGH && digitalRead(BACK_BUTTON_PIN) == HIGH;
}

void resetButtonState() {
  buttonPressTime = 0;
  currentDelay = 200;
}
