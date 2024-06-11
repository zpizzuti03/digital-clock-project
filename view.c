/* view.c -- view module for clock project (the V in MVC)
 *
 * Darren Provine, 17 July 2009
 * Zachary Pizzuti, 24 November 2023
 * Kyle Jasitis, 24 November 2023
 *
 * Copyright (C) Darren Provine, 2009-2023, All Rights Reserved
 */

#include "clock.h"
#include "view.h"

/* see "view.h" for list of bits that set properties */

int view_props = 0x00; // default is 24-hour mode, plain text

// returns old properties so you can save them if needed
void set_view_properties(int viewbits)
{
    view_props = viewbits;
}

int get_view_properties()
{
    return view_props;
}


void do_test(struct tm *dateinfo)
{
    // turn display bits on and off
    digit *where = get_display_location();
    for ( int i = 0; i <= 6; i++ ) {
	    if ( dateinfo->tm_sec % 2 == 0){
		    where[i] = 0x7F;			//0111 1111
		    if ( i == 8 ) {
			    where[i] = 0xFF;	//for colons to be correct
		    }
	    } else {
		    where[i] = 0x00;
	    }
    }
    //This is for side of clock and colons because setting where[7] = 0x7F disables a colon.
    if ( dateinfo->tm_sec % 2 == 0){
	    where[8] = 0xFF;
    } else {
	    where[8] = 0x00;
    }
              
    display();
    fflush(stdout);
}

#define MAX_TIMESTR 40 // big enough for any valid data
// make_timestring
// returns a string formatted from the "dateinfo" object.
char * make_timestring (struct tm *dateinfo)
{
    // TODO:
    // Declaring the pointer like this can lead to crashes or
    // mysterious output.
    // We'll see how to fix it in class.  NEVER DO THIS!
	char *timeformat = "(NO FORMAT SELECTED)";	// see strftime(3)

    /* TODO: add format strings for other settings
     * If not in LED mode, return the string as it should be printed.
     *   ' 5/25/2023 dt' (date of Towel Day) or '12:34:56 am'.
     *
     * If in LED mode, don't add slashes or colons; the LEDs can't
     *    do slashes, and the colons are controlled separately.
     *    Return something like ' 90423d' (Labor Day this year) or
     *    '123456a' (12:34:56 am).
     */
    if ( view_props & LED_MODE ){
    	if ( view_props & DATE_MODE ) {	
		if (( dateinfo->tm_mon < 10 )) {
			timeformat = " %-m%d%y dt";
		} else {
			timeformat = "%-m%d%y dt";
		}
	} else {
		if ( view_props & AMPM_MODE ) {
			//AMPM mode configuration/logic
                	if (( dateinfo->tm_hour >= 0 && dateinfo->tm_hour <= 11 )){
                        	timeformat = "%l%M%Sa";
                	} else {
                        	timeformat = "%l%M%Sp";
			}
		} else {
			timeformat = "%H%M%S2";
                        
		}
	}
    } else {
        if ( view_props & DATE_MODE ) {
            timeformat = "%-m/%d/%G dt";
        } else {
            if ( view_props & AMPM_MODE ) {
		//AMPM mode configuration/logic
		if(( dateinfo->tm_hour >= 0 && dateinfo->tm_hour <= 11 )){
			timeformat = "%l:%M:%S am";
		} else {
			timeformat = "%l:%M:%S pm";
		}

	    } else {
		timeformat = "%H:%M:%S 2";
	    }
        }
    }

    // make the timestring and return it
    static char timestring[MAX_TIMESTR];
    strftime(timestring, MAX_TIMESTR, timeformat, dateinfo);
    return timestring;
}

/* We get a pointer to a "struct tm" object, put it in a string, and
 * then send it to the screen.
 */
void show_led(struct tm *dateinfo)
{

    digit *where = get_display_location();
    int i;
    digit  bitvalues = 0;

    if ( view_props & TEST_MODE ) {
        do_test(dateinfo);
        return;
    }
    
    char *timestringreturn = make_timestring(dateinfo);

    for (i = 0; i < 6; i++) {
        // TODO:
        // Putting the call in the switch is inefficient and
        // makes debugging harder.  We'll fix this in class.
        // *INDENT-OFF*
        switch ( timestringreturn[i] ) {
            case ' ': bitvalues = 0x00; break;
            case '1': bitvalues = 0x50; break; //0101 0000
            case '2': bitvalues = 0x37; break; //0011 0111
            case '3': bitvalues = 0x57; break; //0101 0110
            case '4': bitvalues = 0x5A; break; //0101 1010
            case '5': bitvalues = 0x4F; break; //0100 1111
            case '6': bitvalues = 0x6F; break; //0110 1111
            case '7': bitvalues = 0x51; break; //0101 0000
            case '8': bitvalues = 0x7F; break; //0111 1111
            case '9': bitvalues = 0x5B; break; //0101 1011
            case '0': bitvalues = 0x7D; break; //0111 1101
        }
        // *INDENT-ON*
        where[i] = bitvalues;
    }
	//Colons: You will need ifs here, this does the colons
	//F is all colons, next number controls AM (1) and PM (2) 24HR (4) and DATE (8)
        if ( view_props & LED_MODE ) {
    		if ( view_props & DATE_MODE ) {
			where[8] = 0x08;
        	} else {
            		if ( view_props & AMPM_MODE ) {
                		//AMPM uses colons
                		if(( dateinfo->tm_hour >= 0 && dateinfo->tm_hour <= 11 )){
                        		where[8] = 0xF1;	
                		} else {
					where[8] = 0xF2;
                		}
            		} else {
                		where[8] = 0xF4;
           		}
		}
	}
    display();
    fflush(stdout);
}

void show_text(struct tm *dateinfo)
{
    printf("\r%s ", make_timestring(dateinfo));
    fflush(stdout);
}


void show(struct tm *dateinfo)
{
    if ( view_props & LED_MODE )
        show_led(dateinfo);
    else
        show_text(dateinfo);        
}
