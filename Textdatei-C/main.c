/* 
 * File:   main.c
 * Author: Lukas Fischer
 * GitHub: https://github.com/Jinthebandit/Textdatei-C.git
 * 
 * REQUIREMENTS HW-10:
 * 
 * 
 * DEVELOPMENT CYCLE:
 * Gesucht: Externe Textdatei in stdout wiedergeben.
 * Gegeben: Externe Textdateien.
 * 
 * 
 * Created on 20. November 2019
 */

// import libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getopt()

// definitions
#define CHUNK 1024 /* read 1024 bytes at a time */

// predefine functions
void print_text(char *url);
void print_histogram(void);
int count_abc(const char *letter);

// globals
int count;
const char *ABC[53] = {"a","A","b","B","c","C","d","D","e","E","f","F","g","G", "h","H","i","I","j","J","k","K","l","L","m","M","n","N","o","O","p","P","q","Q","r","R","s","S","t","T","u","U","v","V","w","W","x","X","y","Y","z","Z" };
int counter[26];

/*
 * check arguments
 * call functions
 */
int main(int argc, char *argv[]) {
    char *cvalue;
    
    // clear error flag
    opterr = 0;
    
    int c;
    
    // process arguments
    while ((c = getopt(argc, argv, "f:")) != -1) {
        switch(c) {
            case 'f':
                cvalue = optarg;
                break;
            case '?':
                if (optopt == 'f')
                    fprintf(stderr, "Option -%c requires an argument.\nTry: large-text-files/german/ruebezahl.txt\n", optopt);
                else
                    fprintf(stderr, "Unknown option '%c'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }
           
    // call functions
    print_text(cvalue);
    
    print_histogram();
    
    printf("\nLaenge des gesamten Textes: %i", count);
    
    // process remaining arguments
    for (int index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    
    return (EXIT_SUCCESS);
}

/*
 * open file from argument -f
 * write chunks of text to stdout with chunksize CHUNK
 * call count_abc() for each chunk
 */
void print_text(char *url) {
    char buffer[CHUNK];
    FILE *file;
    size_t nread;

    file = fopen(url, "r");
    
    if (file) {
        while ((nread = fread(buffer, 1, sizeof buffer, file)) > 0) {
            fwrite(buffer, 1, nread, stdout);
            count_abc(buffer);
        }
        if (ferror(file)) {
            puts("File could not be opened.");
            exit(1);
        }
        
        fclose(file);
    }
}

/*
 * print counter value for each letter in the alphabet
 */
void print_histogram(void) {
     
    printf("\n\n\n Histogramm:\n");
    
    for(int i = 1; i <= 26; i++) {
        printf("%c: %i\n", *ABC[i*2-1], counter[i-1]);
    }
}


/*
 * compare letters in text with alphabet and increment on matching letters
 */
int count_abc(const char *letter) {
        
    const char *ptr = letter;
    while(*ptr++) {
        for(int i = 1; i <= 26; i++ ) {
            if (*ptr == *ABC[i*2-2] || *ptr == *ABC[i*2-1]){
                counter[i-1] += 1;
            }
        }
    }
    
    count += ptr-letter;
    
    return 0;
}