#ifndef HASHTABLELIN_H_
#define HASHTABLELIN_H_

#include <vector>

class HashTableLin
{
private:
	std::vector<int> table;
	// define other private fields to store:
	// the size of the table
	int M;
	// current number of keys stored in the table
	int numKeys;
	// max number of keys that can be stored before rehash
	int maxNumKeys;
	// the maximum load factor allowed
	double max_load;

public:
	// required constructor
	HashTableLin(int maxNum, double load);

	// required methods
	bool isPrime(int n);
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	static std::vector<double> simProbeUnsuccess(); // for bonus

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLELIN_H_ */
