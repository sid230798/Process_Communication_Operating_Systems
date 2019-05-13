/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 18/11/18
Purpose :-

	1. Stores the type of message required
*/


/*--------------------------------------------------------------------*/

struct Message{

	/*Request variable for waiting and relasing wait in client and server

		- Value 1 means client is ready
		- Value 2 means HTTP GET request is being done

	*/
	int request;

	/*

		-This Stores Currency input by client whose INR value has to be found.
		- Assuming value <4
	*/
	char str[5];

	/*Stores the fetched value by Http get if wrong input output 0*/
	float parsedValue;

};

/*-------------------------------------------------------------------------*/
