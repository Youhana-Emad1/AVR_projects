/*
 *
 * @file GPIO_interface.h
 * @author Kareem Hussein
 * @brief header file that contain GPIO public functions prototyoes, macros and declarations
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


typedef enum
{
	GPIO_PORTA=0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF,
	GPIO_PORTG,
	GPIO_PORTH
}GPIO_portId_t;

typedef enum
{
	GPIO_PIN0=0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15
}GPIO_pinId_t;

typedef enum
{
	GPIO_PIN_LOW=0,
	GPIO_PIN_HIGH,
}GPIO_pinValue_t;

typedef enum
{
	GPIO_INPUT=0,
	GPIO_OUTPUT,
	GPIO_ALTERNATE_FUNCTION,
	GPIO_ANALOG
}GPIO_pinMode_t;

typedef enum
{
	GPIO_MEDIUM=1,
	GPIO_LOW,
	GPIO_HIGH
}GPIO_pinOutputSpeed_t;

typedef enum
{
	GPIO_PUSH_PULL=0,
	GPIO_OPEN_DRAIN
}GPIO_pinOutputType_t;

typedef enum
{
	GPIO_AF0=0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
}GPIO_pinAltFunc_t;

typedef enum
{
	GPIO_NO_PULL=0,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
}GPIO_pinPullUpDown_t;	

typedef struct
{
	GPIO_portId_t portId;
	GPIO_pinId_t pinId;
	GPIO_pinMode_t pinMode;
	GPIO_pinOutputSpeed_t pinSpeed;
	GPIO_pinOutputType_t pinOutputType;
	GPIO_pinPullUpDown_t pinPullType;
	GPIO_pinAltFunc_t pinAltFunc;
}GPIO_pinConfig_t;


                                        /*** APIS Proto Types ***/
				
uint8_t GPIO_u8InitPin       (const GPIO_pinConfig_t* copy_pStrPinConfig);
uint8_t GPIO_u8SetPinValue   (GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId, GPIO_pinValue_t copy_enuPinValue);
uint8_t GPIO_u8TogglePinValue(GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId);
uint8_t GPIO_u8GetPinValue   (GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId, GPIO_pinValue_t* copy_PEnuPinValue);


#endif