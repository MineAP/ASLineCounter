/*
 * CountInfo.cpp
 *
 *  Created on: 2011/05/21
 *      Author: shiraminekeisuke
 */

#include "CountInfo.h"

CountInfo::CountInfo() {
}

CountInfo::~CountInfo() {
}

void CountInfo::setData(long charCount, long lineCount, long commentCount, const std::string& path, bool isDir)
{
	m_charCount = charCount;
	m_lineCount = lineCount;
	m_commentLineCount = commentCount;
	m_path = path;
	m_isDir = isDir;
}

long CountInfo::getCharCount()
{
	return m_charCount;
}

long CountInfo::getLineCount()
{
	return m_lineCount;
}

long CountInfo::getCommentLineCount()
{
	return m_commentLineCount;
}

bool CountInfo::isDir()
{
	return m_isDir;
}

std::string const CountInfo::getPath()
{
	return m_path;
}

void const CountInfo::addCount(CountInfo& info)
{
	m_charCount += info.getCharCount();
	m_lineCount += info.getLineCount();
	m_commentLineCount += info.getCommentLineCount();
}
