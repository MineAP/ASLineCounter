//============================================================================
// Name        : LineCounter.cpp
// Author      : shiraminekeisuke(MineAP)
// Version     :
// Copyright   : copyright (C) 2011 MineAppProject. All rights reserved.
// Description :
//============================================================================

#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string>
#include "LineCounter.h"

using namespace std;


LineCounter::LineCounter()
{

}

LineCounter::~LineCounter()
{

}

void LineCounter::trim(const std::string& str, std::string& dist)
{
    int i,j,start,end;

    //ltrim
    for (i=0; (str[i]!=0 && str[i]<=32); )
        i++;
    start=i;

    //rtrim
    for(i=0,j=0; str[i]!=0; i++)
        j = ((str[i]<=32)? j+1 : 0);
    end=i-j;

    dist = str.substr(start,end-start);
}

void LineCounter::readAndCount(const std::string& filePath, CountInfo& info)
{

	std::ifstream ifs(filePath.c_str());
	std::string str;
	std::string tempStr;

	long lineCount = 0;
	long charCount = 0;
	long commentCount = 0;


	bool isSkipping = false;

	while (!ifs.eof())
	{

		getline(ifs, str);

		trim(str, tempStr);

		if (tempStr.length() > 0)
		{
			if (tempStr.length() > 1)
			{
				bool isMultiLineStart = false;
				if (tempStr[0] == '/' && tempStr[1] == '/')
				{
//					cout << tempStr[0] << tempStr[1] << endl;
					++commentCount;
					continue;
				}
				if (tempStr[0] == '/' && tempStr[1] == '*')
				{
//					cout << tempStr[0] << tempStr[1] << endl;
					++commentCount;
					isSkipping = true;
					isMultiLineStart = true;
					// "/*" を見つけた時はこの行に "*/" が無いか調べる
				}
				if (tempStr[tempStr.length() - 2] == '*'
						&& tempStr[tempStr.length() - 1] == '/')
				{
//					cout << tempStr[tempStr.length() - 2] <<
//							tempStr[tempStr.length() - 1] << endl;
					if (!isMultiLineStart)
					{
						++commentCount;
					}
					isSkipping = false;
					continue;
				}
				if(isSkipping)
				{
					// "*/" が無ければスキップ
					continue;
				}
			}

			if (isSkipping)
			{
				++commentCount;
				continue;
			}

			++lineCount;
			charCount += tempStr.length();
		}
		else
		{
			// nothing
		}

	}

	info.setData(charCount, lineCount, commentCount, filePath, false);

}

void LineCounter::count(const std::string& path, CountInfo& info)
{

	DIR *dir = opendir( path.c_str() );

	struct dirent *dent;

	if (dir)
	{
		while (dent = readdir( dir ))
		{
			if (dent->d_namlen > 0 && dent->d_name[0] == '.')
			{
				continue;
			}

			if (DT_DIR == dent->d_type)
			{
				std::string tempPath;
				tempPath.append(path);
				tempPath.append("/");
				tempPath.append(dent->d_name);

				CountInfo tempInfo;
				tempInfo.setData(0,0,0,tempPath,true);

				count(tempPath, tempInfo);

				cout << tempInfo.getPath() << endl;
				cout << "line:" << tempInfo.getLineCount() << endl;
				cout << "char:" << tempInfo.getCharCount() << endl;
				cout << "comm:" << tempInfo.getCommentLineCount() << endl;

				info.addCount(tempInfo);
			}
			else
			{
				std::string filename(dent->d_name);

				size_t pos;
				pos = filename.find(".as");
				if(pos == std::string::npos)
				{
					pos = filename.find(".mxml");
				}
				if(pos == std::string::npos)
				{
					continue;
				}

				std::string targetFilePath;
				targetFilePath.append(path);
				targetFilePath.append("/");
				targetFilePath.append(dent->d_name);

				CountInfo tempInfo;
				tempInfo.setData(0,0,0,targetFilePath,false);

//				cout << targetFilePath << endl;
				readAndCount(targetFilePath, tempInfo);

				info.addCount(tempInfo);
			}
		}

		closedir(dir);

		free(dent);
		dent = NULL;

	}
	else
	{
		cout << "Filed to open directory '" << path << "'" << endl;
	}

}



int main() {

	std::string path1 = "/Users/shiraminekeisuke/Documents/Adobe Flash Builder 4.5/NNDDv2/src";

	CountInfo info;
	info.setData(0, 0, 0, path1, true);

	LineCounter counter;
	counter.count(path1, info);


	std::string path2 = "/Users/shiraminekeisuke/Documents/Adobe Flash Builder 4.5/nicovideo4as/src";
	CountInfo info2;
	info2.setData(0, 0, 0, path2, true);
	counter.count(path2, info2);

	info.addCount(info2);

	cout << "コード行数:" << info.getLineCount() << endl;
	cout << "文字数:" << info.getCharCount() << endl;
	cout << "コメント行数:" << info.getCommentLineCount() << endl;

//	コード行数:32247
//	文字数:1168423
//	コメント行数:7684

	return 0;
}
