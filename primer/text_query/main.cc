#include "text_query.h"

TextQuery::QueryResult func(void)
{
  TextQuery query;
  query.Open("./bashrc");

  return query.Query("elif");
}

int main()
{

  TextQuery query;
  query.Open("./bashrc");

  query.Query("elif").ShowResult();
  query.Query("this").ShowResult();
  query.Query("zejunx").ShowResult();

  query.Close();

  query.Open("./smb");
  query.Query("you").ShowResult();
  query.Query("the").ShowResult();
  query.Close();

  return 0;
}
