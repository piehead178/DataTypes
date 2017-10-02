# DataTypes Version 1.0.0
A libarry containing two data types. A linked list and a matrix.

The max function is a template of typename t and takes two arguments of type t. It returns the max of the two numbers. It's preprocessed.
The min function is a template of typename t and takes two arguments of type t. It returns the min of the two numbers. It's preprocessed.
The multiply struct has ta template of typename t, and the two numbers of type t. It stores the result of the two numbers multiplied together as a constant.
The add struct has ta template of typename t, and the two numbers of type t. It stores the result of the two numbers added together as a constant.

Linked List is a object that creates a list that has pointers to different objects in the list. It has a template of typename t.
The insert function adds a new element to the list equal to the argument.
The returnData function gets the data from the list in the argument location.
The returnPointer gives us the location of the next element of the list at the argument location.
The changeData changes the data to the argument data at the argument location.
The deleteElementData deletes the object at the argument location.
~ deletes the whole list.

The Matrix is not a movie in this libarary. It is a mathmatical arrary of data.
It is templated with typename t for the type and unsigned int rows and collumms for the size.
Use aggrevated initialization in the class constructor list to initilize the data
The getElementData function takes a unsigned int for the row and one for the collumm. The function returns the data in the location.
The changeElementData function takes a data element for what the data is changed to and data for the row and collumm to specify where the data is changing.
The Matrix suports multiplication, addition and subtraction reading from left to right.
