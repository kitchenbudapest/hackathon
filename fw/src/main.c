/* INFO **
** INFO */

/* Include standard headers */
#include <stdio.h>  /*
    func  : printf
*/
#include <stdlib.h> /*
    const : EXIT_FAILURE
            EXIT_SUCCESS
*/
#include <stdbool.h> /*
    type  : bool
    const : true
            false
*/


/* Include wiringPi headers */
#include <wiringPi.h> /*
    func  : wiringPiSetup
            pinMode
            digitalWrite
            delay
    const : OUTPUT
            HIGH
            LOW
*/


/*----------------------------------------------------------------------------*/
int
main(void)
{
    wiringPiSetup();
    pinMode(0, OUTPUT);

    while (true)
    {
        digitalWrite(0, HIGH);
        delay(500);
        digitalWrite(0, LOW);
        delay(500);
    }

    return EXIT_SUCCESS;
}
