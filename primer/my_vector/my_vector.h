#ifndef CPP_LOCAL_TEST_MY_VECTOR_MY_VECTOR_H_
#define CPP_LOCAL_TEST_MY_VECTOR_MY_VECTOR_H_

#include "my_assert.h"

#include <string>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <iostream>


template<typename T>
class MyVector
{
public:
  using size_type = typename std::allocator<T>::size_type;
  using iterator = T *;
  using const_iterator = const T *;

  const static size_type kMinAlloc = 16;

  explicit MyVector(size_type size = 0, const T &val = T());

  template<typename InputIterator>
  MyVector(InputIterator first, InputIterator last): start_(nullptr),
   first_free_(nullptr), end_(nullptr)
  {
    for(auto it=first; it!=last; ++it) {
      push_back(*it);
    }
  }

  MyVector(std::initializer_list<T> il);

  size_type size() const
  {return first_free_ - start_;}

  size_type capacity() const
  {return end_ - start_;}

  bool empty() const
  {return first_free_ == start_;}

  T &operator[](size_type n)
  {return at(n);}

  const T &operator[](size_type n) const
  {
    auto ptr = const_cast<MyVector<T> *>(this);
    return (*ptr)[n];
  }

  T &at(size_type n);
  const T &at(size_type n) const;

  T &front()
  {return at(0);}

  const T &front() const
  {
    auto ptr = const_cast<MyVector<T> *>(this);
    return ptr->front();
  }

  T &back()
  {return at(size()-1);}

  const T &back() const
  {
    auto ptr = const_cast<MyVector<T> *>(this);
    return ptr->back();
  }

  void push_back(const T &val);
  void push_back(T &&val);
  void pop_back();

  iterator begin()
  {return start_;}

  iterator end()
  {return first_free_;}

  const_iterator begin() const
  {return start_;}

  const_iterator end() const
  {return first_free_;}

private:
  bool HasNCapacityLeft(size_type n) const
  {
    size_type left = GetLeftCapacity();
    return left >= n;
  }

  bool ReAllocate(size_type capacity);

  size_type CalculateNewCapacityFromNeededSize(size_type need_size) const;

  size_type CalculateNextMultipleOf2Unsigned(size_type val) const;

  size_type GetLeftCapacity() const
  {
    return capacity() - size();
  }

  void Free(T *start, T *first_free, T *end)
  {
    for(auto pos = start; pos != end; ++pos) {
      alloc_.destroy(pos);
    }
    alloc_.deallocate(start, (end - start));
  }

  void AddOneToTailSafely(const T &val)
  {
    alloc_.construct(first_free_, val);
    ++first_free_;
  }

  void AddOneToTailSafely(T &&val)
  {
    alloc_.construct(first_free_, std::move(val));
    ++first_free_;
  }

  T RemoveOneFromTailSafely()
  {
    --first_free_;
    alloc_.destroy(first_free_);
  }

  size_type CalculateCapacityFromSize(size_type size) const
  {
    size_type capacity = kMinAlloc;
    if(size >= kMinAlloc) {
      capacity = CalculateNextMultipleOf2Unsigned(size+kMinAlloc-1);
    }
    return capacity;
  }

  std::allocator<T> alloc_;
  T *start_;
  T *first_free_;
  T *end_;
};

template<typename T>
MyVector<T>::MyVector(size_type size, const T &val): start_(nullptr),
 first_free_(nullptr), end_(nullptr)
{
  size_type capacity = CalculateCapacityFromSize(size);

  start_ = alloc_.allocate(capacity);
  first_free_ = std::uninitialized_fill_n(start_, size, val);
  end_ = start_ + capacity;
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> il): start_(nullptr),
 first_free_(nullptr), end_(nullptr)
{
  size_type size = il.size();
  size_type capacity = CalculateCapacityFromSize(size);

  start_ = alloc_.allocate(capacity);
  first_free_ = std::uninitialized_copy(il.begin(), il.end(), start_);
  end_ = start_ + capacity;
}

template<typename T>
void MyVector<T>::push_back(const T &val)
{
  if(HasNCapacityLeft(1)) {
    AddOneToTailSafely(val);
  } else {
    size_type new_capacity = CalculateNewCapacityFromNeededSize(1);
    ReAllocate(new_capacity);
    AssertTrue(HasNCapacityLeft(1), "Can't get enough space!");
    this->push_back(val);
  }
}

template<typename T>
void MyVector<T>::push_back(T &&val)
{
  if(HasNCapacityLeft(1)) {
    AddOneToTailSafely(std::move(val));
  } else {
    size_type new_capacity = CalculateNewCapacityFromNeededSize(1);
    ReAllocate(new_capacity);
    AssertTrue(HasNCapacityLeft(1), "Can get enough space!");
    this->push_back(std::move(val));
  }
}

template<typename T>
void MyVector<T>::pop_back()
{
  AssertFalse(empty(), "The container is empty!");

  RemoveOneFromTailSafely();
}

template<typename T>
bool MyVector<T>::ReAllocate(size_type new_capacity)
{
  AssertTrue(new_capacity>capacity(), "Don't need to reallocate!");

  T *new_start = alloc_.allocate(new_capacity);

  T *old_start = start_;
  T *old_first_free = first_free_;
  T *old_end = end_;

  first_free_ = std::uninitialized_copy(std::make_move_iterator(old_start),
   std::make_move_iterator(old_first_free), new_start);
  start_ = new_start;
  end_ = start_ + new_capacity;

  Free(old_start, old_first_free, old_end);
  return true;
}

template<typename T>
typename MyVector<T>::size_type 
 MyVector<T>::CalculateNewCapacityFromNeededSize(size_type need_size) const
{
  size_type left = GetLeftCapacity();
  if(left >= need_size) {
    return 0;
  }

  size_type total_size = capacity() + need_size;
  return CalculateCapacityFromSize(total_size);
}

template<typename T>
typename MyVector<T>::size_type 
 MyVector<T>::CalculateNextMultipleOf2Unsigned(size_type val) const
{
  size_type type_max = UINT32_MAX;

  if(val > (type_max/2)) {
    return type_max;
  }

  size_type result = 1;
  while(result <= val) {
    result = result * 2;
  }

  return result;
}

template<typename T>
T &MyVector<T>::at(size_type n)
{
  AssertTrue(n<size(), "Out of range happens!");
  return start_[n];
}

template<typename T>
const T &MyVector<T>::at(size_type n) const
{
  auto ptr = const_cast<MyVector<T> *>(this);
  return ptr->at(n);
}

#endif  //CPP_LOCAL_TEST_MY_VECTOR_MY_VECTOR_H_