#include "file.h"
#include <stdio.h>

//function definition for save contacts to file 
void saveContactsToFile(AddressBook *addressBook) {
  FILE *fptr = fopen("contacts.csv","w");//open file in write mode

  //write contacts into file by using fprintf()
  fprintf(fptr,"#%d\n",addressBook->contactCount);
  for(int i = 0;i < addressBook->contactCount;i++)
  {
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name
                            ,addressBook->contacts[i].phone
                        ,addressBook->contacts[i].email);
  }

  //close file
  fclose(fptr);
}

//function definition for load contacts from file
void loadContactsFromFile(AddressBook *addressBook) {
    
  //open file in read mode
    FILE *fptr = fopen("contacts.csv","r");

    //check if file existing or not
    if(fptr == NULL)
    {
      printf("ERROR: Unable to open file for Saving\n");
      return;
    }

    //load all contacts structure array by using fscanf()
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name
                            ,addressBook->contacts[i].phone
                        ,addressBook->contacts[i].email);

    }

    //close file
    fclose(fptr);
}
