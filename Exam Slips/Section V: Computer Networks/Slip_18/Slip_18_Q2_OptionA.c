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

/* Display fake login page based on site type */
void display_fake_login(int site_type) {
    clear_screen();
    
    printf("\n");
    
    switch (site_type) {
        case 1:  /* Bank */
            printf("╔════════════════════════════════════════════════════════════╗\n");
            printf("║          🏦 SECURE NATIONAL BANK - ONLINE BANKING 🏦        ║\n");
            printf("║              Your Trusted Financial Partner                 ║\n");
            printf("╠════════════════════════════════════════════════════════════╣\n");
            printf("║                                                            ║\n");
            printf("║   ⚠️  SECURITY ALERT: Unusual activity detected!            ║\n");
            printf("║   Please verify your identity to continue.                 ║\n");
            printf("║                                                            ║\n");
            printf("║   🔒 Secure Connection: https://secure-national-bank.com   ║\n");
            printf("║                                                            ║\n");
            printf("╚════════════════════════════════════════════════════════════╝\n");
            break;
            
        case 2:  /* Email */
            printf("╔════════════════════════════════════════════════════════════╗\n");
            printf("║              📧 GLOBAL MAIL - Sign In 📧                    ║\n");
            printf("║                  Access Your Inbox                         ║\n");
            printf("╠════════════════════════════════════════════════════════════╣\n");
            printf("║                                                            ║\n");
            printf("║   Your session has expired. Please sign in again.          ║\n");
            printf("║                                                            ║\n");
            printf("║   🔐 URL: https://accounts.global-mail.com/signin          ║\n");
            printf("║                                                            ║\n");
            printf("╚════════════════════════════════════════════════════════════╝\n");
            break;
            
        case 3:  /* Social Media */
            printf("╔════════════════════════════════════════════════════════════╗\n");
            printf("║           📱 SOCIAL CONNECT - Login 📱                      ║\n");
            printf("║              Connect with Friends                          ║\n");
            printf("╠════════════════════════════════════════════════════════════╣\n");
            printf("║                                                            ║\n");
            printf("║   Someone may have accessed your account.                  ║\n");
            printf("║   Confirm your identity to secure your account.            ║\n");
            printf("║                                                            ║\n");
            printf("║   🔗 URL: https://www.socialconnect-security.com/login     ║\n");
            printf("║                                                            ║\n");
            printf("╚════════════════════════════════════════════════════════════╝\n");
            break;
            
        case 4:  /* E-commerce */
            printf("╔════════════════════════════════════════════════════════════╗\n");
            printf("║          🛒 MEGA SHOP - Account Verification 🛒             ║\n");
            printf("║              Your One-Stop Online Store                    ║\n");
            printf("╠════════════════════════════════════════════════════════════╣\n");
            printf("║                                                            ║\n");
            printf("║   🎁 You have a pending reward! Sign in to claim.          ║\n");
            printf("║   Limited time offer - Act now!                            ║\n");
            printf("║                                                            ║\n");
            printf("║   🔐 URL: https://megashop-rewards.com/verify              ║\n");
            printf("║                                                            ║\n");
            printf("╚════════════════════════════════════════════════════════════╝\n");
            break;
            
        default:
            printf("╔════════════════════════════════════════════════════════════╗\n");
            printf("║              🔐 SECURE LOGIN PORTAL 🔐                      ║\n");
            printf("╠════════════════════════════════════════════════════════════╣\n");
            printf("║      Please enter your credentials to continue             ║\n");
            printf("╚════════════════════════════════════════════════════════════╝\n");
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
        fprintf(fp, "═══════════════════════════════════════\n");
        fprintf(fp, "Timestamp: %s\n", creds->timestamp);
        fprintf(fp, "IP Address: %s\n", creds->ip_address);
        fprintf(fp, "Username: %s\n", creds->username);
        fprintf(fp, "Password: %s\n", creds->password);
        fprintf(fp, "═══════════════════════════════════════\n\n");
        fclose(fp);
        
        printf("  [DEBUG] Credentials logged to %s\n", LOG_FILE);
    } else {
        printf("  [DEBUG] Could not write to log file\n");
    }
}

/* Display educational content about phishing */
void display_phishing_education(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║        ⚠️  PHISHING SIMULATION - EDUCATIONAL DEMONSTRATION ⚠️       ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                   ║\n");
    printf("║  This was a SIMULATED phishing attack for educational purposes.  ║\n");
    printf("║  Your credentials were NOT sent anywhere malicious.              ║\n");
    printf("║                                                                   ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║               HOW TO IDENTIFY PHISHING ATTACKS:                   ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                   ║\n");
    printf("║  1. CHECK THE URL CAREFULLY                                       ║\n");
    printf("║     ❌ secure-national-bank.com  (FAKE - hyphenated)              ║\n");
    printf("║     ✅ nationalbbank.com         (REAL - official domain)         ║\n");
    printf("║                                                                   ║\n");
    printf("║  2. LOOK FOR URGENCY/FEAR TACTICS                                 ║\n");
    printf("║     • \"Your account will be closed!\"                             ║\n");
    printf("║     • \"Unusual activity detected!\"                               ║\n");
    printf("║     • \"Act now or lose access!\"                                  ║\n");
    printf("║                                                                   ║\n");
    printf("║  3. VERIFY SENDER EMAIL ADDRESSES                                 ║\n");
    printf("║     ❌ support@paypa1.com (using '1' instead of 'l')              ║\n");
    printf("║     ✅ support@paypal.com                                         ║\n");
    printf("║                                                                   ║\n");
    printf("║  4. HOVER OVER LINKS BEFORE CLICKING                              ║\n");
    printf("║     Check if the actual URL matches the displayed text            ║\n");
    printf("║                                                                   ║\n");
    printf("║  5. LEGITIMATE COMPANIES NEVER ASK FOR:                           ║\n");
    printf("║     • Passwords via email                                         ║\n");
    printf("║     • Credit card numbers via email                               ║\n");
    printf("║     • Social Security numbers                                     ║\n");
    printf("║                                                                   ║\n");
    printf("║  6. WHEN IN DOUBT:                                                ║\n");
    printf("║     • Don't click links - type the URL manually                   ║\n");
    printf("║     • Call the company directly using official numbers            ║\n");
    printf("║     • Report suspicious emails                                    ║\n");
    printf("║                                                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
}

/* Display warning banner */
void display_warning_banner(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║     ⚠️  WARNING: PHISHING SIMULATION - EDUCATIONAL ONLY ⚠️          ║\n");
    printf("║                                                                   ║\n");
    printf("║  This program demonstrates how phishing attacks work.             ║\n");
    printf("║  DO NOT use this for malicious purposes!                          ║\n");
    printf("║  Unauthorized collection of credentials is ILLEGAL.               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

/* Select which fake site to display */
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
        
        /* Display fake login page */
        display_fake_login(site_type);
        
        /* Capture credentials */
        printf("  ┌─────────────────────────────────────────────┐\n");
        printf("  │              Enter Your Credentials         │\n");
        printf("  └─────────────────────────────────────────────┘\n\n");
        
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
        printf("  ╔════════════════════════════════════════════════╗\n");
        printf("  ║  ❌ Authentication Failed!                      ║\n");
        printf("  ║                                                 ║\n");
        printf("  ║  Invalid username or password.                  ║\n");
        printf("  ║  Please try again or reset your password.       ║\n");
        printf("  ╚════════════════════════════════════════════════╝\n");
        
        /* Display educational content */
        display_phishing_education();
        
        /* Display captured data (for learning) */
        printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
        printf("║                    CAPTURED DATA (DEMONSTRATION)                   ║\n");
        printf("╠═══════════════════════════════════════════════════════════════════╣\n");
        printf("║  Timestamp: %-55s║\n", creds.timestamp);
        printf("║  IP Address: %-54s║\n", creds.ip_address);
        printf("║  Username: %-56s║\n", creds.username);
        printf("║  Password: %-56s║\n", creds.password);
        printf("╚═══════════════════════════════════════════════════════════════════╝\n");
        
        printf("\nWould you like to try another simulation? (y/n): ");
        scanf(" %c", &continue_choice);
        while (getchar() != '\n');  /* Clear input buffer */
        
    } while (continue_choice == 'y' || continue_choice == 'Y');
    
    /* Final message */
    clear_screen();
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║            Thank you for learning about phishing!                 ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                   ║\n");
    printf("║  KEY TAKEAWAYS:                                                   ║\n");
    printf("║                                                                   ║\n");
    printf("║  • Always verify URLs before entering credentials                 ║\n");
    printf("║  • Be suspicious of urgent security messages                      ║\n");
    printf("║  • Never click links in suspicious emails                         ║\n");
    printf("║  • Use two-factor authentication (2FA) when available             ║\n");
    printf("║  • Report phishing attempts to your IT department                 ║\n");
    printf("║                                                                   ║\n");
    printf("║  Stay safe online!                                                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");
    
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
