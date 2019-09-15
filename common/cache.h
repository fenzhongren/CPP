#ifndef CPP_COMMON_CACHE_H_
#define CPP_COMMON_CACHE_H_

#include <list>
#include <utility>
#include <algorithm>
#include <iostream>

#include "my_assert.h"

template<typename Key, typename T>
class Cache final
{
public:
  using key_type = Key;
  using mapped_type = T;
  using size_type = typename std::list<std::pair<key_type,
   mapped_type>>::size_type;

  Cache() = delete;
  explicit Cache(size_type max_size): max_size_(max_size)
  {}

  ~Cache() = default;

  void AddItem(const key_type &key, const mapped_type &value);
  std::pair<bool, mapped_type> GetItem(const key_type &key);

  std::ostream &Debug(std::ostream &os) const
  {
    for(auto it = content_.cbegin(); it != content_.cend(); ++it) {
      os << it->first << " ";
    }
    return os;
  }

private:
  using value_type = std::pair<key_type, mapped_type>;
  using iterator = typename std::list<value_type>::iterator;

  void RemoveOneFromTail()
  {
    content_.pop_back();
  }

  void AddOne2Head(value_type &&val)
  {
    content_.push_front(std::move(val));
  }

  iterator TryToFindTheKey(const key_type &key)
  {
    iterator it = std::find_if(content_.begin(), content_.end(),
     [key](const value_type &val){return val.first == key ? true : false;});

    return it;
  }

  iterator MoveTheItem2Head(iterator &it)
  {
    if(it != content_.begin()) {
      value_type item = std::make_pair(it->first,
       it->second);
      content_.remove(*it);
      AddOne2Head(std::move(item));
    }
    return content_.begin();
  }

  size_type max_size_;
  std::list<value_type> content_;
};

template<typename Key, typename T>
void Cache<Key, T>::AddItem(const key_type &key,
 const mapped_type &value)
{
  auto it = TryToFindTheKey(key);

  if(it != content_.end()) {
    it->second = value;
    MoveTheItem2Head(it);
  } else {
    size_type size = content_.size();
    AssertTrue(size <= max_size_, "Size error happens!");

    if(size == max_size_) {
      RemoveOneFromTail();
    }

    AddOne2Head(std::make_pair(key, value));
  }
}

template<typename Key, typename T>
std::pair<bool, T> Cache<Key, T>::GetItem
 (const key_type &key)
{
  auto it = TryToFindTheKey(key);

  if(it != content_.end()) {
    it = MoveTheItem2Head(it);
    return std::make_pair(true, it->second);
  } else {
    return std::make_pair(false, mapped_type());
  }
}

#endif  //CPP_COMMON_CACHE_H_