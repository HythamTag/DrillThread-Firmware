# CNC Drilling and Threading Controller

An advanced CNC controller built for drilling and threading operations using an Arduino UNO. Designed with modular C/C++ components and menu-based LCD interaction, this controller ensures accurate, flexible, and user-friendly control of multi-axis stepper systems.

> ⚠️ **Note:** This project is functional but still in need of **code refactoring and cleanup** to improve structure, naming consistency, and full separation of concerns.

---

## 🎯 Key Features

- ✅ **Multi-Axis Stepper Control** using SpeedyStepper library
- ✅ **LCD Menu System** for intuitive navigation and real-time tuning
- ✅ **EEPROM Parameter Saving** to retain user preferences across sessions
- ✅ **Dedicated Drilling and Threading Modes**
- ✅ **Modular Codebase** structured with reusability in mind
- ⚠️ **Work-in-Progress Refactoring**: Several `.ino` files are still being migrated to `.h/.cpp` format

---

## 📽️ Demo Video

<div align="center">
  <a href="https://www.youtube.com/watch?v=bgPlOXEIMDQ">
    <img src="https://img.youtube.com/vi/bgPlOXEIMDQ/hqdefault.jpg" alt="Watch the video" />
  </a>
</div>


---



<!--
## 🗂️ Project Structure
```
cnc-drilling-controller/
├── include/
│   └── EEPROMManager.h
├── lib/
│   ├── EEPROM/           # EEPROM read/write manager
│   ├── LCD/              # LCD menu and UI navigation
│   ├── Memory/           # Runtime state utilities
│   ├── Stepper/          # Axis motion control
│   ├── Drilling/         # Drilling process control
│   ├── Threading/        # Threading process logic
│   └── Items/            # Custom menu items logic
├── src/
│   └── main.cpp          # Application entry point (to be implemented)
├── README.md
└── platformio.ini        # PlatformIO project configuration
```
-->

> ⚙️ **Refactoring in progress**: `.ino` files are being modularized. Some logic is still duplicated or needs relocation into proper C++ classes.

---

## 🛠 Hardware Requirements

- Arduino UNO
- 16x2 or 20x4 I2C LCD Display
- Stepper Motors & Drivers (A4988, DRV8825, etc.)
- External Power Supply
- User Input Buttons

---

## 🔧 Software Requirements

- Arduino IDE
- Arduino Libraries:
  - `SpeedyStepper`
  - `LiquidCrystal_I2C`
  - `EEPROM`

---

## 🧠 How It Works

1. On boot, machine parameters are loaded from EEPROM.
2. LCD displays a menu to select modes and adjust values.
3. Upon command, stepper motors execute precise sequences.
4. Changes to parameters are saved automatically.

---

## 📌 To-Do

- [ ] Complete `.ino` to `.h/.cpp` modularization
- [ ] Refactor global variables into encapsulated classes
- [ ] Implement jog control and better user input
- [ ] Integrate limit switch safety logic
- [ ] Add spindle and toolpath support
- [ ] Finalize `main.cpp` orchestration

---

## 🤝 Contributions

Pull requests and feedback are welcome! Please fork and suggest improvements.
