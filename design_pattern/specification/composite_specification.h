#ifndef CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_
#define CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_

#include "ISpecification.h"

template<typename Entity>
class AndSpecification;

template<typename Entity>
class OrSpecification;

template<typename Entity>
class NotSpecification;

template<typename Entity>
class CompositeSpecification: public ISpecification<Entity>,
  public std::enable_shared_from_this<CompositeSpecification<Entity>>
{
public:
  using SPtr = typename ISpecification<Entity>::SPtr;
  using CSPtr = typename ISpecification<Entity>::CSPtr;

  CompositeSpecification() = default;

  virtual bool IsSatisfiedBy(const Entity &) const = 0;

  virtual SPtr And(CSPtr right) const override
  {
    return std::make_shared<AndSpecification<Entity>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Or(CSPtr right) const override
  {
    return std::make_shared<OrSpecification<Entity>>(this->shared_from_this(),
      right);
  }

  virtual SPtr Not() const override
  {
    return std::make_shared<NotSpecification<Entity>>(this->shared_from_this());
  }

  virtual ~CompositeSpecification() = default;
};

template<typename Entity>
class AndSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename ISpecification<Entity>::SPtr;
  using CSPtr = typename ISpecification<Entity>::CSPtr;

  AndSpecification() = delete;
  AndSpecification(CSPtr left, CSPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(const Entity &entity) const override
  {
    bool result = false;

    if(left_->IsSatisfiedBy(entity)) {
      if(right_->IsSatisfiedBy(entity)) {
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

template<typename Entity>
class OrSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename ISpecification<Entity>::SPtr;
  using CSPtr = typename ISpecification<Entity>::CSPtr;

  OrSpecification() = delete;
  OrSpecification(CSPtr left, CSPtr right): left_(left), right_(right)
  {}

  virtual bool IsSatisfiedBy(const Entity &entity) const override
  {
    bool result = false;
    if(left_->IsSatisfiedBy(entity) || right_->IsSatisfiedBy(entity)) {
      result = true;
    }
    return result;
  }

  virtual ~OrSpecification() = default;
private:
  CSPtr left_;
  CSPtr right_;
};

template<typename Entity>
class NotSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename ISpecification<Entity>::SPtr;
  using CSPtr = typename ISpecification<Entity>::CSPtr;

  NotSpecification() = delete;
  NotSpecification(CSPtr previous): previous_(previous)
  {}

  virtual bool IsSatisfiedBy(const Entity &entity) const override
  {
    bool result = false;
    if(!previous_->IsSatisfiedBy(entity)) {
      result = true;
    }
    return result;
  }

  virtual ~NotSpecification() = default;
private:
  CSPtr previous_;
};
#endif  //CPP_DESIGN_PATTERN_SPECIFICATION_COMPOSITE_SPECIFICATION_H_