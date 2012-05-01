// -----------------------------------------------------------------------------
// File:    location.h
// Authors: Tyler Thierolf, Timothy Miller, Garrett Smith
// Created: 10-26-2010
//
// Routines for identifying location.
// -----------------------------------------------------------------------------

#ifndef _UAV_location__H_
#define _UAV_location__H_

#include "position.h"
#include "utility.h"

// Initializes and starts the threads for the two localization techniques
int location_init(client_info_t *client);

// Shuts down and cleans up the localization threads
void location_shutdown(void);

// Sets enable for radio localization
void location_radio_enable(int enabled);

// Sets enable for inertial localization
void location_inertial_enable(int enabled);

// Sets the frequency of localization for radio
void location_radio_set_rate(unsigned int rate);

// Sets the frequency of localization for inertial
void location_inertial_set_rate(unsigned int rate);

// Retreives the frequency of localization for radio
unsigned int location_radio_get_rate(void);

// Retreives the frequency of localization for inertial
unsigned int location_inertial_get_rate(void);

// Retrievs a copy of coordinates from globals for position reported by radio
int location_radio_read_state(location_coords_t *coords, access_mode_t mode);

// Retrievs a copy of coordinates from globals for position reported by radio
int location_inertial_read_state(location_coords_t *coords, access_mode_t mode);

// return current location enable state for radio
int location_radio_get_enable();

// return current location enable state for radio
int location_inertial_get_enable();

void add_waypoint(location_coords_t *new_waypoint)

void clear_waypoints()

location_coords_t* get_next_waypoint()

void increment_waypoint_index()

location_coords_t get_current_location()

#endif // _UAV_location__H_

