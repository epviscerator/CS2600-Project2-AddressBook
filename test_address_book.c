// Importing unity and address book 
#include "unity.h"
#include "address_book.h"
#include <stdio.h>
#include <string.h>


void setUp(void){
}

void tearDown(void){
}

/* 
Testing to see if the structure in address_book.h is setting everything equal to null
So book.fp is seeing if the file pointer becomes null 
book.list is checking to see if the contact pointer is null 
and 0, book.count is ensuring that there are no contacts when starting the program 
*/ 

void test_address_book_creation(void){
    AddressBook book = {0}; // setting everything to zero so fp is zero list is zero and count is zero
    
    // Setting up tests
    TEST_ASSERT_NULL(book.fp);
    TEST_ASSERT_NULL(book.list);
    TEST_ASSERT_EQUAL_INT(0, book.count);
}

// Testing to see if default file is correctly named
void test_default_csv_file(void){
    TEST_ASSERT_EQUAL_STRING("address_book.csv", DEFAULT_FILE);
}

// Just making sure that the lengths remain with 32 in case someone changes it later
void test_lengths_of_usr(void){
    TEST_ASSERT_EQUAL_INT(32, NAME_LEN);
    TEST_ASSERT_EQUAL_INT(32, NUMBER_LEN);
    TEST_ASSERT_EQUAL_INT(32, EMAIL_ID_LEN);
}

/*
Testing that there is only one name allowed and under that one name / contact
5 emails and phone numbers are allowed - again in case someone changes it later 
 */
void test_counts(void){
    TEST_ASSERT_EQUAL_INT(1, NAME_COUNT);
    TEST_ASSERT_EQUAL_INT(5, PHONE_NUMBER_COUNT);
    TEST_ASSERT_EQUAL_INT(5, EMAIL_ID_COUNT);
}



// Validating that all information is stored correctly in Contact info struct

void test_contact_info(void){

    ContactInfo testContact = {0}; //setting everything to zero so name is zero list is zero and count is zero
    // so name = '0' phone = '0' email = '0' and si_no = '0'

    // Creating and assigning values into the '0' index of each respective array except for si_no which is an int 
    strcpy(testContact.name[0], "Test");
    strcpy(testContact.phone_numbers[0], "123-456-7890");
    strcpy(testContact.email_addresses[0], "usr@testing.xyz");
    testContact.si_no = 2;

    // Checking values defined above are the same as at index validating that they were stored in the correct place
    TEST_ASSERT_EQUAL_STRING("Test", testContact.name[0]);
    TEST_ASSERT_EQUAL_STRING("123-456-7890", testContact.phone_numbers[0]);
    TEST_ASSERT_EQUAL_STRING("usr@testing.xyz", testContact.email_addresses[0]);

     TEST_ASSERT_EQUAL_INT(2, testContact.si_no);
}


// Setting up main where tests functions are called
int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_address_book_creation);
    RUN_TEST(test_default_csv_file);
    RUN_TEST(test_lengths_of_usr);
    RUN_TEST(test_counts);
    RUN_TEST(test_contact_info);

    return UNITY_END();
}
