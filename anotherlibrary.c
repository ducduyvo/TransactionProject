#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "anotherlibrary.h"


int get_file_size(FILE *file)
{
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    size = size / sizeof(transaction);

    return size;
}

int findSize(transaction *arr)
{
    int count = 0;
    while (arr[count].m_amount > 0.0 && (arr[count].m_type == 1 || arr[count].m_type == -1))
        count++;
    //arr[count+1].m_amount=0.0;
    printf("size of structure: %d\n", count);
    return count;
}

void fixString(char *str)
{
    if (str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }
}

int toInt(char *str, int size)
{
    int amount;

    fgets(str, size, stdin);
    fixString(str);
    while ((sscanf(str, "%d", &amount) != 1) || amount <= 0)
    {

        printf("Invalid.\n");
        fgets(str, size, stdin);
        fixString(str);
    }

    return amount;
}
float toFloat(char *str, int size)
{
    float amount;

    fgets(str, size, stdin);
    fixString(str);
    while ((sscanf(str, "%f", &amount) != 1) || amount <= 0)
    {

        printf("Invalid.\n");
        fgets(str, size, stdin);
        fixString(str);
    }

    return amount;
}
void clearFile(char *fileName)
{
    FILE *file;
    file = fopen(fileName, "wb");
    if (file == NULL)
    {
        printf("Unable to open %s\n", fileName);
    }
    fclose(file);
}
void deleteTransaction(char *fileName1)
{
    FILE *file1;
    FILE *file2;
    char fileName2[SIZE] = "out_file.txt";
    transaction *read = malloc(sizeof(transaction));
    file1 = fopen(fileName1, "rb");
    if (file1 == NULL)
    {
        printf("Unable to open %s\n", fileName1);
    }
    else
    {
        file2 = fopen(fileName2, "wb");
        if (file2 == NULL)
        {
            printf("Unable to open %s\n", fileName2);
        }
        else
        {
            int size = get_file_size(file1);
            if (size > 0)
            {
                int index = 0;
                char str[liSIZE];
                printf("Enter the element to (%d-%d) delete: ", 1, size);
                index = toInt(str, liSIZE);
                printf("size = %d\n", size);
                printf("index = %d\n", index);

                while (index > size || index < 1)
                {
                    printf("Element is invalid\n");
                    index = toInt(str, liSIZE);
                }

                int count = 1;
                while (!feof(file1))
                {
                    if (fread(read, sizeof(transaction), 1, file1) == 1)
                    {
                        if (count != index)
                        {
                            fwrite(read, sizeof(transaction), 1, file2);
                        }
                        count++;
                    }
                }
            }

            else
            {
                printf("Nothing to delete.\n");
            }
            fclose(file2);
        }
        fclose(file1);
    }
    file1 = fopen(fileName1, "wb");

    if (file1 == NULL)
    {
        printf("Unable to open %s\n", fileName1);
    }
    else
    {
        file2 = fopen(fileName2, "rb");
        if (file2 == NULL)
        {
            printf("Unable to open %s\n", fileName2);
        }
        else
        {
            int count = 0;
            int size2 = get_file_size(file2);
            printf("sizeo file %d", size2);

            while (!feof(file2))
            {
                if (fread(read, sizeof(transaction), 1, file2) == 1)
                {
                    fwrite(read, sizeof(transaction), 1, file1);
                    count++;
                }
            }
        }
        fclose(file2);
    }

    free(read);
    fclose(file1);
}

void getDate(char *date)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strcpy(date, asctime(timeinfo));
    fixString(date);
}
void printArray(transaction *arr, int *count)
{
    int n = *count;
    float incomes = 0.0;
    float expenses = 0.0;
    for (int i = 0; i < n; i++)
    {
        
            printf("[%d] %-30s %-20s %-20.2f %-20s\n", i + 1, arr[i].m_date, (arr[i].m_type == 1 ? "Income" : "Expense"), arr[i].m_amount, arr[i].m_description);
            if (arr[i].m_type == 1)
            {
                incomes += arr[i].m_amount;
            }
            else
            {
                expenses += arr[i].m_amount;
            }
        
    }

    printf("\n");
    printf("Total expense: %.2f\n", expenses);
    printf("Total income: %.2f\n", incomes);
    printf("Balance: %.2f\n", -1 * expenses + incomes);
}

void printMenu()
{
    printf("-----------------------------\n"
           "Transaction / Choose option:\n\t"
           "1. Add money\n\t"
           "2. Spend money\n\t"
           "3. Read financial records from file\n\t"
           "4. Save financial records to file\n\t"
           "5. Prints all transactions\n\t"
           "6. Clear all records\n\t"
           "7. Clear the file\n\t"
           "8. Clear a transaction in file\n\t"
           "x. Exit\n"
           "-----------------------------\n");
}

void addToFile(char *fileName, transaction *arr, int *count)
{
    FILE *file;
    file = fopen(fileName, "ab");
    if (file == NULL)
    {
        printf("Unable to open %s\n", fileName);
    }
    else
    {
        int n = *count;
        for (int i = 0; i < n; i++)
        {
           
                fwrite(&arr[i], sizeof(transaction), 1, file);
            
        }
    }
    fclose(file);
}

transaction *addMoney(transaction *arr, char *description, float amount, char *date, int *count)
{

	(*count)++;
	transaction *temp = realloc(arr, sizeof(transaction) * (*count));
	if (temp == NULL)
	{   
        (*count)--;
		printf("Error in allocating memory.\n");
	}
	else
	{
		arr = temp;
		arr[*count - 1].m_type = 1;
		strcpy(arr[*count - 1].m_description, description);
		arr[*count - 1].m_amount = amount;
		printf("[%d]%s\n", *count, arr[*count - 1].m_description);
		strcpy(arr[*count - 1].m_date, date);
	}
	return arr;
}

transaction *spendMoney(transaction *arr, char *description, float amount, char *date, int *count)
{

	(*count)++;
	transaction *temp = realloc(arr, sizeof(transaction) * (*count));
	if (temp == NULL)
	{        
        (*count)--;
		printf("Error in allocating memory.\n");
	}
	else
	{
		arr = temp;
		arr[*count - 1].m_type = -1;
		strcpy(arr[*count - 1].m_description, description);
		arr[*count - 1].m_amount = amount;
		printf("[%d]%s\n", *count, arr[*count - 1].m_description);
		strcpy(arr[*count - 1].m_date, date);
	}
	return arr;
}
void handleCommand()
{
    int count = 0;
    char description[SIZE];
    char amount[liSIZE];
    char date[SIZE];
    float amountF;
    transaction *arr = NULL;
    while (1)
    {
        if (arr == NULL && count == 0)
        {
            printf("Array is NULL \n");
            arr = malloc(sizeof(transaction));
        }
        char choice[liSIZE];
        int choiceNumber = 0;

        printf("Please your an option: ");
        fgets(choice, liSIZE, stdin);
        fixString(choice);
        if (strcmp(choice, "x") == 0)
        {
            break;
        }
        sscanf(choice, "%d", &choiceNumber);

        switch (choiceNumber)
        {
        case 1:
        {

            printf("Income description: ");
            fgets(description, SIZE, stdin);
            fixString(description);
            printf("Income amount: ");
            amountF = toFloat(amount, liSIZE);

            getDate(date);

            arr = addMoney(arr, description, amountF, date, &count);
            for (int i = 0; i < count; i++)
            {
                printf("[%d] %-30s %-20s %-20.2f %-20s\n", i + 1, arr[i].m_date, (arr[i].m_type == 1 ? "Income" : "Expense"), arr[i].m_amount, arr[i].m_description);
            }

            break;
        }
        case 2:
        {

            printf("Expense description: ");
            fgets(description, SIZE, stdin);
            fixString(description);
            printf("Expense amount: ");
            amountF = toFloat(amount, liSIZE);

            getDate(date);

            arr = spendMoney(arr, description, amountF, date, &count);

            for (int i = 0; i < count; i++)
            {
                printf("[%d] %-30s %-20s %-20.2f %-20s\n", i + 1, arr[i].m_date, (arr[i].m_type == 1 ? "Income" : "Expense"), arr[i].m_amount, arr[i].m_description);
            }
            break;
        }
        case 3:
            printRecord("myTransaction.txt");
            break;
        case 4:
            if (arr == NULL || count == 0)
                printf("Nothing to save.\n");
            else
                addToFile("myTransaction.txt", arr, &count);
            break;
        case 5:
            if (arr == NULL || count == 0)
                printf("Empty list of transactions.\n");
            else
                printArray(arr, &count);
            break;
        case 6:
            if (arr == NULL || count == 0)
                printf("Nothing to clear.\n");
            else
                arr = NULL;
            count = 0;
            break;
        case 7:
            clearFile("myTransaction.txt");
            break;
        case 8:
            deleteTransaction("myTransaction.txt");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    }
    free(arr);
}

void printRecord(char *fileName)
{
    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("Unable to open %s\n", fileName);
    }
    else
    {
        transaction *read = malloc(sizeof(transaction));
        printf("\n");
        printf("%-30s %-20s %-20s %-20s\n\n", "Date", "Type", "Amount", "Description");

        float incomes = 0;
        float expenses = 0;
        int count = 0;

        while (!feof(file))
        {
            if (fread(read, sizeof(transaction), 1, file) == 1)
            {
                count++;
                printf("[%d] %-30s %-20s %-20.2f %-20s\n", count, read->m_date, (read->m_type == 1 ? "Income" : "Expense"), read->m_amount, read->m_description);
                if (read->m_type == 1)
                {
                    incomes += read->m_amount;
                }
                else
                {
                    expenses += read->m_amount;
                }
            }
        }
        printf("\n");
        printf("Total expense: %.2f\n", expenses);
        printf("Total income: %.2f\n", incomes);
        printf("Balance: %.2f\n", -1 * expenses + incomes);
        free(read);
        fclose(file);
    }
}