/*  This program gave me familiarity with the basics of
    programming such as functions, control structures, file I/O, etc.
    The program takes in a csv file via command line arguments parses out
    the information, and performs calculations to determine the
    most popular and profitable items as well as the item that generated
    the most profit. While not the most attractive looking code, I look
    forward to rewriting the code to be more modular.
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

    

// function prototypes
void showMenu();
// fills the arrays with data from files
bool readIntoArrays(string filename, string items[],double retails[],
double costs[], int quantities[], int size);
// returns the most popular item in terms of sale quantity
string mostPopularItem(string items[], int quantities[], int size);
// returns the item that has the highest profit margin
// profit = retail - cost
string mostProfitablItem(string items[],double retails[], 
double costs[], int size);
// shows all items on the screen, check assignment document for spacing
void showItems(string items[],double retails[],double costs[], 
int quantities[], int size);
// returns the item that generated the most profit
// generated profit = (retail - cost) * quantity sold
string generatedMostProfit(string items[],double retails[],
double costs[], int quantities[], int size);

int main(int argc, char *argv[]){

    //if there are no arguments or too many, exit program
    if (argc <= 1)
    {
        cout << "Must enter data file name!" << endl;
        return 0;
    }

    if (argc > 2)
    {
        cout << "Too many arguments!" << endl;
        return 0;
    }
    
    string filename = argv[1];
    const int size = 10; 
    // parallel arrays to store data
    string items[size]={""};
    double retails[size]={};
    double costs[size]={};
    int quantities[size]={};

    // trying to read data into arrays
    bool fileOpenend = readIntoArrays(filename, items,retails,costs, 
    quantities,size);

    //if file didn't open, exit
    if (fileOpenend == false)
    {
        return 0;
    }
    
    //welcome
    cout<<"Opening "<<filename<<endl;
    int choice = 0;
    bool flag = false;
    cout<<"--- Welcome to the sales data analyzer ---\n";

  
    do{
        if (flag){
            cin.clear();
            cin.ignore(100,'\n');
            flag = false;
        }
        showMenu();
        cout<<"Select from the menu above:\n";
        cin>>choice;
        if(cin.fail() || choice < 1 || choice >5){
            cout<<"Invalid selection!\n";
            flag = true;
            continue;
        }
        switch (choice)
        {
        case 1:
        showItems(items, retails, costs, quantities, size);
        break;
        case 2:
        cout<<"Most popular item is: "
        <<mostPopularItem(items,quantities,size)<<endl;
        break;
        case 3:
        cout<<"The with highest profit margin is: "<<
        mostProfitablItem(items,retails,costs,size)<<endl;
        break;
        case 4:
        cout<<"The item that generated most profit is: "
        <<generatedMostProfit(items,retails,costs,quantities,size)
        <<endl;
        break;
        case 5: 
        cout<<"--- Thank you for using the sales data analyzer! ---\n";
        return 0;
        }
    }while(cin.fail()|| choice !=5);
    
    
    return 0;
}

//shows menu to user
void showMenu()
{
    cout << "1. Show all items.\n2. Show most popular item.\n";
    cout << "3. Show item with highest profit margin.\n";
    cout << "4. Show item that generated most profit.\n5. Exit.\n";
}

//opens file, read array and returns true if file opened, otherwise false
bool readIntoArrays(string filename, string items[],double retails[],
                    double costs[], int quantities[], int size)
{   
    //file object
    ifstream input;
    //open file
    input.open(filename);
    //if file did not open, exit
    if(!input.is_open())
    {   
        cout << "File can not be found!\n";
        cout << "Check filename and try again!";
        return false;
    }
    //string to read in line from input
    string reader = "";
    //remove header
    getline(input, reader);
    //indexes
    int firstComma=0;
    int index = 0;

    //loop that reads in line from input and assigns data to parallel arr
    while (getline(input, reader))
    {   
        //declare strings needed for loop
        string Item, Retail, Cost, QuantitySold;

        //parse item info from line
        firstComma = reader.find(",");
        Item = reader.substr(0, firstComma);
        items[index] = Item;

        //updated string that ignores everything before last comma
        reader = reader.substr(firstComma + 1, reader.length());
        firstComma = reader.find(",");

        //parse retail info from line
        Retail = reader.substr(0, firstComma);
        double retailDouble=0.2;
        istringstream(Retail) >> retailDouble;
        retails[index] = retailDouble;
        
        //updated string that ignores everything before last comma
        reader = reader.substr(firstComma + 1, reader.length());
        firstComma = reader.find(",");

        //parse cost info from line
        Cost = reader.substr(0, firstComma);
        double costDouble = 1.1;
        istringstream(Cost) >> costDouble;
        costs[index] = costDouble;

        //updated string that ignores everything before last comma
        reader = reader.substr(firstComma + 1, reader.length());
        firstComma = reader.find(",");

        //parse qty sold from line
        QuantitySold = reader.substr(0, firstComma);
        int qtyInt=0;
        istringstream(QuantitySold) >> qtyInt;
        quantities[index] = qtyInt;
        
        //increment index
        index++;
    }
    //if file was read into array return true
    return true;
}


string mostPopularItem(string items[], int quantities[], int size)
{  
    int popIndex = 0;
    int mostPopular = 1;
    for(int i = 0; i < size; i++)
    {   //if data at index i is > current popular, make it new popular
        if(quantities[i]>mostPopular)
        {
            mostPopular = quantities[i];
            popIndex = i;
        }
    }
    //return the item at the popular index
    return items[popIndex];
}

string mostProfitablItem(string items[],double retails[], 
double costs[], int size)
{
    double profitMargin[10] ={3.5};
    for(int i = 0; i < size; i++)
    {   //create new array and have its values at retails[i] - costs[i]
        profitMargin[i] = (retails[i]-costs[i]);
    }
    
    int marginIndex = 0;
    double bestMargin = profitMargin[0];
    for (int x = 0; x < size; x++)
    {   
        if(profitMargin[x] > bestMargin)
        {   //if data at index x is > current best, make it new best
            bestMargin = profitMargin[x];
            marginIndex = x; 
        }
    }
    //return item with the highest margin 
    return items[marginIndex];
}

string generatedMostProfit(string items[],double retails[],
double costs[], int quantities[], int size)
{
    double profitGen[10]={};
    for(int i = 0; i < size; i++)
    {   //create new arr, its values[i] = retails - costs * quantities
        profitGen[i] = (retails[i]-costs[i]) * quantities[i];
    }
    
    int genIndex = 0;
    double bestGen = profitGen[0];
    for (int y = 0; y < size; y++)
    {
        if(profitGen[y] > bestGen)
        {   //if data at index y is > current best, make it new best
            bestGen = profitGen[y];
            genIndex = y; 
        }
    }
    return items[genIndex];
}


void showItems(string items[],double retails[],double costs[], 
int quantities[], int size)
{   //output header
    cout << left << setw(25) << "Item" << setw(16) << "Retail" <<
     setw(16) << "Cost" << setw(16) << "Quantity" << endl;

    //output table
    for(int i = 0; i < size; i++)
    {
        cout << left << setw(25) << items[i] << "$" << setw(15) <<
         retails[i] << "$"<<
         setw(15) << costs[i] << setw(15) << quantities[i] << endl;
    }
    cout << "\n";
}