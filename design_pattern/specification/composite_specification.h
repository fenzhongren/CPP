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
  using CSPtr = typename ISpecification<EntitySPtr>::CSPtr;

  CompositeSpecification() = default;

  virtual bool IsSatisfiedBy(EntitySPtr) const = 0;

  virtual SPtr And(CSPtr right) const override
  {
    return std::make_shared<AndSpecification<EntitySPtr>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Or(CSPtr right) const override
  {
    return std::make_shared<OrSpecification<EntitySPtr>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Not() const override
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
  using CSPtr = typename ISpecification<EntitySPtr>::CSPtr;

  AndSpecification() = delete;
  AndSpecification(CSPtr left, CSPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const override
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
  CSPtr left_;
  CSPtr right_;
};

template<typename EntitySPtr>
class OrSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  using CSPtr = typename ISpecification<EntitySPtr>::CSPtr;

  OrSpecification() = delete;
  OrSpecification(CSPtr left, CSPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const override
  {
    bool result = false;
    if(left_->IsSatisfiedBy(e_sptr) || right_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~OrSpecification() = default;
private:
  CSPtr left_;
  CSPtr right_;
};

template<typename EntitySPtr>
class NotSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  using SPtr = typename ISpecification<EntitySPtr>::SPtr;
  using CSPtr = typename ISpecification<EntitySPtr>::CSPtr;

  NotSpecification() = delete;
  NotSpecification(CSPtr previous): previous_(previous)
  {}

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) const override
  {
    bool result = false;
    if(!previous_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~NotSpecification() = default;
private:
  CSPtr previous_;
};
#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_