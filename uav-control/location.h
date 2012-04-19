// -----------------------------------------------------------------------------
// File:    location.h
// Authors: Tyler Thierolf, Timothy Miller, Garrett Smith
// Created: 10-26-2010
//
// Routines for identifying location.
// -----------------------------------------------------------------------------

#ifndef _UAV_location__H_
#define _UAV_location__H_

#include "colordetect.h"
#include "utility.h"

// TODO: describe me
int location_init(client_info_t *client);

// TODO: describe me
void location_shutdown(void);

// TODO: describe me
void location_radio_enable(int enabled);

// TODO: describe me
void location_inertial_enable(int enabled);

// TODO: describe me
void location_radio_set_rate(unsigned int rate);

// TODO: describe me
void location_inertial_set_rate(unsigned int rate);

// TODO: describe me
unsigned int location_radio_get_rate(void);

// TODO: describe me
unsigned int location_inertial_get_rate(void);

// TODO: describe me
int location_radio_read_state(track_coords_t *coords, access_mode_t mode);

// TODO: describe me
int location_inertial_read_state(track_coords_t *coords, access_mode_t mode);

// return current location state
int location_radio_get_enable();

// return current location state
int location_inertial_get_enable();

#endif // _UAV_location__H_

