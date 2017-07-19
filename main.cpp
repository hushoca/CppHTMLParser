/*
 * main.cpp
 *
 *  Created on: 17 Jul 2017
 *      Author: hhoca
 */

#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <map>

using namespace std;

typedef struct{
	string name;
	string value;
	string attributes;
	vector<void *> children;
	//map<string, string> attributes;
}HTML_TAG;

typedef enum{
	TAG=0, ENDTAG=1, ATTR=2, INNER=3, IGNORE=4
} PARSE_STATE;

string state(PARSE_STATE s){
	switch(s){
		case TAG:
			return "tag";
		case ENDTAG:
			return "end_tag";
		case INNER:
			return "inner";
		case ATTR:
			return "tag";
		case IGNORE:
			return "ignore";
	}
	return "";
} //FOR DEBUGGING

void printTag(HTML_TAG *child){
		cout << "--------------------------------" << endl;
		cout << "Name is " << child->name << endl;
		cout << "Attributes are " << child->attributes << endl;
		cout << "Value is " << child->value << endl;
		cout << "Children count " << child->children.size() << endl;
		for(int c = 0; c < child->children.size(); c++){
			printTag((HTML_TAG*)child->children[c]);
		}
}

int main(int argCount, char **args){

	if(argCount < 2){
		cout << "Not enough arguments" << endl;
		return -1;
	}

	//cout << args[1] << endl;

	stack<HTML_TAG*> tagStack;
	PARSE_STATE activeState = TAG; //holds the active state

	//stack<HTML_TAG*> resultStack;

	HTML_TAG* result;

	string html = args[1];
	int htmlLength = strlen(args[1]);

	//run though each character in the string
	//not C++11 way
	for(int loc = 0; loc < htmlLength; loc++){

		char currentChar = html[loc];
		char nextChar = (loc + 1 >= htmlLength)? '\0' : html[loc + 1];

		//FOR DEBUGGING
		cout << "state is " << state(activeState) << " character is " << currentChar << endl;

		//ignore the end tag so it doesn't get put into the inner value
		if(activeState == IGNORE && currentChar != '>'){
			if(currentChar == '>') activeState == TAG;
			continue;
		}

		//TODO ** USE A SWITCH IT'S CLEANER **
		if(currentChar == '<'){
			if(nextChar == '/'){
				string name = tagStack.top()->name;
				//if(name.compare(html) == 0){
					HTML_TAG* active = tagStack.top();
					tagStack.pop();
					cout << "Popped the tag off the stack" << endl;
					if(tagStack.empty()){
						cout << "Stack empty" << endl;
						result = active;
					}else tagStack.top()->children.push_back(active);// = active;
					//resultStack.push(active);
				//}
				//tag end
			}else{
				activeState = TAG;
				tagStack.push(new HTML_TAG);
				cout << "Pushed a new tag to stack" << endl;
				//tag start
			}
		}else if(currentChar == '>'){
			if(activeState == TAG || activeState == ATTR){
				activeState = INNER;
			}
			//tag end
		}else if(currentChar == ' '){
			//attribute start
			if(activeState == TAG){
				activeState = ATTR;
			}
		}else{
			//routine inserting values into the struct
			if(tagStack.empty()){
				cout << "stack empty" << endl;
				continue;
			}
			switch(activeState){
				case TAG:
					tagStack.top()->name += currentChar;
					break;
				case INNER:
					tagStack.top()->value += currentChar;
					break;
				case ATTR:
					tagStack.top()->attributes += currentChar;
					break;
				default:
					cout << "Wrong state!" << endl;
					break;
			}
			//add value or attribute
		}

	}

	printTag(result);
	//TODO ** FREE THE TAGS! MEMORY LEAK! **

}
