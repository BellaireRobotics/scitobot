#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  leftStick = new Joystick(1);
  rightStick = new Joystick(2);

  shooter = new Jaguar(4);
  pickup = new Jaguar(5);

  bridge = new Relay(1);

  // AxisCamera &cam = AxisCamera::GetInstance();
}

void ScitoBot::RobotInit(void) {
  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(0.1);
  drive->SetSafetyEnabled(true);
}

void ScitoBot::DisabledInit(void) {
}

void ScitoBot::AutonomousInit(void) {
}

void ScitoBot::TeleopInit(void) {
}

void ScitoBot::DisabledPeriodic(void) {
}

void ScitoBot::AutonomousPeriodic(void) {
  drive->Drive(0.0, 0.0); // stop!
}

void ScitoBot::TeleopPeriodic(void) {
  drive->TankDrive(leftStick, rightStick);

  // Shooter - Right Joy (Trigger)
  if (rightStick->GetTrigger()) {
    shooter->Set((-rightStick->GetThrottle() + 1) / 2);
  } else {
    shooter->Set(0.0);
  }

  // Pickup: Forward - Left Joy (3) || Backward - Left Joy (2)
  if (leftStick->GetRawButton(3)) {
    pickup->Set((-leftStick->GetThrottle() + 1) / 2);
  } else if (leftStick->GetRawButton(2)) {
    pickup->Set((leftStick->GetThrottle() - 1) / 2);
  } else {
    pickup->Set(0.0);
  }

  // Bridge: Up - Right Joy (3) || Down - Right Joy (2)
  if (rightStick->GetRawButton(3)) {
    bridge->Set(Relay::kForward);
  } else if (rightStick->GetRawButton(2)) {
    bridge->Set(Relay::kReverse);
  } else {
    bridge->Set(Relay::kOff);
  }
}

void ScitoBot::DisabledContinuous(void) {
}

void ScitoBot::AutonomousContinuous(void) {
}

void ScitoBot::TeleopContinuous(void) {
}

START_ROBOT_CLASS(ScitoBot);
