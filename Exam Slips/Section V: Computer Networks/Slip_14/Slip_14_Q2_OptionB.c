/*
 * ============================================================================
 * Slip 14 - Q2 Option B: LAN Chat Application (Client-Server) Using Sockets
 * ============================================================================
 * 
 * This program implements a LAN chat system with:
 * - Multi-client server using select() for concurrent connections
 * - Broadcast messaging to all connected clients
 * - Private messaging between clients
 * - Username-based identification
 * - Real-time message delivery
 *
 * Compile Server: gcc -o chat_server Slip_14_Q2_OptionB.c -DSERVER
 * Compile Client: gcc -o chat_client Slip_14_Q2_OptionB.c -DCLIENT
 *
 * Run Server: ./chat_server 8888
 * Run Client: ./chat_client 127.0.0.1 8888
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define USERNAME_SIZE 32

/* ============================================================================
 * Common Structures and Functions
 * ============================================================================ */

/* Message types */
#define MSG_NORMAL    0
#define MSG_JOIN      1
#define MSG_LEAVE     2
#define MSG_PRIVATE   3
#define MSG_LIST      4
#define MSG_SYSTEM    5

/* Chat message structure */
typedef struct {
    int type;
    char sender[USERNAME_SIZE];
    char recipient[USERNAME_SIZE];  /* For private messages */
    char content[BUFFER_SIZE];
    time_t timestamp;
} ChatMessage;

/* Get current time string */
void get_time_string(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", tm_info);
}

/* Display banner */
void print_banner() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║            LAN CHAT APPLICATION - Socket Programming           ║\n");
    printf("║            Slip 14 - Computer Networks                         ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
}

#ifdef SERVER

/* ============================================================================
 * SERVER IMPLEMENTATION
 * ============================================================================ */

/* Client information structure */
typedef struct {
    int socket;
    char username[USERNAME_SIZE];
    struct sockaddr_in address;
    int is_active;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
int server_socket;
int client_count = 0;

/* Signal handler for graceful shutdown */
void handle_signal(int sig) {
    printf("\n[SERVER] Shutting down...\n");
    
    /* Notify all clients */
    ChatMessage msg;
    msg.type = MSG_SYSTEM;
    strcpy(msg.sender, "SERVER");
    strcpy(msg.content, "Server is shutting down. Goodbye!");
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_active) {
            send(clients[i].socket, &msg, sizeof(msg), 0);
            close(clients[i].socket);
        }
    }
    
    close(server_socket);
    exit(0);
}

/* Find client by username */
int find_client_by_username(const char *username) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_active && 
            strcmp(clients[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

/* Broadcast message to all clients */
void broadcast_message(ChatMessage *msg, int exclude_socket) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_active && clients[i].socket != exclude_socket) {
            if (send(clients[i].socket, msg, sizeof(ChatMessage), 0) < 0) {
                perror("[SERVER] Send failed");
            }
        }
    }
}

/* Send client list to requesting client */
void send_client_list(int client_socket) {
    ChatMessage msg;
    msg.type = MSG_LIST;
    strcpy(msg.sender, "SERVER");
    
    char list[BUFFER_SIZE] = "Online users: ";
    int first = 1;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_active) {
            if (!first) strcat(list, ", ");
            strcat(list, clients[i].username);
            first = 0;
        }
    }
    
    strcpy(msg.content, list);
    send(client_socket, &msg, sizeof(msg), 0);
}

/* Handle client disconnection */
void handle_disconnect(int client_index) {
    char time_str[16];
    get_time_string(time_str, sizeof(time_str));
    
    printf("[%s] Client '%s' disconnected\n", 
           time_str, clients[client_index].username);
    
    /* Notify other clients */
    ChatMessage msg;
    msg.type = MSG_LEAVE;
    strcpy(msg.sender, clients[client_index].username);
    sprintf(msg.content, "%s has left the chat", clients[client_index].username);
    broadcast_message(&msg, clients[client_index].socket);
    
    close(clients[client_index].socket);
    clients[client_index].is_active = 0;
    client_count--;
}

/* Process client message */
void process_message(int client_index, ChatMessage *msg) {
    char time_str[16];
    get_time_string(time_str, sizeof(time_str));
    
    switch (msg->type) {
        case MSG_NORMAL:
            /* Broadcast to all */
            printf("[%s] [%s]: %s\n", time_str, msg->sender, msg->content);
            broadcast_message(msg, clients[client_index].socket);
            break;
            
        case MSG_PRIVATE: {
            /* Send to specific user */
            int target = find_client_by_username(msg->recipient);
            if (target != -1) {
                send(clients[target].socket, msg, sizeof(ChatMessage), 0);
                printf("[%s] [PRIVATE] %s -> %s: %s\n", 
                       time_str, msg->sender, msg->recipient, msg->content);
            } else {
                ChatMessage reply;
                reply.type = MSG_SYSTEM;
                strcpy(reply.sender, "SERVER");
                sprintf(reply.content, "User '%s' not found", msg->recipient);
                send(clients[client_index].socket, &reply, sizeof(reply), 0);
            }
            break;
        }
            
        case MSG_LIST:
            send_client_list(clients[client_index].socket);
            break;
            
        default:
            break;
    }
}

/* Main server function */
int main(int argc, char *argv[]) {
    int port;
    struct sockaddr_in server_addr, client_addr;
    fd_set read_fds, master_fds;
    int max_fd;
    
    print_banner();
    printf("║                      SERVER MODE                               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        printf("Example: %s 8888\n", argv[0]);
        exit(1);
    }
    
    port = atoi(argv[1]);
    
    /* Setup signal handler */
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    
    /* Initialize clients array */
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].is_active = 0;
    }
    
    /* Create socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("[SERVER] Socket creation failed");
        exit(1);
    }
    
    /* Set socket options */
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    /* Configure server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    /* Bind socket */
    if (bind(server_socket, (struct sockaddr *)&server_addr, 
             sizeof(server_addr)) < 0) {
        perror("[SERVER] Bind failed");
        exit(1);
    }
    
    /* Listen for connections */
    if (listen(server_socket, 5) < 0) {
        perror("[SERVER] Listen failed");
        exit(1);
    }
    
    printf("[SERVER] Chat server started on port %d\n", port);
    printf("[SERVER] Waiting for connections...\n");
    printf("[SERVER] Press Ctrl+C to shutdown\n\n");
    
    /* Initialize file descriptor sets */
    FD_ZERO(&master_fds);
    FD_SET(server_socket, &master_fds);
    max_fd = server_socket;
    
    /* Main server loop */
    while (1) {
        read_fds = master_fds;
        
        /* Wait for activity */
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            if (errno == EINTR) continue;
            perror("[SERVER] Select error");
            break;
        }
        
        /* Check for new connection */
        if (FD_ISSET(server_socket, &read_fds)) {
            socklen_t addr_len = sizeof(client_addr);
            int new_socket = accept(server_socket, 
                                   (struct sockaddr *)&client_addr, 
                                   &addr_len);
            
            if (new_socket < 0) {
                perror("[SERVER] Accept failed");
                continue;
            }
            
            /* Check if server is full */
            if (client_count >= MAX_CLIENTS) {
                ChatMessage msg;
                msg.type = MSG_SYSTEM;
                strcpy(msg.sender, "SERVER");
                strcpy(msg.content, "Server is full. Try again later.");
                send(new_socket, &msg, sizeof(msg), 0);
                close(new_socket);
                continue;
            }
            
            /* Receive username */
            ChatMessage join_msg;
            if (recv(new_socket, &join_msg, sizeof(join_msg), 0) <= 0) {
                close(new_socket);
                continue;
            }
            
            /* Check for duplicate username */
            if (find_client_by_username(join_msg.sender) != -1) {
                ChatMessage msg;
                msg.type = MSG_SYSTEM;
                strcpy(msg.sender, "SERVER");
                strcpy(msg.content, "Username already taken. Choose another.");
                send(new_socket, &msg, sizeof(msg), 0);
                close(new_socket);
                continue;
            }
            
            /* Add new client */
            int slot = -1;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (!clients[i].is_active) {
                    slot = i;
                    break;
                }
            }
            
            clients[slot].socket = new_socket;
            clients[slot].address = client_addr;
            strcpy(clients[slot].username, join_msg.sender);
            clients[slot].is_active = 1;
            client_count++;
            
            FD_SET(new_socket, &master_fds);
            if (new_socket > max_fd) max_fd = new_socket;
            
            char time_str[16];
            get_time_string(time_str, sizeof(time_str));
            
            printf("[%s] New client connected: %s (%s:%d)\n",
                   time_str, clients[slot].username,
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
            printf("[SERVER] Total clients: %d\n", client_count);
            
            /* Send welcome message */
            ChatMessage welcome;
            welcome.type = MSG_SYSTEM;
            strcpy(welcome.sender, "SERVER");
            sprintf(welcome.content, "Welcome to the chat, %s! Type /help for commands.",
                    clients[slot].username);
            send(new_socket, &welcome, sizeof(welcome), 0);
            
            /* Broadcast join notification */
            ChatMessage notify;
            notify.type = MSG_JOIN;
            strcpy(notify.sender, clients[slot].username);
            sprintf(notify.content, "%s has joined the chat", clients[slot].username);
            broadcast_message(&notify, new_socket);
        }
        
        /* Check client sockets for data */
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!clients[i].is_active) continue;
            
            if (FD_ISSET(clients[i].socket, &read_fds)) {
                ChatMessage msg;
                int bytes = recv(clients[i].socket, &msg, sizeof(msg), 0);
                
                if (bytes <= 0) {
                    /* Client disconnected */
                    FD_CLR(clients[i].socket, &master_fds);
                    handle_disconnect(i);
                } else {
                    process_message(i, &msg);
                }
            }
        }
    }
    
    close(server_socket);
    return 0;
}

#endif /* SERVER */

#ifdef CLIENT

/* ============================================================================
 * CLIENT IMPLEMENTATION
 * ============================================================================ */

int client_socket;
char username[USERNAME_SIZE];
volatile int running = 1;

/* Signal handler */
void handle_signal(int sig) {
    running = 0;
    printf("\n[CLIENT] Disconnecting...\n");
    close(client_socket);
    exit(0);
}

/* Display help */
void show_help() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    AVAILABLE COMMANDS                          ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  /help          - Show this help message                       ║\n");
    printf("║  /list          - Show online users                            ║\n");
    printf("║  /msg <user> <text> - Send private message                     ║\n");
    printf("║  /quit          - Exit the chat                                ║\n");
    printf("║  <text>         - Send message to all                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
}

/* Process received message */
void display_message(ChatMessage *msg) {
    char time_str[16];
    get_time_string(time_str, sizeof(time_str));
    
    switch (msg->type) {
        case MSG_NORMAL:
            printf("\r[%s] [%s]: %s\n", time_str, msg->sender, msg->content);
            break;
            
        case MSG_JOIN:
            printf("\r[%s] >>> %s\n", time_str, msg->content);
            break;
            
        case MSG_LEAVE:
            printf("\r[%s] <<< %s\n", time_str, msg->content);
            break;
            
        case MSG_PRIVATE:
            printf("\r[%s] [PRIVATE from %s]: %s\n", 
                   time_str, msg->sender, msg->content);
            break;
            
        case MSG_LIST:
        case MSG_SYSTEM:
            printf("\r[%s] [SERVER]: %s\n", time_str, msg->content);
            break;
    }
    
    printf("[%s]: ", username);
    fflush(stdout);
}

/* Parse and send user input */
void process_input(char *input) {
    ChatMessage msg;
    msg.timestamp = time(NULL);
    strcpy(msg.sender, username);
    
    /* Remove newline */
    input[strcspn(input, "\n")] = 0;
    
    if (strlen(input) == 0) return;
    
    /* Check for commands */
    if (input[0] == '/') {
        if (strcmp(input, "/help") == 0) {
            show_help();
            return;
        }
        else if (strcmp(input, "/list") == 0) {
            msg.type = MSG_LIST;
            send(client_socket, &msg, sizeof(msg), 0);
            return;
        }
        else if (strcmp(input, "/quit") == 0) {
            running = 0;
            return;
        }
        else if (strncmp(input, "/msg ", 5) == 0) {
            /* Private message: /msg username message */
            char *rest = input + 5;
            char *space = strchr(rest, ' ');
            
            if (space == NULL) {
                printf("[ERROR] Usage: /msg <username> <message>\n");
                return;
            }
            
            *space = '\0';
            msg.type = MSG_PRIVATE;
            strncpy(msg.recipient, rest, USERNAME_SIZE - 1);
            strncpy(msg.content, space + 1, BUFFER_SIZE - 1);
            
            printf("[%s] [PRIVATE to %s]: %s\n", username, msg.recipient, msg.content);
            send(client_socket, &msg, sizeof(msg), 0);
            return;
        }
        else {
            printf("[ERROR] Unknown command. Type /help for available commands.\n");
            return;
        }
    }
    
    /* Normal message */
    msg.type = MSG_NORMAL;
    strncpy(msg.content, input, BUFFER_SIZE - 1);
    send(client_socket, &msg, sizeof(msg), 0);
}

/* Main client function */
int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    fd_set read_fds;
    char input[BUFFER_SIZE];
    
    print_banner();
    printf("║                      CLIENT MODE                               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        printf("Example: %s 192.168.1.100 8888\n", argv[0]);
        exit(1);
    }
    
    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    
    /* Setup signal handler */
    signal(SIGINT, handle_signal);
    
    /* Get username */
    printf("Enter your username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;
    
    if (strlen(username) == 0) {
        printf("[ERROR] Username cannot be empty\n");
        exit(1);
    }
    
    /* Create socket */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("[CLIENT] Socket creation failed");
        exit(1);
    }
    
    /* Configure server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        printf("[ERROR] Invalid server address\n");
        exit(1);
    }
    
    /* Connect to server */
    printf("[CLIENT] Connecting to %s:%d...\n", server_ip, port);
    
    if (connect(client_socket, (struct sockaddr *)&server_addr, 
                sizeof(server_addr)) < 0) {
        perror("[CLIENT] Connection failed");
        exit(1);
    }
    
    printf("[CLIENT] Connected to server!\n");
    
    /* Send join message with username */
    ChatMessage join_msg;
    join_msg.type = MSG_JOIN;
    strcpy(join_msg.sender, username);
    send(client_socket, &join_msg, sizeof(join_msg), 0);
    
    show_help();
    printf("[%s]: ", username);
    fflush(stdout);
    
    /* Main client loop */
    while (running) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(client_socket, &read_fds);
        
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        
        int activity = select(client_socket + 1, &read_fds, NULL, NULL, &tv);
        
        if (activity < 0) {
            if (errno == EINTR) continue;
            perror("[CLIENT] Select error");
            break;
        }
        
        /* Check for server message */
        if (FD_ISSET(client_socket, &read_fds)) {
            ChatMessage msg;
            int bytes = recv(client_socket, &msg, sizeof(msg), 0);
            
            if (bytes <= 0) {
                printf("\n[CLIENT] Server disconnected\n");
                break;
            }
            
            display_message(&msg);
        }
        
        /* Check for user input */
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
                process_input(input);
                if (running) {
                    printf("[%s]: ", username);
                    fflush(stdout);
                }
            }
        }
    }
    
    printf("[CLIENT] Goodbye!\n");
    close(client_socket);
    return 0;
}

#endif /* CLIENT */

/* Compile combined version if neither SERVER nor CLIENT defined */
#if !defined(SERVER) && !defined(CLIENT)

int main(int argc, char *argv[]) {
    print_banner();
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    COMPILATION INSTRUCTIONS                    ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║  This program needs to be compiled twice - once for the        ║\n");
    printf("║  server and once for the client.                               ║\n");
    printf("║                                                                ║\n");
    printf("║  Compile Server:                                               ║\n");
    printf("║    gcc -o chat_server Slip_14_Q2_OptionB.c -DSERVER            ║\n");
    printf("║                                                                ║\n");
    printf("║  Compile Client:                                               ║\n");
    printf("║    gcc -o chat_client Slip_14_Q2_OptionB.c -DCLIENT            ║\n");
    printf("║                                                                ║\n");
    printf("║  Run Server (first):                                           ║\n");
    printf("║    ./chat_server 8888                                          ║\n");
    printf("║                                                                ║\n");
    printf("║  Run Client (on same or different machine):                    ║\n");
    printf("║    ./chat_client <server_ip> 8888                              ║\n");
    printf("║    ./chat_client 127.0.0.1 8888    (same machine)              ║\n");
    printf("║    ./chat_client 192.168.1.100 8888  (LAN)                     ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                     FEATURES                                   ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  • Multi-client support (up to 10 clients)                     ║\n");
    printf("║  • Broadcast messaging to all connected users                  ║\n");
    printf("║  • Private messaging between users                             ║\n");
    printf("║  • User join/leave notifications                               ║\n");
    printf("║  • Online user list                                            ║\n");
    printf("║  • Timestamped messages                                        ║\n");
    printf("║  • Graceful disconnect handling                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                     ARCHITECTURE                               ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║    ┌─────────┐                          ┌─────────┐            ║\n");
    printf("║    │ Client1 │───┐                  ┌───│ Client3 │            ║\n");
    printf("║    └─────────┘   │                  │   └─────────┘            ║\n");
    printf("║                  │   ┌──────────┐   │                          ║\n");
    printf("║    ┌─────────┐   ├───│          │───┤   ┌─────────┐            ║\n");
    printf("║    │ Client2 │───┼───│  SERVER  │───┼───│ Client4 │            ║\n");
    printf("║    └─────────┘   │   │ Port:8888│   │   └─────────┘            ║\n");
    printf("║                  │   └──────────┘   │                          ║\n");
    printf("║    ┌─────────┐   │                  │   ┌─────────┐            ║\n");
    printf("║    │ Client5 │───┘                  └───│ Client6 │            ║\n");
    printf("║    └─────────┘                          └─────────┘            ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}

#endif

/* ============================================================================
 * Sample Output:
 * ============================================================================
 *
 * SERVER OUTPUT:
 * --------------
 * ╔════════════════════════════════════════════════════════════════╗
 * ║            LAN CHAT APPLICATION - Socket Programming           ║
 * ║            Slip 14 - Computer Networks                         ║
 * ╚════════════════════════════════════════════════════════════════╝
 * ║                      SERVER MODE                               ║
 * ╚════════════════════════════════════════════════════════════════╝
 *
 * [SERVER] Chat server started on port 8888
 * [SERVER] Waiting for connections...
 * [SERVER] Press Ctrl+C to shutdown
 *
 * [10:30:15] New client connected: Alice (192.168.1.10:54321)
 * [SERVER] Total clients: 1
 * [10:30:25] New client connected: Bob (192.168.1.11:54322)
 * [SERVER] Total clients: 2
 * [10:30:35] [Alice]: Hello everyone!
 * [10:30:40] [Bob]: Hi Alice!
 * [10:30:50] [PRIVATE] Alice -> Bob: Meet me at the cafe?
 * [10:31:00] Client 'Alice' disconnected
 *
 * CLIENT OUTPUT (Alice):
 * ----------------------
 * ╔════════════════════════════════════════════════════════════════╗
 * ║            LAN CHAT APPLICATION - Socket Programming           ║
 * ╚════════════════════════════════════════════════════════════════╝
 * ║                      CLIENT MODE                               ║
 * ╚════════════════════════════════════════════════════════════════╝
 *
 * Enter your username: Alice
 * [CLIENT] Connecting to 192.168.1.100:8888...
 * [CLIENT] Connected to server!
 *
 * ╔════════════════════════════════════════════════════════════════╗
 * ║                    AVAILABLE COMMANDS                          ║
 * ╠════════════════════════════════════════════════════════════════╣
 * ║  /help          - Show this help message                       ║
 * ║  /list          - Show online users                            ║
 * ║  /msg <user> <text> - Send private message                     ║
 * ║  /quit          - Exit the chat                                ║
 * ╚════════════════════════════════════════════════════════════════╝
 *
 * [10:30:15] [SERVER]: Welcome to the chat, Alice! Type /help for commands.
 * [Alice]: Hello everyone!
 * [10:30:25] >>> Bob has joined the chat
 * [10:30:40] [Bob]: Hi Alice!
 * [Alice]: /msg Bob Meet me at the cafe?
 * [Alice]: /quit
 * [CLIENT] Goodbye!
 *
 * ============================================================================ */
