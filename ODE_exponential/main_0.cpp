///* assert example */
//#include <stdio.h>      /* printf */
//#include <iostream>      /* printf */
//#include <assert.h>     /* assert */
//
//
//int main ()
//{
//  int id_;
//
//  id_=3; std::cout <<" id_= "<<id_<<std::endl;
//  assert( id_ != 0 && "Employee ID is invalid (must be nonzero)" );
//
//  id_=0; 
//  assert( id_ != 0 && "Employee ID is invalid (must be nonzero)" );
//  std::cout <<" id_= "<<id_<<std::endl;
//
//  return 0;
//}

#include <iostream>
#include <exception>
using namespace std;

struct MyException : public exception
{
  const char * what () const throw ()
  {
    return "C++ Exception";
  }
};
 
int main()
{
  try
  {
    throw MyException();
  }
  catch(MyException& e)
  {
    std::cout << "MyException caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    //Other errors
  }
}
