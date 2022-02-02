#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char filename[100];
    char substring[100];
    char ch = '\0';
    char sentence[500], word[100];
    int len = 0, count = 0, a = 0, index = 0, y = 0, e = 0;
    int len1 = 0, i = 0;
    printf("Please enter file name: \n");
    scanf("%s", filename);
    printf("Please enter substring to find in the file: \n");
    scanf("%s", substring);

    len = strlen(substring);
    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File can't be opened.\n");
    }
    else {
        while ((ch = fgetc(fp)) != EOF) {
            sentence[index] = ch;   //storing the whole sentence in an array
            ch = fgetc(fp);
            index++;
            sentence[index] = ch;
            index++;
        }
        sentence[index++] = '\0';
        sentence[index++] = ' ';
        fclose(fp);
    }

    while (i < index) {
        for (y = 0;sentence[i] != ' ';y++) {
            word[y] = sentence[i];
            i++;
        }
        i++;
        word[y] = '\0';
        len1 = strlen(word);
       
        for (int w = 0; w < len1 - len + 1;w++) {
            for (int x = 0, h = w;x < len;x++, h++) {
                if (word[h] != substring[x]) {
                    a++;
                }     
            }
                    
            if (a == 0) {
                count++;
            }
            a = 0; 
        }
        y++;
    }


    printf("The number of times this substring occurred is: %d", count);

    return 0;
}
