/*  Name: Bryan Flores
    Description: This program reads in a .txt file that has a set
                 number of test cases, categories, and associated words
                 per category. It reads in the categories to a vector, 
                 and maps each keyword to its respective category in the map.
                 From there, the program checks a description and if a minimum
                 number of words per category is found, that category is printed out.                 
    Input: text file of test cases
    Output: the type of categories a description contains
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

int main()
{   
    //read in the test cae number
    int testCase; cin >> testCase;

    //Test Case Loop
    for (int i = 0; i < testCase; i++)
    {
        //read in the number of categories
        int C; cin >> C; 

        //string used to get the line for each description
        string line;  

        //parallel vectors | stores the order of the categories
        vector <string> ledger;
        //parallel vectors | stores the keyword count for each category
        vector <int> counts;

        //map that stores the keywords and maps them to a category 
        unordered_map <string, string> map;

        //map that stores the number of keywords needed for each category
        unordered_map <string, int> count;

        //keeps track of whether or not a category was printed
        int categoryCount = 0;
        
 
        //Number of Categories loop
        for(int j = 0; j < C; j++)
        {   
            //read in category, number of words per and number of words needed
            string category; int categoryAmt, wordsNeeded;
            cin >> category >> categoryAmt >> wordsNeeded;

            //string used to read in the category keywords
            string input;

            //insert the category name and the words needed to parallel vectors
            ledger.push_back(category);
            counts.push_back(wordsNeeded);
      
            //loop that reads in all the words in a category
            for (int x = 0; x < categoryAmt; x++)
            {
                //read in the word to input
                cin >> input;

                //converts all characters in a keyword to lowercase
                for(int ch = 0; ch < input.length(); ch++)
                {
                    //for each index of the word, converts to lowercase
                    input[i] = tolower(input[i]);
                }

                //adds the keyword to the map
                map[input] = category;

                //sets the count for the current category to 0
                count[category] = 0;
            }         
        }
        
        //moves the cin iterator to the next line
        getline(cin, line);

        //loop that reads in each word and checks if it in the map of keywords
        while(getline(cin, line))
        {
            //once line is empty, we are at end of test case
            if(line.empty()){break;}
            
            istringstream iss(line);
            string word;

            //while word is able to take in a word from iss
            while(iss >> word)
            {
                //converts all characters in a keyword to lowercase
                for(int ch = 0; ch < word.length(); ch++)
                {
                    //for each index of the word, converts to lowercase
                    word[i] = tolower(word[i]);
                }

                //this checks to see if the word is found in the map.
                if (map.count(word) > 0)
                { 
                    //sets the string to the value at the current keyword
                    string check = map[word];

                    //finds the count for the current category and increments it by 1
                    count[check] = count[check] + 1;

                    //removes the keyword from the map so that no duplicates are found
                    map.erase(word);
                }
            }            
        }

        //start of the output
        cout << "Test case " << i + 1 << endl; 
    
        //loop that iterates through the vector holding the counts needed
        for (int i = 0; i < counts.size(); i++)
        {
           //loop that loops through all the items in the map count
           for(auto c:count)
           {
                //if the category is the same as the current key then check the value
                if (ledger[i] == c.first)
                {
                    //if the count == words needed then cout category
                    if(c.second == counts[i])
                    {   
                        //prints the valid category
                        cout << ledger[i] << endl;
                    }
                    else
                        //since the category wasnt valid, this increments
                        categoryCount++;
                }
            }         
        }

        //if the count is equal to the amount of categories in the test case
        //then this runs as it means no categories were valid
        if (categoryCount == C)
        {
            cout << "SQF Problem" << endl;
        }
    }
}
