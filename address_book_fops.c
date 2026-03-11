#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

// Do not, at all costs, touch anything in here
// I managed to get it to work and I'm not sure I could figure it out again
Status load_file(AddressBook *address_book)
{
	int ret = access(DEFAULT_FILE, F_OK);

	/* 
	 * Check for file existance
	 */

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "r");
		int numLines = 1;
		int fileChar;
		int hasContent = 0;
		do {
			fileChar = fgetc(address_book->fp);
			if (fileChar == '\n') {
				numLines++;
			}
		} while (fileChar != EOF);
		rewind(address_book->fp);
		address_book->count = numLines;
		address_book->list = malloc(sizeof(ContactInfo) * (numLines + 1));
		if (address_book->list == NULL) {
			fprintf(stderr, "Error: Not enough memory for file read/write");
			fclose(address_book->fp);
			exit(1);
			return e_fail;
		}
		else {
			char *field;
			int maxChars = NAME_LEN + 1 + (PHONE_NUMBER_COUNT * (NUMBER_LEN + 1)) + (EMAIL_ID_COUNT * (EMAIL_ID_LEN + 1)) - 1;
			char placeholder[maxChars];
			if (fgetc(address_book->fp) != EOF) {
				rewind(address_book->fp);
				for (int row = 0; row < address_book->count; row++) {
					if (fgets(placeholder, maxChars, address_book->fp) != NULL) {
						strcpy(address_book->list[row].name[0], strtok(placeholder, ","));
						strcpy(address_book->list[row].phone_numbers[0], strtok(NULL, ","));
						strcpy(address_book->list[row].phone_numbers[1], strtok(NULL, ","));
						strcpy(address_book->list[row].phone_numbers[2], strtok(NULL, ","));
						strcpy(address_book->list[row].phone_numbers[3], strtok(NULL, ","));
						strcpy(address_book->list[row].phone_numbers[4], strtok(NULL, ","));	
						strcpy(address_book->list[row].email_addresses[0], strtok(NULL, ","));
						strcpy(address_book->list[row].email_addresses[1], strtok(NULL, ","));
						strcpy(address_book->list[row].email_addresses[2], strtok(NULL, ","));
						strcpy(address_book->list[row].email_addresses[3], strtok(NULL, ","));
						strcpy(address_book->list[row].email_addresses[4], strtok(NULL, ","));
						address_book->list[row].si_no = row + 1;				
					}
				}
			}
			rewind(address_book->fp);
		}
		fclose(address_book->fp);
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		address_book->count = 0;
		address_book->list = malloc(sizeof(ContactInfo) * 1);
		if (address_book->list == NULL) {
			fprintf(stderr, "Error: Not enough memory for file read/write");
			fclose(address_book->fp);
			return e_fail;
		}
		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w+");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	if (address_book->count != 0) {
		for (int i = 0; i < (address_book->count - 1); i++) {
			fprintf(address_book->fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",
				address_book->list[i].name[0],
				address_book->list[i].phone_numbers[0],
				address_book->list[i].phone_numbers[1],
				address_book->list[i].phone_numbers[2],
				address_book->list[i].phone_numbers[3],
				address_book->list[i].phone_numbers[4],
				address_book->list[i].email_addresses[0],
				address_book->list[i].email_addresses[1],
				address_book->list[i].email_addresses[2],
				address_book->list[i].email_addresses[3],
				address_book->list[i].email_addresses[4],
				address_book->list[i].si_no
			);
		}
		fprintf(address_book->fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d",
			address_book->list[address_book->count - 1].name[0],
			address_book->list[address_book->count - 1].phone_numbers[0],
			address_book->list[address_book->count - 1].phone_numbers[1],
			address_book->list[address_book->count - 1].phone_numbers[2],
			address_book->list[address_book->count - 1].phone_numbers[3],
			address_book->list[address_book->count - 1].phone_numbers[4],
			address_book->list[address_book->count - 1].email_addresses[0],
			address_book->list[address_book->count - 1].email_addresses[1],
			address_book->list[address_book->count - 1].email_addresses[2],
			address_book->list[address_book->count - 1].email_addresses[3],
			address_book->list[address_book->count - 1].email_addresses[4],
			address_book->list[address_book->count - 1].si_no
		);
	}
	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
