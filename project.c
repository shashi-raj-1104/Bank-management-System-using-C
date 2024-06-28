/*
Project title:-Online Bank Manegment system
Name: SHASHI RAJ
Roll_number: 2201EE64
Department: Electrical and Electronics Engineering
CS102 cource project under Dr. Satendra Kumar(CSE Department, IIT Patna) 
*/

#include <stdio.h>
#include <stdlib.h>                                     /*including header file to us dyanamic memory allocation*/       
#include <string.h>                                     /*including header file to use strcmp,strcpy function*/
#include <ctype.h>                                      /*including header file to use isdigit,isalnum function*/

/*functions prototype*/
void displaydatabase();
void databaseaccess();
void start();                                           
int isStringOnlyIntegers(const char *str);
int isValidPassword(const char *password);

/*functions defination*/
int isStringOnlyIntegers(const char *str)             /*function to check string containing integer or not*/
{
   for (int i = 0; str[i] != '\0'; i++)
   {
      if (!isdigit(str[i]))                           /*calling of isdigit function*/
      {                                               
         return 0;
      }
   }
   return 1;
}

int isValidPassword(const char *password)          /*function to check password is valid or not*/
{
   int length = strlen(password);

   if (length < 8)
   {
      return 0;                                    // Return 0 if Password length is less than 8 characters
   }

   int hasInteger = 0;
   int hasSymbol = 0;

   for (int i = 0; i < length; i++)
   {
      if (isdigit(password[i]))
      {
         hasInteger = 1;
      }
      else if (!isalnum(password[i]))           /*Condition to check password containing symbols*/
      {
         hasSymbol = 1;
      }
   }

   return (hasInteger * hasSymbol);             /*Return 1 for valid password otherwise 0*/
}

int b1 = 0, nou = 0, b2 = 0;                    /*Decleration of global variable*/
char a1, a2, a3;
char *s1, *masterkey;


typedef struct                                  /*Defination of user define datatype*/
{
   char username[50];
   int age;
   char gender[50];
   char passcode[30];
   char phone[15];
   char mail[50];
   int balance;
} account;

account user[100];                           /*Declaring array of 100 accounts called user*/

void displaydatabase()                       /*function to display user accounts detail*/
{
   for (int i = 0; i < 100; i++)
   {
      if (strcmp(user[i].username, "NEXT") != 0)
         printf("Account %i: username: %s, age: %i, gender: %s, passcode: %s, phone number: %s, mail id: %s, account balance: ₹%i\n", i + 1, user[i].username, user[i].age, user[i].gender, user[i].passcode, user[i].phone, user[i].mail, user[i].balance);
      else
         break;
   }
}

void databaseaccess()                                    /*function to access bank database*/
{
   if (b1 < 3)
   {
      printf("Enter masterkey: ");
      s1 = malloc(sizeof(char) * 20);
      scanf("%s", s1);
      if (strcmp(s1, masterkey) == 0)                    /*checking of entered masterkey*/
      {
         printf("Unlocked\n");
         displaydatabase();                              /*calling of displaydatabase function if entered masterkey is correct*/
         printf("Enter 'm' to go to main page\n");
         char h;
         scanf(" %c", &h);
         if (h == 'm')
            start();                                     /*after that function continues to main menu*/
      }
      else
      {
         printf("Wrong password\n");                     
         b1++;
         databaseaccess();                               /*calling of function*/
      }
   }
   else if (b1 == 3)                                     /*Employee can enter wrong password atmost 3 times*/
   {
      printf("Too many incorrect attempts\n");
      exit(0);                                           /*After maximum limit program will terminate*/
   }
}

void start()                                             
{
   masterkey = "AbcdEfg";                                /*creating masterkey: it will be required to access database*/
   printf("\nHI! WELCOME TO BANK\nPress 'e' if you're an employee or 'c' if you're a customer. Press 't' to exit  ");
   scanf(" %c", &a1);

   if (a1 == 'e')                                        // EMPLOYEE SEGMENT
   {
      printf("Enter 'a' to access database\nEnter 'b' to go back\n\n");
      scanf(" %c", &a2);
      if (a2 == 'b')
         start();
      if (a2 == 'a')
         databaseaccess();
   }

   else if (a1 == 't')                                  // EXIT
   {
      printf("\nThank you for visiting bank, have a lovely day\n");
      exit(0);
   }

   else if (a1 == 'c')                                 // CUSTOMER SEGMENT

   {
      printf("\nWELCOME\n");
      printf("Enter 'o' to open a bank account\nEnter 'a' to access the existing account\nEnter 'b' to go back\n\n");
      scanf(" %c", &a3);
      if (a3 == 'o')                                  /*loop to open new bank account*/
      {
         user[nou].balance = 0;
         char confirmation;
         printf("\nEnter username (preferably your full name): ");
         scanf(" %[^\n]", user[nou].username);        /*user name can be anything otherthan new line*/

         for (int i = 0; i < 100; i++)
         {
            int x = 0;
            for (int i = 0; i < nou; i++)
            {
               if (strcmp(user[i].username, user[nou].username) == 0)
               {
                  x++;
               }
            }
            if (x != 0)                                /*if username already exists*/
            {
               printf("\nAccount with this username already exists.");
               printf("\nEnter a different username: ");
               scanf(" %[^\n]", user[nou].username);
            }
            else
               break;
         }
         printf("Enter age: ");                                                  
         scanf("%d", &user[nou].age);                                               /*inputing age*/
         printf("Enter gender\nPress 'm' for male\nPress 'f' for female\n");       
         scanf("%s", user[nou].gender);                                             /*input gender*/
         for (int i = 0; i < 100; i++)
         {
            if (strcmp(user[nou].gender, "m") != 0 && strcmp(user[nou].gender, "f") != 0)     
            {
               printf("Enter a valid gender: ");                 /*if entered character is other than m and f*/ 
               scanf("%s", user[nou].gender);
            }
            else
              break;
         }
         printf("Enter passcode for the account (It must have at least 1 integer, 1 symbol and must be at least 8 characters long): ");
         scanf(" %s", user[nou].passcode);                                          /*input passcode*/
         for (int i = 0; i < 100; i++)
         {
            if (isValidPassword(user[nou].passcode) == 0)                  /*calling of function and ensuring that password is strong enough*/
            {
               printf("Enter a valid password: ");
               scanf(" %s", user[nou].passcode);
            }
            else
               break;
         }

         printf("Link your phone number to your account number: ");
         scanf(" %s", user[nou].phone);                                            /*input phone number*/
         for (int i = 0; i < 100; i++)
         {
            if (strlen(user[nou].phone) == 10 && isStringOnlyIntegers(user[nou].phone) != 0)       /*condition to check valid phone number*/
               break;
            else
               printf("Enter a valid phone number: ");            /*phone number is valid only if size is 10 and contains only integers*/
            scanf("%s", user[nou].phone);
         }

         printf("Link your email to your account: ");
         scanf(" %s", user[nou].mail);                                            /*input your mail*/

         printf("Would you like to deposit some money? y/n\n");
         scanf(" %c", &confirmation);                                             /*input amount to deposit (optional)*/

         for (int i = 0; i < 100; i++)
         {
            if (confirmation != 'y' && confirmation != 'n')
            {
               printf("Type y or n: ");
               scanf(" %c", &confirmation);
            }
            else if (confirmation == 'y')
            {
               printf("Enter amount to be deposited: ₹");
               scanf("%i", &user[nou].balance);
               break;
            }
            else
               break;
         }

         nou++;
         strcpy(user[nou].username, "NEXT");
         printf("\nYour bank account has been opened. Thank you for choosing our bank!\n");
         start();                                        
      }
      else if (a3 == 'b')
         start();                                        /*excution continues from main menu*/
      else if (a3 == 'a')                                /*to access existing account by user*/
      {
         char name[100], pass[100];
         int index, b3 = 0;
         printf("Enter username: ");
         scanf(" %[^\n]", name);
         for (int i = 0; i < 100; i++)
         {
            if (strcmp(user[i].username, name) == 0)        /*checking if username exists or not */
            {
               index = i;
               b3++;
               break;
            }
         }

         if (b3 != 0)                                       /*username exist*/
         {

            printf("Enter passcode: ");
            scanf("%s", pass);

            if (strcmp(user[index].passcode, pass) == 0)    /*condition to check for correct password*/
            {
               char v;
               printf("\n\nUnlocked\n");
               printf("username: %s\nage: %i\ngender: %s\npasscode: %s\nphone number: %s\nmail id: %s\naccount balance: ₹%i\n", user[index].username, user[index].age, user[index].gender, user[index].passcode, user[index].phone, user[index].mail, user[index].balance);
               printf("Enter 'w' to withdraw money, 'd' to deposit money, 'e' to edit account details, 'b' to go to start\n");
               scanf(" %c", &v);
               if (v == 'b')
                  start();
               else if (v == 'd')                         /*Deposit money */
               {
                  int v1;
                  printf("Enter amount: ₹");
                  scanf("%i", &v1);
                  user[index].balance += v1;
                  printf("Available balance: ₹%d", user[index].balance);
                  start();
               }
               else if (v == 'w')                        /*Withdrawal of money*/
               {
                  int v2;
                  printf("Enter amount: ₹");
                  scanf("%d", &v2);
                  if (v2 > user[index].balance)          /*condition to check for balance is sufficient or not*/
                  {
                     printf("\nInsufficient balance\n");
                     start();
                  }

                  else
                  {
                     user[index].balance = user[index].balance - v2;                   /*if balance is sufficient*/
                     printf("\nAvailable balance: ₹%d\n", user[index].balance);
                     start();
                  }
               }
               else if (v == 'e')                           /*Editing of account details*/
               {
                  char y;
                  printf("Enter 'u' to edit username.\nEnter 'p' to edit passcode.\nEnter 'n' to change linked phone number.\nEnter 'e' to edit linked e-mail.\nEnter 'b' to return to main menu.\n");
                  scanf(" %c", &y);
                  for (int i = 0; i < 100; i++)
                  {
                     if (y == 'u')                          /*editing username*/
                     {
                        char p1;
                        char z[100];
                        char new[100];
                        printf("Enter new username: ");
                        scanf(" %[^\n]", z);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z, user[index].username) == 0)             /*if username is same*/
                           {
                              printf("Same username.\nEnter new username: ");
                              scanf(" %[^\n]", z);
                           }
                           else
                           {

                              for (int i = 0; i < 100; i++)
                              {
                                 int x = 0;
                                 for (int i = 0; i < nou; i++)
                                 {
                                    if (strcmp(user[i].username, z) == 0)
                                    {
                                       x++;
                                    }
                                 }
                                 if (x != 0)                                     /*if entered username is matched with other users*/
                                 {
                                    printf("\nAccount with this username already exists.");
                                    printf("\nEnter a different username: ");
                                    scanf(" %[^\n]", z);
                                 }
                                 else
                                    break;
                              }

                              printf("Press 'c' to Confirm username.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p1);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p1 == 'c')
                                 {
                                    printf("confirm username: ");
                                    scanf(" %[^\n]", new);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new, z) == 0)                        /*comparision betwwen two string */
                                       {
                                          strcpy(user[index].username, new);           /*new username assign to user*/
                                          printf("Your username has been changed\n");
                                          start();                                     /*go back to start*/
                                          break;
                                       }
                                       else
                                       {
                                          printf("Username mismatch.\n");
                                          printf("confirm username: ");
                                          scanf(" %[^\n]", new);
                                       }
                                    }
                                 }
                                 else if (p1 == 'b')              /*go to start menu*/
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm username.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p1);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'p')               /*password change*/
                     {
                        char p2;
                        char z2[100];
                        char new2[100];
                        printf("Enter new passcode: ");
                        scanf(" %[^\n]", z2);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z2, user[index].passcode) == 0)
                           {
                              printf("Same passcode.\nEnter new passcode: ");
                              scanf(" %[^\n]", z2);
                           }
                           else
                           {
                              for (int i = 0; i < 100; i++)
                              {
                                 if (isValidPassword(z2) == 0)             /*check for valid password*/
                                 {
                                    printf("Enter a valid password: ");
                                    scanf(" %s", z2);
                                 }
                                 else
                                    break;
                              }
                              printf("Press 'c' to Confirm passcode.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p2);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p2 == 'c')
                                 {
                                    printf("confirm passcode: ");
                                    scanf(" %[^\n]", new2);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new2, z2) == 0)
                                       {
                                          strcpy(user[index].passcode, new2);             /*assign new password to user password*/
                                          printf("Your passcode has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("passcode mismatch.\n");
                                          printf("confirm passcode: ");
                                          scanf(" %[^\n]", new2);
                                       }
                                    }
                                 }
                                 else if (p2 == 'b')                 /*go to start menu*/
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm passcode.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p2);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'n')                  /*change linked phone number*/
                     {
                        char p3;
                        char z3[100];
                        char new3[100];
                        printf("Enter new phone number: ");
                        scanf(" %[^\n]", z3);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z3, user[index].phone) == 0)
                           {
                              printf("Same phone number.\nEnter new phone number: ");
                              scanf(" %[^\n]", z3);
                           }
                           else
                           {
                              for (int i = 0; i < 100; i++)
                              {
                                 if (strlen(z3) == 10 && isStringOnlyIntegers(z3) != 0)         /*condition to check valid phone number*/
                                    break;
                                 else
                                    printf("Enter a valid phone number: ");
                                 scanf("%s", z3);
                              }
                              printf("Press 'c' to Confirm phone number.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p3);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p3 == 'c')
                                 {
                                    printf("confirm phone number: ");
                                    scanf(" %[^\n]", new3);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new3, z3) == 0)
                                       {
                                          strcpy(user[index].phone, new3);
                                          printf("Your phone number has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("phone number mismatch.\n");
                                          printf("confirm phone number: ");
                                          scanf(" %[^\n]", new3);
                                       }
                                    }
                                 }
                                 else if (p3 == 'b')
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm phone number.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p3);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'e')                        /*change Email id linked to account*/
                     {
                        char p4;
                        char z4[100];
                        char new4[100];
                        printf("Enter new e-mail id: ");
                        scanf(" %[^\n]", z4);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z4, user[index].mail) == 0)
                           {
                              printf("Same e-mail id.\nEnter new e-mail id: ");
                              scanf(" %[^\n]", z4);
                           }
                           else
                           {

                              printf("Press 'c' to Confirm e-mail id.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p4);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p4 == 'c')
                                 {
                                    printf("confirm e-mail id");
                                    scanf(" %[^\n]", new4);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new4, z4) == 0)
                                       {
                                          strcpy(user[index].mail, new4);
                                          printf("Your e-mail id has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("e-mail id mismatch.\n");
                                          printf("confirm e-mail id: ");
                                          scanf(" %[^\n]", new4);
                                       }
                                    }
                                 }
                                 else if (p4 == 'b')              /*go back to start*/
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to e-mail id.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p4);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'b')                           /*go back to start*/
                        start();
                     else
                     {
                        printf("Invalid key\nEnter a valid key\n");
                        scanf("%c", &y);
                     }
                  }
               }
            }

            else
            {
               printf("Incorrect password\n");
               start();                                        /*go back to start*/
            }
         }

         else
         {
            printf("User not found\n");
            start();                                        /*go back to start*/
         }
      }

      else
      {
         printf("Invalid key\n");
         start();                                        /*go back to start*/
      }
   }
   else
   {
      printf("Invalid key\n");
      start();                                        /*go back to start*/         
   }
}

int main()                                            /*excution of program start from here*/
{
   start();
   return 0;
}