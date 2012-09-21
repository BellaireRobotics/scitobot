#ifndef MAIN_H
#define MAIN_H 1

#include "Encoder.h"
#include "Gyro.h"
#include "IterativeRobot.h"
#include "Joystick.h"
#include "RobotDrive.h"
#include "Timer.h"
#include "Ultrasonic.h"
#include "Vision/AxisCamera.h"

class ScitoBot : public IterativeRobot {
  RobotDrive *drive;
  Joystick *rightStick;
  Joystick *leftStick;
  Gyro *gyro;
  Ultrasonic *sonar;
  Encoder *encoder;

public:
  ScitoBot(void);

  void RobotInit(void);
  void DisabledInit(void);
  void AutonomousInit(void);
  void TeleopInit(void);
  void DisabledPeriodic(void);
  void AutonomousPeriodic(void);
  void TeleopPeriodic(void);
  void DisabledContinuous(void);
  void AutonomousContinuous(void);
  void TeleopContinuous(void);
};

#endif
