#include "HashTableLin.h"
#include <cmath>
#include <cstdio>
#include <random>
#include <set>
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
	if(isIn(n)==false){
		// get hash code (index)
		int i = n % M;

		// insert directly at index if empty
		if(table[i]==0){
			table[i]=n;
		}
		// otherwise perform linear probing to attempt to find a slot
		else{
			/*
			if(isIn(0)==false){
				rehash();
			}
			*/
			while(table[i]!=0){ // once it equals 0, we can insert at this index
				i=(i+1)%M;
			}
			// break when it's 0
			table[i]=n;

		}

		// increment properties
		numKeys++;
		double load = numKeys/(M+0.0);
		if(load>max_load){
			rehash();
		}
	}
}

// function for number of probes it takes to insert a certain number
int HashTableLin::insertCount(int n){
	int count=0;

	// check for duplicate
	if(isIn(n)==true){
		return 0;
	}

	int i = n % M;

	if(table[i]==0){
		table[i]=n;
		count++;
		return count;
	}

	else{
		while(table[i]!=0){
			i=(i+1)%M;
			count++;
		}
		/*
		if(i==n%M){ //cycling; can't insert
			return count;
		}
		*/
	}
	table[i]=n;
	count++;

	return count;
}

void HashTableLin::rehash()
{
    std::vector<int> tmp = table;
    int initial_size = table.size();

    // for rehashing, we double the size of the array
    M*=2;
    // what can fit (before rehashing) is now max_load times the new size
    maxNumKeys=max_load*M;

    // but remember we need a prime number for size of table
    while(!isPrime(M)){
    	M++;
    }

    // wipe table
    table.resize(0);
    // resize table so it contains M elements (new size)
    table.resize(M,0);

    // numKeys and shit wouldn't change
    // but we have to reset numKeys to 0 cuz it increments when we call insert function
    numKeys=0;
    // replace values
    for(int i=0;i<initial_size;i++){
    	if(tmp[i]!=0){
    		insert(tmp[i]);
    	}
    }

}

bool HashTableLin::isIn(int n)
{
	// hash index
	int i = n % M;

	// make sure i doesn't surpass
	while(table[i]!=0){
		// if table(i) is 0 then the element hasn't been found; not placed via linear probing
		if(table[i]==n){
			return true; // element has been found
		}
		else{
			// continue linear probing until a zero element is reached, or element is found
			i = (i + 1) % M;
			// if i gets back to original value, it's done the full circle and this table doesn't have the value n
			if(i == (n % M)){
				break;
			}
		}
	}
	// element n wasn't found
    return false;
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
    vector<double> result(9);
    // for loop containing diff load factors
    double tryLoad=0;
    double maxKeys = 10000;
    double avgTries = 100;
    for(int j=0;j<9;j++){
    	tryLoad+=0.1;
    	int k=0;
    	double avg2=0;
    	double avg=0;
    	while(k<avgTries){
    		HashTableLin tmp = HashTableLin(maxKeys,tryLoad);
    		while(tmp.numKeys<maxKeys){
    			int n = rand()*rand();
    			if(tmp.isIn(n)==false){
    				avg+=tmp.insertCount(n);
    				tmp.numKeys++;
    			}
    		}
    		k++;
    		avg/=maxKeys;
    		avg2+=avg;
    	}
    	avg2/=avgTries;
    	result[j]=avg2;
    }

    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
