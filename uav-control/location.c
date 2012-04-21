// -----------------------------------------------------------------------------
// File:    location.c
// Authors: Tyler Thierolf, Timothy Miller, Garrett Smith
// Created: 10-26-2010
//
// Routines for location colors.
// -----------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <syslog.h>
#include <time.h>
#include "uav_protocol.h"
#include "location.h"

typedef struct location_args
{
    client_info_t  *client;              // connect client handle
    location_coords_t  radio_coords;     // location as reported by the location service
    location_coords_t  inertial_coords;  // location as reported by the IMU estimates
    unsigned int    running;             // subsystem is currently running
    unsigned int    radio_enabled;
    unsigned int    inertial_enabled;
    pthread_t       radio_thread;     // handle to location service thread
    pthread_t       inertial_thread;  // handle to IMU location estimation thread
    unsigned int    radio_rate;
    unsigned int    inertial_rate
    pthread_mutex_t lock;
    pthread_mutex_t radio_lock;
    pthread_cond_t  radio_cond;
    pthread_mutex_t inertial_lock;
    pthread_cond_t  inertial_cond;
} location_args_t;

static location_args_t globals;

// -----------------------------------------------------------------------------
static void *radio_thread(void *arg)
{   
    globals.radio_enabled = 1;
    location_args_t *data = (location_args_t *)arg;
    location_coords_t coords;
    video_data_t vid_data;
    unsigned long buff_sz = 0;
    uint8_t *jpg_buf = NULL, *rgb_buff = NULL;
    int delta, frames_computed = 0, location_fps = 0, streaming_fps = 0;
    struct timespec t0, t1, tc;
    
    clock_gettime(CLOCK_REALTIME, &t0);
    while (data->radio_enabled) {
        // lock the colordetect parameters and determine our location fps
        pthread_mutex_lock(&data->radio_lock);
        /* old code
        streaming_fps = video_get_fps();
        location_fps = MIN(data->radio_rate, streaming_fps);
        */
        location_fps = data->radio_rate;
        pthread_mutex_unlock(&data->radio_lock);
        
        // if location is disable - sleep and check for a change every second
        if (location_fps <= 0 || globals.radio_enabled == 0) {
            sleep(1);
            continue;
        }
        
        
        // LOCATION TODO: insert code to retrieve radio data
        //                remember to lock on that data. See example code below
        
        /*
        Code to retrieve video data
        // make synchronous frame read -- sleep for a second and retry on fail
        if (!video_lock(&vid_data, ACCESS_SYNC)) {
            syslog(LOG_ERR, "colordetect failed to lock frame\n");
            sleep(1);
            continue;
        }

        clock_gettime(CLOCK_REALTIME, &tc);
        delta = timespec_delta(&t0, &tc);
        if (((frames_computed * 1000000) / delta) >= location_fps) {
            video_unlock();
            continue;
        }

        // copy the jpeg to our buffer now that we're safely locked
        if (buff_sz < vid_data.length) {
            free(jpg_buf);
            buff_sz = vid_data.length;
            jpg_buf = (uint8_t *)malloc(buff_sz);
        }

        memcpy(jpg_buf, vid_data.data, vid_data.length);     
        video_unlock();
        */

        // LOCATION TODO: do processing to determine location according to radio
        //                store results in local coords member
        
        /* Old Code
        if (0 != jpeg_rd_mem(jpg_buf, buff_sz, &rgb_buff,
                             &coords.width, &coords.height)) {
            colordetect_hsl_fp32(rgb_buff, &data->color, &coords);
            frames_computed++;
        }
        */

        pthread_mutex_lock(&data->radio_lock);

        // copy over the updated coordinates to the global struct
        globals.radio_coords = coords;

        // inform any listeners that new data is available
        pthread_cond_broadcast(&globals.radio_cond);
        pthread_mutex_unlock(&data->radio_lock);

        if (frames_computed >= streaming_fps) {
            // every time we hit the streaming fps, dump out the location rate
            clock_gettime(CLOCK_REALTIME, &t1);
            real_t delta = timespec_delta(&t0, &t1) / (real_t)1000000;
            syslog(LOG_INFO, "location fps: %f\n", streaming_fps / delta);
            frames_computed = 0;
            t0 = t1;
        }
    }

    pthread_exit(NULL);
}

// -----------------------------------------------------------------------------
static void *inertial_thread(void *arg)
{   
    globals.inertial_enabled = 1;
    location_args_t *data = (location_args_t *)arg;
    location_coords_t coords;
    video_data_t vid_data;
    unsigned long buff_sz = 0;
    uint8_t *jpg_buf = NULL, *rgb_buff = NULL;
    int delta, frames_computed = 0, location_fps = 0, streaming_fps = 0;
    struct timespec t0, t1, tc;
    
    clock_gettime(CLOCK_REALTIME, &t0);
    while (data->inertial_enabled) {
        // lock the colordetect parameters and determine our location fps
        pthread_mutex_lock(&data->inertial_lock);
        /* old code
        streaming_fps = video_get_fps();
        location_fps = MIN(data->radio_rate, streaming_fps);
        */
        location_fps = data->inertial_rate;
        pthread_mutex_unlock(&data->inertial_lock);
        
        // if location is disable - sleep and check for a change every second
        if (location_fps <= 0 || globals.inertial_enabled == 0) {
            sleep(1);
            continue;
        }
        
        
        // LOCATION TODO: insert code to retrieve IMU data
        //                remember to lock on that data. See example code below
        
        /*
        Code to retrieve video data
        // make synchronous frame read -- sleep for a second and retry on fail
        if (!video_lock(&vid_data, ACCESS_SYNC)) {
            syslog(LOG_ERR, "colordetect failed to lock frame\n");
            sleep(1);
            continue;
        }

        clock_gettime(CLOCK_REALTIME, &tc);
        delta = timespec_delta(&t0, &tc);
        if (((frames_computed * 1000000) / delta) >= location_fps) {
            video_unlock();
            continue;
        }

        // copy the jpeg to our buffer now that we're safely locked
        if (buff_sz < vid_data.length) {
            free(jpg_buf);
            buff_sz = vid_data.length;
            jpg_buf = (uint8_t *)malloc(buff_sz);
        }

        memcpy(jpg_buf, vid_data.data, vid_data.length);     
        video_unlock();
        */

        // LOCATION TODO: do processing to determine location according to IMU
        //                store results in local coords member
        
        /* Old Code
        if (0 != jpeg_rd_mem(jpg_buf, buff_sz, &rgb_buff,
                             &coords.width, &coords.height)) {
            colordetect_hsl_fp32(rgb_buff, &data->color, &coords);
            frames_computed++;
        }
        */

        pthread_mutex_lock(&data->inertial_lock);

        // copy over the updated coordinates to the global struct
        globals.inertial_coords = coords;

        // inform any listeners that new data is available
        pthread_cond_broadcast(&globals.inertial_cond);
        pthread_mutex_unlock(&data->inertial_lock);

        if (frames_computed >= streaming_fps) {
            // every time we hit the streaming fps, dump out the location rate
            clock_gettime(CLOCK_REALTIME, &t1);
            real_t delta = timespec_delta(&t0, &t1) / (real_t)1000000;
            syslog(LOG_INFO, "location fps: %f\n", streaming_fps / delta);
            frames_computed = 0;
            t0 = t1;
        }
    }

    pthread_exit(NULL);
}


// -----------------------------------------------------------------------------
int location_init(client_info_t *client)
{   
    int rc;
    if (globals.running) {
        syslog(LOG_INFO, "attempting multiple colordetect_init calls\n");
        return 0;
    }

    // zero out all globals
    memset(&globals, 0, sizeof(globals));

    globals.running = 1;
    globals.radio_enabled = 1;
    globals.inertial_enabled = 1;
    globals.client = client;

    // set initial location threshold values
    // LOCATION TODO: set initial coordinates

    if (0 != (rc = pthread_mutex_init(&globals.lock, NULL))) {
        syslog(LOG_ERR, "error creating colordetect param mutex (%d)", rc);
        return 0;
    }

    if (0 != (rc = pthread_mutex_init(&globals.radio_lock, NULL))) {
        syslog(LOG_ERR, "error creating radio coord mutex (%d)", rc);
        return 0;
    }

    if (0 != (rc = pthread_cond_init(&globals.radio_cond, NULL))) {
        syslog(LOG_ERR, "error creating radio location event condition (%d)", rc);
        return 0;
    }

    if (0 != (rc = pthread_mutex_init(&globals.inertial_lock, NULL))) {
        syslog(LOG_ERR, "error creating IMU coord mutex (%d)", rc);
        return 0;
    }

    if (0 != (rc = pthread_cond_init(&globals.inertial_cond, NULL))) {
        syslog(LOG_ERR, "error creating IMU location event condition (%d)", rc);
        return 0;
    }

    // create and kick off the radio location thread
    pthread_create(&globals.radio_thread, 0, radio_thread, &globals);
    pthread_detach(globals.radio_thread);
    
    // create and kick off the IMU location thread
    pthread_create(&globals.inertial_thread, 0, inertial_thread, &globals);
    pthread_detach(globals.inertial_thread);

    return 1;
}

// -----------------------------------------------------------------------------
void location_shutdown(void)
{   
    if (!globals.running) {
        syslog(LOG_INFO, "calling colordetect_shutdown prior to init\n");
        return;
    }

    globals.running = 0;
    pthread_cancel(globals.radio_thread);
    pthread_cancel(globals.inertial_thread);
    pthread_mutex_destroy(&globals.lock);
    pthread_mutex_destroy(&globals.radio_lock);
    pthread_cond_destroy(&globals.radio_cond);
    pthread_mutex_destroy(&globals.inertial_lock);
    pthread_cond_destroy(&globals.inertial_cond);
}

// -----------------------------------------------------------------------------
void location_radio_enable(int enabled)
{
    globals.radio_enabled = enabled;    
    syslog(LOG_INFO, "Radio Localization Enabled Set to:%d\n",enabled);    
}

// -----------------------------------------------------------------------------
void location_inertial_enable(int enabled)
{
    globals.inertial_enabled = enabled;    
    syslog(LOG_INFO, "Inertial Localization Enabled Set to:%d\n",enabled);    
}

// -----------------------------------------------------------------------------
int location_radio_get_enable()
{    
    return globals.radio_enabled;
}

// -----------------------------------------------------------------------------
int location_inertial_get_enable()
{    
    return globals.inertial_enabled;
}

//------------------------------------------------------------------------------
void location_radio_set_rate(unsigned int rate)
{
    pthread_mutex_lock(&globals.lock);
    globals.radio_rate = rate;
    pthread_mutex_unlock(&globals.lock);
}

//------------------------------------------------------------------------------
unsigned int location_inertial_set_rate()
{
    unsigned int rval;
    pthread_mutex_lock(&globals.lock);
    rval = globals.inertial_rate;
    pthread_mutex_unlock(&globals.lock);
    return rval;
}

//------------------------------------------------------------------------------
int location_radio_read_state(location_coords_t *coords, access_mode_t mode)
{
    pthread_mutex_lock(&globals.radio_lock);

    switch (mode) {
    case ACCESS_ASYNC:
        // access in an asynchronous (non-blocking) fashion
        break;
    case ACCESS_SYNC:
        // access in a synchronous (blocking) fashion
        pthread_cond_wait(&globals.radio_cond, &globals.radio_lock);
        break;
    default:
        pthread_mutex_unlock(&globals.radio_lock);
        memset(coords, 0, sizeof(location_coords_t));
        syslog(LOG_ERR, "location_read_state: invalid access mode\n");
        return 0;
    }

    *coords = globals.radio_coords;
    pthread_mutex_unlock(&globals.radio_lock);
    return 1;
}

//------------------------------------------------------------------------------
int location_inertial_read_state(location_coords_t *coords, access_mode_t mode)
{
    pthread_mutex_lock(&globals.inertial_lock);

    switch (mode) {
    case ACCESS_ASYNC:
        // access in an asynchronous (non-blocking) fashion
        break;
    case ACCESS_SYNC:
        // access in a synchronous (blocking) fashion
        pthread_cond_wait(&globals.inertial_cond, &globals.inertial_lock);
        break;
    default:
        pthread_mutex_unlock(&globals.inertial_lock);
        memset(coords, 0, sizeof(location_coords_t));
        syslog(LOG_ERR, "location_read_state: invalid access mode\n");
        return 0;
    }

    *coords = globals.inertail_coords;
    pthread_mutex_unlock(&globals.inertial_lock);
    return 1;
}

