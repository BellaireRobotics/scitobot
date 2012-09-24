#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  rightStick = new Joystick(1);
  leftStick = new Joystick(2);
  gyro = new Gyro(1);
  // sonar = new Ultrasonic(ULTRASONIC_ECHO_PULSE_OUTPUT, ULTRASONIC_TRIGGER_PULSE_INPUT);
  encoder = new Encoder(1, 2, true);
  AxisCamera &cam = AxisCamera::GetInstance();
}

void ScitoBot::RobotInit(void) {
  drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(0.1);
  drive->SetSafetyEnabled(true);
}

void ScitoBot::DisabledInit(void) {
}

void ScitoBot::AutonomousInit(void) {
  gyro->Reset(); // Calibrate - Set heading to 0.
}

void ScitoBot::TeleopInit(void) {
}

void ScitoBot::DisabledPeriodic(void) {
}

void ScitoBot::AutonomousPeriodic(void) {
  static const float Kp = 0.03; // proportional constant for gyro re-align
  float angle = gyro->GetAngle();

  drive->Drive(0.25, 0.0);
  Wait(0.25);

  // Mess up the heading on purpose
  drive->Drive(0.25, 0.5);
  Wait(0.25);

  drive->Drive(-1.0, -angle * Kp);
  Wait(0.5);

  drive->Drive(0.0, 0.0);
  Wait(0.5);
}

void ScitoBot::TeleopPeriodic(void) {
  drive->TankDrive(leftStick, rightStick);
}

void ScitoBot::DisabledContinuous(void) {
}

void ScitoBot::AutonomousContinuous(void) {
}

void ScitoBot::TeleopContinuous(void) {
}

START_ROBOT_CLASS(ScitoBot);
