Crappy C++ HTML Parsing Library [WIP]
==================================

The current version works as intended. Only thing it lacks is that there is no validator therefore, you have to make sure that the html you are parsing is valid to be more exact it can only parse xhtml (every tag should have a start and an end and img tag should be written as <img/> instead of <img>).

**TO DO**

- Implement a validator so that html can be used.
- Implement a website fetcher
- Bunch of bug fixes
- Documentation writing...

----------

**Example Input and Code**

    "<body style=\"color:#fff\">
		<head><title>Test Page</title></head>
		<html>
			<p>
				<b>Bla bla</b><i> ohhh yeaah</i><u> wuhuuuu</u></p>
				<img src="test.png"/>
		</html>
		</br>
	</body>"

---

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
		
	}

**Output using the code piece above**

    name -> {body
			
			}
	attributes -> { style="color:#fff"}
	inner -> {
			}
	

	name -> {head}
	attributes -> {}
	inner -> {}

	
	name -> {title}
	attributes -> {}
	inner -> {Test Page}

	
	name -> {html
					}
	attributes -> {
			}
	inner -> {
				}
	

	name -> {p}
	attributes -> {}
	inner -> {
					}
	

	name -> {b}
	attributes -> {}
	inner -> {Bla bla}
	

	name -> {i}
	attributes -> {}
	inner -> { ohhh yeaah}
	

	name -> {u}
	attributes -> {}
	inner -> { wuhuuuu}
	

	name -> {img}
	attributes -> { src=test.png}
	inner -> {}
