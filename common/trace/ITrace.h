#ifndef CPP_COMMON_TRACE_ITRACE_H_
#define CPP_COMMON_TRACE_ITRACE_H_

#include <string>
#include <set>

template<typename T>
class TraceObject
{
public:
  TraceObject() = default;

  void AddItem(const T &val)
  {
    enabled_object_set_.insert(val);
  }

  void AddItem(T &&val)
  {
    enabled_object_set_.insert(std::move(val));
  }

  void RemoveItem(const T &val)
  {
    enabled_object_set_.erase(val);
  }

  bool IsEnabled(const T &val) const
  {
    auto count = enabled_object_set_.count(val);
    return (count > 0);
  }

  virtual ~TraceObject()
  {
    enabled_object_set_.clear();
  }

private:
  std::set<T> enabled_object_set_;
};

class ITrace
{
public:
  static ITrace &GetInstance();

  virtual void SetEnabledObjects(const TraceObject<std::string> &objects) = 0;
  virtual void PrintError(const std::string &type, const char *fmt, ...) const = 0;
  virtual void PrintWarn(const std::string &type, const char *fmt, ...) const = 0;
  virtual void PrintInfo(const std::string &type, const char *fmt, ...) const = 0;
  virtual void PrintDebug(const std::string &type, const char *fmt, ...) const = 0;
};

#endif  //CPP_COMMON_TRACE_ITRACE_H_