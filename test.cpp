//g++ test.cpp -lpqxx -lpq -o test.o

#include "Local_Includes.c"
     

int main(int argc, char* argv[]) 
{
    char const * sql;
    try 
    {
        CreateTable();
        InsertIntoTable();
        SelectFromTable();
        UpdateTable();
        SelectFromTable();
        DeleteFromTable();
        SelectFromTable();


    } 
    catch (const std::exception &e) 
    {
        cerr << e.what() << std::endl;
        return 1;
    }
}



