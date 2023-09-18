#ifndef QBOT_CURSES_H
#define QBOT_CURSES_H

#include "qbot.h"

void
qbot_initialize_curses()
{
  initscr();
  curs_set(0);
}

void
qbot_print_curses_sensors(qbot _qbot)
{
  qbot_inputs inputs = _qbot.inputs;

  erase(); 
  mvprintw(1,0,"Right wheel encoder: %d",inputs.encoder.wheel.right);
  mvprintw(2,0,"Left  wheel encoder: %d",inputs.encoder.wheel.left);
  mvprintw(3,0,"Right Bumper:        %d",inputs.digital.bumper.right);
  mvprintw(4,0,"Center Bumper:       %d",inputs.digital.bumper.center);
  mvprintw(5,0,"Left Bumper:         %d",inputs.digital.bumper.left);
  mvprintw(6,0,"Right Wheel drop     %d",inputs.digital.wheel_drop.right);
  mvprintw(7,0,"Left Wheel drop      %d",inputs.digital.wheel_drop.left);
  mvprintw(8,0,"Right cliff          %d",inputs.digital.cliff.right);
  mvprintw(9,0,"Center cliff         %d",inputs.digital.cliff.center);
  mvprintw(10,0,"Left cliff           %d",inputs.digital.cliff.left);
  mvprintw(11,0,"Button B0            %d",inputs.digital.button.b0);
  mvprintw(12,0,"Button B1            %d",inputs.digital.button.b1);
  mvprintw(13,0,"Button B2            %d",inputs.digital.button.b2);
  /* mvprintw(14,0,"DOCK_IR_RIGHT_NEAR_RIGHT %d",inputs.digital[DOCK_IR_RIGHT_NEAR_RIGHT]); */
  /* mvprintw(15,0,"DOCK_IR_RIGHT_NEAR_CENTER %d",inputs.digital[DOCK_IR_RIGHT_NEAR_CENTER]); */
  /* mvprintw(16,0,"DOCK_IR_RIGHT_NEAR_LEFT %d",inputs.digital[DOCK_IR_RIGHT_NEAR_LEFT]); */
  /* mvprintw(17,0,"DOCK_IR_RIGHT_FAR_RIGHT %d",inputs.digital[DOCK_IR_RIGHT_FAR_RIGHT]); */
  /* mvprintw(18,0,"DOCK_IR_RIGHT_FAR_CENTER %d",inputs.digital[DOCK_IR_RIGHT_FAR_CENTER]); */
  /* mvprintw(19,0,"DOCK_IR_RIGHT_FAR_LEFT %d",inputs.digital[DOCK_IR_RIGHT_FAR_LEFT]); */
  /* mvprintw(20,0,"DOCK_IR_CENTRAL_NEAR_RIGHT %d",inputs.digital[DOCK_IR_CENTRAL_NEAR_RIGHT]); */
  /* mvprintw(21,0,"DOCK_IR_CENTRAL_NEAR_CENTER %d",inputs.digital[DOCK_IR_CENTRAL_NEAR_CENTER]); */
  /* mvprintw(22,0,"DOCK_IR_CENTRAL_NEAR_LEFT %d",inputs.digital[DOCK_IR_CENTRAL_NEAR_LEFT]); */
  /* mvprintw(23,0,"DOCK_IR_CENTRAL_FAR_RIGHT %d",inputs.digital[DOCK_IR_CENTRAL_FAR_RIGHT]); */
  /* mvprintw(24,0,"DOCK_IR_CENTRAL_FAR_CENTER %d",inputs.digital[DOCK_IR_CENTRAL_FAR_CENTER]); */
  /* mvprintw(25,0,"DOCK_IR_CENTRAL_FAR_LEFT %d",inputs.digital[DOCK_IR_CENTRAL_FAR_LEFT]); */
  /* mvprintw(26,0,"DOCK_IR_LEFT_NEAR_RIGHT %d",inputs.digital[DOCK_IR_LEFT_NEAR_RIGHT]); */
  /* mvprintw(27,0,"DOCK_IR_LEFT_NEAR_CENTER %d",inputs.digital[DOCK_IR_LEFT_NEAR_CENTER]); */
  /* mvprintw(28,0,"DOCK_IR_LEFT_NEAR_LEFT %d",inputs.digital[DOCK_IR_LEFT_NEAR_LEFT]); */
  /* mvprintw(29,0,"DOCK_IR_LEFT_FAR_RIGHT %d",inputs.digital[DOCK_IR_LEFT_FAR_RIGHT]); */
  /* mvprintw(30,0,"DOCK_IR_LEFT_FAR_CENTER %d",inputs.digital[DOCK_IR_LEFT_FAR_CENTER]); */
  /* mvprintw(31,0,"DOCK_IR_LEFT_FAR_LEFT %d",inputs.digital[DOCK_IR_LEFT_FAR_LEFT]); */

  mvprintw(31,0,"ANGLE_Z_AXIS %f",inputs.other.angle_z_axis);
  mvprintw(32,0,"GYROSCOPE_X %f",inputs.other.gyroscope.x);
  mvprintw(33,0,"GYROSCOPE_Y %f",inputs.other.gyroscope.y);
  mvprintw(34,0,"GYROSCOPE_Z %f",inputs.other.gyroscope.z);
  mvprintw(35,0,"WHEEL_PWM_RIGHT %f",inputs.other.wheel_pwm.right);
  mvprintw(36,0,"WHEEL_PWM_LEFT %f",inputs.other.wheel_pwm.left);
  mvprintw(37,0,"TIMESTAMP %f",inputs.other.timestamp);
  mvprintw(38,0,"CHARGER_STATE %f",inputs.other.charger_state);
}

#endif /* QBOT_CURSES_H */
