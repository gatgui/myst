/*

Copyright (C) 2009  Gaetan Guidet

This file is part of myst.

myst is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

myst is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#include <myst/hashtable.h>

namespace myst {

unsigned int hash_djb(const unsigned char *data, size_t len) {
  unsigned int hash = 5381;
  
  for (size_t i=0; i<len; ++i) {
    hash = ((hash << 5) + hash) + (unsigned int)data[i]; /* hash * 33 + c */
  }

  return hash;
}

unsigned int hash_jenkins(const unsigned char *data, size_t len) {
  unsigned int hash = 0;
  
  for (size_t i=0; i<len; ++i) {
    hash += (unsigned int) data[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  
  return hash;
}

unsigned int hash_fnv1(const unsigned char *data, size_t len) {
  unsigned int hash = 2166136261; // use 14695981039346656037 for 64 bit hash
  
  for (size_t i=0; i<len; ++i) {
    hash = hash * 16777619; // use 1099511628211 for 64 bit hash
    hash = hash ^ ((unsigned int) data[i]);
  }
  
  return hash;
}

unsigned int hash_fnv1a(const unsigned char *data, size_t len) {
  unsigned int hash = 2166136261; // use 14695981039346656037 for 64 bit hash
  
  for (size_t i=0; i<len; ++i) {
    hash = hash ^ ((unsigned int) data[i]);
    hash = hash * 16777619; // use 1099511628211 for 64 bit hash
  }
  
  return hash;
}

unsigned int hash_murmur2(const unsigned char *data_in, size_t len) {
  
  unsigned int seed = 0;
  
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.
  const unsigned int m = 0x5bd1e995;
  const int r = 24;
  
  // Initialize the hash to a 'random' value
  unsigned int h = seed ^ len;
  
  // Mix 4 bytes at a time into the hash
  const unsigned char *data = data_in;
  
  while (len >= 4) {
    unsigned int k = *((unsigned int *) data);
    
    k *= m; 
    k ^= k >> r; 
    k *= m; 
    
    h *= m; 
    h ^= k;
    
    data += 4;
    len -= 4;
  }
  
  // Handle the last few bytes of the input array
  switch (len) {
    case 3  : h ^= data[2] << 16;
    case 2  : h ^= data[1] << 8;
    case 1  : h ^= data[0];
              h *= m;
    default : break;
  };
  
  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  
  return h;
} 

#define mmix(h, k) { k *= m; k ^= k >> r; k *= m; h *= m; h ^= k; }

unsigned int hash_murmur2a(const unsigned char *data_in, size_t len) {
  
  unsigned int seed = 0;
  
  const unsigned int m = 0x5bd1e995;
  const int r = 24;
  unsigned int l = len;
  
  const unsigned char * data = data_in;
  
  unsigned int h = seed;
  
  while (len >= 4) {
    unsigned int k = *(unsigned int*)data;
    
    mmix(h, k);
    
    data += 4;
    len -= 4;
  }
  
  unsigned int t = 0;
  
  switch (len) {
    case 3  : t ^= data[2] << 16;
    case 2  : t ^= data[1] << 8;
    case 1  : t ^= data[0];
    default : break;
  };
  
  mmix(h, t);
  mmix(h, l);
  
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  
  return h;
}

}

/*

class MurmurHash2A
{
public:
  
  void Begin(unsigned int seed = 0) {
    m_hash  = seed;
    m_tail  = 0;
    m_count = 0;
    m_size  = 0;
  }
  
  void Add(const char *data) {
    unsigned int len = strlen(data);

    m_size += len;

    MixTail(data, len);

    while(len >= 4) {
      unsigned int k = *(unsigned int*)data;
      mmix(m_hash, k);
      data += 4;
      len -= 4;
    }

    MixTail(data, len);
  }
  
  unsigned int End(void) {
    mmix(m_hash, m_tail);
    mmix(m_hash, m_size);

    m_hash ^= m_hash >> 13;
    m_hash *= m;
    m_hash ^= m_hash >> 15;

    return m_hash;
  }

private:
  
  static const unsigned int m = 0x5bd1e995;
  static const int r = 24;

  void MixTail(const char *data, unsigned int len) {

    while (len && ((len<4) || m_count)) {

      m_tail |= (*data++) << (m_count * 8);

      m_count++;
      len--;

      if (m_count == 4) {
        mmix(m_hash,m_tail);
        m_tail = 0;
        m_count = 0;
      }
    }
  }

  unsigned int m_hash;
  unsigned int m_tail;
  unsigned int m_count;
  unsigned int m_size;
};

*/

