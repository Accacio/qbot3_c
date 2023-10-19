
#include <stdlib.h>

#include "qbot.h"
/* #include "qbot_video.h" */

typedef struct tag_video_capture * t_video_capture;

typedef enum tag_image_format
  {
   IMAGE_FORMAT_COL_MAJOR_PLANAR_RGB,
   IMAGE_FORMAT_COL_MAJOR_GREYSCALE,
   IMAGE_FORMAT_ROW_MAJOR_INTERLEAVED_BGR,
   IMAGE_FORMAT_COMPRESSED,

   NUMBER_OF_IMAGE_FORMATS
  } t_image_format;

typedef enum tag_image_data_type
  {
   IMAGE_DATA_TYPE_UINT8,
   IMAGE_DATA_TYPE_UINT16,
   IMAGE_DATA_TYPE_UINT32,
   IMAGE_DATA_TYPE_SINGLE,
   IMAGE_DATA_TYPE_DOUBLE,

   NUMBER_OF_IMAGE_DATA_TYPES
  } t_image_data_type;

typedef enum tag_video_capture_property_code
  {
   VIDEO_CAPTURE_PROPERTY_BRIGHTNESS,
   VIDEO_CAPTURE_PROPERTY_CONTRAST,
   VIDEO_CAPTURE_PROPERTY_HUE,
   VIDEO_CAPTURE_PROPERTY_SATURATION,
   VIDEO_CAPTURE_PROPERTY_SHARPNESS,
   VIDEO_CAPTURE_PROPERTY_GAMMA,
   VIDEO_CAPTURE_PROPERTY_COLOREFFECT,
   VIDEO_CAPTURE_PROPERTY_WHITEBALANCE,
   VIDEO_CAPTURE_PROPERTY_BACKLIGHTCOMPENSATION,
   VIDEO_CAPTURE_PROPERTY_GAIN,


   VIDEO_CAPTURE_PROPERTY_PAN,
   VIDEO_CAPTURE_PROPERTY_TILT,
   VIDEO_CAPTURE_PROPERTY_ROLL,
   VIDEO_CAPTURE_PROPERTY_ZOOM,
   VIDEO_CAPTURE_PROPERTY_EXPOSURE,
   VIDEO_CAPTURE_PROPERTY_IRIS,
   VIDEO_CAPTURE_PROPERTY_FOCUS,

   NUMBER_OF_VIDEO_CAPTURE_PROPERTIES
  } t_video_capture_property_code;

typedef enum tag_video_capture_color_effect
  {
   COLOR_EFFECT_NONE,
   COLOR_EFFECT_BLACK_AND_WHITE,
   COLOR_EFFECT_SEPIA,
   COLOR_EFFECT_NEGATIVE,
   COLOR_EFFECT_EMBOSS,
   COLOR_EFFECT_SKETCH,
   COLOR_EFFECT_SKY_BLUE,
   COLOR_EFFECT_GRASS_GREEN,
   COLOR_EFFECT_SKIN_WHITEN,
   COLOR_EFFECT_VIVID,
   COLOR_EFFECT_AQUA,
   COLOR_EFFECT_ART_FREEZE,
   COLOR_EFFECT_SILHOUETTE,
   COLOR_EFFECT_SOLARIZATION,
   COLOR_EFFECT_ANTIQUE,

   NUMBER_OF_COLOR_EFFECTS
  } t_video_capture_color_effect;

typedef struct tag_video_capture_attribute
{
  t_double value;
  t_video_capture_property_code property_code;
  t_boolean manual;
  t_boolean is_enumeration;
} t_video_capture_attribute;

t_error
(*video_capture_open)(const char * url,
		      t_double frame_rate,
		      t_uint frame_width, t_uint frame_height,
		      t_image_format format,
		      t_image_data_type data_type,
		      t_video_capture * capture,
		      t_video_capture_attribute * attr, t_uint num_attributes);

t_error
(*video_capture_start)(t_video_capture capture);

t_error
(*video_capture_stop)(t_video_capture capture);

t_error
(*video_capture_read)(t_video_capture capture,
		      void * image_data);

t_error
(*video_capture_close)(t_video_capture* capture);

typedef struct tag_video3d * t_video3d;
typedef struct tag_video3d_stream * t_video3d_stream;
typedef struct tag_video3d_frame * t_video3d_frame;

typedef enum tag_video3d_property
  {
   VIDEO3D_PROPERTY_BACKLIGHT_COMPENSATION,
   VIDEO3D_PROPERTY_BRIGHTNESS,
   VIDEO3D_PROPERTY_CONTRAST,
   VIDEO3D_PROPERTY_EXPOSURE,
   VIDEO3D_PROPERTY_GAIN,
   VIDEO3D_PROPERTY_GAMMA,
   VIDEO3D_PROPERTY_HUE,
   VIDEO3D_PROPERTY_SATURATION,
   VIDEO3D_PROPERTY_SHARPNESS,
   VIDEO3D_PROPERTY_WHITE_BALANCE,
   VIDEO3D_PROPERTY_ENABLE_AUTO_EXPOSURE,
   VIDEO3D_PROPERTY_ENABLE_AUTO_WHITE_BALANCE,
   VIDEO3D_PROPERTY_ENABLE_EMITTER,
   VIDEO3D_PROPERTY_VISUAL_PRESET,
    
   NUMBER_OF_VIDEO3D_PROPERTIES
  } t_video3d_property;

typedef enum tag_video3d_stream_type
  {
   VIDEO3D_STREAM_DEPTH,
   VIDEO3D_STREAM_COLOR,
   VIDEO3D_STREAM_INFRARED,
   VIDEO3D_STREAM_FISHEYE,
   VIDEO3D_STREAM_GYROSCOPE,
   VIDEO3D_STREAM_ACCELEROMETER,
   VIDEO3D_STREAM_POSE,
   /*VIDEO3D_STREAM_GPIO,*/

   NUMBER_OF_VIDEO3D_STREAMS
  } t_video3d_stream_type;

typedef enum tag_video3d_distortion_model
  {
   VIDEO3D_DISTORTION_NONE,
   VIDEO3D_DISTORTION_MODIFIED_BROWN_CONRADY,
   VIDEO3D_DISTORTION_INVERSE_BROWN_CONRADY,
   VIDEO3D_DISTORTION_FTHETA,
   VIDEO3D_DISTORTION_BROWN_CONRADY,
   VIDEO3D_DISTORTION_KANNALA_BRANDT4,

   NUMBER_OF_VIDEO3D_DISTORTIONS
  } t_video3d_distortion_model;

/* Video3D Functions */

t_error
(*video3d_open)(const char * device_id, t_video3d * handle);
    
t_error
(*video3d_open_file)(const char * device_file, t_video3d * handle);
    
t_error
(*video3d_close)(t_video3d handle);

/* Stream Functions */

t_error
(*video3d_stream_open)(t_video3d handle,
		       t_video3d_stream_type type, t_uint index,
		       t_double frame_rate, t_uint frame_width, t_uint frame_height,
		       t_image_format format, t_image_data_type data_type,
		       t_video3d_stream * stream);
				
t_error
(*video3d_stream_close)(t_video3d_stream stream);
				
t_error
(*video3d_stream_set_properties)(t_video3d_stream stream,
				t_video3d_property * properties, size_t num_properties,
				double * values);
t_error
(*video3d_stream_get_camera_intrinsics)(t_video3d_stream stream, float intrinsics[3][3],
					t_video3d_distortion_model* distortion, float distortion_coefficients[5]);

t_error
(*video3d_stream_get_extrinsics)(t_video3d_stream from_stream, t_video3d_stream to_stream, t_single transform[4][4]);

t_error
(*video3d_start_streaming)(t_video3d handle);

t_error
(*video3d_stop_streaming)(t_video3d handle);

t_error
(*video3d_stream_get_frame)(t_video3d_stream stream, t_video3d_frame * frame);
    
/* Frame Functions */

t_error
(*video3d_frame_release)(t_video3d_frame frame);

t_error
(*video3d_frame_get_number)(t_video3d_frame frame, t_uint64 * number);

t_error
(*video3d_frame_get_timestamp)(t_video3d_frame frame, t_double * timestamp);

t_error
(*video3d_frame_get_data)(t_video3d_frame frame, void * data);
    
t_error
(*video3d_frame_get_meters)(t_video3d_frame frame, t_single * data);

typedef enum tag_errors
  {
   ERROR_FRAME_WOULD_BLOCK=-34,

  } t_errors;



 void
 quanser_bind_video_functions()
 {
   char *error;
   // void *handle = dlopen("hil",RTLD_NOW);
   void *handle = dlopen("libquanser_media.so.1",RTLD_NOW);
   if(!handle) {
     fprintf(stderr,"%s\n",dlerror());
     exit(EXIT_FAILURE);
   }
   dlerror();

   BIND_FUNCTION(handle,video3d_open);
   BIND_FUNCTION(handle,video3d_stream_open);
   BIND_FUNCTION(handle,video3d_stream_close);
   BIND_FUNCTION(handle,video3d_stream_get_frame);
   BIND_FUNCTION(handle,video3d_frame_get_data);
   BIND_FUNCTION(handle,video3d_frame_release);
   BIND_FUNCTION(handle,video3d_start_streaming);
   BIND_FUNCTION(handle,video3d_stop_streaming);
   BIND_FUNCTION(handle,video3d_close);
 }

 int
 main(int argc, char * argv[])
 {

   quanser_bind_video_functions();
   t_video3d video = {0};
   t_video3d_stream color_stream = {0};
   t_video3d_stream depth_stream = {0};

   t_error error;
   error = (*video3d_open)("0",&video);
   if(error){
     printf("Quanser error no: %d\n", error);
   }

   int stream_index = 0;
   int frame_width = 640;
   int frame_height = 480;
   float frame_rate_depth = 15.0;
   float frame_rate_color = 30.0;
   int image_data_type = IMAGE_DATA_TYPE_UINT8;

   error = (*video3d_stream_open)(video, VIDEO3D_STREAM_COLOR, stream_index,
				  frame_rate_color, frame_width, frame_height,
				  IMAGE_FORMAT_ROW_MAJOR_INTERLEAVED_BGR, IMAGE_DATA_TYPE_UINT8,
				  &color_stream);
   if(error){
     printf("Failed to open color stream. Quanser error no: %d\n", error);
   }

   error = (*video3d_stream_open)(video, VIDEO3D_STREAM_DEPTH, stream_index,
   				  frame_rate_depth, frame_width, frame_height,
   				  IMAGE_FORMAT_COL_MAJOR_GREYSCALE, IMAGE_DATA_TYPE_UINT8,
   				  &depth_stream);
   if(error){
     printf("Failed to open depth stream. Quanser error no: %d\n", error);
   }

   error = (*video3d_start_streaming)(video);
   if(error){
     printf("Failed to start streaming. Quanser error no: %d\n", error);
   }

   t_video3d_frame new_frame = {0};

   error = ERROR_FRAME_WOULD_BLOCK;
   
   while(error==ERROR_FRAME_WOULD_BLOCK) {
     error = (*video3d_stream_get_frame)(color_stream,&new_frame);
     if(error & error!=ERROR_FRAME_WOULD_BLOCK){
       printf("Failed to get frame from stream. Quanser error no: %d\n", error);
     }
   }
   t_uint8 frame_buffer[640][480][3] = {0};

   /* error = (*video3d_frame_get_data)(new_frame,&frame_buffer); */
   /* if(error<0){ */
   /*   printf("Failed to get data from frame. Quanser error no: %d\n", error); */
   /* } */
   /* error = (*video3d_frame_release)(new_frame); */
   /* if(error){ */
   /*   printf("Failed to get data from frame. Quanser error no: %d\n", error); */
   /* } */

   printf("P3\n");
   printf("%d %d 255\n",frame_width,frame_height);
   for (int i = 0;i<frame_height;i++){
     for (int j = 0;j<frame_width;j++){
       /* printf("(%d %d)\n",i, j); */
       /* t_uint r,g,b; */
       t_double r,g,b;
       /* r = frame_buffer[i][j][0]; */
       /* g = frame_buffer[i][j][1]; */
       /* b = frame_buffer[i][j][2]; */
       /* r = (int) (((float) frame_buffer[i][j][0])/4294967295)*255; */
       /* g = (int) (((float) frame_buffer[i][j][1])/4294967295)*255; */
       /* b = (int) (((float) frame_buffer[i][j][2])/4294967295)*255; */
       printf("%zu %zu %zu\n", r,g,b);
     }
   }

   /* error = (*video3d_stop_streaming)(video); */
   /* if(error){ */
   /*   printf("Failed to stop streaming. Quanser error no: %d\n", error); */
   /* } */
   
   /* error = (*video3d_stream_close)(color_stream); */
   /* if(error){ */
   /*   printf("Failed to stop streaming. Quanser error no: %d\n", error); */
   /* } */
   /* error = (*video3d_stream_close)(depth_stream); */
   /* if(error){ */
   /*   printf("Failed to stop streaming. Quanser error no: %d\n", error); */
   /* } */
	
   exit(EXIT_SUCCESS);
 }
