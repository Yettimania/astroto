#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <gphoto2/gphoto2.h>

#include "config.h"
#include "capture.h"

int
main() {

    int i, z;
    int retval= 0;

    struct Sequence sequences[2];

    /* Dark Frames */
    sequences[0].enable = DARK_ENABLE;
    sequences[0].image_count = DARK_IMAGE_COUNT;
    sequences[0].exposure = DARK_EXPOSURE;
    sequences[0].interval = DARK_INTERVAL;

    /* Bias Frames */
    sequences[1].enable = BIAS_ENABLE;
    sequences[1].image_count = BIAS_IMAGE_COUNT;
    sequences[1].exposure = BIAS_EXPOSURE;
    sequences[1].interval = BIAS_INTERVAL;

    /* Initilaization */
    Camera *camera;
    GPContext *context;

    gp_camera_new(&camera);
    context = gp_context_new();

    retval = gp_camera_init(camera, context);
    if (retval != GP_OK) 
    {
        printf("Initilaization Error: %d\n", retval);
        exit(1);
    }

    /* Main Execution */
    for (i=0; i<2; i++) 
    {
        if (sequences[i].enable)
        {

            if (i == 0) {
                printf("Beginning Dark Sequence...\n");
            } else if (i == 1) {
                printf("Beginning Bias Sequence...\n");
            }
            printf("Confirm camera is set to MANUAL with cap on or off.\n");
            printf("Press Enter to Continue");
            while( getchar() != '\n' );

            printf("Sequence: %d\n", i+1);
            for (z=0; z<sequences[i].image_count; z++)
            {
                printf("Image Count: %d\n", z+1);
                capture_and_download(camera, sequences[i].exposure, sequences[i].interval, context);
            }
        };
        
    }


    /* Time to Wait before next press */
   // while (1) 
   // {
   //     gettimeofday(&curtime, NULL);
   //     timediff = ((curtime.tv_sec - start.tv_sec)*1000)+((curtime.tv_usec - start.tv_usec)/1000);
   //     if (timediff >= waittime)
   //         break;

   //     retval = gp_camera_wait_for_event(camera, waittime - timediff, &evtype, &data, context);
   // }

   // printf("Retval: %d\n", retval);
   // printf("Event Type: %d\n", evtype);

    /* Takes photo but needs to be 'Press Full' on timeout */
   //  retval = gp_camera_trigger_capture(camera, context);
   //  if ((retval != GP_OK) && (retval != GP_ERROR) && (retval != GP_ERROR_CAMERA_BUSY)) {
   //  	fprintf(stderr,"triggering capture had error %d\n", retval);
   //  }
   //  printf("Retval: %d\n", retval);

    return 0;
}
