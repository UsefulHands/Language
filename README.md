Another personal project that I challenged myself for creating a simple language using C language.
I also want to create my own garbage collector we will see that in the future.
Without using any of the LLM's, copy paste, auto compilation tools.
Like sweet old days :D

First day: I wrote a simple lexer. I will add more and more keywords in the close future.
Second day: I added punctuation marks, more keywords, operators, and solve the confict between operator(+, -) with the number (+, -). For example x -+5 is still valid.

Now I have a basic lexer that validates and differantiate tokens types.
Example output of my lexer:
Tokens goes like:
[TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> =] [TOKEN_NUMBER -> -5]
[TOKEN_PUNCTUATION -> {] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> =] [TOKEN_NUMBER -> 5] [TOKEN_PUNCTUATION -> }]
[TOKEN_IDENTIFIER -> y] [TOKEN_OPERATOR -> =] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> +] [TOKEN_NUMBER -> 3]
[TOKEN_KEYWORD -> while] [TOKEN_IDENTIFIER -> x] [TOKEN_OPERATOR -> !=] [TOKEN_NUMBER -> 0]

Third day: I added subtype format for tokens so it will be easy to get the value of the token in the future.
Fourth day: I added a Makefile. fileReader, charBuffer, and tests.

Now I have a fileReader that puts the file into my charBuffer.
Example output of my reader:
Buffer goes like: 
[ [i] [f] [ ] [x] [ ] [=] [ ] [5] [ ] [+] [ ] [-] [5] [\n] 
[w] [h] [i] [l] [e] [ ] [f] [o] [r] [ ] [*] [ ] [/] [\0] ]

For the next process, I am planning to create an intermediate level inbetween fileReader and lexer; so I can use fileReader for other purposes too.