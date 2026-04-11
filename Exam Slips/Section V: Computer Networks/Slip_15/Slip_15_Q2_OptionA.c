/*
 * Slip 15 - Q2 Option A: Command-Line Phishing Simulation
 *
 * Purpose: Educational demonstration of phishing attack techniques
 * WARNING: For educational purposes ONLY - Do NOT use maliciously!
 *
 * Concepts Demonstrated:
 * - Social engineering techniques
 * - Credential harvesting methods
 * - How phishing attacks work
 *
 * Compile: gcc -o phishing Slip_15_Q2_OptionA.c
 * Run: ./phishing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

#define MAX_INPUT 256
#define LOG_FILE "captured_credentials.log"

/* Structure to store captured credentials */
typedef struct {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char service[50];
    char timestamp[30];
} Credentials;

/* Function to hide password input (Linux) */
#ifndef _WIN32
void get_password(char *password, int max_len) {
    struct termios old_term, new_term;
    int i = 0;
    char ch;

    /* Disable echo */
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    /* Read password character by character */
    while (i < max_len - 1 && (ch = getchar()) != '\n' && ch != EOF) {
        password[i++] = ch;
printf("*");
        printf("*");  /* Show asterisks */
        fflush(stdout);
    }
    password[i] = '\0';

    /* Restore terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    printf("\n");
}
#else
void get_password(char *password, int max_len) {
    int i = 0;
    char ch;

    while (i < max_len - 1 && (ch = _getch()) != '\r') {
        password[i++] = ch;
        printf("*");
    }
    password[i] = '\0';
    printf("\n");
}
#endif

/* Get current timestamp */
void get_timestamp(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void display_bank_banner(void) {
    printf("\n");


    printf("\n");
}

void display_email_banner(void) {
    printf("\n");


    printf("\n");
}

void display_social_banner(void) {
    printf("\n");


    printf("\n");
}

/* Log captured credentials */
void log_credentials(Credentials *creds) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp != NULL) {
        fprintf(fp, "=== CAPTURED CREDENTIALS ===\n");
        fprintf(fp, "Timestamp: %s\n", creds->timestamp);
        fprintf(fp, "Service: %s\n", creds->service);
        fprintf(fp, "Username: %s\n", creds->username);
        fprintf(fp, "Password: %s\n", creds->password);
        fprintf(fp, "============================\n\n");
        fclose(fp);
    }
}

void display_capture_summary(Credentials *creds) {
    printf("\n");


}

/* Run phishing simulation for a service */
void run_phishing_simulation(int service_type) {
    Credentials creds;

    system(CLEAR_SCREEN);

    switch (service_type) {
        case 1:
            display_bank_banner();
            strcpy(creds.service, "Trust Bank Online");
            break;
        case 2:
            display_email_banner();
            strcpy(creds.service, "Secure Mail");
            break;
        case 3:
            display_social_banner();
            strcpy(creds.service, "SocialNet");
            break;
        default:
            display_bank_banner();
            strcpy(creds.service, "Generic Service");
    }

    /* Collect credentials */
    printf("  Username / Email: ");
    fgets(creds.username, MAX_INPUT, stdin);
    creds.username[strcspn(creds.username, "\n")] = '\0';

    printf("  Password: ");
    get_password(creds.password, MAX_INPUT);

    /* Simulate authentication delay */
    printf("\n  Authenticating");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        #ifdef _WIN32
            Sleep(500);
        #else
            usleep(500000);
        #endif
    }

    /* Fake error message (typical phishing behavior) */
    printf("\n\n");


    /* Get timestamp and log */
    get_timestamp(creds.timestamp, sizeof(creds.timestamp));
    log_credentials(&creds);

    printf("\n\nPress Enter to see what was captured...");
    getchar();

    system(CLEAR_SCREEN);
    display_capture_summary(&creds);
}

void display_educational_warning(void) {
    printf("\n");


    printf("\n");
}

void analyze_phishing_indicators(void) {
    system(CLEAR_SCREEN);
    printf("\n");


    printf("\n");
    printf("  In this simulation, the following phishing indicators were used:\n\n");


    printf("  Press Enter to continue...");
    getchar();
}

/* Main menu */
void display_menu(void) {
    printf("\n");


    printf("\n  Enter your choice (1-6): ");
}

int main(void) {
    int choice;
    char input[10];

    printf("\n");


    printf("\n  Press Enter to continue...");
    getchar();

    while (1) {
        system(CLEAR_SCREEN);
        display_menu();

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1:
            case 2:
            case 3:
                run_phishing_simulation(choice);
                break;
            case 4:
                analyze_phishing_indicators();
                break;
            case 5:
                system(CLEAR_SCREEN);
                display_educational_warning();
                printf("  Press Enter to continue...");
                getchar();
                break;
            case 6:
                system(CLEAR_SCREEN);
                display_educational_warning();
                printf("  Thank you for learning about phishing protection!\n");
                printf("  Stay safe online.\n\n");
                return 0;
            default:
                printf("\n  Invalid choice. Please try again.\n");
                printf("  Press Enter to continue...");
                getchar();
        }
    }

    return 0;
}

/*
 * Sample Output:
 *
 * ╔══════════════════════════════════════════════════════════════╗
 * ║         PHISHING SIMULATION - EDUCATIONAL TOOL               ║
 * ║                                                              ║
 * ║     ⚠️  FOR EDUCATIONAL PURPOSES ONLY ⚠️                      ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║                                                              ║
 * ║     1. Simulate Bank Phishing                                ║
 * ║     2. Simulate Email Phishing                               ║
 * ║     3. Simulate Social Media Phishing                        ║
 * ║     4. Analyze Phishing Indicators                           ║
 * ║     5. View Educational Warning                              ║
 * ║     6. Exit                                                  ║
 * ║                                                              ║
 * ╚══════════════════════════════════════════════════════════════╝
 *
 *   Enter your choice (1-6): 1
 *
 * [Bank Login Page Appears]
 *   Username / Email: user@example.com
 *   Password: ********
 *
 *   Authenticating.....
 *
 *   ╔════════════════════════════════════════════╗
 *   ║  ❌ Authentication Failed                   ║
 *   ║                                            ║
 *   ║  Invalid username or password.             ║
 *   ║  Please try again or contact support.      ║
 *   ╚════════════════════════════════════════════╝
 *
 * [Shows captured credentials for educational purposes]
 */
