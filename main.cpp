/*
 * main.cpp
 *
 *  Created on: 17 Jul 2017
 *      Author: hhoca
 */

#include <iostream>
#include "HTMLParser.h"

using namespace std;
using namespace weblib;

int main(int argCount, char **args){

	if(argCount < 2){
		cout << "Not enough arguments" << endl;
		return -1;
	}

	HTMLParser parser(args[1]);
	Website site = parser.getResult();
	HTMLParser::debugPrint(site);

	//cout << "html tag count is " << site.html.size() << endl;

}
