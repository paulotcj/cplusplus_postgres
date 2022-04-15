#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

//------------------------------
// CORE DATA / VARS / CONSTANTS
char const * _connectionString = "dbname = database_name user = user_name password = secure_password \
            hostaddr = 99.99.99.99 port = 5432";
//------------------------------  

pqxx::connection* GetConnection();
void CreateTable();
void InsertIntoTable();
void SelectFromTable();
void UpdateTable();
void DeleteFromTable();



pqxx::connection* GetConnection()
{
    pqxx::connection* conn;
    // cout << 
    // "-----------------------------------\n" \
    // "GetConnection - start"
    // << endl;


    // Connect to the database
    conn = new pqxx::connection(_connectionString);

    try 
    {
        if (conn->is_open()) 
        {
            //cout << "Opened database successfully: " << conn->dbname() << endl;
        } 
        else 
        {
            cout << "Can't open database" << endl;
        }

    }
    catch (const std::exception &e) 
    {
        cerr << e.what() << std::endl;
    }

    return conn;
     
}

void DeleteFromTable()
{
    cout << 
    "-----------------------------------\n" \
    "DeleteFromTable - start"
    << endl;
    pqxx::connection* varConn = GetConnection();
    char const * sql; 

    //Create a transactional object.
    work varDBWork(*varConn);

    /* Create SQL statement */
    sql = "DELETE from COMPANY where ID = 2"; 
    cout << "    " << sql << "\n" << endl;   

    // Execute SQL query
    varDBWork.exec( sql );
    varDBWork.commit();    
    cout << "Records created successfully" << endl;            

    varConn->disconnect ();      
}


void UpdateTable()
{
    cout << 
    "-----------------------------------\n" \
    "UpdateTable - start"
    << endl;
    pqxx::connection* varConn = GetConnection();
    char const * sql; 

    //Create a transactional object.
    work varDBWork(*varConn);

    /* Create SQL statement */
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1";    
    cout << "    " << sql << "\n" << endl;

    // Execute SQL query
    varDBWork.exec( sql );
    varDBWork.commit();    
    cout << "Records updated successfully" << endl;            

    varConn->disconnect ();      
}

void SelectFromTable()
{
    cout << 
    "-----------------------------------\n" \
    "SelectFromTable - start"
    << endl;
    pqxx::connection* varConn = GetConnection();
    char const * sql;

    // Create a non-transactional object.
    nontransaction varDBNonTransactional(*varConn);

    sql = "SELECT * FROM COMPANY ORDER BY ID";

    //Execute SQL query
    result varDB_Result( varDBNonTransactional.exec( sql ));

    //List down all the records */
    for (result::const_iterator varRow = varDB_Result.begin(); varRow != varDB_Result.end(); ++varRow) 
    {
        cout << "    ID = " << varRow[0].as<int>() << endl;
        cout << "    Name = " << varRow[1].as<string>() << endl;
        cout << "    Age = " << varRow[2].as<int>() << endl;
        cout << "    Address = " << varRow[3].as<string>() << endl;
        cout << "    Salary = " << varRow[4].as<float>() << endl;
        cout << "    -----" << endl;
    }
    cout << "Operation done successfully" << endl;    

 
    varConn->disconnect ();  

}

void InsertIntoTable()
{
    cout << 
    "-----------------------------------\n" \
    "InsertIntoTable - start"
    << endl;
    pqxx::connection* varConn = GetConnection();
    char const * sql;

    //Create a transactional object.
    work varDBWork(*varConn);

    /* Create SQL statement */
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";    

    // Execute SQL query
    varDBWork.exec( sql );
    varDBWork.commit();    
    cout << "Records created successfully" << endl;            

    varConn->disconnect ();        
        
}

void CreateTable()
{
    cout << 
    "-----------------------------------\n" \
    "CreateTable - start"
    << endl;
    pqxx::connection* varConn = GetConnection();
    char const * sql;

    //Create a transactional object.
    work varDBWork(*varConn);

    //CREATE TABLE
    sql = "DROP TABLE IF EXISTS Company; "  \
    "CREATE TABLE COMPANY("  \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "AGE            INT     NOT NULL," \
    "ADDRESS        CHAR(50)," \
    "SALARY         REAL );";  

    // Execute SQL query
    varDBWork.exec( sql );
    varDBWork.commit();

    cout << "Table created successfully" << endl;                   


    varConn->disconnect ();

}
