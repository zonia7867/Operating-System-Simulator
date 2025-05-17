#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const string RESET = "\033[0m";
const string CYAN = "\033[34m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string BOLD = "\033[1m";
int main()
{
string fileName;
string extention;
int choice;

cout << CYAN << "Enter File Name: " << RESET;
cin >> fileName;
do{
  cout << GREEN << "Select extention: \n"
  << "1. Text (.txt)" << endl
  << "2. Data (.dat)\n" 
  << "choice: " << RESET ;
  cin >> choice;
  if(choice == 1)
  {
    extention = ".txt";
  }
  else if (choice == 2)
  {
    extention = ".dat";
  }
  else
  {
    cout<< RED<< "Wrong Extention\n" << RESET;
  }
}while(choice < 1 || choice > 2);

  fileName = fileName+extention;
  ifstream temp;
  temp.open(fileName);
  if (temp.fail())
  {
    cout << RED << "No file of this name exists\n" << RESET;
  }
  else
  {
    remove(fileName.c_str());
    cout << RED << "File successfully removed!\n" << RESET;
  }
  
    cin.ignore();
  cout << YELLOW <<"\t\t\t" << "Press any key to Exit...\n" << RESET;
  cin.get();
     system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate DELETE");
   
  return 0;
}
