#include "text_query.h"

#include <iostream>

using std::cout;
using std::endl;

#if 0
TextQuery::QueryResult func(void)
{
  TextQuery query;
  query.Open("./bashrc");

  return query.Query("elif");
}
#endif

int main()
{

  TextQuery query;
  query.Open("./bashrc");

  query.Query("elif").ShowResult(cout) << endl;
  query.Query("this").ShowResult(cout) << endl;;
  query.Query("zejunx").ShowResult(cout) << endl;

  query.Close();

#if 0
  query.Open("./smb");
  query.Query("you").ShowResult();
  query.Query("the").ShowResult();
  query.Close();
#endif
  return 0;
}
