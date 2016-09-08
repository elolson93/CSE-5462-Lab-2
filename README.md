#CSE 5462 Lab 2: TCP socket file transfer application

Authors: James Baker, Eric Olson

##TABLE OF CONTENTS

1. About

2. Installation

3. Usage

4. Help

-----------------------------------------------------------------------------

##1. ABOUT

This application will send a file using TCP sockets from a client called ftpc
to a server called ftps. 

-----------------------------------------------------------------------------

##2. INSTALLATION

Ensure that 'ftpc.c', 'ftps.c', and 'Makefile' are located in your desired 
installation directory. 

Navigate to this directory in your terminal. 

Type 'make' to compile the application. There will now be an executable
client (ftpc) and executable server (ftps) in the installation directory. 

-----------------------------------------------------------------------------

##3. USAGE

Make note of the location of the file you wish to transfer. In the terminal,
navigate to the location of that the program was installed above. 


First the server must be started. You can do so with the command below.

~$ ./ftps <local-port>

Here, <local-port> is the designated port you choose for the file transfer.


Next, the client must be started on the machine you wish to send the file
from. You can do so with the following command.

~$ ./ftpc <remote-IP> <remote-port> <local-file-to-transfer>

Here, <remote-IP> is the IP address of the machine running the server,
<remote-port> should be the same port designated to the server above, and
<local-file-to-transfer> is the name (and path if applicable) of the local 
file on the client machine you wish to send to the server.

Upon execution of the client, a TCP socket connection is made, the local file
is read in and then sent over the connection to the server. The server reads
in the file and saves it in a sub-directory called 'recvd'. This 
sub-directory will be located in the same location as this application was
installed. If the directory does not exist, it will be created by the
application.

Both the client and server programs will close once the file transfer has
completed.

-----------------------------------------------------------------------------

##4. HELP

Below are common errors encountered in the server program.

"There are not enough arguments. Please be sure to include the local port 
number."
 - Please ensure the server execution command includes the correct argument
   as listed above in the Usage section.

"Error opening socket"
 - Ensure that the port arguemnt is correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.


"Error binding stream socket"
 - Ensure that the port arguemnt is correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.

"Error connecting stream socket"
 - Ensure that the port arguemnt is correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.

"Error: The size read returned less than 4"
 - The file size was sent incorrectly or data was lost in transmission. 
   Please ensure file is valid and try again.

"Error: The name read returned less than 20"
 - The file name was sent incorrectly or data was lost in transmission. 
   Please ensure file is valid and try again.

"Error opening the output file"
 - Please ensure that the file sent is valid.
 - Ensure directory application is running from is accessible.

"Error reading from the connection stream. Server terminating"
 - There was an error within the connection stream and data was lost.
   Please try again.

Below are common errors encountered in the client program. Ensure that
the server was executed first or else unexpected behavior may occur.

"Error: Include host in arguments, port, and local file to transfer in 
arguments"
 - Please ensure the client execution command includes the correct arguments
   as listed above in the Usage section.

"Error opening socket"
 - Ensure that the host and port arguemnts are correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.

"<Host>: unknown host"
 - Ensure that the host and port arguemnts are correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.

"Error connecting stream socket."
 - Ensure that the host and port arguemnts are correct. Avoid the use of 
   "Well-known TCP Ports"
 - Ensure host is online and accessible.

"Error opening file"
 - Please ensure the file exists, the name was entered correctly, and if 
   applicable that the path was entered correctly.

"Error reading file"
 - Please ensure the file exists, the name was entered correctly, and if 
   applicable that the path was entered correctly.

-----------------------------------------------------------------------------

This README was written on Thur Sep 8 9:45 2016.

-----------------------------------------------------------------------------

