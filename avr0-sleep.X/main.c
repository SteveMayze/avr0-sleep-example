/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#define F_CPU 20000000UL
#include "mcc_generated_files/mcc.h"
#include <avr/sleep.h>

#define LOGGER_LEVEL_OFF 0
#define LOGGER_LEVEL_ERROR 1
#define LOGGER_LEVEL_INFO 2
#define LOGGER_LEVEL_DEBUG 4
#define LOGGER_LEVEL_ALL 7

#define LOGGER_LEVEL LOGGER_LEVEL_ALL 


#include "logger.h"

#include <util/delay.h>
bool tick;

void pit_cb(void)
{
    /* Clear flag by writing '1': */
    RTC.PITINTFLAGS = RTC_PI_bm;
    LOG_INFO("TICK \n");

    tick = true;
}

/*
    Main application
*/
int main(void)
{
    SYSTEM_Initialize();
    sleep_disable();

    LOG_INFO("Starting \n");
    
    RTC_SetPITIsrCallback( pit_cb );

    _delay_ms(1000);

    /* Enable Global Interrupts */
    sei();
    RTC_EnablePITInterrupt();
    while (1) 
    {
        
        /* Put the CPU in sleep */
        for(uint8_t i = 0; i < 4; i++){
            sleep_mode();
//            {
//                RTC_DisablePITInterrupt();
//                LOG_INFO("   peek %d \n", i);
//                RTC_EnablePITInterrupt();
//            };
        }
        
        LOG_INFO("Waking \n");
        
        if (tick){
            RTC_DisablePITInterrupt();
            LOG_INFO(">> TOCK \n");
            LED_Toggle();
            tick = false;
            _delay_ms(5000);
            RTC_EnablePITInterrupt();
        }    
    }

}
/**
    End of File
*/