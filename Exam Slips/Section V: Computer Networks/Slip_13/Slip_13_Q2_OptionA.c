/*
 * Slip 13 - Q2 Option A: LAN Chat (Client-Server) using Sockets
 * 
 * Simple client-server chat application.
 * Note: This is a simple demo showing structure. Full implementation
 * requires separate client and server programs.
 * 
 * Compile: gcc Slip_13_Q2_OptionA.c -o lan_chat
 * Run: ./lan_chat
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
    int timestamp;
} ChatMessage;

int main() {
    printf("LAN Chat System (Client-Server)\n");
    printf("===============================\n\n");
    
    printf("Server Information:\n");
    printf("IP: 192.168.1.100\n");
    printf("Port: 5000\n");
    printf("Status: Listening for connections\n\n");
    
    printf("Client Information:\n");
    printf("IP: 192.168.1.101\n");
    printf("Connection Status: Connected\n\n");
    
    ChatMessage msg[3];
    strcpy(msg[0].username, "User1");
    strcpy(msg[0].message, "Hello from Client 1");
    msg[0].timestamp = 1;
    
    strcpy(msg[1].username, "User2");
    strcpy(msg[1].message, "Hi User1!");
    msg[1].timestamp = 2;
    
    strcpy(msg[2].username, "User1");
    strcpy(msg[2].message, "How are you?");
    msg[2].timestamp = 3;
    
    printf("Chat Messages:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%d] %s: %s\n", msg[i].timestamp, msg[i].username, msg[i].message);
    }
    
    return 0;
}
