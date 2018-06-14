# BF-Interpreter
## The BF Language
The BF language was created in 1993 by Urban Müller and only has eight valid operators and no keywords.This language is generally considered an esoteric programming language due to the difficulty in making effective programs. Even with that in mind, the language is turing complete and that therefore means that any computing task can be theoretically completed in this language given appropriate resources. 

The file extensions for soruce files are: .b and .bf
However, this interperter will attempt to parse any file its pointed to, regardless of file extension.

### Syntax for the language
White space is ignored, and non-valid characters are ignored by the interpreter.
Comments are made by any non-reserved character

|Operator | MEANING |
| :------------: | ------------ |
|>| Increment pointer|
|<| Decrement pointer|
|+| Increment value at pointer|
|-| Decrement value at pointer|
|.| Output byte at pointer to STDOUT as ASCII|
|,| Recieve one byte of input from STDIN and store at pointer|
|\[|Begin a loop if value at pointer is non-zero|
|]| Jump to assoicated\[ if value at pointer i non-zero|


## This Interpreter
###General Information
The current build of this interperter takes in a bf language file as a commandline argument, and does a two pass interpretation of it. Where pass I discards all non-valid operators, and assocaites the square brackets to each other. Pass II then executes the program in run time. 


### Techinical Information
This interpreter uses signed char's for the data type of each cell. This means the size of the cell is equal to one byte on the host machine, which in the vast majority of cases will be 8 bits. Therefore the valid values a cell can hold is \[-128, 127] and these values can be wrapped around through overflows without any runtime error. 

### Features of this Interpreter
The program's memory can expand indefinitely* in both directions from the "zero" cell. Which removes about the only common runtime error this language will encounter. 

* indefinitely in this context means the only limiation will be down on the physical machine that is running the interpreter. There is no software limitation on the size of program memory. 

## Author
[Joseph Allen](https://github.com/jallenNJ) 
