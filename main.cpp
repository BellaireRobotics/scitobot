#include "main.h"

ScitoBot::ScitoBot(void) {
  drive = new RobotDrive(1, 2);
  left_joy = new Joystick(1);
  right_joy = new Joystick(2);

  shooter = new Jaguar(4);
  pickup = new Jaguar(5);

  bridge = new Relay(1);

  dash = SmartDashboard::GetInstance();
}

void ScitoBot::RobotInit(void) {
  GetWatchdog().SetEnabled(false);
  drive->SetExpiration(0.05);
  drive->SetSafetyEnabled(true);
}

void ScitoBot::DisabledInit(void) {
}

void ScitoBot::AutonomousInit(void) {
  pickup_delay_done = 0;
}

void ScitoBot::TeleopInit(void) {
  shooter_speed_selection = 1; // default to button speed control
  shooter_speed = 0.0; // default shooter speed

  pickup_speed_selection = 2; // default to throttle speed control
  pickup_speed = 0.0; // default pickup speed
}

void ScitoBot::DisabledPeriodic(void) {
}

void ScitoBot::AutonomousPeriodic(void) {
  shooter->Set(0.4);

  if (pickup_delay_done == 0) {
    Wait(3.0);
    pickup_delay_done = 1;
  }

  pickup->Set(0.50);
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

    shooter->Set(shooter_speed);
  }

  // Shooter - Throttle Speed Selection
  if (shooter_speed_selection == 2) {
    if (right_joy->GetTrigger()) {
      shooter_speed = NORMALIZE(right_joy->GetThrottle());
      shooter->Set(shooter_speed);
    } else {
      shooter->Set(0.0);
    }
  }

  // Shooter - Select Button/Throttle Speed Control
  if (right_joy->GetRawButton(8)) {
    shooter_speed_selection = 1;
    shooter_speed = 0;
  } else if (right_joy->GetRawButton(9)) {
    shooter_speed_selection = 2;
  }


  // Pickup - Button Speed Selection
  if (pickup_speed_selection == 1) {
    if (left_joy->GetRawButton(6)) {
      pickup_speed = 0.25;
    } else if (left_joy->GetRawButton(7)) {
      pickup_speed = 0.50;
    } else if (left_joy->GetRawButton(11)) {
      pickup_speed = 0.75;
    } else if (left_joy->GetRawButton(10)) {
      pickup_speed = 1.0;
    }

    pickup->Set(pickup_speed);
  }

  // Pickup Throttle: Up - Left Joy (3) or Left Trigger || Reverse - Left Joy (2)
  if (pickup_speed_selection == 2) {
    if (left_joy->GetRawButton(3)) {
      pickup->Set(NORMALIZE(left_joy->GetThrottle()));
    } else if (left_joy->GetTrigger()) {
      pickup_speed = NORMALIZE(left_joy->GetThrottle());
      pickup->Set(pickup_speed);
    } else if (left_joy->GetRawButton(2)) {
      pickup->Set(-NORMALIZE(left_joy->GetThrottle()));
    } else {
      pickup->Set(0.0);
    }
  }

  // Pickup - Select Button/Throttle Speed Control
  if (left_joy->GetRawButton(8)) {
    pickup_speed_selection = 1;
    pickup_speed = 0;
  } else if (left_joy->GetRawButton(9)) {
    pickup_speed_selection = 2;
  }

  // Bridge: Up - Right Joy (3) || Down - Right Joy (2)
  if (right_joy->GetRawButton(3)) {
    bridge->Set(Relay::kForward);
  } else if (right_joy->GetRawButton(2)) {
    bridge->Set(Relay::kReverse);
  } else {
    bridge->Set(Relay::kOff);
  }

  // Push data values to Dashboard
  dash->PutDouble("shooter_speed", shooter_speed);
  dash->PutInt("shooter_mode", shooter_speed_selection);
  dash->PutDouble("pickup_speed", pickup_speed);
  dash->PutInt("pickup_mode", pickup_speed_selection);
}

void ScitoBot::DisabledContinuous(void) {
}

void ScitoBot::AutonomousContinuous(void) {
}

void ScitoBot::TeleopContinuous(void) {
}

START_ROBOT_CLASS(ScitoBot);
