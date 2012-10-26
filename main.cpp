#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  leftStick = new Joystick(1);
  rightStick = new Joystick(2);

  shooter = new Jaguar(4);
  pickup = new Jaguar(5);

  bridge = new Relay(1);
}

void ScitoBot::RobotInit(void) {
  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(0.1);
  drive->SetSafetyEnabled(true);

  shooter_speed_selection = 2;
  shooter_speed = 1.0;
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
  shooter->Set(1.0);
  Wait(5.0);
  pickup->Set(0.75);
}

void ScitoBot::TeleopPeriodic(void) {
  drive->TankDrive(leftStick, rightStick);

  // Shooter - Right Joy (Trigger)
  /*
  if (rightStick->GetTrigger()) {
    shooter->Set((-rightStick->GetThrottle() + 1) / 2);
  } else {
    shooter->Set(0.0);
  }
  */

  if (shooter_speed_selection == 1) {
    if (rightStick->GetRawButton(6)) {
      shooter_speed = 0.25;
    } else if (rightStick->GetRawButton(7)) {
      shooter_speed = 0.50;
    } else if (rightStick->GetRawButton(11)) {
      shooter_speed = 0.75;
    } else if (rightStick->GetRawButton(10)) {
      shooter_speed = 1.0;
    }

    shooter->Set(shooter_speed);
  }

  if (shooter_speed_selection == 2) {
    if (rightStick->GetTrigger()) {
      shooter->Set((-rightStick->GetThrottle() + 1) / 2);
    } else {
      shooter->Set(0.0);
    }
  }

  if (rightStick->GetRawButton(8)) {
    shooter_speed_selection = 1;
  } else if (rightStick->GetRawButton(9)) {
    shooter_speed_selection = 2;
  }

  // Pickup: Forward - Left Joy (3) || Backward - Left Joy (2)
  if (leftStick->GetRawButton(3)) {
    pickup->Set((-leftStick->GetThrottle() + 1) / 2);
  } else if (leftStick->GetTrigger()) {
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
