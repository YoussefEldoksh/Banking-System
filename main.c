#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define maxaccount 100

/* File pointers for various file operations */
FILE*f1;        /*pointer to users file*/
FILE*f2;        /*pointer to accounts file*/
FILE*f3;        /*pointer to any other file needed*/


/* Global variables */
int n = 100;
int counter_accounts = 0;
int num_users = 0;

/* Structure to store user credentials */
typedef struct
{
    char username[20];    /* Username of the user */
    char password[10];    /* Password of the user */

} sign_in;

/* Structure to store date information */
typedef struct
{
    int month;    /* Month (1-12) */
    int year;     /* Year */
} date;


/* Structure to represent an account */
typedef struct
{
    char account_number[11];    /* Account number (10 digits) */
    char name[30];            /* Account holder's name */
    char mobile[12];         /* Mobile number of the account holder */
    char email[40];         /* Email address of the account holder */
    float balance;         /* Current balance in the account */
    date dop;             /* Date of opening account */
} account;

account accounts[100];   /* Array to store account information */

/* Function to validate username and password */
int pass_validate(sign_in *users)
{
    int i=0;

    char username[20];
    printf("Enter username: ");
    scanf("%s",username);

    char password[10];
    printf("Enter password: ");
    scanf("%s",password);


    for(i=0; i<num_users; i++)
    {
        if(strcmp(username,users[i].username) == 0)
        {
            if(strcmp(password,users[i].password) == 0)
            {
                printf("Authentication Successful.\n");
                return 1;
            }
            else
            {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    return 0;
}

/* Function to save account data to a file */
void save()
{
    int i;
    f2=fopen("accounts.txt","w");

    if(f2 == NULL)
    {
        printf("File not in the system.");
        return;
    }

    if(counter_accounts==0)
        return;
    for(i=0; i<counter_accounts; i++)
    {
        fprintf(f2,"%s,%s,%s,%.2f,%s,%d-%d\n",accounts[i].account_number,accounts[i].name,accounts[i].email,accounts[i].balance,accounts[i].mobile,accounts[i].dop.month,accounts[i].dop.year);
    }

    printf("The data has been saved.\n");
    fclose(f2);
    return;

}


/* Function to load account data from a file */
void load()
{
    f2 = fopen("accounts.txt", "r");
    int i=0;
    char accounts_arr[100];
    char delim2[]=",-\n";
    char*token2;
    if(f2==NULL)
    {
        printf("The file was not found");
        quit();
    }
    counter_accounts=0;

    while(fgets(accounts_arr,100, f2) != NULL )
    {

        token2=strtok(accounts_arr,delim2);

        while(token2 != NULL)
        {

            strcpy(accounts[i].account_number, token2);
            token2 = strtok(NULL, delim2);

            strcpy(accounts[i].name,token2);
            token2 = strtok(NULL, delim2);

            strcpy(accounts[i].email, token2);
            token2 = strtok(NULL, delim2);

            accounts[i].balance = atof(token2);
            token2 = strtok(NULL, delim2);

            strcpy(accounts[i].mobile,token2);
            token2 = strtok(NULL, delim2);

            accounts[i].dop.month = atoi(token2);
            token2 = strtok(NULL, delim2);

            accounts[i].dop.year = atoi(token2);
            token2 = strtok(NULL, delim2);
        }
        i++;
        counter_accounts++;
    }
    fclose(f2);
}



/* Function to convert month number to month name */
char* month_convert(int month_num)
{
    char * month = malloc(14);

    switch(month_num)
    {
    case 1:
        strcpy(month,"January");

        break;
    case 2:
        strcpy(month,"February");

        break;
    case 3:
        strcpy(month,"March");

        break;
    case 4:
        strcpy(month,"April");

        break;
    case 5:
        strcpy(month,"May");

        break;
    case 6:
        strcpy(month,"June");

        break;
    case 7:
        strcpy(month,"July");

        break;
    case 8:
        strcpy(month,"August");

        break;
    case 9:
        strcpy(month,"September");

        break;
    case 10:
        strcpy(month,"October");
        break;
    case 11:
        strcpy(month,"November");
        break;
    case 12:
        strcpy(month,"December");
        break;
    }
    return month;
}


/* Function to add a new account */
void add()
{
    int i,j,back_option;
    time_t t=time(0);
    struct tm date =*localtime(&t);
    account newaccount;
    f2=fopen("accounts.txt","a");
    printf("Enter a new account number of 10 digits: ");
    scanf("%s",newaccount.account_number);
    for(i=0; i<counter_accounts; i++)
    {
        while(accnum_validate(newaccount.account_number) != 1 || strcmp(accounts[i].account_number,newaccount.account_number)==0 || strlen(newaccount.account_number)!=10)            /*duplicate account number and account number length*/
        {

            printf("The account number invalid!\nPlease enter a unique, 10 digit account number: ");
            scanf("%s",newaccount.account_number);

        }
    }
    printf("Enter name of new client: ");
    char name[20];
    getchar();
    gets(name);

    /*make first letter in each name uppercase*/

    if(name[0]>='a'&& name[0]<='z')
    {
        name[0]-=32;
    }
    for(j=1; name[j]!='\0'; j++)
    {
        if(name[j]<='Z'&& name[j]>='A')
        {
            name[j]+=32;
        }
        else if(name[j] == ' ' && name[j+1]>='a'&& name[j+1]<='z')
        {
            name[j+1]-=32;
            j++;
        }

    }
    printf("%s",name);
    strcpy(newaccount.name,name);


    printf("Enter E-mail of client: ");
    scanf("%s",newaccount.email);

    while(validate_email(newaccount.email) != 1)
    {
        printf("Invalid email. please enter a valid email in format example@example.com \n");
        printf("Enter E-mail of client: ");
        scanf("%s",newaccount.email);
        validate_email(newaccount.email);
    }

    printf("Enter balance: ");
    scanf("%f",&newaccount.balance);
    while(newaccount.balance <= 0)
    {
        printf("Please enter a valid balance.\n");
        printf("Enter balance: ");
        scanf("%f",&newaccount.balance);
    }
    printf("Enter phone number of client: ");
    scanf("%s",newaccount.mobile);
    while(mobile_validate(newaccount.mobile)!= 1 || strlen(newaccount.mobile) != 11)
    {
        printf("Invalid mobile number. please enter a valid mobile number. \n");
        printf("Enter mobile number of client: ");
        scanf("%s",newaccount.mobile);
    }
    printf("Current date is %d-%d:\n",date.tm_mon+1,date.tm_year+1900);
    int option;
    do
    {
        printf("Do you want to save the changes? 1:save 2:discard\n");
        scanf("%d",&option);
    }
    while(option!=1 && option!=2);
    if(option==1)
    {
        fprintf(f2,"%s,%s,%s,%.2f,%s,%d-%d\n",newaccount.account_number,newaccount.name,newaccount.email,newaccount.balance,newaccount.mobile,date.tm_mon+1,date.tm_year+1900);
        fclose(f2);
        load();
        return;
    }

    return;
}


/* Function to withdraw money from an account */
void withdraw()
{
    float amount;
    int i;
    char account_number[15];
    while(1)
    {
        printf("Enter a valid account number:");
        scanf("%s",account_number);
        for(i=0; i<n; i++)
        {
            if(strcmp(account_number,accounts[i].account_number)==0)
            {
                break;
            }
        }
        if(i==counter_accounts)
        {
            printf("Error. Account number is invalid.\n");
            return;
        }
        else
            break;
    }

    do
    {
        printf("Enter amount to be withdrawn: ");
        scanf("%f",&amount);
    }
    while(amount<=0);
    for(i=0; i<counter_accounts; i++)
    {
        if(strcmp(accounts[i].account_number,account_number)==0)
        {
            if(amount<=accounts[i].balance)
            {
                if (amount<=10000)
                {
                    accounts[i].balance-=amount;
                    printf("Transaction successful.\n");
                    break;
                }
                else
                {
                    printf("Transaction failed. Please enter a number less than 10000$.\n");
                    return;
                }
            }
            else
            {
                printf("Transaction failed. amount enter is in valid.");
                return;

            }
        }
    }

    save();

    char extention[] = ".txt";
    char file_name[16] ;
    strcpy(file_name,account_number);
    f3 = fopen(strcat(file_name,extention),"a");

    time_t t=time(0);
    struct tm date =*localtime(&t);

    fprintf(f3, "%d-%d-%d | %d:%d | Withdrawal from account | $%.2f\n",date.tm_mon + 1,date.tm_mday, date.tm_year + 1900, date.tm_hour, date.tm_min, amount);
    fclose(f3);

    return;
}

/* Function to deposit money into an account */
void deposit()
{
    float amount;
    int option;
    int i;
    char account_number[11];

    while(1)
    {
        printf("Enter a valid account number:");
        scanf("%s",account_number);
        for(i=0; i<n; i++)
        {
            if(strcmp(account_number,accounts[i].account_number)==0)
            {
                break;
            }
        }
        if(i==counter_accounts)
        {
            printf("Error. Account number is invalid.\n");
            return;
        }
        else
            break;
    }


    do
    {
        printf("Enter amount to be deposited: ");
        scanf("%f",&amount);
    }
    while(amount<=0 );
    for(i=0; i<counter_accounts; i++)
    {
        if (amount<=10000)
        {
            accounts[i].balance+=amount;
            printf("Transaction successful.\n");
            break;
        }
        else
        {
            printf("Transaction failed. Please enter a number less than 10000$.\n");
            return;

        }
    }

    save();

    char extention[] = ".txt";
    char file_name[16];
    strcpy(file_name,account_number);
    f3 = fopen(strcat(file_name,extention),"a");

    time_t t=time(0);
    struct tm date =*localtime(&t);

    fprintf(f3, "%d-%d-%d | %d:%d | Deposit to account | $%.2f\n",date.tm_mon + 1,date.tm_mday, date.tm_year + 1900, date.tm_hour, date.tm_min, amount);
    fclose(f3);

    return;
}


/* Function to transfer money between accounts */
void transfer()
{
    char sender[15],receiver[15];
    int i,j;

    while(1)
    {
        printf("Enter a valid account number for the sender:");
        scanf("%s",sender);
        for(i=0; i<n; i++)
        {
            if(strcmp(sender,accounts[i].account_number)==0)
            {
                break;
            }
        }
        if(i==n)
        {
            printf("Error. Account number is invalid.\n");
            return;
        }

        else
            break;
    }

    while(1)
    {
        printf("Enter a valid account number for the receiver:");
        scanf("%s",receiver);
        for(j=0; j<counter_accounts; j++)
        {
            if(strcmp(receiver,accounts[j].account_number)==0)
            {
                break;
            }
        }

        if(j==counter_accounts)
        {
            printf("Error. Account number is invalid.\n");
            break;
        }
        else
            break;
    }

    if(i==j)   /*check is same account*/
    {
        printf("Can't transfer from an account to itself.\n");
        return;
    }

    float amount;
    printf("Enter amount to be transferred:");
    scanf("%f",&amount);
    while(amount>accounts[i].balance || accounts[i].balance <= 0)
    {
        printf("Invalid amount, transaction failed.\n");
        printf("Please, enter an amount within the limit.\n");
        printf("Enter amount to be transferred:");
        scanf("%f",&amount);
    }

    if(amount<=accounts[i].balance)
    {
        accounts[i].balance-=amount;
        accounts[j].balance+=amount;
        printf("Transfer was successful.\n");
        save();
    }

    char extention[] = ".txt";
    char file_name[16];
    strcpy(file_name,sender);
    f3 = fopen(strcat(file_name,extention),"a");

    time_t t=time(0);
    struct tm date =*localtime(&t);

    fprintf(f3, "%d-%d-%d | %d:%d | Transfered to a friend | $%0.2f\n",date.tm_mon + 1,date.tm_mday, date.tm_year + 1900, date.tm_hour, date.tm_min, amount);

    fclose(f3);
    file_name[16];
    strcpy(file_name,receiver);
    f3 = fopen(strcat(file_name,extention),"a");

    fprintf(f3, "%d-%d-%d | %d:%d | Received from a friend | $%0.2f\n",date.tm_mon + 1,date.tm_mday, date.tm_year + 1900, date.tm_hour, date.tm_min, amount);
    fclose(f3);

    return;
}

/* Function to modify account information */
void modify()
{
    char account_number[11];
    int choice,i=0;
    printf("Enter account number: ");
    scanf("%s",account_number);
    while(strcmp(accounts[i].account_number,account_number) != 0)
    {
        printf("Invalid account number.");
        printf("Enter account number: ");
        scanf("%s",account_number);
    }



    while(i<counter_accounts)
    {
        if(strcmp(account_number,accounts[i].account_number)==0)
        {
            printf("Do you want to change the name?press 1:yes or 0:no\n");
            scanf("%d",&choice);

            while(choice != 1 && choice != 0)
            {

                printf("Please, Enter a valid choice: ");
                scanf("%d",&choice);
            }

            if(choice == 1)
            {
                char new_name[30];
                int j;
                printf("Enter the new name: ");
                getchar();
                gets(new_name);
                if(new_name[0]>='a'&& new_name[0]<='z')
                {
                    new_name[0]-=32;
                }
                for(j=1; new_name[j]!='\0'; j++)
                {
                    if(new_name[j] == ' '&&new_name[j+1]<='z'&& new_name[j+1]>='a')
                    {
                        new_name[j+1]-=32;
                    }
                }

                strcpy(accounts[i].name,new_name);
            }

            printf("Do you want to change the mobile?press 1:yes or 0:no\n");

            scanf("%d",&choice);

            while(choice != 1 && choice != 0)
            {
                printf("Please, Enter a valid choice: ");

                scanf("%d",&choice);


            }

            if(choice == 1)
            {

                char new_mobile[12];
                printf("Enter the new mobile number: ");
                scanf("%s",new_mobile);
                while(mobile_validate(new_mobile)!= 1 || strlen(new_mobile) != 11)
                {
                    printf("Invalid mobile number. please enter a valid mobile number \n");
                    printf("Enter mobile number of client: ");
                    scanf("%s",new_mobile);
                }

                strcpy(accounts[i].mobile,new_mobile);

            }

            printf("Do you want to change the email address?press 1:yes or 0:no\n");
            scanf("%d",&choice);

            while(choice != 1 && choice != 0)
            {
                printf("Please, Enter a valid choice: ");
                scanf("%d",&choice);
            }
            if(choice == 1)
            {
                char new_email[40];
                printf("Enter the new email: ");
                scanf("%s",new_email);
                while(validate_email(new_email) != 1)
                {
                    printf("Invalid email. please enter a valid email in format example@example.com \n");
                    printf("Enter E-mail of client: ");
                    scanf("%s",new_email);
                }
                strcpy(accounts[i].email,new_email);
            }
        }
        i++;
    }

    printf("Do you want to save the changes? 1:yes or 0:no\n");
    scanf("%d",&choice);

    while(choice != 1 && choice != 0)
    {
        printf("Please, Enter a valid choice: ");
        scanf("%d",&choice);
    }
    if(choice==1)
    {
        save();
    }
    if(choice==0)
    {
        printf("Changes discarded.\n");
        load();
    }
    return;
}


/* Function to delete an account */
void delete_account()
{
    char account_number[11];
    int flag = 0, i, num;
    printf("Please enter the account number you would like to delete:\n");
    scanf("%s", account_number);
    for(i=0; i<counter_accounts; i++)
    {
        if(strcmp(accounts[i].account_number,account_number)==0)
        {
            flag = 1;
            num=i;
            for(i=num ; i<counter_accounts; i++)
            {
                accounts[i] = accounts[i+1];
            }
            counter_accounts--;
            break;
        }
    }


    if(flag==0)
    {
        printf("The account number you have entered wasn't found\n");
        return;

    }
    save();
    return;

}


/* Function to generate a transaction report for an account */
void report()
{
    int i=0,count=0;
    char account_number[15];
    char transactions[100][100];
    printf("Enter account number: ");
    scanf("%s",account_number);

    while(strlen(account_number)-4!= 10  && strcmp(accounts[i].account_number,account_number)!=0)
    {
        printf("Please, enter a valid account number: ");
        scanf("%s",account_number);
        i++;
    }
    i=0;

    char extention[] = ".txt" ;


    strcat(account_number,extention);

    f3 = fopen(account_number, "r");

    if (f3 == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while(fgets(transactions[count],100,f3)!=NULL)
    {
        count++;
    }
    for(i=count-1; i>=count-5 && i>=0; i--)
    {
        printf("%s",transactions[i]);
    }

    fclose(f3);
}

/* Function for advanced search based on a keyword */
void advanced_search()
{
    char keyword[40];
    int i=0,j, flag=0;
    printf("Enter keyword: ");
    scanf("%s",keyword);

    printf("\n");

    for(i=0; i<counter_accounts; i++)
    {
        if(strstr(accounts[i].name, keyword) || strstr(accounts[i].account_number, keyword) || strstr(accounts[i].email, keyword))
        {
            flag=1;
            printf("Account Number: %s\n", accounts[i].account_number);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].email);
            printf("Balance: %.2f$\n",accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            printf("Date opened: %s-%d\n", month_convert(accounts[i].dop.month), accounts[i].dop.year);
            printf("\n");

        }
    }


    if(keyword[0]>='a'&& keyword[0]<='z')
    {
        keyword[0]-=32;
    }
    for(j=1; keyword[j]!='\0'; j++)
    {
        if(keyword[j]<='Z'&& keyword[j]>='A')
        {
            keyword[j]+=32;
        }
        else if(keyword[j] == ' ' && keyword[j+1]>='a'&& keyword[j+1]<='z')
        {
            keyword[j+1]-=32;
        }
    }



    for(j=0;j<counter_accounts;j++)
    {
        if(strstr(accounts[j].name, keyword)|| strstr(accounts[j].account_number, keyword) || strstr(accounts[j].email, keyword))
        {
            flag=1;
            printf("Account Number: %s\n", accounts[j].account_number);
            printf("Name: %s\n", accounts[j].name);
            printf("E-mail: %s\n", accounts[j].email);
            printf("Balance: %.2f$\n",accounts[j].balance);
            printf("Mobile: %s\n", accounts[j].mobile);
            printf("Date opened %s-%d\n", month_convert(accounts[j].dop.month), accounts[j].dop.year);
            printf("\n");
        }
    }


    if(flag==0)
    {
        printf("No accounts were found containing this keyword\n");
        return;
    }

    return;
}

/* Function to search for an account by account number */
void search()
{
    char account_number[11];
    int i, flag=0;
    printf("Enter the account number:");
    scanf("%s", account_number);
    for(i=0; i<n; i++)
    {
        if(strcmp(account_number, accounts[i].account_number)==0)
        {
            flag=1;
            printf("Account Number: %s\n", accounts[i].account_number);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].email);
            printf("Balance: %.2f$\n",accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            printf("Date opened %s-%d\n", month_convert(accounts[i].dop.month), accounts[i].dop.year);
            printf("\n");
            break;
        }
    }
    if(flag==0)
    {
        printf("invalid account number.\n");
        return;
    }

    return;
}

/* Function to sort accounts by name */
void sortByName()
{
    int n,j,pass,sorted=1; /*sorted flag, default is sorted*/
    int i=0;
    account temp;
    account copy_arr[counter_accounts];

    for(i=0; i<counter_accounts; i++)
    {
        copy_arr[i] = accounts[i];
    }


    for(pass=0; pass<counter_accounts; pass++)
    {
        /*
        Outer loop iterates through each element of the array.
        */
        sorted=0;
        for(j=0; j<counter_accounts-pass-1; j++)
        {
            /*
            Inner loop compares and swaps adjacent elements if they are in the wrong order.
            After each pass, the largest unsorted element reaches its correct position at the end.
            */
            if(strcmp(copy_arr[j].name,copy_arr[j+1].name)==1) /*Swap arr[j] and arr[j+1]*/
            {
                temp=copy_arr[j];
                copy_arr[j]=copy_arr[j+1];
                copy_arr[j+1]=temp;
                sorted=1;
            }

        }
        if(sorted==0)
            break;
    }

    /*Print the sorted accounts*/

    for(j=0; j<counter_accounts; j++)
    {
        printf("Account Number: %s\n",  copy_arr[j].account_number);
        printf("Name: %s\n", copy_arr[j].name);
        printf("E-mail: %s\n", copy_arr[j].email);
        printf("Balance: %.2f$\n", copy_arr[j].balance);
        printf("Mobile: %s\n", copy_arr[j].mobile);
        printf("Date opened: %d-%d\n", copy_arr[j].dop.month, copy_arr[j].dop.year);
        printf("\n");
    }
    return;
}



/* Function to sort accounts by balance */
void sortbybalance()
{
    int pass,j,i,sorted = 1; /*sorted flag, default is sorted*/
    account temp;

    account copy_arr[counter_accounts];

    for(i=0; i<counter_accounts; i++)
    {
        copy_arr[i] = accounts[i];
    }

    for(pass=0; pass<counter_accounts; pass++)
    {
        /*
        Outer loop iterates through each element of the array.
        */
        sorted = 0;
        for(j=0; j<counter_accounts - pass - 1; j++)
        {
            /*
             Inner loop compares and swaps adjacent elements if they are in the wrong order.
             After each pass, the largest unsorted element reaches its correct position at the end.
            */
            if(copy_arr[j].balance>copy_arr[j+1].balance)   /*Swap arr[j] and arr[j+1]*/
            {
                temp = copy_arr[j];
                copy_arr[j] = copy_arr[j+1];
                copy_arr[j+1] = temp;
                sorted = 1;
            }
        }
        if(sorted == 0)
            break;
    }
    /*Print the sorted accounts*/

    for(i=0; i<counter_accounts; i++)
    {
        printf("Account Number: %s\n", copy_arr[i].account_number);
        printf("Name: %s\n", copy_arr[i].name);
        printf("E-mail: %s\n", copy_arr[i].email);
        printf("Balance: %.2f$\n", copy_arr[i].balance);
        printf("Mobile: %s\n", copy_arr[i].mobile);
        printf("Date opened: %d-%d\n", copy_arr[i].dop.month,copy_arr[i].dop.year);
        printf("\n");
    }
    return;
}

/* Function to sort accounts by date of opening */
void sortbydate()
{
    int pass,j,i,sorted = 1; /*sorted flag, default is sorted*/
    account temp;

    account copy_arr[counter_accounts];

    for(i=0; i<counter_accounts; i++)
    {
        copy_arr[i] = accounts[i];
    }

    for(pass=0; pass<counter_accounts; pass++)
    {
        /*
        Outer loop iterates through each element of the array.
        */

        sorted = 0;
        for(j=0; j<counter_accounts - pass - 1; j++)
        {

            /*
            Inner loop compares and swaps adjacent elements if they are in the wrong order.
            After each pass, the largest unsorted element reaches its correct position at the end.
            */
            if(copy_arr[j].dop.year>copy_arr[j+1].dop.year)  /*Swap arr[j] and arr[j+1] if year greater*/
            {
                temp = copy_arr[j];
                copy_arr[j] = copy_arr[j+1];
                copy_arr[j+1] = temp;
                sorted = 1;
            }
            else if(copy_arr[j].dop.year==copy_arr[j+1].dop.year)
            {
                if(copy_arr[j].dop.month>copy_arr[j+1].dop.month)  /*Swap arr[j] and arr[j+1] if month greater*/
                {
                    temp = copy_arr[j];
                    copy_arr[j] = copy_arr[j+1];
                    copy_arr[j+1] = temp;
                    sorted = 1;
                }
            }
        }
        if(sorted == 0)
            break;
    }

    /*Print the sorted accounts*/

    for(i=0; i<counter_accounts; i++)
    {
        printf("Account Number: %s\n", copy_arr[i].account_number);
        printf("Name: %s\n", copy_arr[i].name);
        printf("E-mail: %s\n", copy_arr[i].email);
        printf("Balance: %.2f$\n", copy_arr[i].balance);
        printf("Mobile: %s\n", copy_arr[i].mobile);
        printf("Date opened: %d-%d\n", copy_arr[i].dop.month,copy_arr[i].dop.year);
        printf("\n");
    }
    return;
}


/* Function to print account information with sorting options */
void print()
{
    int choice,i;
    printf("1-Do you want to sort the data by name?\n2-Do you want to sort the data by date opened?\n3-Do you want to sort the data by balance?\n");
    scanf("%d",&choice);
    fflush(stdin);
    while(choice!=1 && choice!=2 && choice!=3)
    {
        printf("Please enter a valid option!\n1-Do you want to sort the data by name?\n2-Do you want to sort the data by date opened?\n3-Do you want to sort the data by balance?\n");
        scanf("%d",&choice);
        fflush(stdin);
    }
    if(choice==1)
    {
        sortByName();
        return;
    }
    else if(choice==2)
    {
        sortbydate();
        return;
    }
    else if(choice==3)
    {
        sortbybalance();
        return;
    }
    return;
}



/* Function to exit the program */
void quit()
{
    printf("Quitting...");
    exit(0);
}


/* Function to validate account number format */
int accnum_validate(char*account_number)
{
    int i;
    int asciivalue;
    for(i=0; account_number[i] != '\0'; i++)
    {
        asciivalue = (int)account_number[i] ;
        if(asciivalue<48 || asciivalue>57)
        {
            return 0;
        }
    }

    return 1;
}

/* Function to validate mobile number format */
int mobile_validate(char*mobile)
{
    int i;
    int asciivalue;
    for(i=0; mobile[i] != '\0'; i++)
    {
        asciivalue = (int)mobile[i] ;
        if(asciivalue<48 || asciivalue>57)
        {
            return 0;
        }

    }
    return 1;
}


/* Function to validate email format */
int validate_email(char *email)
{
    int i;
    int len=strlen(email);
    if(len<5)
        return 0;
    char *p=strchr(email,'@');
    char *s=strstr(email,".com");
    if(strchr(email,'@'))
    {
        if(strstr(email,".com") && s>(p+1))
            return 1;
        else
            return 0;
    }
    else return 0;
}



int main()
{
    char users_arr[100][100];

    char delim1[]=" \n";
    char*token1;


    f1 = fopen("users.txt","r");

    if(f1==NULL)
    {
        printf("The file of the users was not found");
        quit();
    }

    int i=0;
    int count;
    while(fgets(users_arr[count],100,f1)!=NULL)
    {
        count++;
    }
    sign_in users[count];

    while(i<count)
    {

        token1=strtok(users_arr[i],delim1);

        while(token1 != NULL)
        {

            strcpy(users[i].username, token1);
            token1 = strtok(NULL, delim1);

            strcpy(users[i].password, token1);
            token1 = strtok(NULL, delim1);

        }
        num_users++;
        i++;

    }
    fclose(f1);


    int choice1;
    printf("1-LOGIN\n2-QUIT\n");
    printf("Enter choice: ");
    scanf("%d",&choice1);
    fflush(stdin);


    int valid;
    while(choice1 != 1 && choice1 != 2)
    {
        printf("Please, enter a valid choice:");
        scanf("%d",&choice1);
        fflush(stdin);
    }


    if(choice1 == 1)
    {
        printf("LOGIN:\n");
        valid = pass_validate(users);
    }

    else if(choice1 == 2)
    {
        quit();
    }


    if(valid == 1)
    {
        load(accounts);

        int choice;
        while(1)
        {
            printf("Menu:\n");
            printf(" 1-ADD\n 2-DELETE\n 3-MODIFY\n 4-SEARCH\n 5-ADVANCED SEARCH\n 6-WITHDRAW\n 7-DEPOSIT\n 8-TRANSFER\n 9-REPORT\n 10-PRINT\n 11-QUIT\n 12-LOGOUT\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);

            while(choice>12 || choice<1)
            {
                printf("Please, enter a valid choice or press 12 to logout.\n");
                printf("Enter your choice: ");
                scanf("%d",&choice);
            }


            switch (choice)
            {
            case 1:
                add();
                break;
            case 2:
                delete_account();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                advanced_search();
                break;
            case 6:
                withdraw();
                break;
            case 7:
                deposit();
                break;
            case 8:
                transfer();
                break;
            case 9:
                report();
                break;
            case 10:
                print();
                break;
            case 11:
                quit();
                break;
            default:
                main();
                break;
            }
        }
    }

    else
    {
        printf("Wrong password or username.\n");
        main();

    }


    return 0;
}
