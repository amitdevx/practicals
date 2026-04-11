/*
 * Slip 18 - Q2 Option A: Phishing Simulation Program
 *
 * EDUCATIONAL PURPOSE ONLY - Demonstrates phishing mechanics
 * DO NOT use for malicious purposes!
 *
 * This program simulates how phishing attacks collect credentials
 * to educate users about the dangers of entering sensitive information
 * on untrusted websites/applications.
 *
 * Compile: gcc Slip_18_Q2_OptionA.c -o phishing_sim
 * Run: ./phishing_sim
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

#define MAX_USERNAME 64
#define MAX_PASSWORD 64
#define MAX_LINE 256
#define LOG_FILE "captured_credentials.txt"

/* Structure to store captured credentials */
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char timestamp[32];
    char ip_address[16];
} Credentials;

/* Function prototypes */
void clear_screen(void);
void display_fake_login(int site_type);
void get_hidden_password(char *password, int max_len);
void get_timestamp(char *buffer, int size);
void log_credentials(const Credentials *creds);
void display_phishing_education(void);
void simulate_authentication_delay(void);
int select_phishing_site(void);
void display_warning_banner(void);

/* Clear terminal screen */
void clear_screen(void) {
    system(CLEAR_SCREEN);
}

/* Get password with hidden input (cross-platform) */
void get_hidden_password(char *password, int max_len) {
#ifdef _WIN32
    int i = 0;
    char ch;
    while (i < max_len - 1) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') break;
        if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
#else
    struct termios old, new;
    int i = 0;
    char ch;

    /* Disable echo */
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while (i < max_len - 1) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') break;
        if (ch == 127 && i > 0) {  /* Backspace */
            i--;
            printf("\b \b");
            fflush(stdout);
        } else if (ch != 127) {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    password[i] = '\0';
    printf("\n");

    /* Restore terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
#endif
}

/* Get current timestamp */
void get_timestamp(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void display_fake_login(int site_type) {
    clear_screen();

    printf("\n");

    switch (site_type) {
        case 1:  /* Bank */


            break;

        case 2:  /* Email */


            break;

        case 3:  /* Social Media */


            break;

        case 4:  /* E-commerce */


            break;

        default:


    }

    printf("\n");
}

/* Simulate authentication processing delay */
void simulate_authentication_delay(void) {
    printf("\n  🔄 Verifying credentials");
    fflush(stdout);

    for (int i = 0; i < 3; i++) {
#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000);
#endif
        printf(".");
        fflush(stdout);
    }
    printf("\n\n");
}

/* Log captured credentials to file */
void log_credentials(const Credentials *creds) {
    FILE *fp = fopen(LOG_FILE, "a");

    if (fp != NULL) {
        fprintf(fp, "Timestamp: %s\n", creds->timestamp);
        fprintf(fp, "IP Address: %s\n", creds->ip_address);
        fprintf(fp, "Username: %s\n", creds->username);
        fprintf(fp, "Password: %s\n", creds->password);
        fclose(fp);

        printf("  [DEBUG] Credentials logged to %s\n", LOG_FILE);
    } else {
        printf("  [DEBUG] Could not write to log file\n");
    }
}

void display_phishing_education(void) {
    printf("\n");


}

void display_warning_banner(void) {
    printf("\n");


    printf("\n");
}

int select_phishing_site(void) {
    int choice;

    clear_screen();
    display_warning_banner();

    printf("Select phishing simulation type:\n\n");
    printf("  [1] Bank Login (Security Alert)\n");
    printf("  [2] Email Service (Session Expired)\n");
    printf("  [3] Social Media (Account Security)\n");
    printf("  [4] E-commerce (Reward Claim)\n");
    printf("  [5] Generic Login Portal\n");
    printf("\n");
    printf("Enter choice (1-5): ");

    if (scanf("%d", &choice) != 1) {
        choice = 1;
    }

    /* Clear input buffer */
    while (getchar() != '\n');

    if (choice < 1 || choice > 5) {
        choice = 1;
    }

    return choice;
}

/* Main function */
int main(void) {
    Credentials creds;
    int site_type;
    char continue_choice;

    do {
        /* Initialize credentials */
        memset(&creds, 0, sizeof(Credentials));
        strcpy(creds.ip_address, "192.168.1.100");  /* Simulated IP */

        /* Select phishing site type */
        site_type = select_phishing_site();

        display_fake_login(site_type);

        /* Capture credentials */


        printf("  Username/Email: ");
        fgets(creds.username, MAX_USERNAME, stdin);
        creds.username[strcspn(creds.username, "\n")] = '\0';  /* Remove newline */

        printf("  Password: ");
        get_hidden_password(creds.password, MAX_PASSWORD);

        /* Get timestamp */
        get_timestamp(creds.timestamp, sizeof(creds.timestamp));

        /* Simulate processing */
        simulate_authentication_delay();

        /* Log credentials (for demonstration) */
        log_credentials(&creds);

        /* Display fake error (typical phishing behavior) */


        display_phishing_education();


        printf("\nWould you like to try another simulation? (y/n): ");
        scanf(" %c", &continue_choice);
        while (getchar() != '\n');  /* Clear input buffer */

    } while (continue_choice == 'y' || continue_choice == 'Y');

    /* Final message */
    clear_screen();
    printf("\n");


    return 0;
}

/*
 * Sample Output:
 *
 * ╔════════════════════════════════════════════════════════════╗
 * ║          🏦 SECURE NATIONAL BANK - ONLINE BANKING 🏦        ║
 * ║              Your Trusted Financial Partner                 ║
 * ╠════════════════════════════════════════════════════════════╣
 * ║                                                            ║
 * ║   ⚠️  SECURITY ALERT: Unusual activity detected!            ║
 * ║   Please verify your identity to continue.                 ║
 * ║                                                            ║
 * ║   🔒 Secure Connection: https://secure-national-bank.com   ║
 * ║                                                            ║
 * ╚════════════════════════════════════════════════════════════╝
 *
 *   ┌─────────────────────────────────────────────┐
 *   │              Enter Your Credentials         │
 *   └─────────────────────────────────────────────┘
 *
 *   Username/Email: user@example.com
 *   Password: ********
 *
 *   🔄 Verifying credentials...
 *
 *   ╔════════════════════════════════════════════════╗
 *   ║  ❌ Authentication Failed!                      ║
 *   ║  Invalid username or password.                  ║
 *   ╚════════════════════════════════════════════════╝
 *
 * [Educational content displayed]
 */
