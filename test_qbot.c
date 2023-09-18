
#include <stdlib.h>

#include "qbot.h"
#include "qbot_curses.h"

int
main(int argc, char * argv[])
{

  quanser_bind_functions();
	
  qbot myqbot = {0};
  qbot_initialize(&myqbot);

  qbot_initialize_curses();
  
  char ch;
  if(nodelay(stdscr,TRUE)==ERR){
    return -1;
  }
  int stop = 0;
  for(;;){

    qbot_read(&myqbot);

    ch = getch();

    qbot_outputs * outputs = &myqbot.outputs;

    if(ch!=ERR){
      if(ch==68){ // left
    	if(stop) {
	  outputs->other.wheel_velocity.right=0.0;
	  outputs->other.wheel_velocity.left=0.0;
    	} else {
	  outputs->other.wheel_velocity.right=0.1;
	  outputs->other.wheel_velocity.left=0.1;
    	}
    	stop=!stop;
      }
      if(ch==67){ // right
	outputs->other.predefined_sound++;
	if(outputs->other.predefined_sound>6) {
	  outputs->other.predefined_sound=0;
	}
      }
      if(ch==66){ // right
    	if(stop) {
    	  outputs->other.custom_pitch=0.0;
    	} else {
    	  outputs->other.custom_pitch=440.;
    	}
    	stop=!stop;
	
      }
      if(ch==113){ // q to quit
    	break;
      }
    }

    qbot_print_curses_sensors(myqbot);

    qbot_write(myqbot);

    usleep(1000);
  }

  qbot_terminate(myqbot);
  endwin();
  exit(EXIT_SUCCESS);
}
