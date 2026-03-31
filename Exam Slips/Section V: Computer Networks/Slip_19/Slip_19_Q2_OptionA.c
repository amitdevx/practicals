/*
 * Slip 19 - Q2 Option A: Phishing Simulation Program
 * 
 * This program demonstrates how phishing attacks work for educational purposes.
 * It creates a simple simulation showing credential capture techniques.
 * 
 * ⚠️ WARNING: This is for EDUCATIONAL PURPOSES ONLY!
 * Using this for unauthorized access is ILLEGAL and UNETHICAL.
 * 
 * Compile: gcc -o phishing_sim Slip_19_Q2_OptionA.c
 * Run: ./phishing_sim
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 100
#define MAX_STRING 256
#define LOG_FILE "phishing_log.txt"

// Structure to store captured credentials
typedef struct {
    char username[MAX_STRING];
    char password[MAX_STRING];
    char ip_address[50];
    char timestamp[50];
    int attempt_number;
} PhishingAttempt;

// Global storage for phishing attempts
PhishingAttempt attempts[MAX_ATTEMPTS];
int attempt_count = 0;

// Function prototypes
void display_banner(void);
void display_educational_warning(void);
void simulate_fake_login_page(const char *target_site);
void capture_credentials(const char *username, const char *password, const char *ip);
void log_attempt(PhishingAttempt *attempt);
void display_captured_data(void);
void generate_html_page(const char *target_site);
void show_phishing_indicators(void);
void run_awareness_quiz(void);
void display_menu(void);
char* get_current_timestamp(void);
char* generate_fake_ip(void);

int main() {
    int choice;
    char target_site[MAX_STRING];
    char username[MAX_STRING];
    char password[MAX_STRING];
    
    display_banner();
    display_educational_warning();
    
    printf("\nPress Enter to continue with the simulation...");
    getchar();
    
    while (1) {
        display_menu();
        printf("\nEnter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                printf("\n=== FAKE LOGIN PAGE SIMULATION ===\n");
                printf("Enter target site name (e.g., 'Bank Login', 'Email Service'): ");
                fgets(target_site, sizeof(target_site), stdin);
                target_site[strcspn(target_site, "\n")] = '\0';
                simulate_fake_login_page(target_site);
                break;
                
            case 2:
                printf("\n=== MANUAL CREDENTIAL CAPTURE TEST ===\n");
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = '\0';
                
                printf("Enter password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0';
                
                capture_credentials(username, password, generate_fake_ip());
                printf("\n✓ Credentials captured for demonstration!\n");
                break;
                
            case 3:
                display_captured_data();
                break;
                
            case 4:
                printf("\nEnter site name for HTML template: ");
                fgets(target_site, sizeof(target_site), stdin);
                target_site[strcspn(target_site, "\n")] = '\0';
                generate_html_page(target_site);
                break;
                
            case 5:
                show_phishing_indicators();
                break;
                
            case 6:
                run_awareness_quiz();
                break;
                
            case 7:
                printf("\n=== EDUCATIONAL SUMMARY ===\n");
                printf("This simulation demonstrated:\n");
                printf("1. How easily fake login pages can be created\n");
                printf("2. How credentials are captured and logged\n");
                printf("3. The importance of verifying website authenticity\n\n");
                printf("PROTECT YOURSELF:\n");
                printf("- Always check the URL before entering credentials\n");
                printf("- Look for HTTPS and valid certificates\n");
                printf("- Never click links in suspicious emails\n");
                printf("- Enable two-factor authentication\n\n");
                printf("Exiting simulation. Stay safe online!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please select 1-7.\n");
        }
    }
    
    return 0;
}

void display_banner(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║         PHISHING SIMULATION - EDUCATIONAL TOOL                 ║\n");
    printf("║                  Computer Networks Lab                         ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
}

void display_educational_warning(void) {
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│                    ⚠️  IMPORTANT WARNING ⚠️                     │\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│  This program is designed SOLELY for EDUCATIONAL PURPOSES     │\n");
    printf("│  to demonstrate how phishing attacks work.                    │\n");
    printf("│                                                               │\n");
    printf("│  USING THIS FOR UNAUTHORIZED ACCESS IS:                       │\n");
    printf("│  • ILLEGAL under computer fraud laws                          │\n");
    printf("│  • UNETHICAL and violates privacy                             │\n");
    printf("│  • PUNISHABLE by fines and imprisonment                       │\n");
    printf("│                                                               │\n");
    printf("│  Only use this in controlled lab environments with proper     │\n");
    printf("│  authorization for security awareness training.               │\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

void display_menu(void) {
    printf("\n");
    printf("┌─────────────────── MAIN MENU ───────────────────┐\n");
    printf("│                                                 │\n");
    printf("│  1. Simulate Fake Login Page                    │\n");
    printf("│  2. Test Credential Capture                     │\n");
    printf("│  3. View Captured Data                          │\n");
    printf("│  4. Generate HTML Phishing Page Template        │\n");
    printf("│  5. Learn Phishing Indicators                   │\n");
    printf("│  6. Take Awareness Quiz                         │\n");
    printf("│  7. Exit                                        │\n");
    printf("│                                                 │\n");
    printf("└─────────────────────────────────────────────────┘\n");
}

char* get_current_timestamp(void) {
    static char timestamp[50];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
    return timestamp;
}

char* generate_fake_ip(void) {
    static char ip[20];
    sprintf(ip, "%d.%d.%d.%d", 
            192 + rand() % 10, 
            168, 
            rand() % 256, 
            rand() % 256);
    return ip;
}

void simulate_fake_login_page(const char *target_site) {
    char username[MAX_STRING];
    char password[MAX_STRING];
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                ║\n");
    printf("║                    %s                                     \n", target_site);
    printf("║                                                                ║\n");
    printf("║   ┌──────────────────────────────────────────────────────┐    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   │              Welcome! Please Sign In                 │    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   │  Username/Email: [________________________]          │    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   │  Password:       [________________________]          │    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   │            [ Remember Me ]    [ Sign In ]            │    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   │              Forgot Password? | Sign Up              │    ║\n");
    printf("║   │                                                      │    ║\n");
    printf("║   └──────────────────────────────────────────────────────┘    ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n[SIMULATION] This is what a victim would see.\n");
    printf("[SIMULATION] In real attack, this would be a web page.\n\n");
    
    printf("Enter username (victim simulation): ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    
    printf("Enter password (victim simulation): ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    
    capture_credentials(username, password, generate_fake_ip());
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                     ⚠️  ALERT ⚠️                                ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║   THIS WAS A PHISHING SIMULATION!                              ║\n");
    printf("║                                                                ║\n");
    printf("║   If this were a real attack, your credentials would           ║\n");
    printf("║   have been stolen and sent to an attacker.                    ║\n");
    printf("║                                                                ║\n");
    printf("║   RED FLAGS YOU SHOULD HAVE NOTICED:                           ║\n");
    printf("║   • The page appeared in a command line (unusual!)             ║\n");
    printf("║   • No HTTPS/SSL certificate verification                      ║\n");
    printf("║   • Generic login prompt without proper branding               ║\n");
    printf("║   • No URL to verify authenticity                              ║\n");
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
}

void capture_credentials(const char *username, const char *password, const char *ip) {
    if (attempt_count >= MAX_ATTEMPTS) {
        printf("Warning: Maximum attempts reached!\n");
        return;
    }
    
    PhishingAttempt *attempt = &attempts[attempt_count];
    
    strncpy(attempt->username, username, MAX_STRING - 1);
    strncpy(attempt->password, password, MAX_STRING - 1);
    strncpy(attempt->ip_address, ip, sizeof(attempt->ip_address) - 1);
    strncpy(attempt->timestamp, get_current_timestamp(), sizeof(attempt->timestamp) - 1);
    attempt->attempt_number = attempt_count + 1;
    
    log_attempt(attempt);
    attempt_count++;
}

void log_attempt(PhishingAttempt *attempt) {
    FILE *log = fopen(LOG_FILE, "a");
    if (log != NULL) {
        fprintf(log, "[%s] Attempt #%d | IP: %s | User: %s | Pass: %s\n",
                attempt->timestamp,
                attempt->attempt_number,
                attempt->ip_address,
                attempt->username,
                "********");  // Don't log actual passwords
        fclose(log);
    }
}

void display_captured_data(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        CAPTURED CREDENTIALS LOG                            ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
    
    if (attempt_count == 0) {
        printf("║  No credentials captured yet.                                              ║\n");
    } else {
        printf("║  #   │ Timestamp           │ IP Address      │ Username                    ║\n");
        printf("║──────┼─────────────────────┼─────────────────┼─────────────────────────────║\n");
        
        for (int i = 0; i < attempt_count; i++) {
            printf("║  %-3d │ %-19s │ %-15s │ %-27s ║\n",
                   attempts[i].attempt_number,
                   attempts[i].timestamp,
                   attempts[i].ip_address,
                   attempts[i].username);
        }
    }
    
    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║  Total Attempts: %-3d                                                       ║\n", attempt_count);
    printf("╚════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nNote: Passwords are not displayed for security. Check %s for logs.\n", LOG_FILE);
}

void generate_html_page(const char *target_site) {
    char filename[MAX_STRING];
    sprintf(filename, "fake_%s_login.html", target_site);
    
    // Replace spaces with underscores
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == ' ') filename[i] = '_';
    }
    
    FILE *html = fopen(filename, "w");
    if (html == NULL) {
        printf("Error: Could not create HTML file!\n");
        return;
    }
    
    fprintf(html, "<!DOCTYPE html>\n");
    fprintf(html, "<html lang=\"en\">\n");
    fprintf(html, "<head>\n");
    fprintf(html, "    <meta charset=\"UTF-8\">\n");
    fprintf(html, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(html, "    <title>%s - Login</title>\n", target_site);
    fprintf(html, "    <style>\n");
    fprintf(html, "        body {\n");
    fprintf(html, "            font-family: Arial, sans-serif;\n");
    fprintf(html, "            background-color: #f0f2f5;\n");
    fprintf(html, "            display: flex;\n");
    fprintf(html, "            justify-content: center;\n");
    fprintf(html, "            align-items: center;\n");
    fprintf(html, "            height: 100vh;\n");
    fprintf(html, "            margin: 0;\n");
    fprintf(html, "        }\n");
    fprintf(html, "        .login-container {\n");
    fprintf(html, "            background: white;\n");
    fprintf(html, "            padding: 40px;\n");
    fprintf(html, "            border-radius: 8px;\n");
    fprintf(html, "            box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n");
    fprintf(html, "            width: 350px;\n");
    fprintf(html, "        }\n");
    fprintf(html, "        h2 { text-align: center; color: #1877f2; }\n");
    fprintf(html, "        input[type=\"text\"], input[type=\"password\"] {\n");
    fprintf(html, "            width: 100%%;\n");
    fprintf(html, "            padding: 12px;\n");
    fprintf(html, "            margin: 8px 0;\n");
    fprintf(html, "            border: 1px solid #ddd;\n");
    fprintf(html, "            border-radius: 4px;\n");
    fprintf(html, "            box-sizing: border-box;\n");
    fprintf(html, "        }\n");
    fprintf(html, "        button {\n");
    fprintf(html, "            width: 100%%;\n");
    fprintf(html, "            padding: 12px;\n");
    fprintf(html, "            background-color: #1877f2;\n");
    fprintf(html, "            color: white;\n");
    fprintf(html, "            border: none;\n");
    fprintf(html, "            border-radius: 4px;\n");
    fprintf(html, "            cursor: pointer;\n");
    fprintf(html, "            font-size: 16px;\n");
    fprintf(html, "            margin-top: 10px;\n");
    fprintf(html, "        }\n");
    fprintf(html, "        button:hover { background-color: #166fe5; }\n");
    fprintf(html, "        .warning {\n");
    fprintf(html, "            background: #ffcccc;\n");
    fprintf(html, "            border: 2px solid #ff0000;\n");
    fprintf(html, "            padding: 20px;\n");
    fprintf(html, "            margin-top: 20px;\n");
    fprintf(html, "            text-align: center;\n");
    fprintf(html, "            display: none;\n");
    fprintf(html, "        }\n");
    fprintf(html, "    </style>\n");
    fprintf(html, "</head>\n");
    fprintf(html, "<body>\n");
    fprintf(html, "    <div class=\"login-container\">\n");
    fprintf(html, "        <h2>%s</h2>\n", target_site);
    fprintf(html, "        <form id=\"loginForm\" onsubmit=\"return captureCredentials()\">\n");
    fprintf(html, "            <input type=\"text\" id=\"username\" placeholder=\"Email or Username\" required>\n");
    fprintf(html, "            <input type=\"password\" id=\"password\" placeholder=\"Password\" required>\n");
    fprintf(html, "            <button type=\"submit\">Log In</button>\n");
    fprintf(html, "        </form>\n");
    fprintf(html, "        <div class=\"warning\" id=\"warning\">\n");
    fprintf(html, "            <h3>⚠️ PHISHING SIMULATION ⚠️</h3>\n");
    fprintf(html, "            <p>This was a demonstration. Your credentials were NOT actually stolen.</p>\n");
    fprintf(html, "            <p>In a real attack, they would have been sent to an attacker!</p>\n");
    fprintf(html, "        </div>\n");
    fprintf(html, "    </div>\n");
    fprintf(html, "    <script>\n");
    fprintf(html, "        function captureCredentials() {\n");
    fprintf(html, "            var username = document.getElementById('username').value;\n");
    fprintf(html, "            var password = document.getElementById('password').value;\n");
    fprintf(html, "            console.log('CAPTURED: ' + username + ' / ' + password);\n");
    fprintf(html, "            document.getElementById('warning').style.display = 'block';\n");
    fprintf(html, "            document.getElementById('loginForm').style.display = 'none';\n");
    fprintf(html, "            return false;\n");
    fprintf(html, "        }\n");
    fprintf(html, "    </script>\n");
    fprintf(html, "</body>\n");
    fprintf(html, "</html>\n");
    
    fclose(html);
    
    printf("\n✓ HTML phishing page template created: %s\n", filename);
    printf("\nNote: This is for EDUCATIONAL demonstration only!\n");
    printf("The page includes a warning that displays after 'login' attempt.\n");
}

void show_phishing_indicators(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    HOW TO IDENTIFY PHISHING ATTEMPTS                       ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 CHECK THE SENDER:                                                      ║\n");
    printf("║     ✗ support@amaz0n-secure.com  (FAKE - notice the '0' and extra words)  ║\n");
    printf("║     ✓ support@amazon.com          (REAL)                                  ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 INSPECT URLs (hover before clicking):                                  ║\n");
    printf("║     ✗ http://paypa1-login.com/secure    (FAKE - 'l' replaced with '1')   ║\n");
    printf("║     ✓ https://www.paypal.com/login      (REAL)                            ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 URGENCY & THREATS:                                                     ║\n");
    printf("║     ✗ 'Your account will be SUSPENDED in 24 hours!'                       ║\n");
    printf("║     ✗ 'Immediate action required - verify NOW!'                           ║\n");
    printf("║     ✓ Legitimate companies rarely use threatening language                ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 GENERIC GREETINGS:                                                     ║\n");
    printf("║     ✗ 'Dear Customer' or 'Dear User'                                      ║\n");
    printf("║     ✓ 'Dear John Smith' (companies know your name)                        ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 SPELLING & GRAMMAR ERRORS:                                             ║\n");
    printf("║     ✗ 'Your account has been compromize. Please login to you're account.' ║\n");
    printf("║     ✓ Professional companies proofread their communications               ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 SUSPICIOUS ATTACHMENTS:                                                ║\n");
    printf("║     ✗ Invoice.exe, Document.zip, Update.scr                               ║\n");
    printf("║     ✓ Be wary of unexpected attachments, especially executables           ║\n");
    printf("║                                                                            ║\n");
    printf("║  🔍 REQUESTS FOR SENSITIVE INFO:                                           ║\n");
    printf("║     ✗ 'Please reply with your password and SSN'                           ║\n");
    printf("║     ✓ Legitimate companies NEVER ask for passwords via email              ║\n");
    printf("║                                                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════╝\n");
}

void run_awareness_quiz(void) {
    int score = 0;
    int answer;
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║              PHISHING AWARENESS QUIZ                           ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    // Question 1
    printf("Q1: You receive an email from 'security@micros0ft-support.com'\n");
    printf("    asking you to verify your account. What should you do?\n");
    printf("    1. Click the link and enter your credentials\n");
    printf("    2. Report it as phishing and delete it\n");
    printf("    3. Forward it to your friends\n");
    printf("    Your answer (1-3): ");
    scanf("%d", &answer);
    if (answer == 2) { score++; printf("    ✓ Correct!\n\n"); }
    else printf("    ✗ Wrong! The domain 'micros0ft' (with zero) is suspicious.\n\n");
    
    // Question 2
    printf("Q2: An email says 'Your account will be deleted in 2 hours unless\n");
    printf("    you verify now!' What type of tactic is this?\n");
    printf("    1. Legitimate security measure\n");
    printf("    2. Social engineering using urgency/fear\n");
    printf("    3. Normal business communication\n");
    printf("    Your answer (1-3): ");
    scanf("%d", &answer);
    if (answer == 2) { score++; printf("    ✓ Correct!\n\n"); }
    else printf("    ✗ Wrong! Creating urgency is a common phishing tactic.\n\n");
    
    // Question 3
    printf("Q3: Before clicking a link in an email, you should:\n");
    printf("    1. Click immediately if it looks important\n");
    printf("    2. Hover over it to see the actual URL\n");
    printf("    3. Forward it to IT only if it doesn't work\n");
    printf("    Your answer (1-3): ");
    scanf("%d", &answer);
    if (answer == 2) { score++; printf("    ✓ Correct!\n\n"); }
    else printf("    ✗ Wrong! Always hover to check the actual URL destination.\n\n");
    
    // Question 4
    printf("Q4: A legitimate bank email would typically:\n");
    printf("    1. Ask you to reply with your password\n");
    printf("    2. Include your full name, not 'Dear Customer'\n");
    printf("    3. Contain multiple spelling errors\n");
    printf("    Your answer (1-3): ");
    scanf("%d", &answer);
    if (answer == 2) { score++; printf("    ✓ Correct!\n\n"); }
    else printf("    ✗ Wrong! Banks know your name and never ask for passwords.\n\n");
    
    // Question 5
    printf("Q5: Which URL is most likely legitimate?\n");
    printf("    1. http://paypal-secure-login.suspicious.com/\n");
    printf("    2. https://www.paypal.com/signin\n");
    printf("    3. http://www.paypa1.com/login\n");
    printf("    Your answer (1-3): ");
    scanf("%d", &answer);
    if (answer == 2) { score++; printf("    ✓ Correct!\n\n"); }
    else printf("    ✗ Wrong! Only option 2 has HTTPS and correct domain.\n\n");
    
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                     QUIZ RESULTS                               ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  Your Score: %d/5                                               ║\n", score);
    
    if (score == 5) {
        printf("║  Rating: EXCELLENT! You're phishing-aware!                     ║\n");
    } else if (score >= 3) {
        printf("║  Rating: GOOD! Review the indicators you missed.               ║\n");
    } else {
        printf("║  Rating: NEEDS IMPROVEMENT - Please review phishing indicators ║\n");
    }
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    while (getchar() != '\n');  // Clear input buffer
}
