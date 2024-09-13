#include<iostream>
#include<thread>
using namespace std;
 
void myprint()
{
  cout <<"线程开始执行" << endl;
  //execute subthread
  cout << "线程执行结束" << endl;
}
int main()
{
  thread myobj(myprint);
  myobj.join();
  cout << "主线程执行" << endl;
  //execute main thread 
  return 0;
}
