// -----------------------------------------------------------------------------
// File:    position.h
// Authors: Tyler Thierolf, Timothy Miller, Garrett Smith
// Created: 10-01-2010
//
// Routines for detecting solid colors within RGB or HSL images, as well as
// algorithms to convert between color spaces.
// -----------------------------------------------------------------------------

#ifndef _UAV_POSITION__H_
#define _UAV_POSITION__H_

#include "utility.h"
#include <time.h>

typedef struct {
    //int tol;        // tolerance of coordinate
    int detected;   // 0 when locations is not known
    int x, y;       // center coordinate
} location_coords_t;

/* Integrated into threads for radio and inertial
// determine position, uses inertial updates to last known location
void position_intertial(const uint8_t *rgb_in,
        const track_color_t *color, track_coords_t *box);

// determine position, uses last reported position from location service
void position_radio(const uint8_t *rgb_in, real_t threshold,
        const track_color_t *color, track_coords_t *box);
*/

#endif // _UAV_position__H_

