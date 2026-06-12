Another personal project that I challenged myself for creating a simple language using C language.
I also want to create my own garbage collector we will see that in the future.
Without using any of the LLM's, copy paste, auto compilation tools.
Like sweet old days :D

*First day: I wrote a simple lexer. I will add more and more keywords in the close future.
*Second day: I added punctuation marks, more keywords, operators, and solve the confict between operator(+, -) with the number (+, -). For example x -+5 is still valid.

Now I have a basic lexer that validates and differantiate tokens types.
Example output of my lexer:

Tokens goes like:
[TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> =] [TOKEN_NUMBER -> -5]
[TOKEN_PUNCTUATION -> {] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> =] [TOKEN_NUMBER -> 5] [TOKEN_PUNCTUATION -> }]
[TOKEN_IDENTIFIER -> y] [TOKEN_OPERATOR -> =] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> +] [TOKEN_NUMBER -> 3]
[TOKEN_KEYWORD -> while] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> !=] [TOKEN_NUMBER -> 0]

*Third day: I added subtype format for tokens so it will be easy to get the value of the token in the future.
*Fourth day: I added a Makefile. fileReader, charBuffer, and tests.

Now I have a fileReader that puts the file into my charBuffer.
Example output of my reader:

Buffer goes like: 
[ [i] [f] [ ] [x] [ ] [=] [ ] [5] [ ] [+] [ ] [-] [5] [\n] 
[w] [h] [i] [l] [e] [ ] [f] [o] [r] [ ] [*] [ ] [/] [\0] ]

*Fifth day: I rename the fileReaders with the sourceBuffers because fileReader could mean some bigger context. I constructed the bridge inbetween lexer and sourceBuffer.
So SourceBuffer provides reading for txt file and lexer handles it. I also added more keywords and got rid of some keywords like "for".
I want to keep it simple "while" works for now. Found a little bug causes tokenization problem such as "method\n" instead of "method" etc.

Current progress so far:
TOKEN_KEYWORD if
TOKEN_IDENTIFIER x
TOKEN_OPERATOR =
TOKEN_NUMBER 5
TOKEN_OPERATOR +
TOKEN_NUMBER -5
TOKEN_KEYWORD while
TOKEN_IDENTIFIER for
TOKEN_OPERATOR *
TOKEN_OPERATOR /

*Sixth day: I created blueprint of my grammar. Added some unforgotten token types. Created Parser, implemented one of the deepest methods of the grammar for test. I think, next couple of commits will be only grammar functions.

*Seventh day: I added some rules to parser such as retreat, advance, restore etc. And I implemented half of the grammar implementations. I will implement the rest most probably the next commit.

*Day 8: I completed implementing the grammar. I fixed a problem that caused tokens to not end with EOF. I tested the parser results after a lengthy implementation process. Now I have a parser works that works perfectly.
Results are like this:

CharBuffer:

number a = 5;
bool c5 = false;
string s = "hello";
number x = 1 + 2 * 3;
number y = (4 + 5) / 3;
bool b = true or false;
bool b2 = true and false;
bool b3 = not true;
a = 10;
a = b = 5;
number r = a == b;
number r2 = a != b;
number r3 = a > b;
number r4 = a < b;
number r5 = a >= b;
number r6 = a <= b;
while (a > 0) { number x = 1; }
if (a == true) { a = 5; }
return 5;
break;
{ number x = 1; number y = 2; }
method foo(a, b) { return a; }

Success: 1

*Commit 9: I added the identifier chain logic and number keyword logic such as 3, 3.5 is considered as "number" rather than "int", "double". 
Added some of the missing grammar rules, lexer is now handling "dot" better.
Now my parser can handle syntax like:

number deepExpr = (x + y) * (z - 1.0) / (x + 1.0);
obj.result = add(obj.a, obj.b) + obj.c.value;
number e3 = obj.a.b.c.d;
obj.x = obj.y + obj.z;
obj.a.b = obj.c.d * 2.0;
method complex(a, b) {
    number i = 0;
    while (i < 10) {
        if (i == a) {
            return i;
        }
        i = i + 1;
    }
    return b;
}

I think the system is good to go for the semantic analysis.

*Commit 10: I created the logic of the semantic analysis. I decided to move forward with the double checking method parser -> semantic analysis -> ....
I made the blueprint of the semantic analyze files. I will add the functions in the next couple of commits.

*Commit 11: I figured out that I made a mistake with the file naming so I did a quick rename operation. I solved another problem that prevents me from creating "number obj.abc = 5;" because identifier chain was not added to the declaration.
I also implemented some of the semantic analyzer functions. I will implement more in the future commits.

*Commit 12: I finished creating and testing all the semantic part. I added some more grammar lures and fixed some. I wanted to create the grammar as flexible as I can. 
current output of the semantics:

Semantic Analyzer success: 1
Name: x, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: y, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: obj.b, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: obj.c.value, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: obj.result, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: a, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: oneParam, SymbolType: SYMBOL_METHOD, TypeSpec: TYPE_NUMBER
Name: b, SymbolType: SYMBOL_VARIABLE, TypeSpec: TYPE_NUMBER
Name: add, SymbolType: SYMBOL_METHOD, TypeSpec: TYPE_NUMBER
Name: obj.foo, SymbolType: SYMBOL_METHOD, TypeSpec: TYPE_NUMBER
Name: obj.a.b.bar, SymbolType: SYMBOL_METHOD, TypeSpec: TYPE_NUMBER