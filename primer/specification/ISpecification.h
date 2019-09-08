#ifndef CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_
#define CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_

class ISpecification
{
public:
  ISpecification() = default;

  ISpecification(const ISpecification &) = delete;

  ISpecification &operator=(const ISpecification &) = delete;

  ISpecification And(const ISpecification &lhs, const ISpecification &rhs);

  ISpecification Or(const ISpecification &lhs, const ISpecification &rhs);

  ISpecification Not(const ISpecification &lhs);

  bool IsSatisfiedBy() const = 0;

  bool operator()() const;
  {
    return IsSatisfiedBy();
  }

  virtual ~ISpecification() = default;

};

#endif  //CPP_PRIMER_SPECIFICATION_ISPECIFICATION_H_