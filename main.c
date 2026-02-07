/**
 * Name         : Rajesh Bathula
 * Batch id     : 25036A + 39
 * Project name : AddressBook
 * 
 * Description : 
 * The Address Book Project is a software application designed to store, manage, and organize contact information efficiently.
 * It allows users to add, view, update, search, and delete contact details such as name, phone number and email address.
 * The system helps users keep their personal or professional contacts well organized and easily accessible.
 */
#include <stdio.h>
#include<stdlib.h>
#include "contact.h"

int main() 
{
    char choice;
    AddressBook addressBook; //creating structure variable
    initialize(&addressBook); //Initialize the address book

    do 
    {
        //printing menu
        printf("\n**Address Book Menu**\n");
        printf("------------------------\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch (choice) 
        {
            case '1'://function call to create contact
                createContact(&addressBook);
                break;
            case '2'://function call to create contact
                searchContact(&addressBook);
                break;
            case '3'://function call to edit contact
                editContact(&addressBook);
                break;
            case '4'://function call to delete contact
                deleteContact(&addressBook);
                break;
            case '5'://function call to list contacts       
                listContacts(&addressBook);
                break;
            case '6'://function call to save contact and exit
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default://invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '6');
    
    return 0;
}
