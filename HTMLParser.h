/*
 * HTMLParser.h
 *
 *  Created on: 17 Jul 2017
 *      Author: hhoca
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <iostream>
#include <stack>
#include <vector>
#include <map>

namespace weblib {

typedef enum{
	STARTTAG, ENDTAG, INNER, ATTRIBUTE
}Parsing_State;

class HTML_Parser;
class HTML_Tag;

class Website{
public:
	Website();
	virtual ~Website();
	std::vector<HTML_Tag> html;
};

class HTML_Tag{
	friend class HTML_Parser;
public:
	HTML_Tag();
	virtual ~HTML_Tag();
	const std::string &getName();
	const std::string &getInnerHTML();
	const std::string &getAttributeText();
	std::vector<HTML_Tag> &getChildren();
	void setName(std::string name);
	void setInnerHTML(std::string inner);
	void setAttributeText(std::string attributeString);
	void addChild(HTML_Tag child);
private:
	std::string name;
	std::string inner;
	std::string attributeStr;
	std::map<std::string, std::string> attributes;
	std::vector<HTML_Tag> children;
};

class HTMLParser {
public:
	HTMLParser(std::string);
	Website &getResult();
	virtual ~HTMLParser();
	static void debugPrint(Website &website);
private:
	std::string html;
	Website site;
	static void printTag(HTML_Tag &tag);
};

} /* namespace weblib */

#endif /* HTMLPARSER_H_ */
