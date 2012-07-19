/*
 * File:   my_hash_set.h
 * Author: Ahmet Celik 2009400111
 *
 * Created on 08 Kasım 2011 Salı, 15:56
 */

#ifndef MY_HASH_SET_H_
#define MY_HASH_SET_H_
#include <tr1\unordered_set>
using namespace std;

typedef unsigned  uint32_t;
typedef unsigned short  uint16_t;

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif



/**
 * Equality class template for vertex* that has name field(string)
 * @param v1
 * @param v2
 * @return 
 */
template<typename obj>
class MyEq 
{
	public:
		bool operator() ( obj v1,  obj v2) const
		{	return (v1->name.compare(v2->name)==0); }
};

/**
 * This hash function is taken from 
 * http://www.azillionmonkeys.com/qed/hash.html website.
 */
template<typename obj>
class MyHash 
{
public:
        uint32_t operator() (obj v) const
        {
        const char * data = v->name.data();
        int len= v->name.length();
	uint32_t hash = len, tmp;
	int rem;

	    if (len <= 0 || data == 0) return 0;

	    rem = len & 3;
	    len >>= 2;

	    /* Main loop */
	    for (;len > 0; len--) {
	        hash  += get16bits (data);
	        tmp    = (get16bits (data+2) << 11) ^ hash;
	        hash   = (hash << 16) ^ tmp;
	        data  += 2*sizeof (uint16_t);
	        hash  += hash >> 11;
	    }

	    /* Handle end cases */
	    switch (rem) {
	        case 3: hash += get16bits (data);
	                hash ^= hash << 16;
	                hash ^= data[sizeof (uint16_t)] << 18;
	                hash += hash >> 11;
	                break;
	        case 2: hash += get16bits (data);
	                hash ^= hash << 11;
	                hash += hash >> 17;
	                break;
	        case 1: hash += *data;
	                hash ^= hash << 10;
	                hash += hash >> 1;
	    }

	    /* Force "avalanching" of final 127 bits */
	    hash ^= hash << 3;
	    hash += hash >> 5;
	    hash ^= hash << 4;
	    hash += hash >> 17;
	    hash ^= hash << 25;
	    hash += hash >> 6;

	    return hash;
	}
};

/**
 *      my_hash_set template for vertex*
 * 
 */
template<typename obj>
class my_hash_set
{
public:
	tr1::unordered_set<obj,MyHash<obj>,MyEq<obj> > * data;
	my_hash_set()
        { 
            data = new tr1::unordered_set<obj,MyHash<obj>,MyEq<obj> >();
        }
	~my_hash_set()
        {
            data->clear(); 
            delete data;
        }
	my_hash_set (const my_hash_set&rhs)
        { 
            data =new tr1::unordered_set<obj,MyHash<obj>,MyEq<obj> >(*(rhs.data));   
           
        }
};

#endif /* MY_HASH_SET_H_ */
