/*
 * Slip 4 - Q2 Option A: Phishing Pattern Detection in Emails
 * 
 * This program reads an email from a file and performs phishing pattern detection
 * by analyzing suspicious patterns, URLs, and common phishing indicators.
 * 
 * Compile: gcc -o phishing_detector Slip_04_Q2_OptionA.c
 * Run: ./phishing_detector email.txt
 * 
 * Author: Computer Networks Lab
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_EMAIL_SIZE 65536
#define MAX_PATTERNS 50

/* Structure to hold detection results */
typedef struct {
    int suspicious_links;
    int urgency_phrases;
    int sensitive_requests;
    int spoofed_sender;
    int mismatched_urls;
    int suspicious_attachments;
    int generic_greeting;
    int spelling_errors;
    int threat_score;
    char details[4096];
} PhishingResult;

/* Common phishing patterns - urgency keywords */
const char *URGENCY_PATTERNS[] = {
    "urgent", "immediate", "action required", "act now",
    "limited time", "expires today", "within 24 hours",
    "account suspended", "verify immediately", "confirm now",
    "final warning", "last chance", NULL
};

/* Sensitive information requests */
const char *SENSITIVE_PATTERNS[] = {
    "password", "credit card", "social security", "ssn",
    "bank account", "pin number", "login credentials",
    "verify your account", "confirm your identity",
    "update payment", "billing information", NULL
};

/* Suspicious URL patterns */
const char *SUSPICIOUS_URL_PATTERNS[] = {
    "bit.ly", "tinyurl", "goo.gl", "t.co",
    "login", "signin", "verify", "secure",
    "update", "confirm", ".tk", ".ml", ".ga",
    "paypa1", "app1e", "g00gle", "amaz0n", NULL
};

/* Known legitimate domains for comparison */
const char *LEGITIMATE_DOMAINS[] = {
    "paypal.com", "apple.com", "google.com", "amazon.com",
    "microsoft.com", "facebook.com", "bank", NULL
};

/* Suspicious attachment extensions */
const char *SUSPICIOUS_EXTENSIONS[] = {
    ".exe", ".scr", ".bat", ".cmd", ".vbs", ".js",
    ".jar", ".zip", ".rar", ".7z", ".iso", NULL
};

/* Function prototypes */
int load_email(const char *filename, char *buffer, int max_size);
void analyze_email(const char *email, PhishingResult *result);
void check_urgency_patterns(const char *email, PhishingResult *result);
void check_sensitive_requests(const char *email, PhishingResult *result);
void check_suspicious_urls(const char *email, PhishingResult *result);
void check_suspicious_attachments(const char *email, PhishingResult *result);
void check_generic_greeting(const char *email, PhishingResult *result);
void check_sender_spoofing(const char *email, PhishingResult *result);
int count_pattern_matches(const char *text, const char *patterns[]);
int contains_pattern_ci(const char *text, const char *pattern);
void to_lowercase(const char *src, char *dest, int max_len);
void calculate_threat_score(PhishingResult *result);
void print_report(const PhishingResult *result);

int main(int argc, char *argv[]) {
    char email_buffer[MAX_EMAIL_SIZE];
    PhishingResult result = {0};
    const char *filename;
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        PHISHING EMAIL PATTERN DETECTOR                     ║\n");
    printf("║        Computer Networks - Slip 4                          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    /* Get filename from argument or use default */
    if (argc < 2) {
        printf("Usage: %s <email_file>\n", argv[0]);
        printf("\nCreating sample phishing email for demonstration...\n\n");
        
        /* Create a sample phishing email file */
        FILE *sample = fopen("sample_phishing_email.txt", "w");
        if (sample) {
            fprintf(sample, "From: security@paypa1-verify.com\n");
            fprintf(sample, "To: user@example.com\n");
            fprintf(sample, "Subject: URGENT: Your Account Has Been Suspended!\n");
            fprintf(sample, "\n");
            fprintf(sample, "Dear Valued Customer,\n");
            fprintf(sample, "\n");
            fprintf(sample, "We have detected unusual activity on your account. Your PayPal\n");
            fprintf(sample, "account has been temporarily suspended due to security concerns.\n");
            fprintf(sample, "\n");
            fprintf(sample, "IMMEDIATE ACTION REQUIRED: Within 24 hours, you must verify\n");
            fprintf(sample, "your identity to restore access to your account.\n");
            fprintf(sample, "\n");
            fprintf(sample, "Click here to verify: http://paypa1-secure.com/login/verify.php?id=12345\n");
            fprintf(sample, "\n");
            fprintf(sample, "You will need to confirm the following:\n");
            fprintf(sample, "- Your password\n");
            fprintf(sample, "- Credit card information\n");
            fprintf(sample, "- Social Security Number (for identity verification)\n");
            fprintf(sample, "\n");
            fprintf(sample, "Failure to act now will result in permanent account closure.\n");
            fprintf(sample, "This is your final warning!\n");
            fprintf(sample, "\n");
            fprintf(sample, "Best regards,\n");
            fprintf(sample, "PayPal Security Team\n");
            fprintf(sample, "\n");
            fprintf(sample, "Attachment: invoice_details.exe\n");
            fclose(sample);
            filename = "sample_phishing_email.txt";
            printf("Sample email created: %s\n\n", filename);
        } else {
            printf("Error: Could not create sample file\n");
            return 1;
        }
    } else {
        filename = argv[1];
    }
    
    /* Load email content */
    if (!load_email(filename, email_buffer, MAX_EMAIL_SIZE)) {
        printf("Error: Could not read email file '%s'\n", filename);
        return 1;
    }
    
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("EMAIL CONTENT:\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("%s\n", email_buffer);
    printf("═══════════════════════════════════════════════════════════════\n\n");
    
    /* Perform analysis */
    printf("Analyzing email for phishing patterns...\n\n");
    analyze_email(email_buffer, &result);
    
    /* Print report */
    print_report(&result);
    
    return 0;
}

/*
 * Load email content from file
 */
int load_email(const char *filename, char *buffer, int max_size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return 0;
    }
    
    int total_read = 0;
    char line[MAX_LINE_LENGTH];
    buffer[0] = '\0';
    
    while (fgets(line, MAX_LINE_LENGTH, fp) && total_read < max_size - MAX_LINE_LENGTH) {
        strcat(buffer, line);
        total_read += strlen(line);
    }
    
    fclose(fp);
    return 1;
}

/*
 * Main analysis function - coordinates all checks
 */
void analyze_email(const char *email, PhishingResult *result) {
    result->details[0] = '\0';
    
    check_urgency_patterns(email, result);
    check_sensitive_requests(email, result);
    check_suspicious_urls(email, result);
    check_suspicious_attachments(email, result);
    check_generic_greeting(email, result);
    check_sender_spoofing(email, result);
    
    calculate_threat_score(result);
}

/*
 * Check for urgency/pressure tactics
 */
void check_urgency_patterns(const char *email, PhishingResult *result) {
    result->urgency_phrases = count_pattern_matches(email, URGENCY_PATTERNS);
    
    if (result->urgency_phrases > 0) {
        char temp[256];
        sprintf(temp, "• Found %d urgency/pressure phrases\n", result->urgency_phrases);
        strcat(result->details, temp);
    }
}

/*
 * Check for requests for sensitive information
 */
void check_sensitive_requests(const char *email, PhishingResult *result) {
    result->sensitive_requests = count_pattern_matches(email, SENSITIVE_PATTERNS);
    
    if (result->sensitive_requests > 0) {
        char temp[256];
        sprintf(temp, "• Found %d requests for sensitive information\n", 
                result->sensitive_requests);
        strcat(result->details, temp);
    }
}

/*
 * Check for suspicious URLs
 */
void check_suspicious_urls(const char *email, PhishingResult *result) {
    char lower_email[MAX_EMAIL_SIZE];
    to_lowercase(email, lower_email, MAX_EMAIL_SIZE);
    
    /* Check for URL shorteners and suspicious patterns */
    result->suspicious_links = count_pattern_matches(email, SUSPICIOUS_URL_PATTERNS);
    
    /* Check for mismatched URLs (display text differs from actual URL) */
    if (strstr(lower_email, "http://") || strstr(lower_email, "https://")) {
        result->suspicious_links++;
        
        /* Look for typosquatting (e.g., paypa1 instead of paypal) */
        for (int i = 0; LEGITIMATE_DOMAINS[i] != NULL; i++) {
            /* Create common typosquatted versions */
            if ((strstr(lower_email, "paypa1") && strcmp(LEGITIMATE_DOMAINS[i], "paypal.com") == 0) ||
                (strstr(lower_email, "g00gle") && strcmp(LEGITIMATE_DOMAINS[i], "google.com") == 0) ||
                (strstr(lower_email, "app1e") && strcmp(LEGITIMATE_DOMAINS[i], "apple.com") == 0) ||
                (strstr(lower_email, "amaz0n") && strcmp(LEGITIMATE_DOMAINS[i], "amazon.com") == 0)) {
                result->mismatched_urls++;
            }
        }
    }
    
    if (result->suspicious_links > 0) {
        char temp[256];
        sprintf(temp, "• Found %d suspicious URL patterns\n", result->suspicious_links);
        strcat(result->details, temp);
    }
    
    if (result->mismatched_urls > 0) {
        char temp[256];
        sprintf(temp, "• Detected %d potential typosquatted domains\n", result->mismatched_urls);
        strcat(result->details, temp);
    }
}

/*
 * Check for suspicious attachment types
 */
void check_suspicious_attachments(const char *email, PhishingResult *result) {
    result->suspicious_attachments = count_pattern_matches(email, SUSPICIOUS_EXTENSIONS);
    
    if (result->suspicious_attachments > 0) {
        char temp[256];
        sprintf(temp, "• Found %d suspicious attachment type(s)\n", 
                result->suspicious_attachments);
        strcat(result->details, temp);
    }
}

/*
 * Check for generic greetings (sign of mass phishing)
 */
void check_generic_greeting(const char *email, PhishingResult *result) {
    const char *generic_greetings[] = {
        "dear customer", "dear user", "dear valued customer",
        "dear member", "dear account holder", "dear sir/madam",
        "dear client", NULL
    };
    
    result->generic_greeting = count_pattern_matches(email, generic_greetings);
    
    if (result->generic_greeting > 0) {
        strcat(result->details, "• Uses generic greeting (not personalized)\n");
    }
}

/*
 * Check for sender spoofing indicators
 */
void check_sender_spoofing(const char *email, PhishingResult *result) {
    char lower_email[MAX_EMAIL_SIZE];
    to_lowercase(email, lower_email, MAX_EMAIL_SIZE);
    
    /* Check for mismatch between claimed sender and actual domain */
    if (strstr(lower_email, "from:")) {
        /* Look for suspicious patterns in sender */
        if (strstr(lower_email, "security@") || 
            strstr(lower_email, "support@") ||
            strstr(lower_email, "admin@") ||
            strstr(lower_email, "verify@") ||
            strstr(lower_email, "alert@")) {
            
            /* Check if domain looks suspicious */
            if (strstr(lower_email, "-verify") || 
                strstr(lower_email, "-secure") ||
                strstr(lower_email, "-support") ||
                strstr(lower_email, "-login")) {
                result->spoofed_sender = 1;
                strcat(result->details, "• Sender domain appears spoofed\n");
            }
        }
    }
}

/*
 * Count matches of patterns in text (case-insensitive)
 */
int count_pattern_matches(const char *text, const char *patterns[]) {
    int count = 0;
    
    for (int i = 0; patterns[i] != NULL; i++) {
        if (contains_pattern_ci(text, patterns[i])) {
            count++;
        }
    }
    
    return count;
}

/*
 * Case-insensitive pattern search
 */
int contains_pattern_ci(const char *text, const char *pattern) {
    char lower_text[MAX_EMAIL_SIZE];
    char lower_pattern[256];
    
    to_lowercase(text, lower_text, MAX_EMAIL_SIZE);
    to_lowercase(pattern, lower_pattern, 256);
    
    return strstr(lower_text, lower_pattern) != NULL;
}

/*
 * Convert string to lowercase
 */
void to_lowercase(const char *src, char *dest, int max_len) {
    int i;
    for (i = 0; src[i] && i < max_len - 1; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

/*
 * Calculate overall threat score
 */
void calculate_threat_score(PhishingResult *result) {
    result->threat_score = 0;
    
    /* Weight different indicators */
    result->threat_score += result->suspicious_links * 15;
    result->threat_score += result->urgency_phrases * 10;
    result->threat_score += result->sensitive_requests * 20;
    result->threat_score += result->spoofed_sender * 25;
    result->threat_score += result->mismatched_urls * 30;
    result->threat_score += result->suspicious_attachments * 25;
    result->threat_score += result->generic_greeting * 5;
    
    /* Cap at 100 */
    if (result->threat_score > 100) {
        result->threat_score = 100;
    }
}

/*
 * Print analysis report
 */
void print_report(const PhishingResult *result) {
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║              PHISHING ANALYSIS REPORT                      ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    /* Threat level indicator */
    printf("║ THREAT SCORE: %3d/100  ", result->threat_score);
    
    if (result->threat_score >= 70) {
        printf("[████████████████████] HIGH RISK      ║\n");
    } else if (result->threat_score >= 40) {
        printf("[████████████        ] MEDIUM RISK    ║\n");
    } else if (result->threat_score >= 20) {
        printf("[████████            ] LOW RISK       ║\n");
    } else {
        printf("[████                ] MINIMAL RISK   ║\n");
    }
    
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ DETECTION SUMMARY:                                         ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    printf("║ Suspicious URLs:        %-3d                                ║\n", 
           result->suspicious_links);
    printf("║ Urgency Phrases:        %-3d                                ║\n", 
           result->urgency_phrases);
    printf("║ Sensitive Data Requests:%-3d                                ║\n", 
           result->sensitive_requests);
    printf("║ Spoofed Sender:         %-3s                                ║\n", 
           result->spoofed_sender ? "Yes" : "No");
    printf("║ Typosquatted Domains:   %-3d                                ║\n", 
           result->mismatched_urls);
    printf("║ Suspicious Attachments: %-3d                                ║\n", 
           result->suspicious_attachments);
    printf("║ Generic Greeting:       %-3s                                ║\n", 
           result->generic_greeting ? "Yes" : "No");
    
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ DETAILED FINDINGS:                                         ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    if (strlen(result->details) > 0) {
        /* Print details line by line */
        char *details_copy = strdup(result->details);
        char *line = strtok(details_copy, "\n");
        while (line != NULL) {
            printf("║ %-58s ║\n", line);
            line = strtok(NULL, "\n");
        }
        free(details_copy);
    } else {
        printf("║ No significant phishing indicators detected.              ║\n");
    }
    
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ RECOMMENDATION:                                            ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    
    if (result->threat_score >= 70) {
        printf("║ ⚠️  HIGH RISK: This email is very likely a phishing attempt.║\n");
        printf("║ Do NOT click any links or download attachments.           ║\n");
        printf("║ Report this email as spam/phishing and delete it.         ║\n");
    } else if (result->threat_score >= 40) {
        printf("║ ⚠️  MEDIUM RISK: Exercise caution with this email.          ║\n");
        printf("║ Verify sender through official channels before acting.    ║\n");
        printf("║ Do not provide sensitive information via email.           ║\n");
    } else if (result->threat_score >= 20) {
        printf("║ ℹ️  LOW RISK: Some suspicious elements detected.            ║\n");
        printf("║ Verify sender if requesting any action or information.    ║\n");
    } else {
        printf("║ ✓  MINIMAL RISK: No major phishing indicators found.       ║\n");
        printf("║ Always remain vigilant with unexpected emails.            ║\n");
    }
    
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

/*
 * ALGORITHM SUMMARY:
 * 
 * 1. Load email content from file
 * 2. Perform multiple pattern checks:
 *    a) Urgency patterns (pressure tactics)
 *    b) Sensitive information requests
 *    c) Suspicious URLs and typosquatting
 *    d) Dangerous attachment types
 *    e) Generic greetings
 *    f) Sender spoofing indicators
 * 3. Calculate weighted threat score
 * 4. Generate detailed report with recommendations
 * 
 * SCORING WEIGHTS:
 * - Mismatched/Typosquatted URLs: 30 points
 * - Spoofed sender: 25 points
 * - Suspicious attachments: 25 points
 * - Sensitive data requests: 20 points each
 * - Suspicious links: 15 points each
 * - Urgency phrases: 10 points each
 * - Generic greeting: 5 points
 * 
 * THREAT LEVELS:
 * - 70-100: HIGH RISK
 * - 40-69:  MEDIUM RISK
 * - 20-39:  LOW RISK
 * - 0-19:   MINIMAL RISK
 */
