// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "unixTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number, int n)
{
    if(n == 1){
        return number.at(0);
    }
    double currMostIsolated;
    double currGreatestGap = 0;
    for(int i = 0; i < number.size(); i++){
        if(i == 0){
            double currVal = number.at(i);
            double next = number.at(i+1);
            double gapN = currVal - next;
            gapN = abs(gapN);
            if(gapN > currGreatestGap){
                currMostIsolated = currVal;
                currGreatestGap = gapN;
            }
        }
        else if(i == number.size() - 1){
            double currVal = number.at(i);
            double prev = number.at(i-1);
            double gapP = currVal - prev;
            gapP = abs(gapP);
            if(gapP > currGreatestGap){
                currMostIsolated = currVal;
                currGreatestGap = gapP;
            }
        }
        else {
            double currVal = number.at(i);
            double next = number.at(i + 1);
            double gapN = currVal - next;
            double prev = number.at(i - 1);
            double gapP = currVal - prev;
            gapN = abs(gapN);
            gapP = abs(gapP);
            if (gapN > currGreatestGap) {
                currMostIsolated = currVal;
                currGreatestGap = gapN;
            }
            if (gapP > currGreatestGap) {
                currMostIsolated = currVal;
                currGreatestGap = gapP;
            }
        }
    }
	return currMostIsolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & a, list<string> & b)
{
	int unmatchedStrings = 0;

	while(true) {
	    int count = 0;
        while (true) {
            string A = a.front();
            string B = b.front();
            if(A == ""){
                count = -1;
                break;
            }
            if(B == ""){
                count = -2;
                break;
            }

            if (a.front() < b.front()) {
                a.pop_front();
                if(count > 0){
                    unmatchedStrings++;
                }
                count++;
            }
            else if(a.front() >= b.front()){
                b.pop_front();
                break;
            }
        }
        if(count == -1){
            unmatchedStrings = unmatchedStrings + a.size();



            return unmatchedStrings;
        }
        if(count == -2){
            return unmatchedStrings;
        }
    }
}


int
main()
{
//	cout << "Find the most isolated number" << endl
//		<< "-----------------------------" << endl << endl;
//	while (true)
//	{
//		cout << "Enter size for numbers: ";
//		int n = 0;
//		cin >> n;
//		if (n <= 0)
//			break;
//		cout << "Enter seed for rand: ";
//		unsigned int seed;
//		cin >> seed;
//		srand(seed);
//
//		// Construct a sorted list of numbers
//		Timer get;
//		get.start();
//		vector<double> numbers = getNums(n, -n, n);
//		get.stop();
//		cout << "Constructed in " << get() << " seconds"
//			<< endl;
//
//		if (n < 10)
//			cout << numbers << endl << endl;
//
//		// Report a most isolated isolated number
//		Timer time;
//		time.start();
//		double isolated = mostIsolated(numbers, n);
//		time.stop();
//		cout << "The most isolated number is "
//			<< isolated << endl
//			<< "calculated in " << time() << " seconds"
//			<< endl << endl;
//	}






	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
