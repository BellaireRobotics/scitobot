#ifndef MAIN_H
#define MAIN_H

#include "IterativeRobot.h"
#include "Jaguar.h"
#include "Joystick.h"
#include "Relay.h"
#include "RobotDrive.h"
#include "Timer.h"
#include "Vision/AxisCamera.h"

class ScitoBot : public IterativeRobot {
  RobotDrive *drive;
  Joystick *rightStick;
  Joystick *leftStick;

  Jaguar *shooter;
  Jaguar *pickup;

  Relay *bridge;

public:
  unsigned int shooter_speed_selection;
  float shooter_speed;

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
