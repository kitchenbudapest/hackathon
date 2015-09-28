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
    kb_rpi2_Pin_UNSET,
    kb_rpi2_Pin_LOW,
    kb_rpi2_Pin_HIGH,
} kb_rpi2_PinState;


/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Pin_OFF,
    kb_rpi2_Pin_UP,
    kb_rpi2_Pin_DOWN,
} kb_rpi2_PinPull;


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
    kb_rpi2_PIN10,

    kb_rpi2_PIN11,
    kb_rpi2_PIN12,
    kb_rpi2_PIN13,
    kb_rpi2_PIN14,
    kb_rpi2_PIN15,
    kb_rpi2_PIN16,
    kb_rpi2_PIN17,
    kb_rpi2_PIN18,
    kb_rpi2_PIN19,
    kb_rpi2_PIN20,

    kb_rpi2_PIN21,
    kb_rpi2_PIN22,
    kb_rpi2_PIN23,
    kb_rpi2_PIN24,
    kb_rpi2_PIN25,
    kb_rpi2_PIN26,
    kb_rpi2_PIN27,
    kb_rpi2_PIN28,
    kb_rpi2_PIN29,
    kb_rpi2_PIN30,

    kb_rpi2_PIN31,
    kb_rpi2_PIN32,
    kb_rpi2_PIN33,
    kb_rpi2_PIN34,
    kb_rpi2_PIN35,
    kb_rpi2_PIN36,
    kb_rpi2_PIN37,
    kb_rpi2_PIN38,
    kb_rpi2_PIN39,
    kb_rpi2_PIN40,

    /* Has to be the last enum */
    kb_rpi2_PINS_COUNT,
} kb_rpi2_PinId;



/*----------------------------------------------------------------------------*/
typedef enum
{
    kb_rpi2_Sensor_ENABLED,
    kb_rpi2_Sensor_DISABLED,
} kb_rpi2_SensorState;


#endif /* KB_RPI2_ENUMS_H_6642544826973767 */
