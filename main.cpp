#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  rightStick = new Joystick(1);
  leftStick = new Joystick(2);

  gyroChannel = new AnalogChannel(14);
  gyro = new Gyro(gyroChannel);

  /* Sonar | What channels?
  sonar_ping = new AnalogChannel(2);
  sonar_echo = new AnalogChannel(3);
  sonar = new Ultrasonic(sonar_ping, sonar_echo);
  */

  shooter_encoder_chan = new AnalogChannel(1);
  // shooter_encoder = new Encoder(shooter_encoder_chan); // fix args

  // Camera not mounted and connected yet.
  // AxisCamera &cam = AxisCamera::GetInstance();
}

void ScitoBot::RobotInit(void) {
  drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(5.0);
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

  drive->Drive(0.3, 0.0);
  Wait(0.5);

  drive->Drive(-0.3, -angle * Kp);
  Wait(0.5);

  drive->Drive(0.3, 0.3);
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
