#ifndef anolibra
#define anolibra

#define SIZE 80
#define liSIZE 5

typedef struct TransactionRecord
{
	int m_type;
	char m_description[SIZE];
	float m_amount;
	char m_date[SIZE];
} transaction;
int findSize(transaction *arr);
void printRecord(char *fileName);
void fixString(char *str);
float toFloat(char *str, int size);
void getDate(char *date);
void printMenu();
void addToFile(char *fileName, transaction *arr, int *count);
transaction *addMoney(transaction *arr, char *description, float amount, char *date, int *count);
transaction *spendMoney(transaction *arr, char *description, float amount, char *date, int *count);
void handleCommand();
void clearFile(char *fileName);
void printArray(transaction *arr, int *count);
void deleteTransaction(char *file);


#endif