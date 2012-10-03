#ifndef MAIN_H
#define MAIN_H

#include "AnalogChannel.h"
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

  AnalogChannel *gyroChannel;
  Gyro *gyro;

  Ultrasonic *sonar;
  AnalogChannel *sonar_ping;
  AnalogChannel *sonar_echo;

  Encoder *enc_shooter;
  Encoder *enc_right;
  Encoder *enc_left;

  static const float Kp = 0.03;
  float angle;

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
