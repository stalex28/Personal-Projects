/** Alex Djordjevic Merge Program

    This program takes in 2 DAT files that contain ordered lists of integers,
    and then merges them together into 1 output file.

*/

/// Header files
#include <iostream>
#include <fstream>
#include <apvector.h>

using namespace std;

int main() {

    /// Variable declaration
    apvector<int> firstList(101);
	apvector<int> secondList(101);
	char input[50];
	int listLength = 0;
	int nfirstList = 0;
	int nfinal = 0;
	int keeper = 0;
	int counter = 0;

	/// User input
    cout << "input the name of the first file:  ";
    cin >> input;

	ifstream fin;

	fin.open(input);

    /// Reads in first file
	while (!fin.eof()) {
		fin >> firstList[listLength++];
	}
	fin.close();
	nfirstList = listLength; /// Records the length of the first list
	listLength = 0;

	/// User input
	cout << endl << "input the name of the second file:  ";
    cin >> input;

    /// Reads in the second file
	fin.open(input);
    while (!fin.eof()) {
		fin >> secondList[listLength++];
	}
	fin.close();
    nfinal = listLength + nfirstList; /// Calculates the length of the final list
    apvector<int> holder(nfinal+1);

    /** Merger: keeper - int that increases by one every time a # from the first list is used
                counter - same as keeper but for the second file
                listLength - total # of things in the second list
                nfirstList - total # of things in the first file
                holder - final list
    */
	for(int j = 0; j <= nfinal; j++){
        if(keeper <= nfirstList && counter <= listLength){
            if(firstList[keeper] <= secondList[counter]){
                holder[j] = firstList[keeper];
                keeper ++;
            }
            else{
                holder[j] = secondList[counter];
                counter ++;
            }
        }
        /// If the first list ends before the second one, the final file just gets filled with the remaining numbers from the second list
        if(keeper > nfirstList){
            holder[j] = secondList[counter];
            counter ++;
        }
        /// Same as the one before but with the lists switched
        if(counter > listLength){
            holder[j] = firstList[keeper];
            keeper ++;
        }
	}

    /// Output of the list into the file
	ofstream fout("output.dat");
	for (int i = 0; i < nfinal; i++) {
		cout << holder[i] << endl;
		fout << holder[i] << endl;
	}
	fout.close();
	return 0;
}
