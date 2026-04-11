# Slip 16 — Computer Networks Solution Guide

## Q1: Short Answer Questions

### a) What is password security?

**Password Security Measures:**
- Minimum 12 characters recommended
- Mix character types: uppercase, lowercase, numbers, symbols
- Avoid personal information and dictionary words
- Unique passwords for different accounts
- Regular password changes (90 days)
- Multi-factor authentication (MFA)

**Password Strength Checker Tools:**
- Have I Been Pwned
- Password Meter
- Kaspersky Password Checker

**Strong Example:** Tr0p!c@l$un$et2024#

---

### b) What is cipher?

**Cipher:** Encryption technique that transforms readable text to unreadable code.

**Cipher Types:**
- **Caesar Cipher**: Shift characters (A→D by 3)
- **Substitution**: Replace each character consistently
- **Transposition**: Rearrange character positions
- **Modern Ciphers**: AES, RSA, Blowfish

**Caesar Cipher Example:**
```
Plain:  HELLO
Shift:  +3
Cipher: KHOOR
```

---

### c) What are digital signatures?

**Digital Signature:**
- Verifies message authenticity
- Ensures data integrity
- Provides non-repudiation
- Created with sender's private key
- Verified with sender's public key

**Process:**
1. Hash the message
2. Encrypt hash with private key (signature)
3. Send message + signature
4. Recipient decrypts signature with public key
5. Verify hash matches

---

### d) What is cryptography?

**Cryptography:** Art/science of secure communication through codes.

**Key Areas:**
- **Encryption**: Transform readable data to unreadable
- **Decryption**: Reverse process
- **Authentication**: Verify identity
- **Integrity**: Ensure data not tampered

**Types:**
- **Symmetric**: Single shared key (AES, DES)
- **Asymmetric**: Public/private key pair (RSA)
- **Hashing**: One-way transformation (SHA-256, MD5)

---

### f) What is network attack?

**Network Attacks:**
- **DDoS**: Flood server with traffic
- **Man-in-the-Middle**: Intercept communications
- **Phishing**: Social engineering
- **SQL Injection**: Database exploitation
- **Malware**: Viruses, trojans, ransomware

---

### g) What is data integrity?

**Data Integrity:** Ensures data hasn't been modified.

**Mechanisms:**
- **Checksums**: Detect transmission errors
- **Hash Functions**: One-way fingerprints (SHA-256)
- **Digital Signatures**: Authenticate and verify
- **CRC**: Cyclic Redundancy Check

---

## Q2: Practical Questions

Password strength analysis and encryption techniques implementation.

---

