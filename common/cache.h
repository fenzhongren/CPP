#ifndef CPP_COMMON_CACHE_H_
#define CPP_COMMON_CACHE_H_

#include <list>
#include <utility>

#include "my_assert.h"

template<typename Key, typename Value>
class Cache final
{
public:
  Cache() = delete;
  explicit Cache(std::size_t size): max_size_(size)
  {}

  ~Cache() = default;

  void AddItem(const Key &key, const Value &value);
  Value GetItem(const Key &key);

private:
  std::size_t max_size_;
  std::list<std::pair<Key, Value>> content_;
};

template<typename Key, typename Value>
void Cache<key, Value>::AddItem(const Key &key, const Value &value)
{
  std::size_t size = content_.size();
  AssertTrue(size > max_size_, "Size error happens!");

  if(size == max_size_) {
    content_.pop_back();
  }

  content_.push_front(std::make_pair(key, value));
}

template<typename Key, typename Value>
Value Cache<key, Value>::GetItem(const Key &key)
{
  
}

#endif  //CPP_COMMON_CACHE_H_