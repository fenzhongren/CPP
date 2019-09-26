#include "text_query.h"

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

  query.Query("elif").ShowResult();
  query.Query("this").ShowResult();
  query.Query("zejunx").ShowResult();

  query.Close();

#if 0
  query.Open("./smb");
  query.Query("you").ShowResult();
  query.Query("the").ShowResult();
  query.Close();
#endif
  return 0;
}
