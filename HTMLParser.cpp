/*
 * HTMLParser.cpp
 *
 *  Created on: 17 Jul 2017
 *      Author: hhoca
 */

#include "HTMLParser.h"

namespace weblib {

using namespace std;

//constructor...
HTMLParser::HTMLParser(std::string html){
	this->html = html;
}

//handle the popping process of the stack
static int handlePop(stack<HTML_Tag> &stack, Website &site){
	//make sure stack is not empty
	if(!stack.empty()){
		//save the last entity, pop it then put it into the one above
		//as child.
		HTML_Tag topEntity = stack.top();
		stack.pop();
		if(stack.empty()){
			//if there is no parent, put the top entity into the website
			site.html.push_back(topEntity);
			return -1;
		}else stack.top().getChildren().push_back(topEntity);
	}else return -1;
	return 0;
}

//determine the start of a tag (and the start of end tags) and push and pop to the stack
//accordingly
static int checkTagStart(stack<HTML_Tag> &stack, char currentChr, char nextChr, Parsing_State &state, Website &site){
	if(nextChr == '/'){
		//end tag
		state = ENDTAG;
		if(handlePop(stack, site) != 0){
			return -1;
		}
		return 1;
	}else{
		//tag start detected push a HTML_Tag onto the stack
		HTML_Tag tag;
		stack.push(tag);
	}

	state = STARTTAG;
	return 0;
}

//switch state according to current state
static int checkEnding(Parsing_State &state){
	switch(state){
		case STARTTAG:
			state = INNER;
			return 0;

		case ATTRIBUTE:
			state = INNER;
			return 0;

		case ENDTAG:
			state = STARTTAG;
			return 0;

		default:
			return -1;
	}
	return 0;
}

//determine which data object gets the current char
static int putCharIntoCollection(stack<HTML_Tag> &stack, char chr, Parsing_State &state){
	if(stack.empty()) return -1;
	HTML_Tag &tag = stack.top();
	switch(state){
		case STARTTAG:
			tag.setName(tag.getName() + chr);
			break;
		case INNER:
			tag.setInnerHTML(tag.getInnerHTML() + chr);
			break;
		case ATTRIBUTE:
			tag.setAttributeText(tag.getAttributeText() + chr);
			break;
		default:
			break;
	}
	return 0;
}

//determine if a tag is singleton, if so pop it
static int singletonTagCheck(stack<HTML_Tag> &stack, char currentChr, char nextChr, Parsing_State &state, Website &site){
	if(state == STARTTAG || state == ATTRIBUTE){
		if(currentChr == '/' && nextChr == '>'){
			if(handlePop(stack, site) != 0){
				return -1;
			}else{
				return 1;
			}
		}
	}
	return 0;
}

//for debugging
void HTMLParser::printTag(HTML_Tag &tag){
	cout << "name -> {" << tag.getName() << "}" << endl;
	cout << "attributes -> {" << tag.getAttributeText() << "}" << endl;
	cout << "inner -> {" << tag.getInnerHTML() << "}" << endl << endl;
	if(!tag.getChildren().empty()){
		for(int i = 0; i < tag.getChildren().size(); i++){
			HTMLParser::printTag(tag.getChildren()[i]);
		}
	}
}

//for debugging
inline void printState(Parsing_State state){
	switch(state){
	case STARTTAG:
		cout << "state is start tag" << endl;
		break;
	case ENDTAG:
		cout << "state is end tag" << endl;
		break;
	case INNER:
		cout << "state is inner" << endl;
		break;
	case ATTRIBUTE:
		cout << "state is attributes" << endl;
		break;
	}
}

Website &HTMLParser::getResult(){

	//html tag stack
	stack<HTML_Tag> htmlTags;
	HTML_Tag lastPopped;

	//parsing state
	Parsing_State state;

	//iterate through the html
	string::size_type htmlSize = html.length();
	for(string::size_type chr = 0; chr < htmlSize; chr++){
		//get current and next char (if next char out of bounds make it '\0')
		char currentChr = html[chr];
		char nextChr = (chr + 1 < htmlSize)? html[chr + 1] : '\0';

		int result = 0;
		switch(currentChr){
			case '<':
				//detect start tags and end tags
				result = checkTagStart(htmlTags, currentChr, nextChr, state, site);
				if(result == 1) chr++;
				continue;
			case '>':
				//detect which state to move to
				checkEnding(state);
				continue;
			case ' ':
				//detect attributes
				if(state == STARTTAG) state = ATTRIBUTE;
				break;
			case '/':
				//detect singleton tags
				result = singletonTagCheck(htmlTags, currentChr, nextChr, state, site);
				if(result == 1) chr++;
				continue;

			default:
				//?
				break;
		}

		//push html into data classes
		putCharIntoCollection(htmlTags, currentChr, state);

	}

	return site;
}

void HTMLParser::debugPrint(Website &website){
	for(unsigned int i = 0; i < website.html.size(); i++){
		printTag(website.html[i]);
	}
}

HTMLParser::~HTMLParser(){}

Website::Website(){}

Website::~Website(){}

HTML_Tag::HTML_Tag(){}

const std::string &HTML_Tag::getName(){
	return name;
}

const std::string &HTML_Tag::getInnerHTML(){
	return inner;
}

const std::string &HTML_Tag::getAttributeText(){
	return attributeStr;
}

std::vector<HTML_Tag> &HTML_Tag::getChildren(){
	return children;
}

void HTML_Tag::setName(string name){
	this->name = name;
}

void HTML_Tag::setInnerHTML(string inner){
	this->inner = inner;
}

void HTML_Tag::setAttributeText(string attributeStr){
	this->attributeStr = attributeStr;
}

HTML_Tag::~HTML_Tag(){}

} /* namespace weblib */
