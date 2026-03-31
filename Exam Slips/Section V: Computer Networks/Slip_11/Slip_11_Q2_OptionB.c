/*
 * Slip 11 - Q2 Option B
 * Stop-and-Wait ARQ Protocol Simulation
 * 
 * Concept: Stop-and-Wait ARQ is an error control protocol where:
 * - Sender sends ONE frame and waits for acknowledgment
 * - If ACK received correctly, send next frame
 * - If timeout occurs (ACK lost or frame lost), retransmit
 * - Uses sequence numbers 0 and 1 alternately
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_DATA 100
#define TIMEOUT_DELAY 2
#define LOSS_PROBABILITY 30  // 30% chance of loss for simulation

// Frame structure
typedef struct {
    int seq_num;        // Sequence number (0 or 1)
    char data;          // Data character
    int is_valid;       // Frame validity flag
} Frame;

// ACK structure
typedef struct {
    int ack_num;        // Acknowledgment number
    int is_valid;       // ACK validity flag
} ACK;

// Statistics
typedef struct {
    int frames_sent;
    int frames_resent;
    int acks_received;
    int acks_lost;
    int frames_lost;
} Stats;

// Global statistics
Stats stats = {0, 0, 0, 0, 0};

// Function prototypes
void runSimulation(char *data, int simulateLoss);
int simulateFrameLoss(void);
int simulateACKLoss(void);
Frame createFrame(char data, int seq_num);
ACK createACK(int ack_num);
void sendFrame(Frame *frame, int *channel_has_frame);
int receiveFrame(Frame *frame, int channel_has_frame, int simulateLoss);
void sendACK(ACK *ack, int *channel_has_ack);
int receiveACK(ACK *ack, int channel_has_ack, int simulateLoss);
void printFrame(Frame *frame);
void printACK(ACK *ack);
void printStats(void);
void demonstrateProtocol(void);
void printSenderState(int seq_num, char state[]);
void printReceiverState(int expected_seq, char state[]);

int main() {
    int choice;
    char data[MAX_DATA];
    
    srand(time(NULL));
    
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║        STOP-AND-WAIT ARQ PROTOCOL SIMULATION              ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  • Sender sends ONE frame and waits for ACK               ║\n");
    printf("║  • Sequence numbers: 0 and 1 (alternating)                ║\n");
    printf("║  • Retransmit on timeout or lost ACK                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    
    while (1) {
        printf("\n┌─────────────────────────────────────────┐\n");
        printf("│               MENU                      │\n");
        printf("├─────────────────────────────────────────┤\n");
        printf("│  1. Run Simulation (No Loss)            │\n");
        printf("│  2. Run Simulation (With Random Loss)   │\n");
        printf("│  3. Demonstrate Protocol Concept        │\n");
        printf("│  4. Show Protocol State Diagram         │\n");
        printf("│  5. Exit                                │\n");
        printf("└─────────────────────────────────────────┘\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("\nEnter data to transmit: ");
                fgets(data, MAX_DATA, stdin);
                data[strcspn(data, "\n")] = '\0';
                memset(&stats, 0, sizeof(Stats));
                runSimulation(data, 0);  // No loss
                break;
                
            case 2:
                printf("\nEnter data to transmit: ");
                fgets(data, MAX_DATA, stdin);
                data[strcspn(data, "\n")] = '\0';
                memset(&stats, 0, sizeof(Stats));
                runSimulation(data, 1);  // With random loss
                break;
                
            case 3:
                demonstrateProtocol();
                break;
                
            case 4:
                printf("\n╔════════════════════════════════════════════════════════╗\n");
                printf("║         STOP-AND-WAIT ARQ STATE DIAGRAM                ║\n");
                printf("╚════════════════════════════════════════════════════════╝\n\n");
                
                printf("  SENDER STATE DIAGRAM:\n");
                printf("  ═════════════════════\n\n");
                printf("              ┌───────────────────────────┐\n");
                printf("              │                           │\n");
                printf("              ▼                           │\n");
                printf("        ┌──────────┐    Send Frame   ┌────┴─────┐\n");
                printf("        │   IDLE   │ ──────────────→ │ WAITING  │\n");
                printf("        └──────────┘                 └──────────┘\n");
                printf("              ▲                           │\n");
                printf("              │      ACK Received         │\n");
                printf("              │       (Success)           │\n");
                printf("              └───────────────────────────┘\n");
                printf("                            │\n");
                printf("                    Timeout │\n");
                printf("                   (Retry)  │\n");
                printf("                            ▼\n");
                printf("                      ┌──────────┐\n");
                printf("                      │ RETRANS  │───┐\n");
                printf("                      └──────────┘   │\n");
                printf("                            ▲        │\n");
                printf("                            └────────┘\n\n");
                
                printf("  RECEIVER STATE DIAGRAM:\n");
                printf("  ═══════════════════════\n\n");
                printf("        ┌───────────────────────────────────┐\n");
                printf("        │                                   │\n");
                printf("        ▼                                   │\n");
                printf("  ┌───────────────┐  Frame Received   ┌─────┴─────┐\n");
                printf("  │ WAIT_FOR_0/1  │ ────────────────→ │ SEND_ACK  │\n");
                printf("  └───────────────┘                   └───────────┘\n");
                printf("        ▲                                   │\n");
                printf("        │         Toggle Expected Seq       │\n");
                printf("        └───────────────────────────────────┘\n");
                break;
                
            case 5:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * Function: runSimulation
 * Main simulation of Stop-and-Wait ARQ
 */
void runSimulation(char *data, int simulateLoss) {
    int dataLen = strlen(data);
    int senderSeq = 0;      // Sender's current sequence number
    int receiverExpected = 0; // Receiver's expected sequence number
    int i = 0;              // Current data index
    
    Frame frame;
    ACK ack;
    int channel_has_frame = 0;
    int channel_has_ack = 0;
    char receivedData[MAX_DATA];
    int receivedIdx = 0;
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║           STOP-AND-WAIT ARQ SIMULATION                 ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  Data: \"%s\"                                     \n", data);
    printf("║  Length: %d characters                                 \n", dataLen);
    printf("║  Loss Simulation: %s                                   \n", 
           simulateLoss ? "ENABLED (30%)" : "DISABLED");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("  SENDER                    CHANNEL                RECEIVER\n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    while (i < dataLen) {
        int frameAccepted = 0;
        int retransmitCount = 0;
        
        while (!frameAccepted) {
            // SENDER: Create and send frame
            frame = createFrame(data[i], senderSeq);
            
            if (retransmitCount == 0) {
                printf("  [SEND] Frame[%d,'%c']", frame.seq_num, frame.data);
                stats.frames_sent++;
            } else {
                printf("  [RESEND] Frame[%d,'%c']", frame.seq_num, frame.data);
                stats.frames_resent++;
            }
            
            sendFrame(&frame, &channel_has_frame);
            
            // Simulate frame loss
            if (simulateLoss && simulateFrameLoss()) {
                printf("    ───X───    ");
                printf("            (Frame Lost!)\n");
                stats.frames_lost++;
                printf("  [TIMEOUT] Waiting...\n");
                retransmitCount++;
                continue;
            }
            
            printf("    ─────────→    ");
            
            // RECEIVER: Receive frame
            if (receiveFrame(&frame, channel_has_frame, 0)) {
                printf("[RECV] Frame[%d,'%c']\n", frame.seq_num, frame.data);
                
                // Check sequence number
                if (frame.seq_num == receiverExpected) {
                    // Correct frame - accept and send ACK
                    receivedData[receivedIdx++] = frame.data;
                    printf("                                       [ACCEPT] Data: '%c'\n", frame.data);
                    
                    ack = createACK(frame.seq_num);
                    printf("                     ");
                    
                    // Simulate ACK loss
                    if (simulateLoss && simulateACKLoss()) {
                        printf("   ───X───    ");
                        printf("[SEND] ACK[%d] (ACK Lost!)\n", ack.ack_num);
                        stats.acks_lost++;
                        printf("  [TIMEOUT] Waiting...\n");
                        retransmitCount++;
                        continue;
                    }
                    
                    printf("   ←─────────    ");
                    printf("[SEND] ACK[%d]\n", ack.ack_num);
                    
                    // SENDER: Receive ACK
                    stats.acks_received++;
                    printf("  [RECV] ACK[%d] ✓\n", ack.ack_num);
                    
                    // Toggle sequence numbers
                    senderSeq = 1 - senderSeq;
                    receiverExpected = 1 - receiverExpected;
                    frameAccepted = 1;
                    i++;
                    
                } else {
                    // Duplicate frame - send ACK for previous frame
                    printf("                                       [DUPLICATE] Discarding\n");
                    ack = createACK(1 - receiverExpected);
                    printf("                        ←─────────    ");
                    printf("[SEND] ACK[%d] (Previous)\n", ack.ack_num);
                }
            }
            
            if (!frameAccepted) {
                retransmitCount++;
                if (retransmitCount > 5) {
                    printf("\n  [ERROR] Too many retransmissions! Aborting.\n");
                    return;
                }
            }
        }
        printf("  ───────────────────────────────────────────────────────\n");
    }
    
    receivedData[receivedIdx] = '\0';
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              TRANSMISSION COMPLETE                     ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  Received Data: \"%s\"\n", receivedData);
    printf("║  Match: %s\n", strcmp(data, receivedData) == 0 ? "SUCCESS ✓" : "FAILED ✗");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    printStats();
}

/*
 * Function: demonstrateProtocol
 * Shows the protocol concept with a detailed example
 */
void demonstrateProtocol() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║      STOP-AND-WAIT ARQ - PROTOCOL DEMONSTRATION            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    printf("▶ SCENARIO 1: Normal Operation (No Loss)\n");
    printf("  ════════════════════════════════════════\n\n");
    printf("  SENDER                         RECEIVER\n");
    printf("    │                               │\n");
    printf("    │───── Frame[0,'H'] ──────────→│ Receive 'H'\n");
    printf("    │                               │\n");
    printf("    │←──────── ACK[0] ─────────────│\n");
    printf("    │                               │\n");
    printf("    │───── Frame[1,'I'] ──────────→│ Receive 'I'\n");
    printf("    │                               │\n");
    printf("    │←──────── ACK[1] ─────────────│\n");
    printf("    │                               │\n");
    printf("  Result: \"HI\" transmitted successfully\n\n");
    
    printf("▶ SCENARIO 2: Frame Lost\n");
    printf("  ════════════════════════════════════════\n\n");
    printf("  SENDER                         RECEIVER\n");
    printf("    │                               │\n");
    printf("    │───── Frame[0,'H'] ─────X     │ (Frame lost!)\n");
    printf("    │                               │\n");
    printf("    │     [TIMEOUT]                 │\n");
    printf("    │                               │\n");
    printf("    │───── Frame[0,'H'] ──────────→│ Receive 'H'\n");
    printf("    │                               │\n");
    printf("    │←──────── ACK[0] ─────────────│\n");
    printf("    │                               │\n");
    printf("  Result: Frame retransmitted after timeout\n\n");
    
    printf("▶ SCENARIO 3: ACK Lost\n");
    printf("  ════════════════════════════════════════\n\n");
    printf("  SENDER                         RECEIVER\n");
    printf("    │                               │\n");
    printf("    │───── Frame[0,'H'] ──────────→│ Receive 'H'\n");
    printf("    │                               │\n");
    printf("    │     X───── ACK[0] ───────────│ (ACK lost!)\n");
    printf("    │                               │\n");
    printf("    │     [TIMEOUT]                 │\n");
    printf("    │                               │\n");
    printf("    │───── Frame[0,'H'] ──────────→│ Duplicate!\n");
    printf("    │                               │ (Discard, resend ACK)\n");
    printf("    │←──────── ACK[0] ─────────────│\n");
    printf("    │                               │\n");
    printf("  Result: Duplicate detected and handled\n\n");
    
    printf("▶ KEY CONCEPTS:\n");
    printf("  ════════════════════════════════════════\n");
    printf("  • Sequence numbers alternate: 0 → 1 → 0 → 1 → ...\n");
    printf("  • Only ONE frame in transit at a time\n");
    printf("  • Timeout triggers retransmission\n");
    printf("  • Receiver detects duplicates using sequence numbers\n");
    printf("  • Simple but LOW efficiency on high-latency links\n\n");
    
    printf("▶ EFFICIENCY FORMULA:\n");
    printf("  ════════════════════════════════════════\n");
    printf("  η = 1 / (1 + 2a)\n");
    printf("  where a = Propagation Delay / Transmission Time\n\n");
    printf("  Example: If a = 4 (high latency)\n");
    printf("  η = 1 / (1 + 8) = 1/9 ≈ 11%% efficiency\n");
}

/*
 * Function: simulateFrameLoss
 * Randomly determines if a frame is lost
 */
int simulateFrameLoss() {
    return (rand() % 100) < LOSS_PROBABILITY;
}

/*
 * Function: simulateACKLoss
 * Randomly determines if an ACK is lost
 */
int simulateACKLoss() {
    return (rand() % 100) < LOSS_PROBABILITY;
}

/*
 * Function: createFrame
 * Creates a new frame with given data and sequence number
 */
Frame createFrame(char data, int seq_num) {
    Frame frame;
    frame.seq_num = seq_num;
    frame.data = data;
    frame.is_valid = 1;
    return frame;
}

/*
 * Function: createACK
 * Creates a new ACK with given acknowledgment number
 */
ACK createACK(int ack_num) {
    ACK ack;
    ack.ack_num = ack_num;
    ack.is_valid = 1;
    return ack;
}

/*
 * Function: sendFrame
 * Simulates sending a frame
 */
void sendFrame(Frame *frame, int *channel_has_frame) {
    *channel_has_frame = 1;
}

/*
 * Function: receiveFrame
 * Simulates receiving a frame
 */
int receiveFrame(Frame *frame, int channel_has_frame, int simulateLoss) {
    if (!channel_has_frame) return 0;
    return frame->is_valid;
}

/*
 * Function: sendACK
 * Simulates sending an ACK
 */
void sendACK(ACK *ack, int *channel_has_ack) {
    *channel_has_ack = 1;
}

/*
 * Function: receiveACK
 * Simulates receiving an ACK
 */
int receiveACK(ACK *ack, int channel_has_ack, int simulateLoss) {
    if (!channel_has_ack) return 0;
    return ack->is_valid;
}

/*
 * Function: printFrame
 * Prints frame details
 */
void printFrame(Frame *frame) {
    printf("Frame[seq=%d, data='%c']", frame->seq_num, frame->data);
}

/*
 * Function: printACK
 * Prints ACK details
 */
void printACK(ACK *ack) {
    printf("ACK[ack=%d]", ack->ack_num);
}

/*
 * Function: printStats
 * Prints transmission statistics
 */
void printStats() {
    printf("\n┌────────────────────────────────────────┐\n");
    printf("│         TRANSMISSION STATISTICS        │\n");
    printf("├────────────────────────────────────────┤\n");
    printf("│  Frames Sent:         %3d              │\n", stats.frames_sent);
    printf("│  Frames Retransmitted: %3d             │\n", stats.frames_resent);
    printf("│  Frames Lost:          %3d             │\n", stats.frames_lost);
    printf("│  ACKs Received:       %3d              │\n", stats.acks_received);
    printf("│  ACKs Lost:            %3d             │\n", stats.acks_lost);
    printf("├────────────────────────────────────────┤\n");
    printf("│  Total Transmissions: %3d              │\n", 
           stats.frames_sent + stats.frames_resent);
    
    float efficiency = 0;
    if (stats.frames_sent + stats.frames_resent > 0) {
        efficiency = (float)stats.frames_sent / 
                     (stats.frames_sent + stats.frames_resent) * 100;
    }
    printf("│  Efficiency:         %5.1f%%            │\n", efficiency);
    printf("└────────────────────────────────────────┘\n");
}

/*
 * Function: printSenderState
 * Prints the current state of the sender
 */
void printSenderState(int seq_num, char state[]) {
    printf("  Sender: [State: %s, NextSeq: %d]\n", state, seq_num);
}

/*
 * Function: printReceiverState
 * Prints the current state of the receiver
 */
void printReceiverState(int expected_seq, char state[]) {
    printf("  Receiver: [State: %s, ExpectedSeq: %d]\n", state, expected_seq);
}
