#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_

#include "ISpecification.h"

#include <memory>

template<typename EntitySPtr>
class AndSpecification;

template<typename EntitySPtr>
class OrSpecification;

template<typename EntitySPtr>
class NotSpecification;

template<typename EntitySPtr>
class CompositeSpecification: public ISpecification<EntitySPtr>
  public std::enable_shared_from_this<CompositeSpecification>
{
public:
  CompositeSpecification() = default;

  virtual bool IsSatisfiedBy(EntitySPtr) = 0;

  virtual SPtr And(SPtr right) override
  {
    return make_shared<AndSpecification<EntitySPtr>>(shared_from_this(),
      right);
  }

  virtual SPtr Or(SPtr right) override
  {
    return make_shared<OrSpecification<EntitySPtr>>(shared_from_this(),
      right);
  }

  virtual SPtr Not() override
  {
    return make_shared<NotSpecification<EntitySPtr>>(shared_from_this());
  }

  virtual ~CompositeSpecification() = default;
};

template<typename EntitySPtr>
class AndSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  AndSpecification() = delete;
  AndSpecification(SPtr left, SPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) override
  {
    bool result = false;

    if(left_->IsSatisfiedBy(e_sptr)) {
      if(right_->IsSatisfiedBy(e_sptr)) {
        result = true;
      }
    }
    return result;
  }

  virtual ~AndSpecification() = default
private:
  SPtr left_;
  SPtr right_;
};

template<typename EntitySPtr>
class OrSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  OrSpecification() = delete;
  OrSpecification(SPtr left, SPtr right);

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) override
  {
    bool result = false;
    if(left_->IsSatisfiedBy(e_sptr) || right_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~OrSpecification() = default
private:
  SPtr left_;
  SPtr right_;
};

template<typename EntitySPtr>
class NotSpecification: public CompositeSpecification<EntitySPtr>
{
public:
  NotSpecification() = delete;
  NotSpecification(SPtr previous);

  virtual bool IsSatisfiedBy(EntitySPtr e_sptr) override
  {
    bool result = false;
    if(!previous_->IsSatisfiedBy(e_sptr)) {
      result = true;
    }
    return result;
  }

  virtual ~NotSpecification() = default
private:
  SPtr previous_;
};
#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_