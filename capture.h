#ifndef __CAPTURE_H
#define __CAPTURE_H
#include <gphoto2/gphoto2-camera.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sequence {
    int enable;
    int image_count;
    int exposure;
    int interval;
} Sequence;

int capture_and_download(Camera *camera, int exposure, int interval, GPContext *context);

#if !defined (O_BINARY)
	/*To have portable binary open() on *nix and on Windows */
	#define O_BINARY 0
#endif

#ifdef __cplusplus
};
#endif

#endif
