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

class TestGreaterThan: public CompositeSpecification<Test::SPtr>
{
public:
  using SPtr = typename CompositeSpecification<Test::SPtr>::SPtr;

  explicit TestGreaterThan(int num): CompositeSpecification<Test::SPtr>(),
   nunber_(num)
  {}

  virtual bool IsSatisfiedBy(const Test::SPtr &val) const override
  {
    return val->get_number() > nunber_;
  }

private:
  int nunber_;
};

class TestLessThan: public CompositeSpecification<Test::SPtr>
{
public:
  using SPtr = typename CompositeSpecification<Test::SPtr>::SPtr;

  explicit TestLessThan(int num): CompositeSpecification<Test::SPtr>(),
   nunber_(num)
  {}

  virtual bool IsSatisfiedBy(const Test::SPtr &val) const override
  {
    return val->get_number() < nunber_;
  }

private:
  int nunber_;
};


/*
 * Test repository
 */

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

  void AddItem(Entity &&val)
  {
    vec_.push_back(std::move(val));
  }

  MyVector<Entity> Query(Specification spec);

  virtual ~Repository();

private:
  MyVector<Entity> vec_;
};

template<typename Entity>
MyVector<Entity> Repository<Entity>::Query(Specification spec)
{
  MyVector<Entity> result;

  for(auto it = vec_.cbegin(); it!=vec_.cend(); ++it) {
    if(spec(*it)) {
      result.push_back(*it);
    }
  }

  return std::move(result);
}

template<typename Entity>
Repository<Entity>::~Repository()
{
  vec_.clear();
}

int main()
{
  Repository<Test::SPtr> repo;
  for(int i=0; i<10; ++i) {
    repo.AddItem(std::make_shared<Test>(i));
  }

  //estGreaterThan::SPtr spec = std::make_shared<TestGreaterThan>(5);

  auto list = repo.Query([](const Test::SPtr &val){return true;});
  //auto list = repo.Query(*spec);

  for(auto val: list) {
    cout << val->get_number() << endl;
  }

  return 0;
}
