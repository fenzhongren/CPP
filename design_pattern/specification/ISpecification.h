#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_

#include<memory>

template<typename EntitySPtr>
class ISpecification
{
public:
  using SPtr = std::shared_ptr<ISpecification>;

  ISpecification() = default;

  virtual bool IsSatisfiedBy(EntitySPtr) = 0;
  virtual SPtr And(SPtr) = 0;
  virtual SPtr Or(SPtr) = 0;
  virtual SPtr Not() = 0;

  virtual ～ISpecification() = default;
};

#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_ISPECIFICATION_H_