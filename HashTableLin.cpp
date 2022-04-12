#include "HashTableLin.h"
#include <cmath>
#include <cstdio>
using namespace std;

HashTableLin::HashTableLin(int maxNum, double load)
{
    // empty table initialized; so current number of entry keys is 0
	numKeys=0;
	// max load is the user-specified value
    max_load=load;
    // max num of keys is the user-specified value
    maxNumKeys=maxNum;

    // get initial size to allocate to table
    // use ceil as we want M rounded UP & cast to int
    M = (int)ceil(maxNumKeys/max_load);
    // remember max load is (n/m) where m is the total size of the table and n is the preferred number of entries that can be inserted before rehashing
    // i.e. if the max num keys (n) is 5 and the table size (m) is 10, then max load is 0.5 and the table fills up 50% before rehashing
    // rearranging, if the max num keys is 5 and the load is 0.5, the initial table size should be 10 (so on the 6th index, we'll rehash)

    // M should be a prime number to avoid collisions
    while (!isPrime(M)){
    	M++;
    }

    // allocate space for table with size M
	table = vector<int>(M);
	// in case we had to increment M to find a prime num, we have to redefine maxNumKeys
	maxNumKeys=(int)M*max_load;

}

bool HashTableLin::isPrime(int n){
	if(n<=1){
		return false; // 1 and 0 are not prime
	}
	// 2 is prime, all other even numbers are non prime
	if(n!=2 && n%2==0){
		return false;
	}
	// a prime num. is an odd integer that is not divisible by any odd integer <= square root of the num.
	for(int i=3;i*i<=n;i+=2){
		if(n%i==0){
			return false;
		}
	}
	// if it breaks the loop, it's prime
	return true;
}

void HashTableLin::insert(int n)
{
    //j
}

void HashTableLin::rehash()
{
    // TODO
}

bool HashTableLin::isIn(int n)
{
    // hash
    return true;
}

void HashTableLin::printKeys()
{
    // go through the table and if there's a nonzero value, print it
	for(int i=0;i<M;i++){
		if(table[i]!=0){
			printf("%d",table[i]);
		}
	}
}

void HashTableLin::printKeysAndIndexes()
{
	// print key value pairs
    for(int i=0;i<M;i++){
    	if(table[i]!=0){
    		printf("%d \t %d \n",i,table[i]);
    	}
    }
}

int HashTableLin::getNumKeys() {
    return numKeys;
}

int HashTableLin::getTableSize() {
    return M;
}

double HashTableLin::getMaxLoadFactor() {
    return max_load;
}

std::vector<double> HashTableLin::simProbeSuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
