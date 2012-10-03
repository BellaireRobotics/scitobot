#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  rightStick = new Joystick(1);
  leftStick = new Joystick(2);

  gyroChannel = new AnalogChannel(2);
  gyro = new Gyro(gyroChannel);

  /* Sonar | What channels?
  sonar_ping = new AnalogChannel(2);
  sonar_echo = new AnalogChannel(3);
  sonar = new Ultrasonic(sonar_ping, sonar_echo);
  */

  enc_shooter = new Encoder(1, 2);
  enc_right = new Encoder(3, 4);
  enc_left = new Encoder(5, 6);

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
  angle = gyro->GetAngle();
  printf("angle = %f\n", angle);

  //drive->Drive(-0.4, -angle * 1);
  drive->Drive(0.2, 0.0);
  Wait(2.0);

  drive->Drive(-0.2, 0.0);
  Wait(8.0);

  /*
  drive->Drive(-0.5, 0.0);
  Wait(1.0);
  */

  drive->Drive(0.0, 0.0); // stop!
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
