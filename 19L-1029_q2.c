#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addStudent(int id) {
	char rollnum[9];
	char name[100];
	char email[100];
	
	printf("Please enter Student's name: \n");
	scanf("%s", name);
	printf("Please enter Students roll number: \n");
	scanf("%s", rollnum);
	printf("Please enter Students Email: \n");
	scanf("%s", email);

	FILE* fp1;
	//file writing
	fp1 = fopen("records.txt", "ab");
	fprintf(fp1, "\nID:%d", id);
	fprintf(fp1, " Name: %s", name);
	fprintf(fp1, " Rollnumber: %s", rollnum);
	fprintf(fp1, " Email: %s", email);
	fclose(fp1);

}

void personalinfo(int id) {
	char rollnum[8];
	char name[100];
	char email[100];

	printf("Firstly, add your own details.\nPlease enter your name: \n");
	scanf("%s", name);
	printf("Please enter your roll number: \n");
	scanf("%s", rollnum);
	printf("Please enter your Email: \n");
	scanf("%s", email);

	FILE* fp1;
	//file writing
	fp1 = fopen("records.txt", "w");
	fprintf(fp1, "ID:%d", id);
	fprintf(fp1, " Name: %s", name);
	fprintf(fp1, " Roll number:%s", rollnum);
	fprintf(fp1, " Email:%s", email);
	fclose(fp1);

}

int deleteStudent(int id, FILE* fp) {
	id = id + 48;
	char subs[3] = "ID:";
	char sentence[500];
	char towrite[500];

	char temp = '\0';
	int index = 0;
	int len = 3;

	//storing in an array whole contents of the file
	while ((temp = fgetc(fp)) != EOF) {
		sentence[index] = temp;
		temp = fgetc(fp);
		index++;
		sentence[index] = temp;
		index++;
	}
	sentence[index++] = '\0';					//null added at te end of array
	sentence[index] = '\n';
	fclose(fp);									//closing file

	int len1 = strlen(sentence), count = 0;
	int a = 0, x = 0, h = 0, w = 0, l1 = 0;		//all temp variables to be used in loops

		for ( w = 0; w < len1 - len + 1;w++) {
			for (x = 0, h = w;x < len;x++, h++) {
				if (sentence[h] != subs[x]) {	//searching for keyword ID
					a++;
				}
			}

			l1 = h;
			//keyword found
			if (a == 0) {
				if (sentence[h] == id) {		//confirming id
					count++;					//to know if we actually found what we were lookin for
					l1 = l1 - 3;

					//coping everything except the record to be deleted
					while (sentence[l1] != '\n') {
						
						sentence[l1] = '%';		//in order to keep track of which line to be deleted
						l1++;
					}
					w = len1 + 10;
					
					break;
				}
			}
			a = 0;
		}

		//now coping the records which have not been deleted in order to write on the file
	int j = 0;
	for (int i = 0;i < len1;i++) {
		if (sentence[i] != '%') {
			towrite[j] = sentence[i];
			j++;
		}
	}
	towrite[j] = '\0';

	FILE* fp1;

	//writing to the file
	if (count != 0) {
		fp1 = fopen("records.txt", "w+");
		fprintf(fp1, towrite);

		fclose(fp1);
	}

	//returning to tell if the record been found or not
	return count;
}

void readData(int id, FILE* fp) {
	id = id + 48;
	char subs[3] = "ID:";
	char sentence[500];
	char towrite[500];

	char temp = '\0';
	int index = 0;
	int len = 3;


	//storing in an array whole contents of the file
	while ((temp = fgetc(fp)) != EOF) {
		sentence[index] = temp;
		temp = fgetc(fp);
		index++;
		sentence[index] = temp;
		index++;
	}
	sentence[index++] = '\0';			//null added at te end of array
	sentence[index] = '\n';
	fclose(fp);							//closing file

	int len1 = strlen(sentence), count = 0;
	int a = 0, x = 0, h = 0, w = 0, l1 = 0;		//all temp variables to be used in loops

	for (w = 0; w < len1 - len + 1;w++) {
		for (x = 0, h = w;x < len;x++, h++) {
			if (sentence[h] != subs[x]) {		//searching for keyword ID
				a++;
			}
		}

		l1 = h;
		int j = 0;

		//keyword found
		if (a == 0) {
			if (sentence[h] == id) {			//comfirming id
				count++;						//to know if we actually found what we were lookin for
				l1 = l1 + 2;
				while (sentence[l1] != '\n') {
					towrite[j] = sentence[l1];	//coping only the desired contents into an array to print on the console
					j++;
					l1++;
				}
				towrite[j] = '\0';
				w = len1 + 10;

				break;
			}
		}
		a = 0;
	}

	//cmsole printing
	if (count != 0)
		printf("%s", towrite);
	else
		printf("The record you want to read has either been removed or does not exist.\n");

}


int main() {
	char details[100];
	int choice = 0, number = 0, index = 0, check = 0;
	char ch = '\0';
	int id = 0, num = 0;

	printf("\nEnter 1 to add a new student record. \nEnter 2 to read a Student's record from the file.\nEnter 3 to delete a record from the file.\n Enter your choice:\n");
	scanf("%d", &choice);
	
	if (choice == 1) {
		personalinfo(id);
		id++;
		printf("Enter classmate 1 details: ");
		addStudent(id);
		id++;
		printf("Enter classmate 2 details: ");
		addStudent(id);
		
		//to do more operations
		printf("Do you want to do more operations? \nEnter 2 to read a Student's record from the file.\nEnter 3 to delete a record from the file.\n Enter your choice:\n");
		scanf("%d", &choice);
	}
	if (choice == 2) {
		printf("Enter 0 to read your record. Enter 1 to read first student's record. Enter 2 to read second student's record.\n");
		scanf("%d", &number);
		while (number < 0 && number > 2) {
			printf("Invalid entry. Please enter again.\n");
			printf("Enter 0 to read your record. Enter 1 to read first student's record. Enter 2 to read second student's record.\n");
			scanf("%d", &number);
		}
		FILE* fp;
		fp = fopen("records.txt", "r");
		if (fp == NULL) {
			printf("File can't be opened.\n");
		}
		else {
			readData(number, fp);
		
		}
		printf("\nDo you want to do more operations? \nEnter 3 to delete a record from the file.\n Enter your choice:\n");
		scanf("%d", &choice);

	}
	if (choice == 3) {
		printf("Enter 0 to Delete your record. Enter 1 to delete first student's record. Enter 2 to delete second student's record.\n");
		scanf("%d", &num);
		while (num <0 && num > 2) {
			printf("Invalid entry. Please enter again.\n");
			printf("Enter 0 to delete your record. Enter 1 to delete first student's record. Enter 2 to delete second student's record.\n");
			scanf("%d", &num);
		}
		FILE* fp;
		fp = fopen("records.txt", "r");
		if (fp == NULL) {
			printf("File can't be opened.\n");
		}
		else {
	
			check = deleteStudent(num, fp);
			if (check == 0) {
				printf("The record you want to delete either doesnot exist or has been deleted previously.\n");
			}
			else {
				printf("The record has been deleted successfully.\n");
			}
		}
	}
	else {
		printf("Invalid entry.\n");
	}


	return 0;
}