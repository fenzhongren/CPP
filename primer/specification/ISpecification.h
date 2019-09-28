#ifndef CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_
#define CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_

#include <memory>
#include <functional>

template<typename Entity>
class ISpecification
{
public:
  using SPtr = std::shared_ptr<ISpecification<Entity>>;
  using CSPtr = std::shared_ptr<const ISpecification<Entity>>;

  ISpecification() = default;

  ISpecification(const ISpecification &) = delete;

  ISpecification &operator=(const ISpecification &) = delete;

  virtual SPtr And(CSPtr rhs) const = 0;

  virtual SPtr Or(CSPtr rhs) const = 0;

  virtual SPtr Not() const = 0;

  virtual bool IsSatisfiedBy(const Entity &val) const = 0;

  bool operator()(const Entity &val) const
  {
    return IsSatisfiedBy(val);
  }

  operator std::function<bool(const Entity &val)>() const
  {
    return std::function<bool(const Entity &val)>(std::cref(*this));
  }

  virtual ~ISpecification() = default;

};

#endif  //CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_