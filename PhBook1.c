 /* http://www.cs.bu.edu/faculty/homer/113/ */

 /*
  * File Name: PhBook1.c
  * Name: Asmatullah Yaree, Mohd Dzul Aiman, Nursuliza, Maryam Adinehnia
  * Assignment: 1
  * Problem: 1
  * Date: March 29, 2013
  *
  * This program utilizes a binary search tree to build and maintain
  * a small PhoneBook database. The serial numbers will serve as the
  * search keys for the binary search tree. Data will initially be
  * read from a file, and the user will be prompted with options
  * regarding what to do with the phonebook.
  */
 #include <stdio.h>
 #include <stdlib.h>
 #include "Ph1tree.h"
 //#include "Ph1tree.c"
 
 #define FNAME_MAX 50   /* maximum filename length */
 
 /*
  * TYPE DEFINITIONS
  */
 typedef treeElementT dataT;
 typedef treeKeyT serialNumT;
 
 /*
  * FUNCTION PROTOTYPES
  */
 void PrintInfoMainMenu(void);
 void InfoReadFromFile(treeADT tree);
 void InfoAdd(treeADT tree);
 void InfoUpdate(treeADT tree);
 void InfoDelete(treeADT tree);
 void InfoFind(treeADT tree);
 void InfoPrint(treeADT tree);
 
 /*
  * BEGIN MAIN PROGRAM
  */
 int main(void)
 {
    treeADT tree;  /* tree holding the phonebook information */
 
    char choice[2];   /* main menu choice */
    
    /* create a tree to hold the info. */
    tree = TreeCreate();
  
    InfoReadFromFile(tree);   /* read info from file */
    PrintInfoMainMenu();      /* print main menu */
    printf("Choice> ");
    scanf("%s", choice);
  
    while (choice[0] != 'q')
    {   
       switch (choice[0])
       { 
          case 'a':
             InfoAdd(tree);
             break;
          case 'd':
             InfoDelete(tree);
             break;
          case 'f':
             InfoFind(tree);
             break;
          case 'u':
             InfoUpdate(tree);
             break;
          case 'p':
             InfoPrint(tree);
             break;
          default:
             printf("Error!! Invalid Selection.\n");
             break;
       }
       
        printf("\n\nPress Enter for Main Menu\n");
        getchar(); getchar();
        PrintInfoMainMenu();      /* print main menu */
        printf("\nChoice> "); /* prompts for next selection */
        scanf("%s", choice); /* scans in choice */
    }
  
    printf("Bye! Thanks for using PhoneBook.\n"); /* Goodbye message */         
  
    TreeDestroy(tree);
    
    return 0;
 }
 /*
  * END MAIN PROGRAM
  */
 
 /*
  * Function: PrintInfoMainMenu
  * Usage: PrintInfoMainMenu();
  * ------------------------------
  * This procedure prints out the main menu options.
  */
 void PrintInfoMainMenu(void)
 {
    printf("--------- PhoneBook Data Inventory System V1.0--------\n");	
    printf("Please choose one of the following operations by typing its\n");
    printf("letter and then pressing <Return>:\n\n");
    printf("   a) Add an User info to the database.\n");
    printf("   d) Delete user from the database.\n");
    printf("   f) Find user in the database.\n");
    printf("   u) Update user info in the database.\n");
    printf("   p) Print user database.\n");
    printf("   q) Quit inventory.\n\n");
 }
 
 /*
  * Function: InfoReadFromFile
  * Usage: InfoReadFromFile(tree);
  * ---------------------------------
  * This procedure reads in user data file and adds
  * the user data to a binary search tree.
  */
 void InfoReadFromFile(treeADT tree)
 {
    dataT data;  /* data information */
    
    /* name of phonebook data file to be opened */
    //char filename[FNAME_MAX+1] = "/home/yaree/phone/phonebook.in";
    char filename[FNAME_MAX+1] = "phonebook_10_start6.txt";
    
    FILE *ifp;  /* input file pointer */
    
    printf("Initial user data read from file:\n");
    printf("\"%s\"\n\n",filename);
 
    /* attempt to open user data file for reading */
    ifp = fopen(filename, "r");
 
    /* print error message if unable to open data file */
    if (ifp == NULL)
    {
       printf("Error!! Unable to open phonebook database file.\n");
       exit(1);  /* exit, returning error code */
    }
    else
    {
       /* if file successfully opened, loop to read in user data */
       while (fscanf(ifp,"%d %s %d", &data.key, data.value.name, &data.value.number) == 3)
          TreeAdd(tree,data);  /* add user to tree */
 
       fclose(ifp);   /* close input file */
    }
 }
 
 /*
  * Function: InfoAdd
  * Usage: InfoAdd(tree);
  * ------------------------
  * This procedure prompts a user for a serial number, name, and Telephone Number 
  * and adds the user information to the binary search tree.
  */
 void InfoAdd(treeADT tree)
 {
    dataT data;  /* user information */
 
    printf("Please enter the serial number: ");
    while (scanf("%d",&data.key) == 0 || (data.key < 1) || (data.key > 100000))
    {
       printf("Error!! Serial number is invalid.\n");
       printf("Serial number must be an integer between 1 and 100000.\n");
       printf("Please enter the Serial number: ");
    }
 
    printf("Please enter the name: ");
    scanf("%s",data.value.name);
 
    printf("Please enter the telephone number ");
    while (scanf("%d",&data.value.number ) <= 0)
    {
       printf("Error!! Telephone Number is invalid.\n");
       printf("telephone number must be an integer.\n");
       printf("Please enter the telephone number: ");
    }
 
    TreeAdd(tree,data);  /* add user data to tree */
 }
 
  /*
  * Function: InfoUpdate
  * Usage: InfoUpdate(tree);
  * ------------------------
  * This procedure prompts a user for a serial number, name, and Telephone Number 
  * and updates the user information to the binary search tree.
  */
 void InfoUpdate(treeADT tree)
 {
    dataT data,  /* user information */
          *acctP;
    printf("Please enter the serial number: ");
    while (scanf("%d",&data.key) == 0 || (data.key < 1) || (data.key > 100000))
    {
       printf("Error!! Serial number is invalid.\n");
       printf("Serial number must be an integer between 1 and 100000.\n");
       printf("Please enter the Serial number: ");
    }
    
    /* check if user info exists in tree */
    acctP = TreeFind(tree,data.key);
    PrintElement(*acctP,stdout);
    
    printf("\nPlease enter the name: ");
    scanf("%s",data.value.name);
 
    printf("Please enter the telephone number ");
    while (scanf("%d",&data.value.number ) <= 0)
    {
       printf("Error!! Telephone Number is invalid.\n");
       printf("telephone number must be an integer.\n");
       printf("Please enter the telephone number: ");
    }
 
    TreeAdd(tree,data);  /* add user data to tree */
 }
 
 /*
  * Function: InfoDelete
  * Usage: InfoDelete(tree);
  * ---------------------------
  * This procedure prompts the user for an user info. It then
  * searches for the serial number in the tree. If it is found, it
  * will remove the user information from the tree and print it.
  * If not, it will just print an error message.
  */
 void InfoDelete(treeADT tree)
 {
    serialNumT serial_num;   /* serial number */
    dataT data,    /* user information */
             *acctP;     /* pointer to a user info */
 
    printf("Enter serial number to be deleted: ");
    while (scanf("%d",&serial_num) == 0 || (serial_num < 1) || (serial_num > 100000))
    {
       printf("Error!! Serial number is invalid.\n");
       printf("Serial Number must be an integer between 1 and 100000.\n");
       printf("Enter serial number of the user to be deleted: ");
    }
 
    /* check if user info exists in tree */
    acctP = TreeFind(tree,serial_num);
 
    /* if user info does not exist, print an error message */
    if (acctP == NULL)
       printf("Error!! Serial number \"%d\" does not exist in database.\n", serial_num);
    else
    {
       /* if user exists, delete it from the tree and print its information */
       data = TreeDelete(tree,serial_num);   /* delete data from tree */
       printf("The following user information was deleted:\n");
       PrintElement(data,stdout); 
    }
 }
 
 /*
  * Function: InfoFind
  * Usage: InfoFind(tree);
  * -------------------------
  * This procedure prompts the user for an serial number and
  * attempts to find it in the tree. If it is found, it will
  * print out the phonebook information. If not, it will just
  * print an error message.
  */
 void InfoFind(treeADT tree)
 {
    serialNumT serial_num;   /* serial number */
    dataT *dataP;  /* pointer to a user info */
 
    printf("Enter the serial number to be found: ");
    while (scanf("%d",&serial_num) == 0 || (serial_num < 1) || (serial_num > 100000))
    {
       printf("Error!! Serial number is invalid.\n");
       printf("Serial number must be an integer between 1 and 100000.\n");
       printf("Enter the serial number to be found: ");
    }
 
    /* check if data exists in tree */
    dataP = TreeFind(tree,serial_num);
 
    if (dataP == NULL)
       printf("Error!! Serial number \"%d\" not found.\n", serial_num);
    else
       PrintElement(*dataP,stdout);
 }
 
 /*
  * Function: InfoPrint
  * Usage: InfoPrint(tree);
  * --------------------------
  * This procedure prompts the user whether to print the phonebook
  * database to the screen or to a file and then prints out each
  * user information using preorder traversal of the tree.
  */
 void InfoPrint(treeADT tree)
 {
    char choice[5];   /* string holding user's choice */
    
    FILE *ofp;  /* output file pointer */
 
    printf("Please choose where the user information should\n");
    printf("be printed and hit <Return>:\n\n");
    printf("   s) Print to screen\n");
    printf("   f) Print to file \"phonebook.out\"\n");
    printf("   r) Return to Main Menu prompt.\n\n");
    printf("Print Choice> ");
    scanf("%s",choice);
 
    while (choice[0] != 'r')
    {
       switch (choice[0])
       {
          case 's':
             TreePrint(tree,stdout);   /* print to the screen */
             return;  /* exit function */
          case 'f':
             ofp = fopen("phonebook.out", "w");   /* attempt to open file for writing */
             TreePrint(tree,ofp);   /* print out tree elements to file */
             fclose(ofp);    /* close output file */
             return;  /* exit function */
          default:
             printf("Invalid selection.\n");
             break;
       }
       printf("\nPrint Choice> ");
       scanf("%s",choice);
    }
 }
   /*
   * Printing to "phonebook.out" should have been done automatically
   * as last thing program does.  --TF
   */
 
 /*
  * Function: PrintElement
  * ----------------------
  * This procedure prints out the elements of the tree.
  */
 void PrintElement(dataT data, FILE *outfileP)
 {
    fprintf(outfileP,"Serial Number: %d\n", data.key);
    fprintf(outfileP,"User Name: %s\n", data.value.name);
    fprintf(outfileP,"Telephone Number: %d\n\n", data.value.number);
 }
 
