# digital-clock-project
The digital-clock-project contains code for a program that can run a digital clock both in a terminal window and through a simulated LED display. The clock has four modes, 24hr, ampm, date, and test. It can also be loaded with an offset to the current time in seconds and begin from there. In the simulated LED GUI there is also an indicator for which mode the clock is currently on. Each mode changes both the terminal and GUI clock's formatting to output information accordingly:  
- **24 Hour Mode:** 24hr mode is the default mode for the clock and displays the time in 24 Hour mode.  
- **AM/PM Mode:** ampm mode displays the time in AM/PM time with an indicator for AM or PM (A and P in terminal mode).  
- **Date Mode:** date mode displays the current date on the system when launched in the terminal, or for 5 seconds before returning to the previous display mode in LED mode.  
- **Test Mode:** test mode is only available in the simulated LED display. It will blink all of the LEDs on the clock including the mode indicators for 5 seconds before returning to the previous display mode.  

The following list provides details on each flag, run ./clock -h to find this list of flags as well:
This program displays a realtime clock.  
Usage: ./clock [-advh] [-o number]  
 -  -a    : am/pm instead of 24 hour  
 -  -d    : show date instead of time  
 -  -l    : use simulated LED display  
 -  -o #  : offset the time by # seconds   
 -  -v    : show version information  
 -  -h    : this help message  

