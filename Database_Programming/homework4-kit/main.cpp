#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"

using namespace pqxx;
using namespace std;
//reference code from homework4-kit.zip

int main (int argc, char *argv[]) 
{
  //reference code from homework4-kit.zip
  //Allocate & initialize a Postgres connection object
  connection *C;
  int ii = 0;

  try{
    //Establish a connection to the database
    //reference code from homework4-kit.zip
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    int kk = 0;
    //cout << "in try" << endl;
    if (C->is_open()) {
      //reference code from homework4-kit.zip
    } else {
      cerr << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }

  //drop table
  //cout<<"before drop"<<endl;
  dropTable(C);
  //cout<<"after drop"<<endl;

  //create table
  //cout<<"before create"<<endl;
  createTable(C);
  //cout<<"after create"<<endl;

  //process txt file
  //cout<<"before process"<<endl;
  processFile(C);
  //cout<<"after process"<<endl;

  //cout<<"before exercise"<<endl;
  exercise(C);
  //cout<<"after exercise"<<endl;

  //Close database connection
  C->disconnect();

  return 0;
}

