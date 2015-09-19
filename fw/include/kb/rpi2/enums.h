/* INFO **
** INFO */

#ifndef KB_RPI2_ENUMS_H_6642544826973767
#define KB_RPI2_ENUMS_H_6642544826973767 1

/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Pin_OUTPUT,
    kb_rpi2_Pin_INPUT,
} kb_rpi2_PinRole;


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_HIGH,
} kb_rpi2_PinState;



/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_PIN1,
    kb_rpi2_PIN2,
    kb_rpi2_PIN3,
    kb_rpi2_PIN4,
    kb_rpi2_PIN5,
    kb_rpi2_PIN6,
    kb_rpi2_PIN7,
    kb_rpi2_PIN8,
    kb_rpi2_PIN9,
} kb_rpi2_PinId;



/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Sensor_ENABLED,
    kb_rpi2_Sensor_DISABLED,
} kb_rpi2_SensorState;


#endif /* KB_RPI2_ENUMS_H_6642544826973767 */
