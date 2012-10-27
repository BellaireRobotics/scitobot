#ifndef MAIN_H
#define MAIN_H

#include "IterativeRobot.h"
#include "Jaguar.h"
#include "Joystick.h"
#include "Relay.h"
#include "RobotDrive.h"
#include "SmartDashboard/SmartDashboard.h"

#define NORMALIZE(v) (-v + 1) / 2

class ScitoBot : public IterativeRobot {
  RobotDrive *drive;
  Joystick *left_joy;
  Joystick *right_joy;

  Jaguar *shooter;
  Jaguar *pickup;

  Relay *bridge;

  SmartDashboard *dash;

public:
  unsigned int shooter_speed_selection;
  float shooter_speed;
  unsigned int pickup_speed_selection;
  float pickup_speed;

  unsigned int pickup_delay_done;

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
