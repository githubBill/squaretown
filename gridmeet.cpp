#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {

	std::ios_base::sync_with_stdio(false);

	//std::fstream myfile(argv[1], std::ios_base::in);

   // M : number of horizontal and vertical lines=roads  -------  3<= N <= 5*10^5  ---------   2<= M <= 10^7
   // assume d = 1 between adjacent intersections
   // Input: N=number of students (int)  and  N coordinates of the form : (i,j) with 1<=i,j<=M
   // Output: total distance that all students have to travel to the  chosen house  (chosen house: so that minimizes the total distance that all the students will travel)


	long long int N, i, w, revIndex;
	unsigned long long int a, b;
	unsigned long long int min_Sum  = std::numeric_limits<unsigned long long int>::max();

	//myfile >> N ;
	cin >> N;
	const long long int Size = N;
	vector< pair<unsigned long long int, unsigned int> > Y_array;
	vector< pair<unsigned long long int, unsigned int> > X_array;
	// need to make pointers instead of array[Size] , g++ works with that but it's  not the general case
	unsigned long long int* Xl_sums = new unsigned long long int[Size];
	unsigned long long int* Xr_sums = new unsigned long long int[Size];
	unsigned long long int* Yl_sums = new unsigned long long int[Size];
	unsigned long long int* Yr_sums = new unsigned long long int[Size];
	unsigned long long int* X_sums  = new unsigned long long int[Size];
	unsigned long long int* Y_sums =  new unsigned long long int[Size];
	unsigned long long int  *final_sums = new unsigned long long int[Size];


	for (i = 0; i < N; i++) {
		cin >> a >> b;   // (i,j) pair
		//myfile >> a >> b ;
		Y_array.push_back(make_pair(a, i));
		X_array.push_back(make_pair(b, i));
		Xl_sums[i] = 0;
		Xr_sums[i] = 0;
		Yl_sums[i] = 0;
		Yr_sums[i] = 0;
		X_sums[i] = 0;
		Y_sums[i] = 0;
		final_sums[i] = 0;
	}

	// make copies to create sorted arrays for x-axis and y-axis
	// (i,j) coordinates => i = y and j = x

	std::sort(X_array.begin(), X_array.end());  // Y_sorted  : key first element of pair
	std::sort(Y_array.begin(), Y_array.end());  // X_sorted  : key first element of pair

	// compute y-distance between each point and all points up to the from the respective point

	for (w = 1; w < Size; w++) {
		Yr_sums[w] += Yr_sums[w - 1] + (Y_array[w].first - Y_array[w - 1].first) * w;

	}

	// compute x-distance between each point and all points to the down from the respective point
	revIndex = 1;
	for (w = Size - 2; w >= 0; w--) {
		Yl_sums[w] += Yl_sums[w + 1] + (Y_array[w + 1].first - Y_array[w].first) * revIndex;
		revIndex++;
	}

	// Sum both vectors up => total y-distance from each point to the other N-1 points
	unsigned int original_pos;
	for (w = 0; w < Size; w++) {

		original_pos = Y_array[w].second;
		Y_sums[original_pos] = Yl_sums[w] + Yr_sums[w];


	}


	// same procedure for x-distance
	for (w = 1; w < Size; w++) {
		Xl_sums[w] += Xl_sums[w - 1] + (X_array[w].first - X_array[w - 1].first) * w;
	}

	revIndex = 1;
	for (w = Size - 2; w >= 0; w--) {
		Xr_sums[w] += Xr_sums[w + 1] + (X_array[w + 1].first - X_array[w].first) * revIndex;
		revIndex++;
	}

	// Sum both vectors up => total x-distance from each point to the other N-1 points
	for (w = 0; w < Size; w++) {
		original_pos = X_array[w].second;
		X_sums[original_pos] = Xl_sums[w] + Xr_sums[w];

	}

	for (w = 0; w < Size; w++) {
		final_sums[w] = X_sums[w] + Y_sums[w];
	}

	for (w = 0; w < Size; w++) {
		if (final_sums[w] < min_Sum)
			min_Sum = final_sums[w];
	}

	cout << min_Sum << endl;

	//deallocate the array
	delete[] Xl_sums;
	delete[] Xr_sums;
	delete[] Yl_sums;
	delete[] Yr_sums;
	delete[] X_sums;
	delete[] Y_sums;
	delete[] final_sums;

	return 0;
}

