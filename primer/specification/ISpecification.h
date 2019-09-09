#ifndef CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_
#define CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_

#include <memory>

template<typename Entity>
class ISpecification
{
public:
  using SPtr = std::shared_ptr<ISpecification<Entity>>;
  using CSPtr = std::shared_ptr<const ISpecification<Entity>>

  ISpecification() = default;

  ISpecification(const ISpecification &) = delete;

  ISpecification &operator=(const ISpecification &) = delete;

  SPtr And(CSPtr lhs, CSPtr rhs) = 0;

  SPtr Or(CSPtr lhs, CSPtr rhs) = 0;

  SPtr Not(CSPtr lhs) = 0;

  bool IsSatisfiedBy(const Entity &val) const = 0;

  bool operator()(const Entity &val) const;
  {
    return IsSatisfiedBy(val);
  }

  virtual ~ISpecification() = default;

};

#endif  //CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_