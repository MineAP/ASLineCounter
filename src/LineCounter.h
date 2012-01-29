/*
 * LineCounter.h
 *
 *  Created on: 2011/05/22
 *      Author: shiraminekeisuke
 */

#ifndef LINECOUNTER_H_
#define LINECOUNTER_H_

#include <string>
#include "CountInfo.h"

class LineCounter {
	void trim(const std::string& str, std::string& dist);
public:
	LineCounter();
	virtual ~LineCounter();
	void readAndCount(const std::string& filePath, CountInfo& info);
	void count(const std::string& path, CountInfo& info);
};

#endif /* LINECOUNTER_H_ */
