#include <stdio.h>
#include <gphoto2/gphoto2.h>
#include <sys/time.h>

#include "capture.h"
#include "config.h"


int capture_and_download(Camera *camera, int exposure, int interval, GPContext *context)
{

    CameraEventType evtype;
    void *data;
    int retval = 0;
    int timediff;
    int waittime = 2000;
    struct timeval start, curtime;

    /* Trigger Event */
    printf("Triggering camera...\n");
    retval = gp_camera_trigger_capture(camera, context);
	if ((retval != GP_OK) && (retval != GP_ERROR) && (retval != GP_ERROR_CAMERA_BUSY)) {
		fprintf(stderr,"Triggering capture had error: %d\n", retval);
	}
    printf("Retval: %d\n", retval);
    

    /* Inital Wait After Trigger */
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&curtime, NULL);
        timediff = ((curtime.tv_sec - start.tv_sec)*1000)+((curtime.tv_usec - start.tv_usec)/1000);
        if (timediff >= waittime)
            break;

        retval = gp_camera_wait_for_event(camera, waittime - timediff, &evtype, &data, context);
    }

    printf("Return Value from wait event: %d\n", retval);
    printf("Return eventype from wait event: %d\n", evtype);

    /* TODO Full Press Event*/
    retval = set_config_value_string(camera, "eosremoterelease", "Press Full", context);
    printf("Return Value from config set: %d\n", retval);

    /* Exposure Timeout Event*/
    printf("Exposure...\n");
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&curtime, NULL);
        timediff = ((curtime.tv_sec - start.tv_sec)*1000)+((curtime.tv_usec - start.tv_usec)/1000);
        if (timediff >= exposure * 1000)
            break;

        retval = gp_camera_wait_for_event(camera, exposure * 1000 - timediff, &evtype, &data, context);
    }

    printf("Return Value from wait event: %d\n", retval);
    printf("Return eventype from wait event: %d\n", evtype);

    /* TODO Full Release Event*/
    retval = set_config_value_string(camera, "eosremoterelease", "Release Full", context);
    printf("Return Value from config set: %d\n", retval);


    /* Cooldown Timeout Event OR Wait and Downoad*/
    printf("Cooldown...\n");
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&curtime, NULL);
        timediff = ((curtime.tv_sec - start.tv_sec)*1000)+((curtime.tv_usec - start.tv_usec)/1000);
        if (timediff >= interval * 1000)
            break;

        retval = gp_camera_wait_for_event(camera, interval * 1000 - timediff, &evtype, &data, context);
    }

    printf("Return Value from wait event: %d\n", retval);
    printf("Return eventype from wait event: %d\n", evtype);

    /* TODO If file added during wait event */
    /* TODO Download Image */
    /* TODO Rename file and put in folder */

    /* TODO Sleep for cooldown */


    return 0;
};
