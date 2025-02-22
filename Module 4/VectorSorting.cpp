//============================================================================
// Name        : VectorSorting.cpp
// Author      : Caleb Ewer
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	int low = begin;
	int high = end;

	int pivot = begin + (end - begin) / 2;	//Determine the pivot point

	bool done = false;
	while (!done){		//Loop through till we find the midpoint



	while (bids.at(low).title.compare(bids.at(pivot).title) < 0){	//Increment low until we get to pivot
		++low;
	}

	while (bids.at(pivot).title.compare(bids.at(end).title) < 0){	//Decrement high till we get to pivot
		--high;
	}

	if (low >= high){	//All elements are partitioned or there is only one element
		done = true;
	}

	else {
		swap(bids.at(low), bids.at(high));	//Swap bids

	++low;
	--high;
	}
}

	return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {

// FIXME (1a): Implement the selection sort logic over bid.title
int mid = 0;

	if (begin >= end){		//Base case
		return;
	}

	mid = partition(bids, begin, end); //Determine midpoint value

	quickSort(bids, begin, mid);	//Recursive call using the midpoint as the end

	quickSort(bids, mid + 1, end);	//Recursive call using the midpoint as the beginning
}
/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	int min;
	int pos;

	for(pos = 0; pos < bids.size(); pos++){		//Outer loop to iterate through the bids
		min = pos;	//Assigns minimum to the first element

		for(int j = pos + 1; j < bids.size(); j++){		//Inner loop to compare element to swap with
			if(bids.at(j).title.compare(bids.at(min).title) < 0){	//Compare element at j with the outer loop element
				min = j;
			}
		}
		if (min != pos){
			swap(bids.at(pos), bids.at(min));	//Swap elements
		}
	}
}



/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): Invoke the selection sort and report timing results
        case 3:
                    // Initialize a timer variable before loading bids
                    ticks = clock();

                    // Complete the method call to sort the bids using selection sort
                    selectionSort(bids);

                    cout << bids.size() << " bids read" << endl;

                    // Calculate elapsed time and display result
                    ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                    cout << "time: " << ticks << " clock ticks" << endl;
                    cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                    break;

        // FIXME (2b): Invoke the quick sort and report timing results
        case 4:
                            // Initialize a timer variable before loading bids
                            ticks = clock();

                            // Complete the method call to sort the bids using Quick Sort
                            quickSort(bids, 0, bids.size()-1);

                            cout << bids.size() << " bids read" << endl;

                            // Calculate elapsed time and display result
                            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                            cout << "time: " << ticks << " clock ticks" << endl;
                            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                            break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
