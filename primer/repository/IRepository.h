#ifndef CPP_PRIMER_REPOSITORY_IREPOSITORY_H_
#define CPP_PRIMER_REPOSITORY_IREPOSITORY_H_

#include <functional>
#include "my_vector/my_vector.h"

template<typename Entity>
class IRepository
{
public:
  using Specification = std::function<bool(const Entity &)>;
  using EntityList = MyVector<Entity>;

  IRepository() = default;
  IRepository(const IRepository &) = delete;
  IRepository &operator=(const IRepository &) = delete;

  virtual void AddItem(const Entity &val) = 0;
  virtual void AddItem(Entity &&val) = 0;
  virtual void RemoveItems(const Specification &spec) = 0;
  virtual EntityList Query(const Specification &spec) = 0;

  virtual ~IRepository() = default;
};

#endif  //CPP_PRIMER_REPOSITORY_IREPOSITORY_H_