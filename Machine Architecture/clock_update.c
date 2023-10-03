#include "clock.h"
#include <stdio.h>

int set_tod_from_ports(tod_t *tod) {
    int time = TIME_OF_DAY_PORT; //creating a variable to hold time of day value for a shorthand
    
    if (time > 1382400 || time < 0) { //Error handling for if TIME_OF_DAY_PORT exceeds a day or is negative
        return 1;
    }
    
    tod -> day_secs = ((time + 8) >> 4); //if you add .5 to a any decimal number, then cut off the decimal (leaving only the whole number), that is the same as rounding. In this case, I add 8, then bitshift right by 4 places to get a desired "division" by 16, and that leaves me with rounded seconds in a day

    if (tod -> day_secs < 43200) { //Changing the value of ampm based on if rounded day_secs is less than or equal to or greater than the value equivalent to 12pm
        tod -> ampm = 1;
    } else {
        tod -> ampm = 2;
    }
    
    if (tod -> day_secs == 0) { // Special case 0, everything must be set to 0
        tod -> time_hours = 12;
        tod -> time_mins = 0;
        tod -> time_secs = 0;
    } else if (tod -> day_secs < 3600) { // The case for the first hour of the day, it doesn't have the upper hours to use to calculate values, so I just had to change up the calculations a bit
        tod -> time_hours = 12;
        tod -> time_mins = tod -> day_secs / 60;
        tod -> time_secs = tod -> day_secs - (tod -> time_mins * 60);
    } else { // setting hours, mins, and secs for any time 1AM and on
        tod -> time_hours = (tod -> day_secs / 60) / 60;
        tod -> time_mins = (tod -> day_secs / 60) - (tod -> time_hours * 60);
        tod -> time_secs = tod -> day_secs - (tod -> time_hours * 60 * 60) - (tod -> time_mins * 60);
    }

    if (tod -> time_hours > 12) { // if the hours value is past 12, reset it by subtracting 12 to get the current hour of day
        tod -> time_hours = tod -> time_hours - 12;
    }

    return 0;
}

int set_display_from_tod(tod_t tod, int *display) {
    if (tod.day_secs > 86400 || tod.day_secs < 0 || tod.time_hours < 0 ||tod.time_hours > 12 ||  tod.time_secs < 0 || tod.time_secs >= 60 || tod.time_mins < 0 || tod.time_mins >= 60 || (tod.ampm != 2 && tod.ampm != 1)) { //error handling for any fields that are off
        return 1;
    } 

    *display = 0b000000000000000000000000000000; //Digits are as following: 1110111 = 0, 0100100 = 1, 1011101 = 2, 1101101 = 3, 0101110 = 4, 1101011 = 5, 1111011 = 6, 0100101 = 7, 1111111 = 8, 1101111 = 9, 0000000 = Blank, 0001000 = negative
            
    switch (tod.ampm) { //tens of hours place
        case 1: *display = *display | (0b1 << 28); break; //AM Setting
        case 2: *display = *display | (0b1 << 29); break; //PM Setting
    }

    switch (tod.time_hours / 10) { //tens of hours place
        case 0: *display = *display | (0b0000000 << 21); break; //displays nothing
        case 1: *display = *display | (0b0100100 << 21); break; //displays a 1
    }

    switch (tod.time_hours % 10) { //hours place (each case is one possible digit)
        case 0: *display = *display | (0b1110111 << 14); break;
        case 1: *display = *display | (0b0100100 << 14); break;
        case 2: *display = *display | (0b1011101 << 14); break;
        case 3: *display = *display | (0b1101101 << 14); break;
        case 4: *display = *display | (0b0101110 << 14); break;
        case 5: *display = *display | (0b1101011 << 14); break;
        case 6: *display = *display | (0b1111011 << 14); break;
        case 7: *display = *display | (0b0100101 << 14); break;
        case 8: *display = *display | (0b1111111 << 14); break;
        case 9: *display = *display | (0b1101111 << 14); break;
    }

    switch (tod.time_mins / 10) { //tens of minutes place (each case is one possible digit)
        case 0: *display = *display | (0b1110111 << 7); break;
        case 1: *display = *display | (0b0100100 << 7); break;
        case 2: *display = *display | (0b1011101 << 7); break;
        case 3: *display = *display | (0b1101101 << 7); break;
        case 4: *display = *display | (0b0101110 << 7); break;
        case 5: *display = *display | (0b1101011 << 7); break;
        case 6: *display = *display | (0b1111011 << 7); break;
        case 7: *display = *display | (0b0100101 << 7); break;
        case 8: *display = *display | (0b1111111 << 7); break;
        case 9: *display = *display | (0b1101111 << 7); break;
    }

    switch (tod.time_mins % 10) { //minutes place (each case is one possible digit)
        case 0: *display = *display | (0b1110111); break;
        case 1: *display = *display | (0b0100100); break;
        case 2: *display = *display | (0b1011101); break;
        case 3: *display = *display | (0b1101101); break;
        case 4: *display = *display | (0b0101110); break;
        case 5: *display = *display | (0b1101011); break;
        case 6: *display = *display | (0b1111011); break;
        case 7: *display = *display | (0b0100101); break;
        case 8: *display = *display | (0b1111111); break;
        case 9: *display = *display | (0b1101111); break;
    }

    return 0;
}

int clock_update() {
    tod_t new; //uninitialized struct

    if(set_tod_from_ports(&new) == 1) { //struct passed in to update fields w/error handling
        return 1;
    }; 

    if(set_display_from_tod(new, &CLOCK_DISPLAY_PORT) == 1) { //struct time is updated w/error handling
        return 1;
    }; 

    return 0;
}