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
 * @brief Checks if the timer has counted @p seconds or more.
 * 
 * @param[in] seconds Number of seconds.
 * 
 * @return true if the timer has counted @p seconds or more, else it returns false.
 */
bool checkTimer(int seconds);

