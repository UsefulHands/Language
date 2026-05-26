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
I want to keep it simple "while" works for now.

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