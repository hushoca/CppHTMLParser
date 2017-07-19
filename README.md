Crappy C++ HTML Parsing Code [WIP]
==================================
C++ HTML parsing code (One day It will grow up to be a library.), currently does not support non ending tags like &lt;img>. Still working on it. Messy code alert!

----------

**Example Input**

    "<body style="color:#fff">
    	<head>
    		<title>Test Page</title>
    	</head>
    	<html>
    		<p>
    			<b>Bla bla</b> <i> ohhh yeaah</i> <u> wuhuuuu</>
    		</p>
    	</html>
    </body>"

**Output**

    --------------------------------
    Name is body
    Attributes are style=color:#fff
    Value is 
    	/head
    	/html
    
    Children count 2
    --------------------------------
    Name is head
    Attributes are 
    Value is 
    		/title
    	
    Children count 1
    --------------------------------
    Name is title
    Attributes are 
    Value is Test Page
    Children count 0
    --------------------------------
    Name is html
    Attributes are 
    Value is 
    		/p
    	
    Children count 1
    --------------------------------
    Name is p
    Attributes are 
    Value is 
    			/b/i/
    		
    Children count 3
    --------------------------------
    Name is b
    Attributes are 
    Value is Blabla
    Children count 0
    --------------------------------
    Name is i
    Attributes are 
    Value is ohhhyeaah
    Children count 0
    --------------------------------
    Name is u
    Attributes are 
    Value is wuhuuuu
    Children count 0
