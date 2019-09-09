#ifndef CPP_PRIMER_SPECIFICATION_COMPOSITESPECIFICATION_H_
#define CPP_PRIMER_SPECIFICATION_COMPOSITESPECIFICATION_H_

#include "ISpecification.h"

#include <memory>

template<typename Entity>
class AndSpecification;

template<typename Entity>
class OrSpecification;

template<typename Entity>
class NotSpecification;

template<typename Entity>
class CompositeSpecification: public ISpecification<Entity>
{
public:
  using SPtr = ISpecification<Entity>::SPtr;
  using CSPtr = ISpecification<Entity>::CSPtr;

  CompositeSpecification() = default;
  CompositeSpecification(const CompositeSpecification &) = delete;
  CompositeSpecification &operator=(const CompositeSpecification &) = delete;

  SPtr And(CSPtr lhs, CSPtr rhs)
  {
    return std::make_shared<AndSpecification>(lhs, rhs);
  }

  SPtr Or(CSPtr lhs, CSPtr rhs)

  SPtr Not(CSPtr lhs)

  bool IsSatisfiedBy(const Entity &val) const = 0;

  virtual ~CompositeSpecification() = default;
};

template<typename Entity>
class AndSpecification: public CompositeSpecification
{
public:
  using SPtr = CompositeSpecification<Entity>::SPtr;
  using CSPtr = CompositeSpecification<ENtity>::CSPtr;

  AndSpecification() = delete;
  AndSpecification(const AndSpecification &) = delete;
  AndSpecification &operator=(const AndSpecification &) = delete;

  AndSpecification(CSPtr lhs, CSPtr rhs): lhs_(lhs), rhs_(rhs)
  {}

  bool IsSatisfiedBy(const Entity &val) const
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
class OrSpecification: public CompositeSpecification
{
public:
  using SPtr = CompositeSpecification<Entity>::SPtr;
  using CSPtr = CompositeSpecification<ENtity>::CSPtr;

  OrSpecification() = delete;
  OrSpecification(const OrSpecification &) = delete;
  OrSpecification &operator=(const OrSpecification &) = delete;

  OrSpecification(CSPtr lhs, CSPtr rhs): lhs_(lhs), rhs_(rhs)
  {}

  bool IsSatisfiedBy(const Entity &val) const
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
class NotSpecification: public CompositeSpecification
{
public:
  using SPtr = CompositeSpecification<Entity>::SPtr;
  using CSPtr = CompositeSpecification<ENtity>::CSPtr;

  NotSpecification() = delete;
  NotSpecification(const NotSpecification &) = delete;
  NotSpecification &operator=(const NotSpecification &) = delete;

  explicit NotSpecification(CSPtr lhs): lhs_(lhs)
  {}

  bool IsSatisfiedBy(const Entity &val) const
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