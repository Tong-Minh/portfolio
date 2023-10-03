#include "clock.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int testsrun = 0;

// void showbits(int);
#define PRINT_TEST \
  sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\"} P==1{print}' %s", __LINE__, __FILE__); \
  system(sysbuf); \
  testsrun++;

void test_print_tod(tod_t *tod){
  printf("tod = {\n"); 
  printf("  .day_secs   = %d\n",tod->day_secs);
  printf("  .time_hours = %d\n",tod->time_hours);
  printf("  .time_mins  = %d\n",tod->time_mins);
  printf("  .time_secs  = %d\n",tod->time_secs);
  printf("  .ampm       = %d\n",tod->ampm);
  printf("}\n");
}

void print_ports(){
  printf("%-18s : %d\n","TIME_OF_DAY_PORT", TIME_OF_DAY_PORT);
  printf("%-18s : %s\n","CLOCK_DISPLAY_PORT",bitstr(CLOCK_DISPLAY_PORT,INT_BITS));
  printf("%-18s : %s\n","index",bitstr_index(INT_BITS));
}

void print_display_and_ports(int ret, int *dispint){
  printf("ret: %d\n",ret);
  printf("%-18s : ","dispint bits");
  printf("%s\n",bitstr(*dispint, INT_BITS));
  printf("%-18s : ","index");
  printf("%s\n",bitstr_index(INT_BITS));
  printf("\n");  print_ports();  printf("\n");
  CLOCK_DISPLAY_PORT = *dispint;
  printf("Display based on dispint:\n");
  print_clock_display();
}

int main(int argc, char *argv[]){
  int all = 0;
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  if(strcmp(test_name, "all")==0){
    all = 1;
  }

  int *dispint = malloc(sizeof(int)); // heap allocate to allow valgrind
  tod_t *tod = malloc(sizeof(tod_t)); // to check memory accesses
  int ret = -1;
  if(0){}

  if( all==1 || strcmp( test_name, "midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input 
    TIME_OF_DAY_PORT  = 0;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "midnight-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod->day_secs   = 3;
    tod->time_hours = 12;
    tod->time_mins  = 0;
    tod->time_secs  = 0;
    tod->ampm       = 1;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = 0;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "after-midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input 
    TIME_OF_DAY_PORT  = (0*3600 + 3*60 + 45)*16 + 0;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-midnight-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. NOTE: time_secs if 45 but the
    // displayed Minutes should NOT be rounded up.
    tod->day_secs   = 0*3600 + 3*60 + 45;
    tod->time_hours = 12;
    tod->time_mins  = 3;
    tod->time_secs  = 45;
    tod->ampm       = 1;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (0*3600 + 3*60 + 45)*16 + 0;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "round-seconds-up" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input. In this
    // there are 13/16 seconds so the minutes should
    // round up (time_sec from 30 to 31)
    TIME_OF_DAY_PORT  = (0*3600 + 17*60 + 30)*16 + 13;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "after-1am-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input 
    TIME_OF_DAY_PORT  = (1*3600 + 42*60 + 7)*16 + 5;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1am-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = 1*3600 + 52*60 + 7;
    tod->time_hours = 1;
    tod->time_mins  = 42;
    tod->time_secs  = 7;
    tod->ampm       = 1;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1am-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (1*3600 + 42*60 + 7)*16 + 5;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "nearly-noon-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input 
    TIME_OF_DAY_PORT  = (11*3600 + 59*60 + 57)*16 + 5;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-noon-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = 11*3600 + 58*60 + 57;
    tod->time_hours = 11;
    tod->time_mins  = 58;
    tod->time_secs  = 57;
    tod->ampm       = 1;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-noon-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (11*3600 + 59*60 + 57)*16 + 5;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "is-noon-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input 
    TIME_OF_DAY_PORT  = (12*3600 + 0*60 + 2)*16 + 3;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "is-noon-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = (12*3600 + 0*60 + 2);
    tod->time_hours = 11;
    tod->time_mins  = 58;
    tod->time_secs  = 57;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "is-noon-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (12*3600 + 0*60 + 2)*16 + 3;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "after-1pm-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input. 
    // Round seconds up for this port value.
    TIME_OF_DAY_PORT  = (13*3600 + 47*60 + 19)*16 + 9;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1pm-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = (13*3600 + 47*60 + 20);
    tod->time_hours = 1;
    tod->time_mins  = 47;
    tod->time_secs  = 20;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1pm-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    // Round seconds up for this port value.
    TIME_OF_DAY_PORT  = (13*3600 + 2*60 + 0)*16 + 9;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-4pm-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input. 
    TIME_OF_DAY_PORT  = (16*3600 + 9*60 + 0)*16 + 7;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-4pm-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = (16*3600 + 9*60 + 0);
    tod->time_hours = 4;
    tod->time_mins  = 9;
    tod->time_secs  = 0;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-4pm-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (16*3600 + 9*60 + 0)*16 + 7;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-10pm-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (22*3600 + 46*60 + 21)*16 + 3;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "nearly-midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_ports() sets
    // the time correctly for given input. 
    TIME_OF_DAY_PORT  = (23*3600 + 58*60 + 59)*16 + 2;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-midnight-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct. 
    tod->day_secs   = (23*3600 + 58*60 + 59);
    tod->time_hours = 11;
    tod->time_mins  = 58;
    tod->time_secs  = 59;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_PORT
    TIME_OF_DAY_PORT  = (23*3600 + 58*60 + 59)*16 + 2;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "check-initialized-set" )==0 ) {
    PRINT_TEST;
    // Tests whether all fields of set_tod_from_ports()
    // initializes all fields of the struct. Valgrind
    // will report errors for printing some fields if
    // they are not all fully intialized.
    TIME_OF_DAY_PORT  = 0;
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    printf("tod = {\n"); 
    printf("  .day_secs   = %d\n",tod->day_secs);
    printf("  .time_hours = %d\n",tod->time_hours);
    printf("  .time_mins  = %d\n",tod->time_mins);
    printf("  .time_secs  = %d\n",tod->time_secs);
    printf("  .ampm       = %d\n",tod->ampm);
    printf("}\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "check-initialized-display" )==0 ) {
    PRINT_TEST;
    // Tests whether the int pointed to by dispint is
    // fully initialized by set_display_from_tod().
    // Valgrind will report errors when tryint to print
    // it if all bits are not set in it. Typically this
    // is done by setting dispint to 0 at the start of
    // the function.
    tod->day_secs   = (5*3600 + 19*60 + 48);
    tod->time_hours = 5;
    tod->time_mins  = 19;
    tod->time_secs  = 48;
    tod->ampm       = 1;
    ret = set_display_from_tod(*tod, dispint);
    printf("dispint in hex: %08X\n", *dispint);
  } // ENDTEST



  if( all==1 || strcmp( test_name, "check-anything-display" )==0 ) {
    PRINT_TEST;
    // Tests whether the int pointed to by dispint can be
    // an arbitrary bit pattern and
    // set_display_from_tod() will still work correctly,
    // that it is not assuemd to be 0 or FFF...
    tod->day_secs   = (5*3600 + 19*60 + 48);
    tod->time_hours = 5;
    tod->time_mins  = 19;
    tod->time_secs  = 48;
    tod->ampm       = 1;
    *dispint = 0xFFFFFFFF;
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    *dispint = 0xAAAAAAAA;
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    *dispint = 0x02020202;
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST


  if( all==1 || strcmp( test_name, "field-ranges-display" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_from_tod() checks for
    // ranges of hours, minutes, seconds, etc. and errors
    // out if they are invalid.
    printf("HOURS BAD\n");
    tod->day_secs   = (22*3600 + 31*60 + 33);
    tod->time_hours = -5;       // negative
    tod->time_mins  = 31;
    tod->time_secs  = 33;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    *dispint = -1;              // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    printf("MINUTES BAD\n");
    tod->day_secs   = (22*3600 + 31*60 + 33);
    tod->time_hours = 22;
    tod->time_mins  = 76;       // too large
    tod->time_secs  = 33;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    *dispint = 0;              // should stay 0
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    printf("SECONDS BAD\n");
    tod->day_secs   = (22*3600 + 31*60 + 33);
    tod->time_hours = 22;
    tod->time_mins  = 31;
    tod->time_secs  = -33;      // negative
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    *dispint = -1;              // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    printf("AMPM BAD\n");
    tod->day_secs   = (22*3600 + 31*60 + 33);
    tod->time_hours = 22;
    tod->time_mins  = 31;
    tod->time_secs  = -33;      // negative
    tod->ampm       = 0;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = 0;     // should stay -1
    *dispint = 0;               // should stay 0
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST


  if( all==1 || strcmp( test_name, "repeated-calls-set" )==0 ) {
    PRINT_TEST;
    // Tests whether repeated calls to set_tod_from_ports() 
    // work correctly for given inputs. 
    printf("\n====AFTER 1 AM====\n");
    TIME_OF_DAY_PORT  = (1*3600 + 36*60 + 18)*16 + 2;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
    printf("\n====NEARLY MIDNIGHT====\n");
    TIME_OF_DAY_PORT  = (23*3600 + 54*60 + 13)*16 + 1;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
    printf("\n====LATE MORNING (round seconds up)====\n");
    TIME_OF_DAY_PORT  = (10*3600 + 46*60 + 35)*16 + 12;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "repeated-calls-display" )==0 ) {
    PRINT_TEST;
    // Tests repeated set_display_from_tod() 
    // calls to determine if it works correctly 
    printf("\n====LATE MORNING====\n");
    tod->day_secs   = (11*3600 + 13*60 + 29);
    tod->time_hours = 11;
    tod->time_mins  = 13;
    tod->time_secs  = 29;
    tod->ampm       = 1;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    printf("\n====JUST AFTER NOON====\n");
    tod->day_secs   = (12*3600 + 1*60 + 54);
    tod->time_hours = 12;
    tod->time_mins  = 1;
    tod->time_secs  = 54;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
    printf("\n====AFTER 8 PM====\n");
    tod->day_secs   = (18*3600 + 7*60 + 6);
    tod->time_hours = 8;
    tod->time_mins  = 7;
    tod->time_secs  = 6;
    tod->ampm       = 2;
    TIME_OF_DAY_PORT  = -1;     // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    ret = set_display_from_tod(*tod, dispint);
    print_display_and_ports(ret, dispint);
  } // ENDTEST


  if( all==1 || strcmp( test_name, "repeated-calls-update" )==0 ) {
    PRINT_TEST;
    // Tests whether repeated calls to clock_update()
    // work correctly for given inputs. 
    printf("\n====AFTER 12 AM====\n");
    TIME_OF_DAY_PORT  = (0*3600 + 35*60 + 21)*16 + 4;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
    printf("\n====AFTER 8 AM====\n");
    TIME_OF_DAY_PORT  = (8*3600 + 11*60 + 2)*16 + 3;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
    printf("\n====AFTER 11 PM====\n");
    TIME_OF_DAY_PORT  = (23*3600 + 3*60 + 48)*16 + 12;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // updates DISPLAY
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  if( all==1 || strcmp( test_name, "bad-port-range-set" )==0 ) {
    PRINT_TEST;
    // Checks that when the port has a negative or
    // too-large value, set_tod_from_ports() errors
    // out and does not alter the tod struct
    TIME_OF_DAY_PORT  = -211;   // negative
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    tod->day_secs   = 0;
    tod->time_hours = 0;        // should not change these
    tod->time_mins  = 0;
    tod->time_secs  = 0;
    tod->ampm       = 0;
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
                         // port is too high
    TIME_OF_DAY_PORT  = (24*3600 + 3*60 + 2)*16 + 5;
    CLOCK_DISPLAY_PORT = -1;    // should stay -1
    tod->day_secs   = -1;
    tod->time_hours = -1;        // should not change these
    tod->time_mins  = -1;
    tod->time_secs  = -1;
    tod->ampm       = -1;
    ret = set_tod_from_ports( tod );
    printf("returned: %d\n",ret);
    test_print_tod( tod );
    print_ports();
  } // ENDTEST


  if( all==1 || strcmp( test_name, "bad-port-range-update" )==0 ) {
    PRINT_TEST;
    // Checks that when the port has a negative or
    // too-large value, clock_update() errors
    // out and does not alter anything.
    TIME_OF_DAY_PORT  = (25*3600 + 23*60 + 32)*16 + 2;
    CLOCK_DISPLAY_PORT = -1;
    ret = clock_update();   // should error
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();

    TIME_OF_DAY_PORT  = -4097;
    CLOCK_DISPLAY_PORT = 0;
    ret = clock_update();   // should error
    printf("ret: %d\n",ret);
    print_ports();  printf("\n");
    printf("Display based on CLOCK_DISPLAY_PORT:\n");
    print_clock_display();
  } // ENDTEST

  free(dispint);
  free(tod);

  if(testsrun == 0){
    printf("WARNING: 0 tests run\n");
    printf("test_name: %s\n",test_name);
  }

  return 0;
}
