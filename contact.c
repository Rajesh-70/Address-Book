#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

//function definition for listcontacts
void listContacts(AddressBook *addressBook) 
{
    //check if contacts are in list or not
    if(addressBook->contactCount == 0)
    {
        printf("Error : No contacts in list\n");
        return;
    }

    //print list of contacts
    printf("\n-----------------------------------------------------------\n");
    printf("%30s\n","CONTACT LIST");
    printf("-----------------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-15s\n","S.No","Name","Phone","Email");
    printf("-----------------------------------------------------------\n");
    for(int i = 0;i < (addressBook->contactCount);i++)
    {
        printf("%-5d %-15s %-15s %-15s\n",i+1,addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
    }
    printf("-----------------------------------------------------------\n");

    //print total contact count
    printf("Total contacts: %d\n",addressBook->contactCount);
    printf("-----------------------------------------------------------\n");
    
}

//function definition for initialize
void initialize(AddressBook *addressBook) {
    //initialize count as 1
    addressBook->contactCount = 0;
    
    //function call to load contacts from file
    loadContactsFromFile(addressBook);
}

//function definition for saving contacts to files
void saveAndExit(AddressBook *addressBook) {
    //function call to save contacts to file
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//function definition for validate name
int validname(char *name)
{
    if(strlen(name) < 3)
    {
        return 0;
    }

    int i = 0;
    while(name[i] != '\0')
    {
        //check if charcters in name are alphabets or not
        if(isalpha(name[i]) || name[i] == ' ' || name[i] == '.')
        {
            i++; 
        }
        else
        {
            return 0;// invalid character
        }
    }

    return 1; // valid name
}


//function definition for validate phone number
int validphone(const char *phone,AddressBook *addressBook)
{


    int i;
    //phone number must have 10 digits
    if(strlen(phone) != 10)
    {
        printf("Error : Phone number must be exactly 10 digits\n");
        return 0;
    }

    if(phone[0] < '6' || phone[0] > '9')
    {
        printf("first digit in between 6 to 9\n");
        return 0;
    }

    //phone number contains only digits
    for(i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("Error : Phone number must contain only digits\n");
            return 0;
        }
    }

    // Check for uniqueness
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
          printf("This number already exists! Please enter another number.\n");
            return 0;
        }
    }

    return 1; 
}


//function definition for validate mail
int validemail(char *email,AddressBook *addressBook)
{
    int len = strlen(email);

    // 1. First letter must be alphabet 
    if(!isalpha(email[0]))
    {
        printf("ERROR: Email must start with a letter.\n");
        return 0;
    }

    //2.must contain lower case letters,@,.,digits
    int i = 0;
    while(email[i])
    {
        if(!(islower(email[i]) || email[i] == '@' || email[i] == '.'))
        {
            return 0;
        }
        i++;
    }


    //@ and . bust be occur only once
    i = 0;
    int at = 0, dot = 0;
    while(email[i])
    {
        if(email[i] == '@')
        {
            at++;
        }
        else if(email[i] == '.')
        {
            dot++;
        }
        i++;
    }
    if(at > 1 || dot > 1)
    {
        printf("Error : only one @ and one . should present in email\n");
        return 0;
    }


    // 3. Must contain '@' and end with ".com"
    if(!strchr(email, '@') || strcmp(email + len - 4, ".com") != 0)
    {
        printf("ERROR: Email must contain '@' and end with '.com'.\n");
        return 0;
    }

    // 4. Check at least one character before and after '@'
    if(strchr(email, '@') == email) // nothing before '@'
    {
        printf("ERROR: Email must have at least one character before '@'.\n");
        return 0;//invalid email
    }

    if((strchr(email, '@') + 1) >= (email + len - 4)) // nothing meaningful after '@'
    {
        printf("ERROR: Email must have at least one character after '@'.\n");
        return 0;//invalid email
    }
    // Check for uniqueness
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
          printf("This email already exists! Please enter another number.\n");
            return 0;//invalid email
        }
    }
    return 1;//valid email

}


//function definition for create contact
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    //Name
    int valid = 0,i = 3;
    do
    {
        //ask user to enter name
       printf("Enter name: ");
       scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
       //function call to validate name
       valid = validname(addressBook->contacts[addressBook->contactCount].name);

       if(valid == 0)
       {//invalid name
        printf("Error : Please enter valid name!\n");
        printf("Attempts left %d\n",i - 1);
        i--;
        }
    }while(valid == 0 && i > 0);
    //3 chances to enter valid details 
    if( i == 0)
    {
        return;
    }


    //phone
    i = 3;
    do
    {
      //ask user to enter phone number
       printf("Enter phone number: ");
       scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].phone);

       //function call to validate  phone number.
       valid = validphone(addressBook->contacts[addressBook->contactCount].phone,addressBook);

       if(valid == 0)
       {//invalid phone number
        printf("Error : Please enter valid phone number!\n");
        printf("Attempts left %d\n",i - 1);
        i--;
        }
    }while(valid == 0 && i > 0);
    //3 chances to enter valid details 
    if( i == 0)
    {
        return;
    }
    
    //EMail
    i = 3;
    do
    {
        //ask user to enter email
       printf("Enter Email: ");
       scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].email);

       //function call to validate email
       valid = validemail(addressBook->contacts[addressBook->contactCount].email,addressBook);

       if(valid == 0)
       {//invalid email
        printf("Error : Please enter valid email!\n");
        printf("Attempts left %d\n",i - 1);
        i--;
        }
    }while(valid == 0 && i > 0);
    //3 chances to enter valid details 
    if( i == 0)
    {
        return;
    }

     printf("Contact created successfully\n");
    //increment cotactcount after entering valid details 
    addressBook->contactCount++;
}


//function definition for search name
int searchname(AddressBook *addressBook)
{
    char name[100];
    int i;

    //ask user to enter name to search
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    int contactfound = 0,index[100];
    for(i = 0; i < addressBook->contactCount; i++)
    {
        //search name by calling strcmp()
        if(strcmp(name, addressBook->contacts[i].name) == 0)
        {
            index[contactfound] = i;//store the matched index in array
            contactfound++;
        }
    }

    if(contactfound == 0)
    {
        return -1;
    }  //name not found

    if(contactfound == 1)
    {
        printf("Only one name found in list\n");
        return index[0];//only one name is found
    }  

    //print all matches
    printf("\n-----------------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-15s\n","S.No","Name","Phone","Email");
    printf("-----------------------------------------------------------\n");
    for(int i = 0;i < contactfound;i++)
    {
        printf("%-5d %-15s %-15s %-15s\n",i+1,addressBook->contacts[index[i]].name,
                            addressBook->contacts[index[i]].phone,
                            addressBook->contacts[index[i]].email);
    }
    printf("-----------------------------------------------------------\n");

    char choice;
    //ask user to choise one of contact from printed list
    printf("\nMultiple names are listed which details are you want :");
    scanf(" %c",&choice);//ask user to choose contact details
    if(choice > (contactfound + 48) || choice < '0' )
    {
        printf("Error : Invalid choice\n");
        return -1;//invalid choise
    }
    
    return index[choice - '1'];//return index of user seletectd contact
}



//function definition for search phone number
int searchphone(AddressBook *addressBook)
{
    char phone[100];
    int i;

    //ask user to enter phone number to search
    printf("Enter phone: ");
    scanf(" %[^\n]", phone);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        //search name by call strcmp() function
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return i;   // found → return index
        }
    }

    return -1;  // not found
}


//function definition for search email
int searchemail(AddressBook *addressBook)
{
    char email[100];
    int i;

    //ask user to enter email to search
    printf("Enter email: ");
    scanf(" %[^\n]", email);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        //search email by calling strcmp()
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return i;   // found → return index
        }
    }

    return -1;  // not found
}


//function definition for search contacts by name ,phone,email
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int found,index,i = 3;
    char name[100],opt;
    do
    {
        //MENU
        printf("\n**MENU**\n");
        printf("---------\n");
        printf("1.Name\n");
        printf("2.phone number\n");
        printf("3.Email\n");
        printf("4.Exit\n");
        printf("Enter your choise: ");
        scanf(" %c",&opt);
        
        switch(opt)
        {
            case '1':
                printf("Enter name: ");
                scanf(" %[^\n]", name);
                found = 0;
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    //search name by calling strcmp()
                    if(strcmp(name, addressBook->contacts[i].name) == 0)
                    {
                        printf("\n%d.Name : %s\nPhone: %s\nEmail: %s\n\n",found + 1,addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                            found++;//name found
                    }
                }
                if(!found)//name not found
                {
                    printf("Error : Name not found\n");
                    printf("Attempts left : %d\n",i - 1);
                    i--;
                }
                else
                {
                    return;
                }
                break;
            case '2':
                 //serach phone number by calling serachphone() function
                 index = searchphone(addressBook);
                 if(index != -1)
                 {
                    //print details if matched
                    printf("%s %s %s\n",addressBook->contacts[index].name,
                            addressBook->contacts[index].phone,
                            addressBook->contacts[index].email);
                    return;//return nothing & terminate the function
                 }
                 else
                 {
                    //not found
                    printf("Error : Phone number not found\n");
                    printf("Attempts left : %d\n",i - 1);
                    i--;
                 }
                 break;
            case '3':
                //seach email by calling searchemail() function
                index = searchemail(addressBook);
                if(index != -1)
                {
                    //print details if matched
                    printf("%s %s %s\n",addressBook->contacts[index].name,
                            addressBook->contacts[index].phone,
                            addressBook->contacts[index].email);
                    return;//return nothing and function terminated
                }
                else
                {
                    //not found
                   printf("Error : Email not found\n");
                   printf("Attempts left : %d\n",i - 1);
                   i--;
                }
                break;
            case '4'://exit function
                printf("Exiting search contact...\n");
                break;
            default : //invalid option
                printf("Error : Invalid option\n");
                printf("Choose valid option\n");
        }
    }while(opt != '4' && i > 0);  //two chances to search 
}



//function definition for edit contact
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char opt,edit;
    //MENU
    printf("\n**MENU**\n--------\n1. Name\n2. Phone\n3. Email\n4. Exit\nEnter your choice: ");
    scanf(" %c", &opt);//ask user to choose option 

    int index = -1;
    switch(opt)
    {
        case '1':
            //serach name by calling serachphone() function
            index = searchname(addressBook);
            break;
        case '2':
            //serach phone number by calling serachphone() function
            index = searchphone(addressBook);
            break;
        case '3':
             //serach email by calling serachphone() function
            index = searchemail(addressBook);
            break;
        case '4'://exit function
            printf("edit contact exiting...\n");
            return;
        default://invalid choice
            printf("Invalid choice.\n");
            return;//terminate function
    }

    if(index < 0)//contact not found
    {
        printf("Contact not found!\n");
        return;
    }

    //printf details if contact found
    printf("\n**Contact to edit**\n------------------\nName : %s\nPhone : %s\nEmail : %s\n",
           addressBook->contacts[index].name,
           addressBook->contacts[index].phone,
           addressBook->contacts[index].email);
    

    int valid;//MENU
    printf("\n**Edit by**\n-----------\n1. All \n2. Name \n3. Phone \n4. Email \n5. Exit \nEnter your choice: ");
    scanf(" %c", &edit);//ask user to choose option
    char name[100];
    char phone[20];
    char email[100];

    switch(edit)
    {
        case '1':
            do
            {
                //ask user to enter new name to replace
                printf("Enter name: ");
                scanf(" %[^\n]",name);
                //valiadate name by calling validname() function
                valid = validname(name);
                if(valid)
                {
                    //if name is valid replace old name with new name by calling strcpy()
                    strcpy(addressBook->contacts[index].name,name);
                }
                else
                {
                    //invalid name enterd
                    printf("Error : Invalid name\n");
                    continue;
                }

                //ask user enter new phone to replace 
                printf("Enter phone number: ");
                scanf(" %[^\n]",phone);
                //validate phone number by calling validphone() function
                valid = validphone(phone,addressBook);
                if(valid)
                {
                    //if phone number is valid replace old phone number with new phone number by calling strcpy()
                    strcpy(addressBook->contacts[index].phone,phone);
                }
                else
                {  //invalid phone number enterd
                    printf("Error : Invalid phone number\n");
                    continue;
                }


                //ask user enter new email to replace 
                printf("Enter email: ");
                scanf(" %[^\n]",email);
                //validate email by calling validemail() function
                valid = validemail(email,addressBook);
                if(valid)
                {
                    //if phone number is valid replace old phone number with new phone number by calling strcpy()
                    strcpy(addressBook->contacts[index].email,email);
                    printf("All edited successfully\n");
                }
                else
                {//invalif email entered
                    printf("Error : Invalid email\n");
                }

            }while(!valid);
            break;
        case '2':
            do
            {
                //ask user to enter new name to replace
                printf("Enter name: ");
                scanf(" %[^\n]",name);
                //valiadate name by calling validname() function
                valid = validname(name);
                if(valid)
                {
                    //if name is valid replace old name with new name by calling strcpy()
                    strcpy(addressBook->contacts[index].name,name);
                    printf("Name edited successfully\n");
                }
                else
                {
                    //invalid name enterd
                    printf("Error : Invalid name\n");
                }
            }while(!valid);
            break;
        case '3':
            do
            {
                //ask user enter new phone to replace 
                printf("Enter phone number: ");
                scanf(" %[^\n]",phone);
                //validate phone number by calling validphone() function
                valid = validphone(phone,addressBook);
                if(valid)
                {
                    //if phone number is valid replace old phone number with new phone number by calling strcpy()
                    strcpy(addressBook->contacts[index].phone,phone);
                    printf("Phone number edited successfully\n");
                }
                else
                {  //invalid phone number enterd
                    printf("Error : Invalid phone number\n");
                }
            }while(!valid);
            break;
        case '4':
            do
            {
                //ask user enter new email to replace 
                printf("Enter email: ");
                scanf(" %[^\n]",email);
                //validate email by calling validemail() function
                valid = validemail(email,addressBook);
                if(valid)
                {
                    //if phone number is valid replace old phone number with new phone number by calling strcpy()
                    strcpy(addressBook->contacts[index].email,email);
                    printf("Email edited successfully\n");
                }
                else
                {//invalif email entered
                    printf("Error : Invalid email\n");
                }
            }while(!valid);
            break;;
        case '5'://exit function
            printf("Edit contact exiting...\n");
            return;
        default:
            printf("Invalid choice.\n");
            return;//terminate function
    }
}

//function definition for delete contact
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char delete;//MENU
    printf("\n**Delete by**\n-------------\n1. Name \n2. Phone \n3. Email\n4. Exit\nEnter your choice: ");
    scanf(" %c", &delete);//ask user to choose option

    int index = -1;
    switch(delete)
    {
    case '1':
        //search name by calling searchname() function
        index = searchname(addressBook);
        break;
    case '2':
         //search phone number by calling searchphone() function
        index = searchphone(addressBook);
        break;
    case '3':
        //search email by calling searchemail() function
        index = searchemail(addressBook);
        break;
    case '4'://exit function
        printf("Delete contact exiting...\n");
        return;
    default:
        printf("Invalid choice.\n");
        return;//terminate function
    }

    if(index < 0)
    {
        //contact not found
        printf("Contact not found!\n");
        return;
    }

    //printf details if contact found
    printf("\n**Delete contact**\n-----------------\nName : %s \nPhone : %s \nEmail : %s\n",
           addressBook->contacts[index].name,
           addressBook->contacts[index].phone,
           addressBook->contacts[index].email);


    char confirm;
    printf("\nConfirm delete (Y/N): ");
    scanf(" %c", &confirm);//ask user to comform for deletion

    if(confirm == 'Y' || confirm == 'y')
    {
        //detelet contact by shiting left the all contacts from matched index
        for(int i = index; i < addressBook->contactCount; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;//after deletion decrement thr contact count
        printf("Contact deleted successfully.\n");
        return ;
    }
    else
    {
        //if user enter any other deteletion canceled
        printf("Deletion canceled.\n");
    }
}
