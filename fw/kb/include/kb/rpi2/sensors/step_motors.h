/* INFO **
** INFO */

/* Header guard */
#ifndef KB_RPI2_SENSORS_STEP_MOTOR_H_1110703704466344
#define KB_RPI2_SENSORS_STEP_MOTOR_H_1110703704466344 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */
#include <kb/rpi2/types.h>
/*  type  : kb_rpi2_Event */
#include <kb/rpi2/sensors.h>
/*  type  : kb_rpi2_Sensor
    macro : kb_rpi2_SENSOR_MEMBERS */


/*----------------------------------------------------------------------------*/
#define KB_RPI2_SENSORS_STEP_MOTOR_MEMBERS()                                   \
    KB_RPI2_SENSOR_MEMBERS()
    /* TODO: add callback members: on_green, on_yellow, etc.. */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kb_rpi2_sensors_step_motor
{
    KB_RPI2_SENSORS_STEP_MOTOR_MEMBERS()
} kb_rpi2_sensors_StepMotor;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_new(kb_rpi2_sensors_StepMotor **const self,
                              kb_rpi2_Event              *const event,
                              kb_rpi2_PinId                     pin_in1,
                              kb_rpi2_PinId                     pin_in2,
                              kb_rpi2_PinId                     pin_in3,
                              kb_rpi2_PinId                     pin_in4);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_ini(kb_rpi2_sensors_StepMotor *const self,
                              kb_rpi2_Event             *const event,
                              kb_rpi2_PinId                    pin_in1,
                              kb_rpi2_PinId                    pin_in2,
                              kb_rpi2_PinId                    pin_in3,
                              kb_rpi2_PinId                    pin_in4);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_fin(kb_rpi2_sensors_StepMotor *const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_del(kb_rpi2_sensors_StepMotor **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate(kb_rpi2_sensors_StepMotor *const self,
                                 double                           rotation);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate_degree(kb_rpi2_sensors_StepMotor *const self,
                                        double                           degree);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_sensors_StepMotor_rotate_radian(kb_rpi2_sensors_StepMotor *const self,
                                        double                           radian);


#endif /* KB_RPI2_SENSORS_STEP_MOTOR_H_1110703704466344 */
