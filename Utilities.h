#pragma once

#include <iostream>
using namespace std;

// Simple string helpers (no <string>)

inline void strCopy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

inline int strLength(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

inline bool strEqual(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}



// Manual string copy (replaces strCopy/strcpy)
static void manualStrCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Manual string to int (replaces atoi)
static int manualAtoi(const char* str) {
    int result = 0;
    int i = 0;
    bool negative = false;

    // Skip leading spaces
    while (str[i] == ' ' || str[i] == '\t') i++;

    if (str[i] == '-') {
        negative = true;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return negative ? -result : result;
}

// Manual string to double (replaces atof)
static double manualAtof(const char* str) {
    double result = 0.0;
    double fraction = 0.0;
    int divisor = 1;
    bool negative = false;
    bool afterPoint = false;
    int i = 0;

    // Skip leading spaces
    while (str[i] == ' ' || str[i] == '\t') i++;

    if (str[i] == '-') {
        negative = true;
        i++;
    }

    while (str[i] != '\0' && str[i] != '\n' && str[i] != '\r' && str[i] != '\"') {
        if (str[i] == '.') {
            afterPoint = true;
            i++;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (afterPoint) {
                fraction = fraction * 10 + (str[i] - '0');
                divisor *= 10;
            }
            else {
                result = result * 10 + (str[i] - '0');
            }
        }
        i++;
    }

    result = result + fraction / divisor;
    return negative ? -result : result;
}

// Manual find character in string (replaces strchr)
static char* manualStrchr(char* str, char ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            return &str[i];
        }
    }
    return nullptr;
}

// Add to Utilities.h
int manualStrCmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return *s1 - *s2;
        s1++; s2++;
    }
    return *s1 - *s2;
}
// Manual string tokenizer (replaces strtok)
static char* manualStrtok(char* str, const char* delim, char** saveptr) {
    if (str != nullptr) {
        *saveptr = str;
    }

    if (*saveptr == nullptr || **saveptr == '\0') {
        return nullptr;
    }

    // Skip leading delimiters
    while (**saveptr != '\0') {
        bool isDelim = false;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (**saveptr == delim[i]) {
                isDelim = true;
                break;
            }
        }
        if (!isDelim) break;
        (*saveptr)++;
    }

    if (**saveptr == '\0') {
        return nullptr;
    }

    char* token = *saveptr;

    // Find next delimiter
    while (**saveptr != '\0') {
        bool isDelim = false;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (**saveptr == delim[i]) {
                isDelim = true;
                break;
            }
        }
        if (isDelim) {
            **saveptr = '\0';
            (*saveptr)++;
            return token;
        }
        (*saveptr)++;
    }

    return token;
}

// Trim spaces and quotes from string
static void trimSpaces(char* str) {
    int i = 0;
    // Trim left
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\"') i++;

    int j = 0;
    while (str[i] != '\0') {
        str[j++] = str[i++];
    }
    str[j] = '\0';

    // Trim right
    j--;
    while (j >= 0 && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n' || str[j] == '\r' || str[j] == '\"')) {
        str[j] = '\0';
        j--;
    }
}

// Smart CSV parser that handles quoted fields with commas
static void parseCSVLine(const char* line, char out[][100], int& count) {  // Changed 50 to 100
    count = 0;
    int outIndex = 0;
    bool inQuotes = false;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        }
        else if (line[i] == ',' && !inQuotes) {
            out[count][outIndex] = '\0';
            count++;
            outIndex = 0;
        }
        else if (line[i] == '\n' || line[i] == '\r') {
            // Skip newlines
        }
        else {
            out[count][outIndex++] = line[i];
        }
    }

    // Add the last field
    if (outIndex > 0) {
        out[count][outIndex] = '\0';
        count++;
    }
}


static void splitCSVLine(const char* line, char out[][100], int& count) {
    count = 0;
    int j = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',') {
            out[count][j] = '\0';
            count++;
            j = 0;
        }
        else {
            out[count][j] = line[i];
            j++;
        }
    }
    out[count][j] = '\0';
    count++;
}






