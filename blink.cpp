extern "C"
{
   #include <libopencm3/cm3/common.h>
   #include <libopencm3/stm32/rcc.h>
   #include <libopencm3/stm32/gpio.h>
}

static void my_delay_1( void )
{
   int i = 168e6/2/4;

   while( i > 0 )
     {
        i--;
        __asm__( "nop" );
     }
}

int main( void )
{
   // set the clock to 168mhz speed
   rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

   //LED2 - PD3
   // Enable GPIOD clock
   rcc_periph_clock_enable(RCC_GPIOD);
   gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
                   GPIO_PUPD_NONE, GPIO3);

   // LED1 - PC0
   rcc_periph_clock_enable(RCC_GPIOC);
   gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT,
                   GPIO_PUPD_NONE, GPIO0);

   while( 1 )
     {
        gpio_toggle(GPIOC, GPIO0);
        gpio_toggle(GPIOD, GPIO3);
        my_delay_1();
     }
}
