#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include "RedBlackTree.h"

using namespace std;

template< typename T >
typename std::vector<T>::iterator insert_sorted( std::vector<T> & vec, T const& item ) {
    return vec.insert
            (
                    std::upper_bound( vec.begin(), vec.end(), item ),
                    item
            );
}

int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();

	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;

	// Your code goes here to simulate leaving / joining.
    vector<int> insert {};
    vector<int> remove {};
    const int range_from  = 0;
    const int range_to  = N;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    int random = distr(generator);
    remove.push_back(random);

    while(remove.size() != 10000){
        random = distr(generator);

        if(!std::binary_search(remove.begin(), remove.end(),random)) {
            insert_sorted(remove, random);
            start = clock();
            rbt.Remove(random);
            stop = clock();
            duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
            cout << "Deleted " << to_string(random) << " ID in " << (duration) << " seconds." << endl;
        }
    }

	return 0;
}