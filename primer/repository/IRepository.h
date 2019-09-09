#ifndef CPP_PRIMER_REPOSITORY_IREPOSITORY_H_
#define CPP_PRIMER_REPOSITORY_IREPOSITORY_H_

#include <functional>
#include <vector>

template<Entity>
class IRepository
{
public:
  using Specification = std::function<bool(const Entity &val)>;
  using EntityList = std::vector<Entity>;

  IRepository() = default;
  IRepository(const IRepository &) = delete;
  IRepository &operator=(const IRepository &) = delete;

  void AddItem(const Entity &val) = 0;
  void AddItem(Entity &&val) = 0;
  void RemoveItems(Specification &spec) = 0;
  EntityList Query(Specification &spec) = 0;

  virtual ~IRepository() = default;
};

#endif  //CPP_PRIMER_REPOSITORY_IREPOSITORY_H_