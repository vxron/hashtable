#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_

#include <vector>

class HashTableQuad
{
private:
	// must contain this private field
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
	HashTableQuad(int maxNum, double load);

	// required methods
	bool isPrime(int n);
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	int insertCount(int n);
	static std::vector<double> simProbeSuccess();

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */
