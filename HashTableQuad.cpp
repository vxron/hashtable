#include "HashTableQuad.h"
#include <cmath>
#include <cstdio>
#include <random>
using namespace std;


HashTableQuad::HashTableQuad(int maxNum, double load)
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

bool HashTableQuad::isPrime(int n){
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

void HashTableQuad::insert(int n)
{
	// check for duplicate
    if(isIn(n)==true){
    	return;
    }

    int i = n % M;
    int k=1;

    if(table[i]==0){
    	table[i]=n; // no need for probing
    }

    else{
    	while(table[i]!=0 && k<=M){
    		i=(n+(k*k))%M;
    		k++;
    	}
    	if(k==M+1){ //cycling; can't insert
    		return;
    	}
    	table[i]=n;
    }
    numKeys++;
    double load=numKeys/(M+0.0);
    if(load>max_load){
    	rehash();
    }

}

void HashTableQuad::rehash()
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

bool HashTableQuad::isIn(int n)
{
	// hash index
	int i = n % M;
	int k=1;

	// make sure i doesn't surpass
	while(table[i]!=0){
		// if table(i) is 0 then the element hasn't been found; not placed via linear probing
		if(table[i]==n){
			return true; // element has been found
		}
		else{
			// continue quad probing until a zero element is reached, or element is found
			i = (n+(k*k)) % M;
			// if k gets back to original value, it's done the full circle and this table doesn't have the value n
			if(k == M){ // i.e. n + M^2 % M = n % M, i's original val
				break;
			}
		}
		k++;
	}
	// element n wasn't found
	return false;
}

void HashTableQuad::printKeys()
{
    // go through the table and if there's a nonzero value, print it
	for(int i=0;i<M;i++){
		if(table[i]!=0){
			printf("%d",table[i]);
		}
	}
}

void HashTableQuad::printKeysAndIndexes()
{
	// print key value pairs
    for(int i=0;i<M;i++){
    	if(table[i]!=0){
    		printf("%d \t %d \n",i,table[i]);
    	}
    }
}

int HashTableQuad::getNumKeys() {
    return numKeys;
}

int HashTableQuad::getTableSize() {
    return M;
}

double HashTableQuad::getMaxLoadFactor() {
    return max_load;
}

// function for number of probes it takes to insert a certain number
int HashTableQuad::insertCount(int n){
	int count=0;

	// check for duplicate
	if(isIn(n)==true){
		return 0;
	}

	int i = n % M;
	int k=1;

	if(table[i]==0){
		table[i]=n; // no need for probing
		count++;
		return count;
	}

	else{
		while(table[i]!=0 && k<=M){
			i=(n+(k*k))%M;
			k++;
			count++;
		}

		if(k==M+1){ //cycling; can't insert
			//count++;
			return count;
		}

		table[i]=n;
		count++;
	}

	return count;
}

std::vector<double> HashTableQuad::simProbeSuccess()
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
	    	while(k<avgTries){
	    		HashTableQuad tmp = HashTableQuad(maxKeys,tryLoad);
	    		double avg=0;
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
