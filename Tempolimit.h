/*
 * Tempolimit.h
 *
 *  Created on: 19 Dec 2022
 *      Author: Rebal Atteya
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

enum class Tempolimit {Innerorts = 50, Landstrasse = 100, Autobahn = std::numeric_limits<int>::max()};

#endif /* TEMPOLIMIT_H_ */
