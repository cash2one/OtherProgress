#ifndef _WORD_FILTER_H
#define _WORD_FILTER_H

#include <fstream>
#include "zRegex.h"

/**
 * \brief 禁言过虑类
 *
 */
class wordFilter : public Singleton<wordFilter>
{
	friend class Singleton<wordFilter>;
	private:
		static wordFilter *instance;
		std::map<std::string, std::string> forbidWords;
		wordFilter()
		{
			init();
		}
		void init();
	public:
		bool doFilter(char *text, unsigned int cmdLen);
};

/**
 * \brief 读取禁言过滤表格
 *
 *
 */
void wordFilter::init()
{
	//禁止词汇
	std::string f = Fir::global["forbidWordsFile"];
	if (""==f)
		f = "forbidWords";
	std::ifstream src(f.c_str());
	if (!src)
	{
		Fir::logger->warn("打开词汇过滤列表失败！file=%s", Fir::global["forbidWordsFile"].c_str());
		return;
	}

	char buf[256];
	bzero(buf,sizeof(buf));
	std::vector<std::string> vs;
	std::vector<std::string>::iterator word,replacer;
	while (src.getline(buf, sizeof(buf)))
	{
		vs.clear();
		Fir::stringtok(vs, buf, " \t\r");
		if (vs.size()==3)
		{
			replacer = vs.begin();
			replacer++;
			word = replacer++;

			//转换成小写
			bzero(buf,sizeof(buf));
			word->copy(buf, word->length(), 0);
			for (unsigned int i=0; i<word->length() && i<(count_of(buf)-1); i++)
				buf[i] = tolower(buf[i]);
			word->assign(buf);

			forbidWords[*word] = *replacer;
			Fir::logger->debug("%lu\t%s\t%s", forbidWords.size(), (*word).c_str(), (*replacer).c_str());
		}
	}

	Fir::logger->debug("加载词汇过滤列表 %lu", forbidWords.size());
}

/**
 * \brief 禁言过虑
 *
 *
 * \param text: 过虑内容
 * \param len: 内容长度
 * \return 
 */
bool wordFilter::doFilter(char *text, unsigned int len)
{
	//进行词汇过滤
	zRegex regex;
	bool ret = true;
	
	char copy[MAX_CHATINFO+1];
	bzero(copy, sizeof(copy));
	strncpy(copy, text, MAX_CHATINFO);
	for (unsigned int i=0; i<strlen(copy) && i<(count_of(copy)-1); i++)
		copy[i] = tolower(copy[i]);
	
	std::string content(text);
	std::string content_copy(copy);
	std::string::size_type pos=0;
	
	for (std::map<std::string, std::string>::iterator it=forbidWords.begin(); it!=forbidWords.end(); ++it)
	{
		pos = content_copy.find(it->first.c_str(), 0);
		while (pos!=std::string::npos)
		{
			BYTE val = 0;
			if (pos)
				val = content_copy.c_str()[pos-1];//是否汉字的后面一半

			if (val>=0x80)
				pos = content_copy.find(it->first.c_str(), pos+1);
			else
			{
				content.replace(pos, it->first.length(), it->second.c_str());
				content_copy.replace(pos, it->first.length(), it->second.c_str());

				pos = content_copy.find(it->first.c_str(), pos+it->first.length());
				ret = false;
			}
		}
	}

	strncpy(text, content.c_str(), len);//目前恒等于16,还算安全
	return ret;
}

#endif
