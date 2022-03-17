/**
* @file
* @brief Simple timer logic
*/

#pragma once

/**
 * @brief Resets the timer.
 */
void resetTimer();

/**
 * @brief Checks if time since reset is more than the given seconds.
 * 
 * @param[in] seconds Number of seconds.
 * 
 * @return true if time since reset is more than the given seconds, false otherwise.
 */
bool checkTimer(int seconds);

