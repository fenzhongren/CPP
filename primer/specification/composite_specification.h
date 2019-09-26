#ifndef CPP_PRIMER_SPECIFICATION_COMPOSITESPECIFICATION_H_
#define CPP_PRIMER_SPECIFICATION_COMPOSITESPECIFICATION_H_

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
  CompositeSpecification(const CompositeSpecification &) = delete;
  CompositeSpecification &operator=(const CompositeSpecification &) = delete;

  virtual SPtr And(CSPtr rhs) const override
  {
    return std::make_shared<AndSpecification<Entity>>(this->shared_from_this(),
     rhs);
  }

  virtual SPtr Or(CSPtr rhs) const override
  {
    return std::make_shared<OrSpecification<Entity>>(this->shared_from_this(),
     rhs);
  }

  virtual SPtr Not() const override
  {
    return std::make_shared<NotSpecification<Entity>>(this->shared_from_this());
  }

  virtual bool IsSatisfiedBy(const Entity &val) const = 0;

  virtual ~CompositeSpecification() = default;
};

template<typename Entity>
class AndSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename CompositeSpecification<Entity>::SPtr;
  using CSPtr = typename CompositeSpecification<Entity>::CSPtr;

  AndSpecification() = delete;
  AndSpecification(const AndSpecification &) = delete;
  AndSpecification &operator=(const AndSpecification &) = delete;

  AndSpecification(CSPtr lhs, CSPtr rhs): lhs_(lhs), rhs_(rhs)
  {}

  virtual bool IsSatisfiedBy(const Entity &val) const override
  {
    bool result = false;

    if(lhs_->IsSatisfiedBy(val) && rhs_->IsSatisfiedBy(val)) {
      result = true;
    }

    return result;
  }

  virtual ~AndSpecification() = default;

private:
  CSPtr lhs_;
  CSPtr rhs_;
};

template<typename Entity>
class OrSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename CompositeSpecification<Entity>::SPtr;
  using CSPtr = typename CompositeSpecification<Entity>::CSPtr;

  OrSpecification() = delete;
  OrSpecification(const OrSpecification &) = delete;
  OrSpecification &operator=(const OrSpecification &) = delete;

  OrSpecification(CSPtr lhs, CSPtr rhs): lhs_(lhs), rhs_(rhs)
  {}

  virtual bool IsSatisfiedBy(const Entity &val) const override
  {
    bool result = false;

    if(lhs_->IsSatisfiedBy(val) || rhs_->IsSatisfiedBy(val)) {
      result = true;
    }

    return result;
  }

  virtual ~OrSpecification() = default;

private:
  CSPtr lhs_;
  CSPtr rhs_;
};

template<typename Entity>
class NotSpecification: public CompositeSpecification<Entity>
{
public:
  using SPtr = typename CompositeSpecification<Entity>::SPtr;
  using CSPtr = typename CompositeSpecification<Entity>::CSPtr;

  NotSpecification() = delete;
  NotSpecification(const NotSpecification &) = delete;
  NotSpecification &operator=(const NotSpecification &) = delete;

  explicit NotSpecification(CSPtr lhs): lhs_(lhs)
  {}

  virtual bool IsSatisfiedBy(const Entity &val) const override
  {
    bool result = false;

    if(!lhs_->IsSatisfiedBy(val)) {
      result = true;
    }

    return result;
  }

  virtual ~NotSpecification() = default;

private:
  CSPtr lhs_;
};

#endif  //CPP_PRIMER_SPECIFICATION_COMPOSITESPECIFICATION_H_