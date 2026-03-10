// Importing unity and address book 
#include "unity.h"
#include "address_book.h"
#include "address_book_menu.h"
#include "address_book_fops.h"
#include <stdio.h>
#include <string.h>


void setUp(void){
}

void tearDown(void){
}


//Tests address_book.h//

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



//Tests address_book_menu.h//

// Just making sure that the nums remain the same in case someone changes it later
void test_menu_window_vals(void){
    TEST_ASSERT_EQUAL_INT(0, NONE);
    TEST_ASSERT_EQUAL_INT(1, NUM);
    TEST_ASSERT_EQUAL_INT(2, CHAR);
    TEST_ASSERT_EQUAL_INT(5, WINDOW_SIZE);
}

/*
Currently doesn't work due to bugs in main with add contacts

void test_add_Nums(void){
    AddressBook book = {0};

    FILE *inp_file_test = fopen("inp_file_test.txt", "w");
    TEST_ASSERT_NOT_NULL(inp_file_test);


    fprintf(inp_file_test, "2\n123-456-7890\n");
    

    Status result = add_contacts(&book);

    TEST_ASSERT_EQUAL_INT(e_fail, result);

}
*/

// Making sure the program starts at e_exit for the menu feature struct
void test_menu_ouptut_exit(void){
   TEST_ASSERT_EQUAL_INT(0, e_exit);
}

// Simple test for holding large ints
void test_contact_sino_vals(void){
    ContactInfo testContact2 = {0}; // Again setting everthing to 0

    //Setting it to large int
    testContact2.si_no = 1000000000;

    // Verify if number was stored
    TEST_ASSERT_EQUAL_INT(1000000000, testContact2.si_no);
}


// Setting up main where tests functions are called
int main(void){

    UNITY_BEGIN();

    RUN_TEST(test_address_book_creation);
    RUN_TEST(test_default_csv_file);
    RUN_TEST(test_lengths_of_usr);
    RUN_TEST(test_counts);
    RUN_TEST(test_contact_info);
    RUN_TEST(test_menu_window_vals);
    // RUN_TEST(test_add_Nums);
    RUN_TEST(test_menu_ouptut_exit);
    RUN_TEST(test_contact_sino_vals);
    


    return UNITY_END();
}
