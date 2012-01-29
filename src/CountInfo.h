/*
 * CountInfo.h
 *
 *  Created on: 2011/05/21
 *      Author: shiraminekeisuke
 */

#ifndef COUNTINFO_H_
#define COUNTINFO_H_

#include <string>

class CountInfo {
	long m_charCount;
	long m_lineCount;
	long m_commentLineCount;
	bool m_isDir;
	std::string m_path;
public:
	CountInfo();
	virtual ~CountInfo();
	void setData(long charCount, long lineCount, long commentLineCount, const std::string& path, bool isDir);
	std::string const getPath();
	long getCharCount();
	long getLineCount();
	long getCommentLineCount();
	bool isDir();
	void const addCount(CountInfo& info);
};

#endif /* COUNTINFO_H_ */
