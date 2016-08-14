//--------------------------------------------------                                                
//  This program generates and prints 50000 random    
//  integers between upper and lower bound limits. 
//  It then uses 4 different sorting methods to 
//  sort the arrary and find the execution time
//--------------------------------------------------
//  Author:  Sunny Chowdhury    
//--------------------------------------------------

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int NUMMETHODS = 4;

void InitializeRandomArray(int randomArray[], int len);
bool limitTest(int N, int M, int L);
bool VerifySorted(int inArray[], int L);
void SelectionSort(int inArray[], int N, int M, int L);
void InsertionSort(int inArray[], int N, int M, int L);
void DoubBubbleSort(int inArray[], int N, int M, int L);
void QuickSort(int inArray[], int N, int M);

int main()
{
	int i;
	int k;

	int numOfIntegers;
	char outFileName[80] = { "\0" };

	int myIntegerArray[50000] = { 0 };
	int StartTime;
	int EndTime;
	int insertionTime;
	int selectionTime;
	int bubbleTime;
	int quickTime;

	ofstream fileout;
	fileout.setf(ios::fixed);

	numOfIntegers = 0;
	StartTime = 0;
	EndTime = 0;
	insertionTime = 0;
	selectionTime = 0;
	bubbleTime = 0;
	quickTime = 0;


	// Read the number of integers to be placed in random array
	while (numOfIntegers <= 0 || numOfIntegers > 50000)
	{
		cout << "Enter the number of integers to be sorted, " << endl;
		cout << "must be 0 < numOfIntegers <= 50000: ";
		cin >> numOfIntegers;
	}

	cout << "Enter the name of the output file: ";
	cin >> outFileName;

	// Print table header to the screen
	cout << setw(21) << "Method" << setw(20) << "Execution Time" << endl;
	cout << "____________________________________________________________" << endl;

	// Generate random numbers for all four methods
	for (i = 1; i <= NUMMETHODS; i++)
	{
		fileout.open(outFileName, ios::app);

		if (fileout.fail())
		{
			cerr << "File could not be opened\n";
			system("pause");
			return 1;
		}

		InitializeRandomArray(myIntegerArray, numOfIntegers);

		// Print unsorted array for all 4 sorting method 
		// Print 10 integers per line
		switch (i)
		{
		case 1:
			fileout << "Sorting " << numOfIntegers << " integers using the insertion sort method" << endl;
			break;
		case 2:
			fileout << "Sorting " << numOfIntegers << " integers using the selection sort method" << endl;
			break;
		case 3:
			fileout << "Sorting " << numOfIntegers << " integers using the bubble sort method" << endl;
			break;
		case 4:
			fileout << "Sorting " << numOfIntegers << " integers using the quick sort method" << endl;
			break;
		default:
			cerr << "Not a valid method" << endl;
			break;
		}

		for (k = 0; k < numOfIntegers; k++)
		{
			fileout << setw(10) << myIntegerArray[k];
			if (k % 10 == 9)
			{
				fileout << endl;
			}
		}


		// Calculate time for each sorting
		StartTime = (int)clock();
		switch (i)
		{
		case 1:
			SelectionSort(myIntegerArray, 0, numOfIntegers - 1, numOfIntegers);
			EndTime = (int)clock();
			insertionTime = EndTime - StartTime;
			break;
		case 2:
			InsertionSort(myIntegerArray, 0, numOfIntegers - 1, numOfIntegers);
			EndTime = (int)clock();
			selectionTime = EndTime - StartTime;
			break;
		case 3:
			DoubBubbleSort(myIntegerArray, 0, numOfIntegers - 1, numOfIntegers);
			EndTime = (int)clock();
			bubbleTime = EndTime - StartTime;
			break;
		case 4:
			QuickSort(myIntegerArray, 0, numOfIntegers - 1);
			EndTime = (int)clock();
			quickTime = EndTime - StartTime;
			break;
		default:
			cerr << "Not a valid method" << endl;
			break;
		}


		fileout << endl << endl << endl;

		// Print the sorte array
		// Print 10 integers per line
		for (k = 0; k < numOfIntegers; k++)
		{
			fileout << setw(10) << myIntegerArray[k];
			if (k % 10 == 9)
			{
				fileout << endl;
			}
		}

		fileout << endl << endl;

		// Close the output file
		fileout.close();
		fileout.clear();

		if (!(VerifySorted(myIntegerArray, numOfIntegers)))
		{
			cerr << "ERROR: Data is not sorted after sort algorithm	" << endl;
		}

		// Print timing data to the screen
		switch (i)
		{
		case 1:
			cout << setw(21) << "Insertion sort" << setw(20) << insertionTime << endl;
			break;
		case 2:
			cout << setw(21) << "Selection sort" << setw(20) << selectionTime << endl;
			break;
		case 3:
			cout << setw(21) << "Double Bubble sort" << setw(20) << bubbleTime << endl;
			break;
		case 4:
			cout << setw(21) << "Quick sort" << setw(20) << quickTime << endl;
			break;
		default:
			cout << "Not a valid method " << endl;
			break;
		}

	}

	system("pause");
	return 0;
}

void InitializeRandomArray(int randomArray[], int len)
{
	int seed = 1234;
	int maxValue = 200;
	int minValue = 1;
	int k;

	// intialize the random number generator with the seed
	// Because the same seed is used for each time through
	// the loop the same sequence of random numbers will be
	// generated each time through the loop
	srand(seed);

	// Fill the dynamic array randomArray with random numbers
	// The random numbers will be integers in the range
	// maximum <= integer <= minimum 
	// The maximum and minimum inters supplied by the user
	// *****************************************************
	// NOTE: All sorts must begin with the 
	// same unsorted data (not the sorted data returned from
	// the previous sort)
	// ****************************************************
	for (k = 0; k < len; k++)
	{
		//  Generate SIZE_OF_ARRAY random integers 
		//  Scale each integer to the desired range
		//  place each integer in the array 
		randomArray[k] = rand();
		randomArray[k] %= (maxValue - minValue + 1);
		randomArray[k] += minValue;
	}
}

bool VerifySorted(int inArray[], int L)
{
	for (int i = 0; i < L - 1; i++)
	{
		if (inArray[i] < inArray[i + 1])
		{
			cout << "array is not sorted, error at location	" << i;
			cout << " and " << i + 1 << endl;
			return false;
		}
	}
	return true;
}

void InsertionSort(int inArray[], int N, int M, int L)
{
	// This function sorts a portion of an array of integers inArray   
	// into descending order. The portion of the array sorted starts   
	// at element and index N and ends at the element with index M     
	// The sort is executed using an Insertion Sort algorithm          


	//Test to assure N and M are both with the array of length L
	//Test that N is less than or equal to M
	// 0 <= N <= M <= L-1
	//If the values of N and M are not consistent with the each
	//other or the length L then do not attempt to sort the array
	//Return the unsorted array. 
	//Print a message to inform the user why the array was not sorted
	if (limitTest(N, M, L) == false)
	{
		cout << "Inconsitent input to InsertionSort: sort omitted \n";
		return;
	}


	// declare local variables 
	int i;                  //Loop variable
	int k;                  //Loop variable
	int forinsert;          //Next value to be inserted 
	int insertlocation;     //Index of the array location into which
							//the new value to be inserted is to be 
							//placed

							// Assume the first element of the array has already been inserted 
							// This means the first element to be inserted is at location N+1
							// Determine if it should be inserted at location N+1 or location N
							// Similarly, for each successive element in the array, locate the index of   
							// the correct location among the already sorted data              
	for (i = (N + 1); i<(M + 1); i++)
	{
		insertlocation = i;
		forinsert = inArray[i];

		// find the location to insert the next value
		// The array element with indices < i have already been sorted
		// Need only consider the elements in the part of the array being
		// sorted so that we need not consider i<N
		for (k = N; k<i; k++)
		{
			if (inArray[k] < forinsert)
			{
				insertlocation = k;
				break;
			}
		}

		// move all elements at or above the insertion locataion
		// one location to the left (increase indices by one)
		// then insert the element from location i into the
		// correctlocation
		for (k = i; k >= insertlocation; k--)
		{
			inArray[k] = inArray[k - 1];
		}
		inArray[insertlocation] = forinsert;
	}
}

void DoubBubbleSort(int inArray[], int N, int M, int L)
{
	// This function sorts a portion of an array of integers inArray   
	// into descending order. The portion of the array sorted starts   
	// at element and index N and ends at the element with index M     
	// The sort is executed using an Double Bubble Sort algorithm 

	//Test to assure N and M are both with the array of length L
	//Test that N is less than or equal to M
	// 0 <= N <= M <= L-1
	//If the values of N and M are not consistent with the each
	//other or the length L then do not attempt to sort the array
	//Return the unsorted array. 
	//Print a message to inform the user why the array was not sorted
	if (limitTest(N, M, L) == false)
	{
		cout << "Inconsitent input to DoubleBubbleSort: sort omitted \n";
		return;
	}

	// declare local variables 
	int end;          //Index of the first element in the part of the 
					  //array currently being sorted
	int start;        //Index of the last element in the part of the 
					  //array currently being sorted
	int k;            //loop counter
	int temp;         //Temporary location to hold values whose location
					  //in the array is being swapped
	int sorted = false; //Flag that indicates if the input array is completely
						//sorted. Reflects an accurate value at the end of each
						//iteration only


						// Zero or one item to sort 
	if (N >= M)
	{
		return;
	}

	end = M;
	start = N;
	while (!sorted && start <= end)
	{


		//Assume the array is sorted as you begin an iteration
		//As soon as you find it necessary to move any value 
		//to continue sorting the array you know that the input
		//was not sorted and you set sorted to FALSE 
		sorted = true;

		//Begin at the start of the part of the array to be sorted
		//Compare each succesive pair of array elements putting that
		//pair of values in order. When you have stepped through the
		//part of the array to be sorted the smallest value will be
		//in the last element of the part of the array being sorted
		for (k = start; k<end; k++)
		{
			if (inArray[k] < inArray[k + 1])
			{
				sorted = false;
				temp = inArray[k];
				inArray[k] = inArray[k + 1];
				inArray[k + 1] = temp;
			}
		}


		//The last element of the part of the array being sorted is
		//now in the correct postition. 
		//Redefine the part of the array being sorted
		//From this point on consider that the part of the array being
		//sorted does not include the element you just moved to the
		//correct location (the last element before redefinition).
		end--;


		//Begin at the end of the part of the array to be sorted
		//Compare each succesive pair of array elements putting that
		//pair of values in order. When you have stepped through the
		//part of the array to be sorted the larges value will be
		//in the first element of the part of the array being sorted
		for (k = end; k>start; k--)
		{
			if (inArray[k] > inArray[k - 1])
			{
				sorted = false;
				temp = inArray[k];
				inArray[k] = inArray[k - 1];
				inArray[k - 1] = temp;
			}
		}

		//The first element of the part of the array being sorted is
		//now in the correct postition. 
		//Redefine the part of the array being sorted
		//From this point on consider that the part of the array being
		//sorted does not include the element you just moved to the
		//correct location (the first element before redefinition).
		start++;
	}
}

void QuickSort(int inArray[], int N, int M)
{
	// This function sorts a portion of an array of integers inArray   
	// into descending order. The portion of the array sorted starts   
	// at element and index N and ends at the element with index M     
	// The sort is executed using an Quick Sort algorithm              

	// declare local variables 
	// pivot is used to temporarily hold the value of the pivot when   
	// it is being moved                                               
	// loSwap is used to store the index of the first element          
	// (incrementing from the start of the array) with value < the     
	// value of the pivot                                              
	// hiSwap is used to store the index of the first element          
	// (decrementing from the end of the array) with value > the       
	// value of the pivot  
	// lobound is the index of the first element in the portion of the
	// array to be sorted
	// hibound is the index of the last element in the prortion of the
	// array to be sorted
	int pivot;
	int loSwap;
	int hiSwap;
	int temp;
	int loBound;
	int hiBound;


	loBound = N;
	hiBound = M;


	// Zero or one item to sort, array is already sorted 
	// First stopping case for this recursive algorithm
	if (loBound >= hiBound)
	{
		return;
	}

	// Two items to sort, array is already sorted or two 
	// values need to be exchanged
	// Second stopping case for this recursive algorithm
	if (hiBound - loBound == 1)
	{
		if (inArray[loBound] < inArray[hiBound])
		{
			temp = inArray[loBound];
			inArray[loBound] = inArray[hiBound];
			inArray[hiBound] = temp;
		}
		return;
	}

	// 3 or more items to sort 
	// Normal case for this recursive algorithm
	//
	//
	// find the pivot and swap it with the first element of the array
	// The pivot is the 'centre' element of the array
	pivot = inArray[(loBound + hiBound) / 2];
	inArray[(loBound + hiBound) / 2] = inArray[loBound];
	inArray[loBound] = pivot;

	// hiSwap and loSwap are the variables that hold the present index at which
	// the pointers are pointing (pointers that move to the elements to be swapped
	// each iteration (see slides) 
	// initialize hiswap to the last element in the part of the
	// array to be sorted 
	// initialize loswap to the second element in the part of the 
	// array to be sorted (The pivot has been moved into the first element)
	loSwap = loBound + 1;
	hiSwap = hiBound;

	do
	{
		// find the index of the first element incrementing from the start  
		// of the array) with value < the value of the pivot               
		while (loSwap <= hiSwap && inArray[loSwap] >= pivot)
		{
			loSwap++;
		}
		// find the index of the first element, decrementing from the end  
		// of the array) with value > the value of the pivot               
		while (inArray[hiSwap] < pivot)
		{
			hiSwap--;
		}
		// swap the two values found above (within this do loop) 
		if (loSwap < hiSwap)
		{
			temp = inArray[loSwap];
			inArray[loSwap] = inArray[hiSwap];
			inArray[hiSwap] = temp;
		}
		// continue until the two pointers cross
	} while (loSwap < hiSwap);

	// put pivot back in correct position 
	inArray[loBound] = inArray[hiSwap];
	inArray[hiSwap] = pivot;

	// sort subarrays on each side of the replaced pivot 
	QuickSort(inArray, loBound, hiSwap - 1);
	QuickSort(inArray, hiSwap + 1, hiBound);
}

void SelectionSort(int inArray[], int N, int M, int L)
{
	// This function implements the selection sort algorith to sort a part 
	// of the integer array inArray. The part of the array sorted starts   
	// at element N and ends at element M                                  
	// This routine assumes that the array inArray has at least M elements 
	// declare local variables 
	int index;
	int smallestIndex;   //Array index of the smallest element in the part
						 //of the array presently being sorted
	int minIndex;        //Array index of the element whose sorted value is
						 //being determined
	int temp;

	// initialize local variables 
	index = 0;
	smallestIndex = N;
	minIndex = 0;
	temp = 0;


	//Test to assure N and M are both with the array of length L
	//Test that N is less than or equal to M
	// 0 <= N <= M <= L-1
	//If the values of N and M are not consistent with the each
	//other or the length L then do not attempt to sort the array
	//Return the unsorted array. 
	//Print a message to inform the user why the array was not sorted
	if (limitTest(N, M, L) == false)
	{
		cout << "Inconsitent input to DoubleBubbleSort: sort omitted \n";
		return;
	}


	// Zero or one item to sort 
	if (N >= M)
	{
		return;
	}


	for (index = N; index < M; index++)
	{
		smallestIndex = index;

		// Determines the sorted value of array element index
		// Search through the rest of the array (after element index; 
		// inArray[index+1] to inArray[M]) for the array element with 
		// the smallest value. 
		// smallestIndex will become the array element index of this element.
		for (minIndex = index + 1; minIndex < M + 1; minIndex++)
		{
			if (inArray[minIndex] > inArray[smallestIndex])
			{
				smallestIndex = minIndex;
			}
		}

		// swap element inArray[index] with the largest element            
		// inArray[smallestIndex]
		temp = inArray[smallestIndex];
		inArray[smallestIndex] = inArray[index];
		inArray[index] = temp;
	}
}

bool limitTest(int N, int M, int L)
{
	//Test to assure N and M are both with the array of length L
	//Test that N is less than or equal to M
	// 0 <= N <= M <= L-1
	if (N < 0 || N >(L - 1))
	{
		return 0;
	}
	if (M < 0 || M >(L - 1))
	{
		return 0;
	}
	if (N > M)
	{
		return 0;
	}
	return 1;
}


