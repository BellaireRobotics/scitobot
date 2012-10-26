#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  left_joy = new Joystick(1);
  right_joy = new Joystick(2);

  shooter = new Jaguar(4);
  pickup = new Jaguar(5);

  bridge = new Relay(1);

  auto_time = new Timer();
}

void ScitoBot::RobotInit(void) {
  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(0.05);
  drive->SetSafetyEnabled(true);

  shooter_speed_selection = 1; // default to button speed control
  shooter_speed = 0.75; // default shooter speed
}

void ScitoBot::DisabledInit(void) {
}

void ScitoBot::AutonomousInit(void) {
  auto_time->Start(); // Start a timer to delay pickup motor.
}

void ScitoBot::TeleopInit(void) {
}

void ScitoBot::DisabledPeriodic(void) {
}

void ScitoBot::AutonomousPeriodic(void) {
  shooter->Set(1.0);

  // Check if 5 seconds (5000 milliseconds) has passed.
  if (auto_time->Get() > 5000) {
    pickup->Set(0.75);

    auto_time->Stop();
  }
}

void ScitoBot::TeleopPeriodic(void) {
  drive->TankDrive(left_joy, right_joy);

  // Shooter - Button Speed Selection
  if (shooter_speed_selection == 1) {
    if (right_joy->GetRawButton(6)) {
      shooter_speed = 0.25;
    } else if (right_joy->GetRawButton(7)) {
      shooter_speed = 0.50;
    } else if (right_joy->GetRawButton(11)) {
      shooter_speed = 0.75;
    } else if (right_joy->GetRawButton(10)) {
      shooter_speed = 1.0;
    }

    if (right_joy->GetTrigger()) {
      shooter->Set(shooter_speed);
    }
  }

  // Shooter - Throttle Speed Selection
  if (shooter_speed_selection == 2) {
    if (right_joy->GetTrigger()) {
      shooter->Set(NORMALIZE(right_joy->GetThrottle()));
    } else {
      shooter->Set(0.0);
    }
  }

  // Select Button/Throttle Speed Control
  if (right_joy->GetRawButton(8)) {
    shooter_speed_selection = 1;
  } else if (right_joy->GetRawButton(9)) {
    shooter_speed_selection = 2;
  }

  // Pickup: Up - Left Joy (3) or Left Trigger || Reverse - Left Joy (2)
  if (left_joy->GetRawButton(3)) {
    pickup->Set(NORMALIZE(left_joy->GetThrottle()));
  } else if (left_joy->GetTrigger()) {
    pickup->Set(NORMALIZE(left_joy->GetThrottle()));
  } else if (left_joy->GetRawButton(2)) {
    pickup->Set(-NORMALIZE(left_joy->GetThrottle()));
  } else {
    pickup->Set(0.0);
  }

  // Bridge: Up - Right Joy (3) || Down - Right Joy (2)
  if (right_joy->GetRawButton(3)) {
    bridge->Set(Relay::kForward);
  } else if (right_joy->GetRawButton(2)) {
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
