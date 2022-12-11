#include "DataBase.h"
/*
MADE BY
Abdul Wahab 21i-0675
Hassan Nawaz 21i-2993
Tauheed Akbar 21i-0723
*/
int main(){

	string Files[] = { "NCHS_-_Leading_Causes_of_Death__United_States_1.csv" , "NCHS_-_Leading_Causes_of_Death__United_States_2.csv","NCHS_-_Leading_Causes_of_Death__United_States_3.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_4.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_5.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_6.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_7.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_8.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_9.csv" , "NCHS_-_Leading_Causes_of_Death__United_States_10.csv" };
	int const num_of_files = 10;
	Database database(Files, num_of_files);
	database.Menu();
}