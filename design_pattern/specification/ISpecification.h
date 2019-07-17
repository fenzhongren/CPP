#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_

#include<memory>

template<typename EntitySPtr>
class ISpecification
{
public:
  using CSPtr = std::shared_ptr<const ISpecification<EntitySPtr>>;
  using SPtr = std::shared_ptr<ISpecification<EntitySPtr>>;

  ISpecification() = default;

  virtual bool IsSatisfiedBy(EntitySPtr) const = 0;
  virtual SPtr And(CSPtr) const = 0;
  virtual SPtr Or(CSPtr) const = 0;
  virtual SPtr Not() const = 0;

  virtual ~ISpecification() = default;
};

#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_