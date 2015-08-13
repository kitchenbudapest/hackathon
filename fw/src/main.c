/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>  /*
    const : stderr
    func  : puts
            fputs
*/
#include <stdlib.h> /*
    func  : exit
    const : EXIT_FAILURE
            EXIT_SUCCESS
*/
#include <stdbool.h> /*
    type  : bool
    const : true
            false
*/
#include <stdint.h> /*
    type  : uint8_t
*/
#include <signal.h> /*
    func  : signal
    const : SIGINT
            SIG_ERR
*/


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include bcm2835 headers */
#include <bcm2835.h> /*
    func  : bcm2835_init
            bcm2835_gpio_fsel
            bcm2835_gpio_set
            bcm2835_gpio_clr
            bcm2835_gpio_clr_multi
            bcm2835_delay
            bcm2835_close
    const : HIGH
            LOW
            RPI_V2_GPIO_P1_11
            BCM2835_GPIO_FSEL_OUTP
*/



/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include UNIX specific headers */
#include <unistd.h> /*
    func :  geteuid
*/



#define LED_PIN RPI_BPLUS_GPIO_J8_11
#define FK0_PIN RPI_BPLUS_GPIO_J8_26
#define FK1_PIN RPI_BPLUS_GPIO_J8_18
#define FK2_PIN RPI_BPLUS_GPIO_J8_16
#define FK3_PIN RPI_BPLUS_GPIO_J8_24
#define FK4_PIN RPI_BPLUS_GPIO_J8_22



/*----------------------------------------------------------------------------*/
static void
on_interrupt(int signal)
{
    /* Ignore unused variable */
    (void)signal;

    /* Clean up */
    bcm2835_gpio_clr(LED_PIN);
    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_clr(FK0_PIN);
    bcm2835_gpio_fsel(FK0_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(FK1_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(FK2_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(FK3_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(FK4_PIN, BCM2835_GPIO_FSEL_INPT);

    bcm2835_close();

    /* Terminate the program */
    puts("\nExiting now...\n");
    exit(EXIT_SUCCESS);
}



/*----------------------------------------------------------------------------*/
int
main(void)
{
    if (geteuid() != 0)
    {
        fputs("You have to be root to run this.\n"
              "(Maybe you forgot to use `sudo`?)\n", stderr);
        goto NotRoot_Error;
    }

    /* Initialize library */
    if (!bcm2835_init())
    {
        fputs("An error occured during the "
              "initialization of bcm2835\n", stderr);
        goto Bcm2835_Init_Error;
    }

    /* Set up signal catching */
    if (signal(SIGINT, on_interrupt) == SIG_ERR)
    {
        fputs("An error occured during the signal "
              "handler initialization\n", stderr);
        goto Signal_Init_Error;
    }

    /* Led pin */
    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_OUTP);

    /* Matrix keyboard row pin */
    bcm2835_gpio_fsel(FK0_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_set(FK0_PIN);

    /* Matrix keyboard columns pins */
    size_t  i;
    uint8_t columns[] =
    {
        FK1_PIN,
        FK2_PIN,
        FK3_PIN,
        FK4_PIN,
    };

    for (i=0; i<((sizeof columns)/sizeof(uint8_t)); i++)
    {
        bcm2835_gpio_fsel(columns[i], BCM2835_GPIO_FSEL_INPT);
        bcm2835_gpio_set_pud(columns[i], BCM2835_GPIO_PUD_UP);
    }

    /* Enter main loop */
    while (true)
    {
        /* Set row down to LOW */
        bcm2835_gpio_clr(FK0_PIN);

        /* If key-1 pressed */
        if (!bcm2835_gpio_lev(FK1_PIN))
            bcm2835_gpio_set(LED_PIN);
        /* If key-2 pressed */
        if (!bcm2835_gpio_lev(FK2_PIN))
            bcm2835_gpio_clr(LED_PIN);
        /* If key-3 pressed */
        if (!bcm2835_gpio_lev(FK3_PIN))
            puts("Key-3 Pressed!");
        /* If key-4 pressed */
        if (!bcm2835_gpio_lev(FK4_PIN))
        {
            puts("Shutting down...\n");
            bcm2835_gpio_clr(LED_PIN);
            bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_INPT);

            bcm2835_gpio_clr(FK0_PIN);
            bcm2835_gpio_fsel(FK0_PIN, BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_fsel(FK1_PIN, BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_fsel(FK2_PIN, BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_fsel(FK3_PIN, BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_fsel(FK4_PIN, BCM2835_GPIO_FSEL_INPT);
            return EXIT_SUCCESS;
        }

        /* Set row back to HIGH */
        bcm2835_gpio_set(FK0_PIN);
    }

    /* If there was a problem */
    Signal_Init_Error:
        bcm2835_close();
    Bcm2835_Init_Error:
    NotRoot_Error:
        return EXIT_FAILURE;
}
