Overview
This project shows a client and server work together

The client sends a file name to the server, and the server checks if the file exists. If it does, the server sends back the file content. If the file does not exist, the server says the file does not exist.

---

Files in this project

server.c
This file runs the server. It waits for a client to connect, receives a file name, and sends back the file content if the file exists. If the file is not found, it sends an error message.

client.c
This file runs the client. It connects to the server, asks for a file name, sends it to the server, and prints the response it receives.

---

How to compile

Open a terminal in the project folder and run:

gcc server.c -o server -lws2_32
gcc client.c -o client -lws2_32

---

How to run

Step 1: Start the server first

./server

Step 2: Open another terminal and run the client

./client

Then type a file name like:

test.txt

---

What the program does

- This Client sends a file name to the server
- This Server checks if the file exists
- If the file exists, the server sends the file content
- If the file doesn't exist, the server sends "File not found"

---

Notes

- The server must be running before the client
- The file must be in the same folder as the program
- File content should be small (under 255 characters)
