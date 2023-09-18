#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <curses.h>

typedef char t_boolean;
typedef char t_boolean;
typedef unsigned int t_uint;
typedef unsigned short t_ushort;
typedef t_ushort t_uint16;
typedef t_uint t_uint32;
typedef signed int t_int;
typedef t_int t_int32;
typedef t_int t_error;
typedef double t_double;

typedef struct tag_card* t_card;
typedef struct tag_task* t_task;

#define MAX_STRING_LENGTH 2147483647

#define SIZE(x) ((sizeof(x))/ (sizeof &x))

#define BIND_FUNCTION(function) \
  *(void **) (&(function)) = dlsym(handle, #function); \
  error = dlerror(); \
  if(error!=NULL) { \
    fprintf(stderr,"%s\n",error); \
    exit(EXIT_FAILURE);		  \
  }\


typedef enum tag_hil_double_property
  {
   PROPERTY_DOUBLE_KOBUKI_P_GAIN = 128,
   PROPERTY_DOUBLE_KOBUKI_I_GAIN,
   PROPERTY_DOUBLE_KOBUKI_D_GAIN,
  } t_hil_double_property;


t_error
(*hil_open)(const char* card_type,
	    const char* card_identifier,
	    t_card* card);

t_error
(*hil_set_encoder_counts)(t_card card,
			  const t_uint32 encoder_channels[], t_uint32 num_channels,
			  const t_int32 encoder_buffer[]);
t_error
(*hil_is_valid)(t_card card);

t_error
(*hil_close)(t_card card);

t_error
(*hil_write)(t_card card,
	     const t_uint32 analog_channels[], t_uint32 num_analog_channels,
	     const t_uint32 digital_channels[], t_uint32 num_digital_channels,
	     const t_uint32 digital_lines[], t_uint32 num_digital_lines,
	     const t_uint32 other_channels[], t_uint32 num_other_channels,
	     t_double analog_buffer[],
	     t_int32 encoder_buffer[],
	     t_boolean digital_buffer[],
	     t_double other_buffer[]);

t_error
(*hil_set_card_specific_options)(t_card card,
				 const char* options,
				 size_t options_size);
t_error
(*hil_read)(t_card card,
	    const t_uint32 analog_channels[], t_uint32 num_analog_channels,
	    const t_uint32 digital_channels[], t_uint32 num_digital_channels,
	    const t_uint32 digital_lines[], t_uint32 num_digital_lines,
	    const t_uint32 other_channels[], t_uint32 num_other_channels,
	    t_double analog_buffer[],
	    t_int32 encoder_buffer[],
	    t_boolean digital_buffer[],
	    t_double other_buffer[]);

t_error
(*hil_get_double_property)(t_card card,
			   const t_hil_double_property properties[], t_uint32 num_properties,
			   t_double buffer[]);
t_error
(*hil_set_double_property)(t_card card,
			   t_hil_double_property property_code,
			   char * buffer, size_t buffer_size);


// from docs.quanser.com/quarc/documentation/qbot3.html
enum digital_inputs_channels
  {
   BUMPER_RIGHT_CHANNEL=28,
   BUMPER_CENTER_CHANNEL,
   BUMPER_LEFT_CHANNEL,
   WHEEL_DROP_RIGHT_CHANNEL,
   WHEEL_DROP_LEFT_CHANNEL,
   CLIFF_RIGHT_CHANNEL,
   CLIFF_CENTRAL_CHANNEL,
   CLIFF_LEFT_CHANNEL,
   BUTTON_B0_CHANNEL,
   BUTTON_B1_CHANNEL,
   BUTTON_B2_CHANNEL,
   /* DOCK_IR_RIGHT_NEAR_RIGHT_CHANNEL=41, */
   /* DOCK_IR_RIGHT_NEAR_CENTER_CHANNEL, */
   /* DOCK_IR_RIGHT_NEAR_LEFT_CHANNEL, */
   /* DOCK_IR_RIGHT_FAR_RIGHT_CHANNEL, */
   /* DOCK_IR_RIGHT_FAR_CENTER_CHANNEL, */
   /* DOCK_IR_RIGHT_FAR_LEFT_CHANNEL, */
   /* DOCK_IR_CENTRAL_NEAR_RIGHT_CHANNEL, */
   /* DOCK_IR_CENTRAL_NEAR_CENTER_CHANNEL, */
   /* DOCK_IR_CENTRAL_NEAR_LEFT_CHANNEL, */
   /* DOCK_IR_CENTRAL_FAR_RIGHT_CHANNEL, */
   /* DOCK_IR_CENTRAL_FAR_CENTER_CHANNEL, */
   /* DOCK_IR_CENTRAL_FAR_LEFT_CHANNEL, */
   /* DOCK_IR_LEFT_NEAR_RIGHT_CHANNEL, */
   /* DOCK_IR_LEFT_NEAR_CENTER_CHANNEL, */
   /* DOCK_IR_LEFT_NEAR_LEFT_CHANNEL, */
   /* DOCK_IR_LEFT_FAR_RIGHT_CHANNEL, */
   /* DOCK_IR_LEFT_FAR_CENTER_CHANNEL, */
   /* DOCK_IR_LEFT_FAR_LEFT_CHANNEL, */
  };
  
enum digital_inputs
  {
   BUMPER_RIGHT,
   BUMPER_CENTER,
   BUMPER_LEFT,
   WHEEL_DROP_RIGHT,
   WHEEL_DROP_LEFT,
   CLIFF_RIGHT,
   CLIFF_CENTRAL,
   CLIFF_LEFT,
   BUTTON_B0,
   BUTTON_B1,
   BUTTON_B2,
   /* DOCK_IR_RIGHT_NEAR_RIGHT, */
   /* DOCK_IR_RIGHT_NEAR_CENTER, */
   /* DOCK_IR_RIGHT_NEAR_LEFT, */
   /* DOCK_IR_RIGHT_FAR_RIGHT, */
   /* DOCK_IR_RIGHT_FAR_CENTER, */
   /* DOCK_IR_RIGHT_FAR_LEFT, */
   /* DOCK_IR_CENTRAL_NEAR_RIGHT, */
   /* DOCK_IR_CENTRAL_NEAR_CENTER, */
   /* DOCK_IR_CENTRAL_NEAR_LEFT, */
   /* DOCK_IR_CENTRAL_FAR_RIGHT, */
   /* DOCK_IR_CENTRAL_FAR_CENTER, */
   /* DOCK_IR_CENTRAL_FAR_LEFT, */
   /* DOCK_IR_LEFT_NEAR_RIGHT, */
   /* DOCK_IR_LEFT_NEAR_CENTER, */
   /* DOCK_IR_LEFT_NEAR_LEFT, */
   /* DOCK_IR_LEFT_FAR_RIGHT, */
   /* DOCK_IR_LEFT_FAR_CENTER, */
   /* DOCK_IR_LEFT_FAR_LEFT, */
   TOTAL_DIGITAL_INPUTS,
  };


typedef struct VECTOR_3_BOOLEAN {
  union {
    struct {
      t_boolean x;
      t_boolean y;
      t_boolean z;
    };
    struct {
      t_boolean right;
      t_boolean center;
      t_boolean left;
    };
    struct {
      t_boolean b0;
      t_boolean b1;
      t_boolean b2;
    };
  };
} v3b;

typedef struct VECTOR_3_DOUBLE {
  union {
    struct {
      t_double x;
      t_double y;
      t_double z;
    };
    struct {
      t_double right;
      t_double center;
      t_double left;
    };
    struct {
      t_double red;
      t_double green;
      t_double blue;
    };
  };
} v3d;

typedef struct VECTOR_2_BOOLEAN {
  union {
    struct {
      t_boolean x;
      t_boolean y;
    };
    struct {
      t_boolean right;
      t_boolean left;
    };
    struct {
      t_boolean red;
      t_boolean green;
    };
  };
} v2b;

typedef struct VECTOR_2_DOUBLE {
  union {
    struct {
      t_double x;
      t_double y;
    };
    struct {
      t_double right;
      t_double left;
    };
  };
} v2d;


/* typedef struct DOCK_IR_SENSOR { */
/*   v3b near; */
/*   v3b far; */
/* } ir_sensor; */

typedef struct QBOT_DIGITAL_INPUTS {
  v3b bumper;
  v2b wheel_drop;
  v3b cliff;
  v3b button;
  /* struct { */
  /*   ir_sensor right; */
  /*   ir_sensor central; */
  /*   ir_sensor left; */
  /* } dock_ir; */
} qbot_digital_inputs;


enum encoder_inputs_channels
  {
   WHEEL_RIGHT_CHANNEL,
   WHEEL_LEFT_CHANNEL,
  };
enum encoder_inputs
  {
   WHEEL_RIGHT,
   WHEEL_LEFT,
   TOTAL_ENCODER_INPUTS,
  };

typedef struct QBOT_ENCODER_INPUTS {
  struct {
    t_int32 right;
    t_int32 left;
  } wheel;
} qbot_encoder_inputs;


enum other_inputs_channels
  {
   ANGLE_Z_AXIS_CHANNEL=1002,
   GYROSCOPE_X_CHANNEL=3000,
   GYROSCOPE_Y_CHANNEL,
   GYROSCOPE_Z_CHANNEL,
   WHEEL_PWM_RIGHT_CHANNEL=11000,
   WHEEL_PWM_LEFT_CHANNEL,
   TIMESTAMP_CHANNEL=12000,
   CHARGER_STATE_CHANNEL=16000,
  };
enum other_inputs
  {
   ANGLE_Z_AXIS,
   GYROSCOPE_X,
   GYROSCOPE_Y,
   GYROSCOPE_Z,
   WHEEL_PWM_RIGHT,
   WHEEL_PWM_LEFT,
   TIMESTAMP,
   CHARGER_STATE,
   TOTAL_OTHER_INPUTS,
  };
typedef struct QBOT_OTHER_INPUTS {
  t_double angle_z_axis;
  v3d gyroscope;
  v2d wheel_pwm;
  t_double timestamp;
  t_double charger_state;
} qbot_other_inputs;


enum digital_outputs_channels
  {
   LED1_RED_CHANNEL=28,
   LED1_GREEN_CHANNEL,
   LED2_RED_CHANNEL,
   LED2_GREEN_CHANNEL,
  };
enum digital_outputs
  {
   LED1_RED,
   LED1_GREEN,
   LED2_RED,
   LED2_GREEN,
   TOTAL_DIGITAL_OUTPUTS
  };

typedef struct QBOT_DIGITAl_OUTPUTS {
  v2b led1;
  v2b led2;
} qbot_digital_outputs;

enum other_outputs_channels
  {
   WHEEL_VELOCITY_RIGHT_CHANNEL=2000,
   WHEEL_VELOCITY_LEFT_CHANNEL=2001,
   CUSTOM_PITCH_CHANNEL=14000,
   PREDEFINED_SOUND_CHANNEL=16000,
  };
enum other_outputs
  {
   WHEEL_VELOCITY_RIGHT,
   WHEEL_VELOCITY_LEFT,
   CUSTOM_PITCH,
   PREDEFINED_SOUND,
   TOTAL_OTHER_OUTPUTS
  };
typedef struct QBOT_OTHER_OUTPUTS {
  struct {
  t_double right;
  t_double left;
  } wheel_velocity;
  t_double custom_pitch;
  t_double predefined_sound;
} qbot_other_outputs;

t_int32 read_encoder_channels[] = {
				   WHEEL_RIGHT_CHANNEL,
				   WHEEL_LEFT_CHANNEL,
};
  
t_uint32 read_digital_channels[] = {
				    BUMPER_RIGHT_CHANNEL,
				    BUMPER_CENTER_CHANNEL,
				    BUMPER_LEFT_CHANNEL,
				    WHEEL_DROP_RIGHT_CHANNEL,
				    WHEEL_DROP_LEFT_CHANNEL,
				    CLIFF_RIGHT_CHANNEL,
				    CLIFF_CENTRAL_CHANNEL,
				    CLIFF_LEFT_CHANNEL,
				    BUTTON_B0_CHANNEL,
				    BUTTON_B1_CHANNEL,
				    BUTTON_B2_CHANNEL,
				    /* DOCK_IR_RIGHT_NEAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_RIGHT_NEAR_CENTER_CHANNEL, */
				    /* DOCK_IR_RIGHT_NEAR_LEFT_CHANNEL, */
				    /* DOCK_IR_RIGHT_FAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_RIGHT_FAR_CENTER_CHANNEL, */
				    /* DOCK_IR_RIGHT_FAR_LEFT_CHANNEL, */
				    /* DOCK_IR_CENTRAL_NEAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_CENTRAL_NEAR_CENTER_CHANNEL, */
				    /* DOCK_IR_CENTRAL_NEAR_LEFT_CHANNEL, */
				    /* DOCK_IR_CENTRAL_FAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_CENTRAL_FAR_CENTER_CHANNEL, */
				    /* DOCK_IR_CENTRAL_FAR_LEFT_CHANNEL, */
				    /* DOCK_IR_LEFT_NEAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_LEFT_NEAR_CENTER_CHANNEL, */
				    /* DOCK_IR_LEFT_NEAR_LEFT_CHANNEL, */
				    /* DOCK_IR_LEFT_FAR_RIGHT_CHANNEL, */
				    /* DOCK_IR_LEFT_FAR_CENTER_CHANNEL, */
				    /* DOCK_IR_LEFT_FAR_LEFT_CHANNEL, */
};

t_int32 read_other_channels[] = {
				 ANGLE_Z_AXIS_CHANNEL,
				 GYROSCOPE_X_CHANNEL,
				 GYROSCOPE_Y_CHANNEL,
				 GYROSCOPE_Z_CHANNEL,
				 WHEEL_PWM_RIGHT_CHANNEL,
				 WHEEL_PWM_LEFT_CHANNEL,
				 TIMESTAMP_CHANNEL,
				 CHARGER_STATE_CHANNEL,
};
t_uint32 write_digital_channels[] = {
				     LED1_RED_CHANNEL,
				     LED1_GREEN_CHANNEL,
				     LED2_RED_CHANNEL,
				     LED2_GREEN_CHANNEL,
};
t_uint32 write_other_channels[] = {
				   WHEEL_VELOCITY_RIGHT_CHANNEL,
				   WHEEL_VELOCITY_LEFT_CHANNEL,
				   CUSTOM_PITCH_CHANNEL,
				   PREDEFINED_SOUND_CHANNEL,
};



t_error
qbot_read(t_card card,
	  t_uint32 read_encoder_channels[], t_uint32 number_encoder_channels,
	  qbot_encoder_inputs * read_encoder_buffer,
	  t_uint32 read_digital_channels[], t_uint32 number_digital_channels,
	  qbot_digital_inputs * read_digital_buffer,
	  t_uint32 read_other_channels[], t_uint32 number_other_channels,
	  qbot_other_inputs * read_other_buffer)
{
  return
    (*hil_read)(card, // card
		NULL,0, // analog
		read_encoder_channels,TOTAL_ENCODER_INPUTS, //digital_channels
		read_digital_channels,TOTAL_DIGITAL_INPUTS, //digital_lines
		read_other_channels,TOTAL_OTHER_INPUTS, // other_channels
		NULL, //analog_buffer
		(t_int32*)read_encoder_buffer, //encoder_buffer
		(t_boolean*)read_digital_buffer, //digital_buffer
		(t_double*)read_other_buffer); //other_buffer
}

t_error
qbot_write(t_card card,
	   t_uint32 write_digital_channels[], t_uint32 number_digital_channels,
	   qbot_digital_outputs write_digital_buffer,
	   t_uint32 write_other_channels[], t_uint32 number_other_channels,
	   qbot_other_outputs write_other_buffer)
{
  return (*hil_write)(card, // card
		      NULL,0, // analog
		      NULL,0, //digital_channels
		      write_digital_channels,number_digital_channels, //digital_lines
		      write_other_channels,number_other_channels, // other_channels
		      NULL, //analog_buffer
		      NULL, //encoder_buffer
		      (t_boolean *) (&write_digital_buffer), //digital_buffer
		      (t_double*) (&write_other_buffer)); //other_buffer
}

void
qbot_initialize(t_card *card)
{
  t_error hil_error = (*hil_open)("qbot3","0",card);
  if(hil_error){
    printf("Quanser Error no: %d\n",hil_error);
  }

  t_boolean is_hil_valid = (*hil_is_valid)(*card);
  if(!is_hil_valid){
    printf("Failed to connect\n");
    exit(EXIT_FAILURE);
  }

  // configure specification for pwm (apparently not necessary)
  /* (*hil_set_card_specific_options)(*card, */
  /* 				   "pwm0_en=1;pwm0_pin=12;pwm1_en=1;pwm1_pin=13;", */
  /* 				   MAX_STRING_LENGTH); */

  /* zero encoder values */
  t_int32 read_encoder_channels[] = {
				     WHEEL_RIGHT_CHANNEL,
				     WHEEL_LEFT_CHANNEL,
  };
  t_int32 read_encoder_buffer[TOTAL_ENCODER_INPUTS] = {0};
  (*hil_set_encoder_counts)(*card,
  			    read_encoder_channels,TOTAL_ENCODER_INPUTS,
  			    read_encoder_buffer);
}

void
qbot_terminate(t_card card)
{

  t_uint32 write_digital_channels[] = {
				       LED1_RED_CHANNEL,
				       LED1_GREEN_CHANNEL,
				       LED2_RED_CHANNEL,
				       LED2_GREEN_CHANNEL,
  };
  /* t_boolean write_digital_buffer[TOTAL_DIGITAL_OUTPUTS] = {1,0,0,0}; */
  qbot_digital_outputs write_digital_buffer = {0};

  t_uint32 write_other_channels[] = {
				     WHEEL_VELOCITY_RIGHT_CHANNEL,
				     WHEEL_VELOCITY_LEFT_CHANNEL,
				     CUSTOM_PITCH_CHANNEL,
				     PREDEFINED_SOUND_CHANNEL,
  };
  /* t_double write_other_buffer[TOTAL_OTHER_OUTPUTS] = {0}; */
  qbot_other_outputs write_other_buffer = {0};

  // use memset to zero buffers (if using same buffers)
  /* memset(&write_digital_buffer,0,sizeof(write_digital_buffer)); */
  qbot_write(card,
	     write_digital_channels,SIZE(write_digital_channels),
	     write_digital_buffer,
	     write_other_channels,SIZE(write_other_channels),
	     write_other_buffer);

  (*hil_close)(card);
}

void
qbot_print_sensors(qbot_encoder_inputs read_encoder_buffer,qbot_digital_inputs read_digital_buffer,qbot_other_inputs read_other_buffer)
{
  mvprintw(1,0,"Right wheel encoder: %d",read_encoder_buffer.wheel.right);
  mvprintw(2,0,"Left  wheel encoder: %d",read_encoder_buffer.wheel.left);
  mvprintw(3,0,"Right Bumper:        %d",read_digital_buffer.bumper.right);
  mvprintw(4,0,"Center Bumper:       %d",read_digital_buffer.bumper.center);
  mvprintw(5,0,"Left Bumper:         %d",read_digital_buffer.bumper.left);
  mvprintw(6,0,"Right Wheel drop     %d",read_digital_buffer.wheel_drop.right);
  mvprintw(7,0,"Left Wheel drop      %d",read_digital_buffer.wheel_drop.left);
  mvprintw(8,0,"Right cliff          %d",read_digital_buffer.cliff.right);
  mvprintw(9,0,"Center cliff         %d",read_digital_buffer.cliff.center);
  mvprintw(10,0,"Left cliff           %d",read_digital_buffer.cliff.left);
  mvprintw(11,0,"Button B0            %d",read_digital_buffer.button.b0);
  mvprintw(12,0,"Button B1            %d",read_digital_buffer.button.b1);
  mvprintw(13,0,"Button B2            %d",read_digital_buffer.button.b2);
  /* mvprintw(14,0,"DOCK_IR_RIGHT_NEAR_RIGHT %d",read_digital_buffer[DOCK_IR_RIGHT_NEAR_RIGHT]); */
  /* mvprintw(15,0,"DOCK_IR_RIGHT_NEAR_CENTER %d",read_digital_buffer[DOCK_IR_RIGHT_NEAR_CENTER]); */
  /* mvprintw(16,0,"DOCK_IR_RIGHT_NEAR_LEFT %d",read_digital_buffer[DOCK_IR_RIGHT_NEAR_LEFT]); */
  /* mvprintw(17,0,"DOCK_IR_RIGHT_FAR_RIGHT %d",read_digital_buffer[DOCK_IR_RIGHT_FAR_RIGHT]); */
  /* mvprintw(18,0,"DOCK_IR_RIGHT_FAR_CENTER %d",read_digital_buffer[DOCK_IR_RIGHT_FAR_CENTER]); */
  /* mvprintw(19,0,"DOCK_IR_RIGHT_FAR_LEFT %d",read_digital_buffer[DOCK_IR_RIGHT_FAR_LEFT]); */
  /* mvprintw(20,0,"DOCK_IR_CENTRAL_NEAR_RIGHT %d",read_digital_buffer[DOCK_IR_CENTRAL_NEAR_RIGHT]); */
  /* mvprintw(21,0,"DOCK_IR_CENTRAL_NEAR_CENTER %d",read_digital_buffer[DOCK_IR_CENTRAL_NEAR_CENTER]); */
  /* mvprintw(22,0,"DOCK_IR_CENTRAL_NEAR_LEFT %d",read_digital_buffer[DOCK_IR_CENTRAL_NEAR_LEFT]); */
  /* mvprintw(23,0,"DOCK_IR_CENTRAL_FAR_RIGHT %d",read_digital_buffer[DOCK_IR_CENTRAL_FAR_RIGHT]); */
  /* mvprintw(24,0,"DOCK_IR_CENTRAL_FAR_CENTER %d",read_digital_buffer[DOCK_IR_CENTRAL_FAR_CENTER]); */
  /* mvprintw(25,0,"DOCK_IR_CENTRAL_FAR_LEFT %d",read_digital_buffer[DOCK_IR_CENTRAL_FAR_LEFT]); */
  /* mvprintw(26,0,"DOCK_IR_LEFT_NEAR_RIGHT %d",read_digital_buffer[DOCK_IR_LEFT_NEAR_RIGHT]); */
  /* mvprintw(27,0,"DOCK_IR_LEFT_NEAR_CENTER %d",read_digital_buffer[DOCK_IR_LEFT_NEAR_CENTER]); */
  /* mvprintw(28,0,"DOCK_IR_LEFT_NEAR_LEFT %d",read_digital_buffer[DOCK_IR_LEFT_NEAR_LEFT]); */
  /* mvprintw(29,0,"DOCK_IR_LEFT_FAR_RIGHT %d",read_digital_buffer[DOCK_IR_LEFT_FAR_RIGHT]); */
  /* mvprintw(30,0,"DOCK_IR_LEFT_FAR_CENTER %d",read_digital_buffer[DOCK_IR_LEFT_FAR_CENTER]); */
  /* mvprintw(31,0,"DOCK_IR_LEFT_FAR_LEFT %d",read_digital_buffer[DOCK_IR_LEFT_FAR_LEFT]); */

  mvprintw(31,0,"ANGLE_Z_AXIS %f",read_other_buffer.angle_z_axis);
  mvprintw(32,0,"GYROSCOPE_X %f",read_other_buffer.gyroscope.x);
  mvprintw(33,0,"GYROSCOPE_Y %f",read_other_buffer.gyroscope.y);
  mvprintw(34,0,"GYROSCOPE_Z %f",read_other_buffer.gyroscope.z);
  mvprintw(35,0,"WHEEL_PWM_RIGHT %f",read_other_buffer.wheel_pwm.right);
  mvprintw(36,0,"WHEEL_PWM_LEFT %f",read_other_buffer.wheel_pwm.left);
  mvprintw(37,0,"TIMESTAMP %f",read_other_buffer.timestamp);
  mvprintw(38,0,"CHARGER_STATE %f",read_other_buffer.charger_state);
}


void
quanser_bind_functions()
{
  char *error;
  // void *handle = dlopen("hil",RTLD_NOW);
  void *handle = dlopen("libhil.so.1",RTLD_NOW);
  if(!handle) {
    fprintf(stderr,"%s\n",dlerror());
    exit(EXIT_FAILURE);
  }
  dlerror();

  BIND_FUNCTION(hil_open);
  BIND_FUNCTION(hil_close);
  BIND_FUNCTION(hil_is_valid);
  BIND_FUNCTION(hil_set_card_specific_options);
  BIND_FUNCTION(hil_read);
  BIND_FUNCTION(hil_write);
  BIND_FUNCTION(hil_set_encoder_counts);
  BIND_FUNCTION(hil_get_double_property);
  BIND_FUNCTION(hil_set_double_property);
}


int
main(int argc, char * argv[])
{
  qbot_encoder_inputs read_encoder_buffer = {0};

  qbot_digital_inputs read_digital_buffer = {0};

  qbot_other_inputs read_other_buffer = {0};

  qbot_digital_outputs write_digital_buffer = {0};

  qbot_other_outputs write_other_buffer = {0};

  quanser_bind_functions();
	
  t_card qbot = {0};
  qbot_initialize(&qbot);

  initscr();
  curs_set(0);
  
  char ch;
  if(nodelay(stdscr,TRUE)==ERR){
    return -1;
  }
  int stop = 0;
  for(;;){

    qbot_read(qbot,
	      read_encoder_channels, SIZE(read_encoder_channels),
	      &read_encoder_buffer,
	      read_digital_channels, SIZE(read_digital_channels),
	      &read_digital_buffer,
	      read_other_channels, SIZE(read_other_channels),
	      &read_other_buffer);


    ch = getch();

    if(ch!=ERR){
      if(ch==68){ // left
    	if(stop) {
	  write_other_buffer.wheel_velocity.right=0.0;
	  write_other_buffer.wheel_velocity.left=0.0;
    	} else {
	  write_other_buffer.wheel_velocity.right=0.1;
	  write_other_buffer.wheel_velocity.left=0.1;
    	}
    	stop=!stop;
      }
      if(ch==67){ // right
	write_other_buffer.predefined_sound++;
	if(write_other_buffer.predefined_sound>6) {
	  write_other_buffer.predefined_sound=0;
	}
      }
      if(ch==66){ // right
    	if(stop) {
    	  write_other_buffer.custom_pitch=0.0;
    	} else {
    	  write_other_buffer.custom_pitch=440.;
    	}
    	stop=!stop;
	
      }
      if(ch==113){ // q to quit
    	break;
      }
    }

    erase();
    qbot_print_sensors(read_encoder_buffer, read_digital_buffer, read_other_buffer);

    qbot_write(qbot,
	       write_digital_channels,SIZE(write_digital_channels),
	       write_digital_buffer,
	       write_other_channels,SIZE(write_other_channels),
	       write_other_buffer);

    usleep(1000);
  }

  qbot_terminate(qbot);
  endwin();
  exit(EXIT_SUCCESS);
}
