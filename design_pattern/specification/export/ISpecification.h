#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_

#include<memory>

template<typename Entity>
class ISpecification
{
public:
  using CSPtr = std::shared_ptr<const ISpecification<Entity>>;
  using SPtr = std::shared_ptr<ISpecification<Entity>>;

  ISpecification() = default;

  virtual bool IsSatisfiedBy(const Entity &) const = 0;
  virtual SPtr And(SPtr) const = 0;
  virtual SPtr Or(SPtr) const = 0;
  virtual SPtr Not() const = 0;

  virtual ~ISpecification() = default;
};

#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_