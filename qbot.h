#ifndef QBOT_H
#define QBOT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <curses.h>

typedef char               t_boolean;
typedef unsigned int       t_uint;
typedef unsigned long long t_ulong;
typedef unsigned short     t_ushort;
typedef unsigned char      t_uint8;
typedef t_ushort           t_uint16;
typedef t_uint             t_uint32;
typedef t_ulong            t_uint64;
typedef signed int         t_int;
typedef t_int              t_int32;
typedef t_int              t_error;
typedef float              t_single;
typedef double             t_double;

typedef struct tag_card* t_card;
typedef struct tag_task* t_task;

#define MAX_STRING_LENGTH 2147483647

#define SIZE(x) ((sizeof(x))/ (sizeof &x))

#define BIND_FUNCTION(handle,function)		       \
  *(void **) (&(function)) = dlsym((handle), #function);	\
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

typedef struct QBOT_INPUTS {
  qbot_encoder_inputs encoder;
  qbot_digital_inputs digital;
  qbot_other_inputs other;
} qbot_inputs;

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

typedef struct QBOT_OUTPUTS {
  qbot_digital_outputs digital;
  qbot_other_outputs other;
} qbot_outputs;

typedef struct QBOT {
  t_card card;
  qbot_inputs inputs;
  qbot_outputs outputs;
} qbot;

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
qbot_read(qbot * _qbot)
{
  t_card card = _qbot->card;
  qbot_inputs * inputs = &_qbot->inputs;
  return
    (*hil_read)(card, // card
		NULL,0, // analog
		read_encoder_channels,TOTAL_ENCODER_INPUTS, //digital_channels
		read_digital_channels,TOTAL_DIGITAL_INPUTS, //digital_lines
		read_other_channels,TOTAL_OTHER_INPUTS, // other_channels
		NULL, //analog_buffer
		(t_int32*)&inputs->encoder, //encoder_buffer
		(t_boolean*)&inputs->digital, //digital_buffer
		(t_double*)&inputs->other); //other_buffer
}

t_error
qbot_write(qbot _qbot)
{
  t_card card = _qbot.card;
  qbot_outputs outputs = _qbot.outputs;
  return (*hil_write)(card, // card
		      NULL,0, // analog
		      NULL,0, //digital_channels
		      write_digital_channels,TOTAL_DIGITAL_OUTPUTS, //digital_lines
		      write_other_channels,TOTAL_OTHER_OUTPUTS, // other_channels
		      NULL, //analog_buffer
		      NULL, //encoder_buffer
		      (t_boolean *) (&outputs.digital), //digital_buffer
		      (t_double*) (&outputs.other)); //other_buffer
}

void
qbot_initialize(qbot * _qbot)
{
  t_error hil_error = (*hil_open)("qbot3","0",&_qbot->card);
  if(hil_error){
    printf("Quanser Error no: %d\n",hil_error);
  }

  t_boolean is_hil_valid = (*hil_is_valid)(_qbot->card);
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
  (*hil_set_encoder_counts)(_qbot->card,
  			    read_encoder_channels,TOTAL_ENCODER_INPUTS,
  			    read_encoder_buffer);
}

void
qbot_terminate(qbot _qbot)
{
  t_card card = _qbot.card;

  // set all outputs to zero
  memset(&_qbot.outputs, 0, sizeof(_qbot.outputs));
  qbot_write(_qbot);

  (*hil_close)(card);
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

  BIND_FUNCTION(handle,hil_open);
  BIND_FUNCTION(handle,hil_close);
  BIND_FUNCTION(handle,hil_is_valid);
  BIND_FUNCTION(handle,hil_set_card_specific_options);
  BIND_FUNCTION(handle,hil_read);
  BIND_FUNCTION(handle,hil_write);
  BIND_FUNCTION(handle,hil_set_encoder_counts);
  BIND_FUNCTION(handle,hil_get_double_property);
  BIND_FUNCTION(handle,hil_set_double_property);
}


#endif /* QBOT_H */
