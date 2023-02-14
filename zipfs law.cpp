#include <iostream>
#include<map>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

multimap<int, string> invert(map<string, int>& mymap)
{
    multimap<int, string> multiMap;
    bool add;
    map<string, int> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++)
    {
        add = true;
        int value = it->second;
        //remove duplicates
        /*int upperRange = (value + (value * 0.01));
        int lowerRange = (value - (value * 0.01));
        for(int i = lowerRange ; i <= upperRange ; i++)
        if ((multiMap.find(i) != multiMap.end()))
           add = false;*/

       if(add)
        multiMap.insert(make_pair(it->second, it->first));
    }

    return multiMap;
}
multimap<int, string> invertForCities(map<string, int>& mymap)
{
    multimap<int, string> multiMap;
    bool add;
    map<string, int> ::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++)
    {
        add = true;
        //reducing noise by removing very close values
        int value = it->second;
        int upperRange = (value + (value * 0.01));
        int lowerRange = (value - (value * 0.01));
        for(int i = lowerRange ; i <= upperRange ; i++)
        if ((multiMap.find(i) != multiMap.end()))
           add = false;

        if (add)
            multiMap.insert(make_pair(it->second, it->first));
    }

    return multiMap;
}
multimap<int, string> createMapOfCities(string filename) {
    map <string, int> myMap;


    // filename of the file
    fstream file;


    // opening file
    file.open(filename.c_str());


    // extracting words from the file

    string line;
    while (getline(file, line)) {
        string latestWord;
        string latestNumber;
        bool input = false;
        for (char ch : line) {
            //checking if its a letter using ascii code or a number

            if (((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90)))
                latestWord += ch;
            else if ((ch >= 48 && ch <= 57))
                latestNumber += ch;



        }
        myMap[latestWord] = stoi(latestNumber);

    }
        return (invertForCities(myMap));

    }

multimap<int, string> countWords( string filename ) {
    map <string, int> wordFrequency;


    // filename of the file
    fstream file;


    // opening file
    file.open(filename.c_str());


    // extracting words from the file
    string wordin;
    while (file >> wordin)
    {

        string constructedWord;
        for (char ch : wordin) {
            //checking if its a letter using ascii code , not a symbol or punctuation mark

            if (ch == 32 || ch == 39)// 39 means an apostrophe 'if we use continue instead of break our code will read father and father's as two different words which is not what we want so we break instead
                break;
            if (!((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90)))
                continue; // we can check if the character is a letter easily by checking if it is in the range of capital/small letters in ascii

            if (ch >= 97 && ch <= 122) {
                constructedWord += ch;
            }
            //letter is capital
            else if (ch >= 65 && ch <= 90) {
                constructedWord += tolower(ch);
            }

        }
        wordFrequency[constructedWord]++;

    }



    /**/
    return (invert(wordFrequency));

}


multimap<int, string> createZipfPredection(multimap<int, string> &originalMap) {
    multimap<int, string> zipfMap ;
    int highest = originalMap.rbegin()->first;
    float i = 1;
    auto it = originalMap.rbegin();
    while (i <= originalMap.size()) {
        int freq = (round( (1.0/i) * highest));
        zipfMap.insert(make_pair(freq ,  it->second));
        i++;
        it++;
    }
    return zipfMap;


}

void writeInfoToFile(string filename , multimap <int, string> &mymap) {

    ofstream writer;
    writer.open(filename);
    // writer<<"number of words = "<<totalWordCount<<endl;
    // writer << "number of unique words = " << mymap.size() << endl;
    int i = 1;
    int totalFrequency = 0;
    for (auto it = mymap.rbegin(); it != mymap.rend(); it++, i++) {
        {
            writer << i << "\t" << it->first << "\t" << it->second << endl;
            totalFrequency += it->first;
        }
    }
    int mean = (round((float)totalFrequency /(float) i));
   // writer << "calculated mean is " << mean << endl;
    writer.close();
}
void doZipfsPredectionBooks(string fileName) {
    fileName += ".txt";
    multimap <int, string>mymap = countWords(fileName);

    writeInfoToFile(("ResultedMap.txt"), mymap);
    createZipfPredection(mymap);
    multimap <int, string> zipfMap = createZipfPredection(mymap);
    writeInfoToFile(("ZipfResultedMap.txt"), zipfMap);

    string command = "python ";
    string pythonfilename = "./Graphing.py";
    command += pythonfilename;
    system(command.c_str());
}
void doZipfsPredectionCountries(string fileName) {
    fileName += ".txt";
    multimap <int, string>mymap = createMapOfCities(fileName);

    writeInfoToFile(("ResultedMap.txt"), mymap);
    createZipfPredection(mymap);
    multimap <int, string> zipfMap = createZipfPredection(mymap);
    writeInfoToFile(("ZipfResultedMap.txt"), zipfMap);

    string command = "python ";
    string pythonfilename = "./Graphing.py";
    command += pythonfilename;
    system(command.c_str());
}


int main()
{

    string availableBooks[] = { "Lord of the Rings" , "Harry Potter" ,"The GodFather" };
    string availableCountries[] = { "USA-populations", "Germany-populations" };

    int input;
    int i = 0;
    cout << "\n\n\t\t\tChoose one of the following modes :  (Enter the number of the command)   \n";
    string message = "\t\t\t   1 - measure Zipfs law accuracy in books\n\t\t\t   2 - measure Zipfs law accuracy in city populations\n\n";
    while (true) {
        cout << message;
        cout << "\t\t\tPlease Enter your choice \n";
        input = getch();
        switch (input)
        {
        case '1':
            cout << "\n\n\t\t\tPlease choose one of the avialable books :\n\n";
            i = 1;
            int bookChoice;
            for (string book : availableBooks) {
                cout << "\t\t\t" << i << " - " << book << endl;
                i++;
            }
            cout << "\t\t\t\t\t\t";
            cin >> bookChoice;
            if (bookChoice <1 || bookChoice > i) {
                cout << "\t\t\tPlease enter a valid choice\n";
                break;
            }
            else {
                doZipfsPredectionBooks(availableBooks[--bookChoice]);
            }
            break;
        case '2':
            cout << "\n\n\t\t\tPlease choose one of the avialable Country collected data :\n";
            i = 1;
            int countryCHoice;
            for (string book : availableCountries) {
                cout << "\t\t\t" << i << " - " << book << endl;
                i++;
            }
            cout << "\t\t\t\t\t\t";
            cin >> countryCHoice;
            if (countryCHoice <1 || countryCHoice > i) {
                cout << "Please enter a valid choice\n";
                break;
            }
            else {
                doZipfsPredectionCountries(availableCountries[--countryCHoice]);
            }
            break;
        default:
            cout << "Wrong number , please enter a valid choice\n";
            break;
        }
    }


}

