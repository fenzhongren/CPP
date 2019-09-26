#include "composite_specification.h"

#include <iostream>
#include <memory>
#include <functional>

#include "my_vector/my_vector.h"

using std::cout;
using std::endl;

class Test
{
public:
  using SPtr = std::shared_ptr<Test>;
  explicit Test(int num): number_(num)
  {}

  int get_number() const
  {
    return number_;
  }

  virtual ~Test() = default;

private:
  int number_;
};

class TestGreaterThan: public CompositeSpecification<Test>
{
public:
  explicit TestGreaterThan(int num): nunber_(num)
  {}

  virtual bool IsSatisfiedBy(const Test &val) const override
  {
    return val.get_number() > nunber_;
  }

private:
  int nunber_;
};

class TestLessThan: public CompositeSpecification<Test>
{
public:
  explicit TestLessThan(int num): nunber_(num)
  {}

  virtual bool IsSatisfiedBy(const Test &val) const override
  {
    return val.get_number() < nunber_;
  }

private:
  int nunber_;
};


template<typename Entity>
class Repository
{
public:
  using Specification = std::function<bool(const Entity &)>;
  Repository() = default;

  void AddItem(const Entity &val)
  {
    vec_.push_back(val);
  }

  MyVector<Entity> Query(const Specification &spec)

  virtual ~Repository();

private:
  MyVector<Entity> vec_;
};

template<typename Entity>
MyVector<Entity> Repository<Entity>::Query(const Specification &spec)
{
  MyVector<Entity> result;

  for(it = vec_.cbegin(); it!=vec_.cend(); ++it) {
    if(spec(*it)) {
      result.push_back(*it);
    }
  }

  return std::move(result)
}

template<typename Entity>
Repository<Entity>::~Repository()
{
  vec_.clear();
}

