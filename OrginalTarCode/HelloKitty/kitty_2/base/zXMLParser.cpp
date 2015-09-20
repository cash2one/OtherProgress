/**
 * \file
 * \version  $Id: zXMLParser.cpp 13 2013-03-20 02:35:18Z  $
 * \author  ,okyhc@263.sina.com
 * \date 2004年11月03日 14时21分09秒 CST
 * \brief zXMLParser类实现文件
 *
 * 
 */

#include <iconv.h>
#include <string.h>
#include <iostream>

#include "zXMLParser.h"
#include "zType.h"
#include "Fir.h"

static void finalLibXML2() __attribute__ ((destructor));
void finalLibXML2()
{
	xmlCleanupParser();
}

/**
 * \brief 构造zXMLParser
 */
zXMLParser::zXMLParser()
{
	doc = NULL;
}

/**
 * \brief zXMLParser的析构函数
 *
 * 回收分配的空间，关闭打开文件等
 */
zXMLParser::~zXMLParser()
{
	final();
}

/**
 * \brief 初始化要解析的xml文件
 *
 * 
 * \param xmlFile 文件路径，绝对或者相对的。
 * \return 成功返回true，失败返回false。 
 */
bool zXMLParser::initFile(const std::string &xmlFile)
{
	return initFile(xmlFile.c_str());
}

/**
 * \brief 初始化要解析的xml文件
 * \param xmlFile 文件路径，绝对或者相对的。
 * \return 成功返回true，失败返回false。 
 */
bool zXMLParser::initFile(const char *xmlFile)
{
	final();
	if(xmlFile==NULL) return false;
	doc = xmlParseFile(xmlFile);
	return (doc!=NULL);
}

/**
 * \brief 初始化要解析的XML字符串
 *
 *
 * \param xmlStr 被初始化的xml字符串。
 * \return 成功返回true，失败返回false。
 */
bool zXMLParser::initStr(const std::string &xmlStr)
{
	return initStr(xmlStr.c_str());
}

/**
 * \brief 初始化要解析的XML字符串
 *
 *
 * \param xmlStr 被初始化的xml字符串。
 * \return 成功返回true，失败返回false。
 */
bool zXMLParser::initStr(const char *xmlStr)
{
	final();
	if(xmlStr == NULL) return false;
	doc = xmlParseDoc((xmlChar *)xmlStr);
	return (doc!=NULL);
}

/**
 * \brief 初始化XML
 * \return 成功返回true，失败返回false。
 */
bool zXMLParser::init()
{
	final();
	doc = xmlNewDoc((const xmlChar *)"1.0");
	return (doc!=NULL);
}

/**
 * \brief 释放被解析的xml文档 
 *
 *
 */
void zXMLParser::final()
{
	if(doc)
	{
		xmlFreeDoc(doc);
		doc=NULL;
	}
}

/**
 * \brief dump出XML文档
 * \param s 文档存放位置
 * \param format 输出时候是否格式化文档
 * \return 返回s
 */
std::string & zXMLParser::dump(std::string & s, bool format)
{
	if (doc)
	{
		xmlChar *out=NULL;
		int size=0;
		//xmlDocDumpMemory(doc,&out,&size);
		xmlDocDumpFormatMemory(doc,&out,&size,format?1:0);
		if(out!=NULL )
		{
			s=(char *)out;
			xmlFree(out);
		}
	}
	return s;
}

/**
 * \brief dump出XML文档
 * \param s 文档存放位置
 * \param format 输出时候是否格式化文档
 * \return 返回s
 */
std::string & zXMLParser::dumpNohead(std::string & s)
{
	if (doc)
	{
		xmlChar *out=NULL;
		int size=0;
		//xmlDocDumpMemory(doc,&out,&size);
		xmlDocDumpFormatMemoryEnc(doc,&out,&size,"GB2312",1);
		if(out)
		{
			char* ret = NULL;
			if((ret = strchr((char*)out,'\n')))
				s=ret + 1;
			xmlFree(out);
		}
		
	}
	return s;
}
/**
 * \brief dump出某个节点
 * \param dumpNode 要被Dump的节点
 * \param s 文档存放位置
 * \param head 是否添加xml文件头.默认true
 * \return 返回s
 */
std::string & zXMLParser::dump(xmlNodePtr dumpNode,std::string & s ,bool head)
{
	if (dumpNode==NULL) return s;
	xmlBufferPtr out=xmlBufferCreate();
	if(xmlNodeDump(out,doc,dumpNode,1,1)!=-1)
	{
		unsigned char *cout = charConv((unsigned char *)out->content,"UTF-8",(const char *)doc->encoding);
		if (cout)
		{
			if(head)
			{
				s="<?xml version=\"1.0\" encoding=\"";
				s+=(char *)doc->encoding;
				s+="\"?>";
			}
			else
				s="";
			s+=(char *)cout;
			SAFE_DELETE_VEC(cout);
		}
	}
	xmlBufferFree(out);
	return s;
}

/**
 * \brief 得到xml文档的根节点
 * \param rootName 根节点的名字。
 * \return 返回根节点指针,返回NULL失败。
 */
xmlNodePtr zXMLParser::getRootNode(const char *rootName)
{
	if(doc == NULL) return NULL;

	//得到根节点
	xmlNodePtr cur = xmlDocGetRootElement(doc);
	//准备起始节点
	if(rootName!=NULL)
		while (cur != NULL && xmlStrcmp(cur->name, (const xmlChar *) rootName))
			cur = cur->next;
	return cur;
}

/**
 * \brief 得到某个节点的子节点
 *
 *
 * \param parent 父节点
 * \param childName 子节点的名称，如果为NULL，将会得到第一个子节点。
 * \return 子节点指针，返回NULL失败或者没有相应的节点。
 */
xmlNodePtr zXMLParser::getChildNode(const xmlNodePtr parent, const char *childName)
{
	if(parent==NULL) return NULL;
	xmlNodePtr retval=parent->children;
	if(childName)
		while(retval)
		{
			if(!xmlStrcmp(retval->name, (const xmlChar *) childName)) break;
			retval=retval->next;
		}
	else
		while(retval)
		{
			if(!xmlNodeIsText(retval)) break;
			retval=retval->next;
		}

	return retval;
}

/**
 * \brief 得到下一个节点
 *
 *
 * \param node 当前节点
 * \param nextName 下一个节点的名字，如果为NULL，将会得到相邻的下一个节点。
 * \return 下一个节点指针，返回NULL失败或者没有相应的节点。
 */
xmlNodePtr zXMLParser::getNextNode(const xmlNodePtr node,const char *nextName)
{
	if(node==NULL) return NULL;
	xmlNodePtr retval=node->next;
	if(nextName)
		while(retval)
		{
			if(!xmlStrcmp(retval->name, (const xmlChar *)nextName)) break;
			retval=retval->next;
		}
	else
		while(retval)
		{
			if(!xmlNodeIsText(retval)) break;
			retval=retval->next;
		}
	return retval;
}

/**
 * \brief 统计子节点的数量
 *
 *
 * \param parent 被统计的父节点
 * \param childName 被统计子节点的名字，如果为NULL，统计所有子节点的数量
 * \return 子节点的数量
 */
unsigned int zXMLParser::getChildNodeNum(const xmlNodePtr parent, const char *childName)
{
	int retval=0;
	if(parent==NULL) return retval;
	xmlNodePtr child=parent->children;
	if(childName)
		while(child)
		{
			if(!xmlStrcmp(child->name, (const xmlChar *) childName)) retval++;
			child=child->next;
		}
	else
		while(child)
		{
			if(!xmlNodeIsText(child)) retval++;
			child=child->next;
		}
	return retval;
}

/**
 * \brief 为xml文档添加一个根节点
 * \param rootName 根节点名称
 * \return 添加节点以后，返回节点指针
 */
xmlNodePtr zXMLParser::newRootNode(const char *rootName)
{
	if (NULL == doc)
		return NULL;

	xmlNodePtr root_node = xmlNewNode(NULL, (const xmlChar *)rootName);
	xmlDocSetRootElement(doc, root_node);
	return root_node;
}

/**
 * \brief 在一个节点下面添加子节点
 * \param parent 父节点
 * \param childName 子节点名称
 * \param content 子节点内容
 * \return 返回添加节点的指针
 */
xmlNodePtr zXMLParser::newChildNode(const xmlNodePtr parent, const char *childName, const char *content)
{
	if (NULL == parent)
		return NULL;

	return xmlNewChild(parent, NULL, (const xmlChar *)childName, (const xmlChar *)content);
}

bool zXMLParser::newNodeProp(const xmlNodePtr node,const char *propName,const char *prop)
{
	if (NULL == node)
		return false;

	return (NULL != xmlNewProp(node, (const xmlChar *)propName, (const xmlChar *)prop));
}

bool zXMLParser::newNodeProp(const xmlNodePtr node,const char *propName,const char *prop,const char* encoding)
{
	if (NULL == node)
		return false;

	bool ret = false;
	unsigned char *out =charConv((unsigned char *)prop,encoding,"UTF-8");
	if(out)
	{
		ret = newNodeProp(node,propName,(char*)out);
		SAFE_DELETE_VEC(out);
	}
	return ret;
}

/**
 * \brief 得到节点属性，并转化成数字
 *
 *
 * \param node 对象节点
 * \param propName 要得到的属性名称
 * \param prop 返回结果的存储位置指针
 * \param propSize prop的空间大小
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodePropNum(const xmlNodePtr node,const char *propName,void *prop, const int propSize)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL || prop==NULL || propName==NULL) return false;
	temp = (char *)xmlGetProp(node, (const xmlChar *) propName);
	if(temp ==NULL ) return false;
	switch(propSize)
	{
		case sizeof(BYTE):
			*(BYTE *)prop=(BYTE)atoi(temp);
			break;
		case sizeof(WORD):
			*(WORD *)prop=(WORD)atoi(temp);
			break;
		case sizeof(DWORD):
			*(DWORD *)prop=atoi(temp);
			break;
		case sizeof(QWORD):
			*(QWORD *)prop=atoll(temp);
			break;
		default:
			ret=false;
	}
	if(temp) xmlFree(temp);
	return ret;
}

/**
 * \brief 得到节点属性
 *
 *
 * \param node 对象节点
 * \param propName 要得到的属性名称
 * \param prop 返回结果的存储位置指针
 * \param propSize prop的空间大小
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodePropStr(const xmlNodePtr node,const char *propName,void *prop,int propSize)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL || prop==NULL || propName==NULL) return false;
	temp =(char *)xmlGetProp(node, (const xmlChar *) propName);
	if(temp ==NULL ) return false;
	unsigned char *out =charConv((unsigned char *)temp,"UTF-8",(const char *)doc->encoding);
	if (out)
	{
		bzero(prop, propSize);
		strncpy((char *)prop,(const char*)out, propSize - 1);
		SAFE_DELETE_VEC(out);
	}
	if(temp) xmlFree(temp);
	return ret;
}

/**
 * \brief 得到节点属性
 *
 *
 * \param node 对象节点
 * \param propName 要得到的属性名称
 * \param prop 返回结果的存储位置
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodePropStr(const xmlNodePtr node,const char *propName,std::string &prop)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL || propName==NULL) return false;
	temp =(char *)xmlGetProp(node, (const xmlChar *) propName);
	if(temp ==NULL ) return false;
	unsigned char *out =charConv((unsigned char *)temp,"UTF-8",(const char *)doc->encoding);
	if (out)
	{
		prop = (char *)out;
		SAFE_DELETE_VEC(out);
	}
	if(temp) xmlFree(temp);
	return ret;
}

bool zXMLParser::getNodePropTime(const xmlNodePtr node,const char *propName,time_t &prop)
{
	std::string str;
	if (!getNodePropStr(node, propName, str))
		return false;

	tm tv;
	time_t theTime = 0;
	if (NULL == strptime(str.c_str(), "%Y%m%d %H:%M:%S", &tv))
		return false;
	
	theTime = timegm(&tv);
	if ((time_t)-1 == theTime)
		return false;

	prop = theTime - 8*60*60;//UTC时间
	return true;
}

bool zXMLParser::getNodeContentTime(const xmlNodePtr node,time_t &prop)
{
	std::string str;		
	if (!getNodeContentStr(node, str))
		return false;

	tm tv;
	time_t theTime = 0;
	if (NULL == strptime(str.c_str(), "%Y%m%d %H:%M:%S", &tv))
		return false;

	theTime = timegm(&tv);
	if ((time_t)-1 == theTime)
		return false;

	prop = theTime - 8*60*60;//UTC时间
	return true;
}



/**
 * \brief 得到节点内容，并转化成数字
 *
 *
 * \param node 对象节点
 * \param content 返回结果的存储位置指针
 * \param contentSize content的空间大小
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodeContentNum(const xmlNodePtr node,void *content, int contentSize)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL || content==NULL) return false;
	xmlNodePtr text=node->children;
	while(text!=NULL)
	{
		if(!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp =(char *)text->content;
			break;
		}
		text=text->next;
	}
	if(temp ==NULL ) return false;
	switch(contentSize)
	{
		case sizeof(BYTE):
			*(BYTE *)content=(BYTE)atoi(temp);
			break;
		case sizeof(WORD):
			*(WORD *)content=(WORD)atoi(temp);
			break;
		case sizeof(DWORD):
			*(DWORD *)content=atoi(temp);
			break;
		case sizeof(QWORD):
			*(QWORD *)content=atoll(temp);
			break;
		default:
			ret=false;
	}
	return ret;
}

/**
 * \brief 得到节点内容
 *
 *
 * \param node 对象节点
 * \param content 返回结果的存储位置指针
 * \param contentSize content的空间大小
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodeContentStr(const xmlNodePtr node,void *content, const int contentSize)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL || content==NULL) return false;
	xmlNodePtr text=node->children;
	while(text!=NULL)
	{
		if(!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp =(char *)text->content;
			break;
		}
		text=text->next;
	}
	if(temp ==NULL ) return false;
	unsigned char *out = charConv((unsigned char *)temp,"UTF-8",(const char *)doc->encoding);
	if (out)
	{
		bzero(content, contentSize);
		strncpy((char *)content,(const char *)out, contentSize - 1);
		SAFE_DELETE_VEC(out);
	}
	return ret;
}

/**
 * \brief 得到节点内容
 *
 *
 * \param node 对象节点
 * \param content 返回结果的存储位置
 * \return  成功返回true,否则返回false
 */
bool zXMLParser::getNodeContentStr(const xmlNodePtr node,std::string &content)
{
	char *temp=NULL;
	bool ret=true;
	if(node==NULL) return false;
	xmlNodePtr text=node->children;
	while(text!=NULL)
	{
		if(!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp =(char *)text->content;
			break;
		}
		text=text->next;
	}
	if(temp ==NULL ) return false;
	unsigned char *out = charConv((unsigned char *)temp,"UTF-8",(const char *)doc->encoding);
	if (out)
	{
		content = (char *)out;
		SAFE_DELETE_VEC(out);
	}
	return ret;
}

bool zXMLParser::isNodeName(const xmlNodePtr node, const std::string& name)
{
	if(NULL == node) return false;

	if(!xmlStrcmp(node->name, (const xmlChar *)name.c_str()))
	{
		return true;		
	}

	return false;
}

//准备输入xml字符串
//返回内存指针必须手工释放
unsigned char* zXMLParser::charConv(unsigned char *in, const char *fromEncoding,const char * toEncoding)
{
	unsigned char *out;
	size_t ret, size, out_size;

	size = strlen((char *)in); 
	out_size = size * 2 + 1; 
	out = FIR_NEW unsigned char[out_size]; 
	bzero(out,out_size);
	if (out)
	{
		if(fromEncoding!=NULL && toEncoding!=NULL)
		{
			iconv_t icv_in = iconv_open(toEncoding, fromEncoding);
			if ((iconv_t)-1 == icv_in)
			{
				SAFE_DELETE_VEC(out);
				out = NULL;
			}
			else
			{
				char *fromtemp = (char *)in;
				char *totemp =(char *)out;
				size_t tempout = out_size-1;
				ret =iconv(icv_in, &fromtemp, &size, &totemp,&tempout);
				if ((size_t)-1 == ret)
				{
					SAFE_DELETE_VEC(out);
					out = NULL;
				}
				iconv_close(icv_in);
			}
		}
		else
			strncpy((char *)out,(char *)in,size);
	}
	return (out);
}
