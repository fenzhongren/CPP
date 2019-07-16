#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_

#include "ISpecification.h"

template<typename EntitySPtr>
class AndSpecification;

template<typename EntitySPtr>
class OrSpecification;

template<typename EntitySPtr>
class NotSpecification;

template<typename EntitySPtr>
class CompositeSpecification: public ISpecification<EntitySPtr>,
  public std::enable_shared_from_this<CompositeSpecification<EntitySPtr>>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  CompositeSpecification() = default;

  virtual bool IsSatisfiedBy(EntitySPtr) const = 0;

  virtual SPtr And(SPtr right) const
  {
    return std::make_shared<AndSpecification<EntitySPtr>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Or(SPtr right) const
  {
    return std::make_shared<OrSpecification<EntitySPtr>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Not() const
  {
    return std::make_shared<NotSpecification<EntitySPtr>>(this->shared_from_this());
  }

  virtual ~CompositeSpecification() = default;
};

template<typename EntitySPtr>
class AndSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  AndSpecification() = delete;
  AndSpecification(SPtr left, SPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const
  {
    bool result = false;

    if(left_->IsSatisfiedBy(e_sptr)) {
      if(right_->IsSatisfiedBy(e_sptr)) {
        result = true;
      }
    }
    return result;
  }

  virtual ~AndSpecification() = default;
private:
  SPtr left_;
  SPtr right_;
};

template<typename EntitySPtr>
class OrSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  OrSpecification() = delete;
  OrSpecification(SPtr left, SPtr right);

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const
  {
    bool result = false;
    if(left_->IsSatisfiedBy(e_sptr) || right_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~OrSpecification() = default;
private:
  SPtr left_;
  SPtr right_;
};

template<typename EntitySPtr>
class NotSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  NotSpecification() = delete;
  NotSpecification(SPtr previous);

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const
  {
    bool result = false;
    if(!previous_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~NotSpecification() = default;
private:
  SPtr previous_;
};
#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_