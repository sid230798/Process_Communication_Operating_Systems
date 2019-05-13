------------------------------------------------------------

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 26/11/18

------------------------------------------------------------

To compile :-

Usr:DIR~$ javac -cp .:commons-lang3-3.5.jar:commons-text-1.4.jar Client.java
Usr:DIR~$ javac -cp .:commons-lang3-3.5.jar:commons-text-1.4.jar Server.java


-------------------------------------------------------------------------------
To Run :-

/*On one terminal */
Usr:DIR~$  java -cp .:commons-lang3-3.5.jar:commons-text-1.4.jar Server -ip 127.0.0.1 -port 8080

/*On other terminal*/
Usr:DIR~$  java -cp .:commons-lang3-3.5.jar:commons-text-1.4.jar Client -ip 127.0.0.1 -port 8080 -f 10

--------------------------------------------------------------------------------------------------------

*Outputs :-

	1. Outputs The Data send and response recieved on terminal.
	2. Average time for Server to send request


*Average Time found out to be 8ms
*Maximum Load 3.23MB for minimum loss of 0

------------------------------------------------------------------------------------------------------------
