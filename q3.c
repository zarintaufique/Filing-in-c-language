#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char filename[100];
    char ch = '\0', temp1='\0',temp = '\0';
    char word[100], sentence[500];
    int len1 = 0, i = 0, k = 0, j = 0, index = 0;
    printf("Please enter file name: \n");
    scanf("%s", filename);
 
    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File can't be opened.\n");
    }
    else {
        printf("The reversed sentence: ");
        while ((ch = fgetc(fp)) != EOF) {
            for (i = 0;ch != ' ' && ch != EOF;i++) {
                word[i] = ch;   //storing the word in an array
                ch = fgetc(fp);
            }
            word[i] = '\0';
            len1 = strlen(word);
            j = 0;               // pointer at the start of the word to be reversed
            k = len1 - 1;        //pointer from the end
            
            while (j < k) {
                if (word[j] == 'a' || word[j] == 'A' || word[j] == 'e' || word[j] == 'E' || word[j] == 'i' || word[j] == 'I' || word[j] == 'o' || word[j] == 'O' || word[j] == 'u' || word[j] == 'U')
                    j++;
                else if (word[k] == 'a' || word[k] == 'A' || word[k] == 'e' || word[k] == 'E' || word[k] == 'i' || word[k] == 'I' || word[k] == 'o' || word[k] == 'O' || word[k] == 'u' || word[k] == 'U')
                    k--;
               
                //to ignore punctuations and numbers
                else if (word[j] < 'A' || word[j]>'z') {
                    j++;
                }
                else if (word[k] < 'A' || word[k]>'z') {
                    k--;
                }
                else if (word[j] > 'Z' && word[j] < 'a') {
                    j++;
                }
                else if (word[k] > 'Z' && word[k] < 'a') {
                    k--;
                }
                //swapping 
                else {
                    temp = word[j];
                    word[j] = word[k];
                    word[k] = temp;
                    j++;
                    k--;
                }
            }

            //printing on console
            printf("%s", word);
            printf(" ");
            
            //saving so we can print in a file too
            for (int y = 0;y < len1;y++) {
                sentence[index] = word[y];
                index++;
            }
         
            sentence[index] = ' ';
            index++;
        }
        fclose(fp);
    }
    sentence[index] = '\0';
         
    
    FILE* fp1;
    //file writing
    fp1 = fopen(filename, "w");
        fprintf(fp1, sentence);

        fclose(fp1);
        return 0;
}

