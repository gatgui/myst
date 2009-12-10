#ifndef __myst_hashtable_h_
#define __myst_hashtable_h_

#include <myst/config.h>
#include <myst/exceptions.h>
#include <vector>
#include <list>

namespace myst {
  
  typedef unsigned int (*HashFunc)(const unsigned char *, size_t);
  
  template <typename T, HashFunc H>
  struct HashValue {
    static unsigned int Compute(const T &val) {
      return H((const unsigned char *)&val, sizeof(T));
    }
  };

  template <HashFunc H>
  struct HashValue<char*, H> {
    static unsigned int Compute(const char* &val) {
      return H((const unsigned char *)val, strlen(val));
    }
  };

  template <HashFunc H>
  struct HashValue<std::string, H> {
    static unsigned int Compute(const std::string &val) {
      return H((const unsigned char *)val.c_str(), val.length());
    }
  };
  
  MYST_API unsigned int hash_djb(const unsigned char *data, size_t len);
  MYST_API unsigned int hash_jenkins(const unsigned char *data, size_t len);
  MYST_API unsigned int hash_fnv1(const unsigned char *data, size_t len);
  MYST_API unsigned int hash_fnv1a(const unsigned char *data, size_t len);
  MYST_API unsigned int hash_murmur2(const unsigned char *data, size_t len);
  MYST_API unsigned int hash_murmur2a(const unsigned char *data, size_t len);
  
  template <typename KeyType, typename ValueType, HashFunc H=hash_jenkins>
  class HashMap {
    protected:
      
      struct Entry {
        KeyType key;
        ValueType value;
        unsigned int h;
        
        bool operator==(const Entry &rhs) const {
          return (h == rhs.h && key == rhs.key);
        }
      };
      
      typedef typename std::list<Entry> EntryList;
      typedef typename std::vector<KeyType> KeyVector;
      typedef typename std::vector<ValueType> ValueVector;
      typedef typename std::vector<EntryList> EntryListVector;
    
    public:
      
      HashMap(size_t numBuckets=16)
        : mNumBuckets(numBuckets),
          mNumEntries(0) {
        mBuckets.resize(mNumBuckets);
      }
      
      HashMap(const HashMap &rhs)
        : mBuckets(rhs.mBuckets),
          mNumBuckets(rhs.mNumBuckets),
          mNumEntries(rhs.mNumEntries) {
      }
      
      ~HashMap() {
        mBuckets.clear();
      }
      
      HashMap& operator=(const HashMap &rhs) {
        if (this != &rhs) {
          mBuckets = rhs.mBuckets;
          mNumEntries = rhs.mNumEntries;
          mNumBuckets = rhs.mNumBuckets;
        }
        return *this;
      }
      
      size_t size() const {
        return mNumEntries;
      }
      
      double loadFactor() const {
        return (double(mNumEntries) / double(mNumBuckets));
      }
      
      void clear() {
        mNumEntries = 0;
        for (size_t i=0; i<mBuckets.size(); ++i) {
          mBuckets[i].clear();
        }
      }
      
      void insert(const KeyType &key, const ValueType &val) {
        Entry e;
        e.h = HashValue<KeyType, H>::Compute(key);
        e.key = key;
        unsigned int idx = (e.h % mNumBuckets);
        EntryList &el = mBuckets[idx];
        typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
        if (it == el.end()) {
          el.push_back(e);
          el.back().value = val;
          ++mNumEntries;
          if (100 * mNumEntries / mNumBuckets > 50) {
            // load factor above 50%
            expand();
          }
        } else {
          it->value = val;
        }
      }
      
      const ValueType& find(const KeyType &k) const throw(KeyError) {
        Entry e;
        e.h = HashValue<KeyType, H>::Compute(k);
        e.key = k;
        unsigned int idx = (e.h % mNumBuckets);
        EntryList &el = mBuckets[idx];
        typename EntryList::const_iterator it = std::find(el.begin(), el.end(), e);
        if (it == el.end()) {
          std::ostringstream oss;
          oss << k;
          throw KeyError(oss.str());
        }
        return it->value;
      }
      
      ValueType& find(const KeyType &k) throw(KeyError) {
        Entry e;
        e.h = HashValue<KeyType, H>::Compute(k);
        e.key = k;
        unsigned int idx = (e.h % mNumBuckets);
        EntryList &el = mBuckets[idx];
        typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
        if (it == el.end()) {
          std::ostringstream oss;
          oss << k;
          throw KeyError(oss.str());
        }
        return it->value;
      }
      
      void erase(const KeyType &k) {
        Entry e;
        e.h = HashValue<KeyType, H>::Compute(k);
        e.key = k;
        unsigned int idx = (e.h % mNumBuckets);
        EntryList &el = mBuckets[idx];
        typename EntryList::iterator it = std::find(el.begin(), el.end(), e);
        if (it != el.end()) {
          el.erase(it);
          --mNumEntries;
        }
      }
      
      size_t keys(KeyVector &kl) const {
        kl.resize(mNumEntries);
        for (size_t i=0, j=0; i<mNumBuckets; ++i) {
          const EntryList &el = mBuckets[i];
          typename EntryList::const_iterator it = el.begin();
          while (it != el.end()) {
            kl[j] = it->key;
            ++j;
            ++it;
          }
        }
        return kl.size();
      }
      
      size_t values(ValueVector &vl) const {
        vl.resize(mNumEntries);
        for (size_t i=0, j=0; i<mNumBuckets; ++i) {
          const EntryList &el = mBuckets[i];
          typename EntryList::const_iterator it = el.begin();
          while (it != el.end()) {
            vl[j] = it->value;
            ++j;
            ++it;
          }
        }
        return vl.size();
      }
      
    protected:
      
      void expand() {
        size_t oNumBuckets = mNumBuckets;
        mNumBuckets *= 2;
        EntryListVector buckets(mNumBuckets);
        std::swap(buckets, mBuckets);
        for (size_t i=0; i<oNumBuckets; ++i) {
          EntryList &el = buckets[i];
          typename EntryList::iterator it = el.begin();
          while (it != el.end()) {
            unsigned int idx = (it->h % mNumBuckets);
            mBuckets[idx].push_back(*it);
            ++it;
          }
        }
      }
      
    protected:
      
      EntryListVector mBuckets;
      size_t mNumBuckets;
      size_t mNumEntries;
      
  };
}

#endif

