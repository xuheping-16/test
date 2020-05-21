#include <iostream>
using namespace std;

   int n = 8;//任务数
   int d = 0;//初始距离为0
   int k = n;//初始簇数
   int PN = 2;//要划分的模块数
   int M = 4;//模块中任务上限
   float A[9][9] = {
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0.5,0,0.5,0,0,0},
      {0,0,0,0.5,0.5,0,0,0,0},
      {0,0.5,0.5,0,0.5,1,0.5,0,0},
      {0,0,0.5,0.5,0,0,1,0,0},
      {0,0.5,0,1,0,0,0.5,1,0},
      {0,0,0,0.5,1,0.5,0,0.5,0.5},
      {0,0,0,0,0,1,0.5,0,0.5},
      {0,0,0,0,0,0,0.5,0.5,0}
   };//代价矩阵，将代价矩阵适当扩充，以便于更好的计算

void f1(float B[][9]);//单链接
void f2(float B[][9]);//均链接
void f3(float B[][9]);//全链接
void print(int* K_belong);//打印结果函数，K_belong存储任务的分簇情况
void cost(int* K_belong);//计算代价函数

int main(){
  
   float B[9][9] = {0};
   for(int i = 1;i<=n;i++)//得到距离矩阵
      for(int j = 1;j<=n;j++)
      {
         B[i][j] = 1-A[i][j] + 1;
      }
   //f1(B);//调用单链接函数，得到单链接后的分簇结果
   //f2(B);//调用均链接函数，得到均链接后的分簇结果
   //f3(B);//调用全链接函数，得到全链接后的分簇结果
   return 0;
}

void f1(float B[][9])
{
   cout<<"single connect"<<endl;
   cout<<"d  "<<"k  "<<"cluster "<<endl;
   int K_belong[n+1] = {0,1,2,3,4,5,6,7,8};//K_belong存储任务的分簇情况
   int K_link[n+1][2] = {{0,0},{1,0},{2,0},{3,0},{4,0},
   {5,1},{6,1},{7,1},{8,1}} ;
   while(k!=PN)
   {
      int oldk = k;
      d = d + 1;
      for(int i = 1;i<=n;i++)
      {   
         for(int j = i+1;j<=n;j++)
         {
            int a = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[i])
                    a++;
            if(a==M)
               break;
            if(K_belong[i] == K_belong[j])
            {
               continue;
            }
            
            if(B[i][j]<=d)
            {
               int b = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[j])
                     b++;
               if(a+b>M)
                continue;
               int flag1 = 0;
               if(a == 1 && b == 1)
               {
                  for(int l = j+1;l<n;l++)
                  {
                     int c = 0;
                     int flag = 0;
                     for(int m = l;m<n;m++)
                     {
                        if(K_belong[m]==K_belong[l])
                           {
                              if(B[i][m]<d)
                              flag = 1;
                              c++;
                           }
                     }
                     if(c+a>M||c==1||flag==0)
                        continue;                             
                     flag1 = 1;              
                     break;
                  }
               }
               if(flag1)
               continue;
               int c = K_belong[j];
               for(int l = 1;l<=n;l++)
               {
                  if(K_belong[l]==c)
                  {
                     K_belong[l] = K_belong[i];
                  }
               }
               k = oldk - 1;
               oldk = k;
            }
         }
      }
      print(K_belong);//调用print函数，输出一次分簇的结果
}
cout<<"the cost of single connect:";
cost(K_belong);
}

void f2(float B[][9])
{
   cout<<"average connect"<<endl;
   cout<<"d  "<<"k  "<<"cluster "<<endl;
   int K_belong[n+1] = {0,1,2,3,4,5,6,7,8};//K_belong存储任务的分簇情况
   while(k!=PN)
   {
      int oldk = k;
      d = d + 1;
      for(int i = 1;i<=n;i++)
      {  
         for(int j = i+1;j<=n;j++)
         {
            int a = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[i])
                     a++;
            if(a==M)
               continue;
            if(K_belong[i] == K_belong[j])
            {
               continue;
            }
            
            if(B[i][j]<=d)
            {
               int b = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[j])
                     b++;
               if(a+b>M)
                  continue;
               int flag1 = 0;
               if(a == 1 && b == 1)
               {
                  for(int l = j+1;l<n;l++)
                  {
                     int c = 0;
                     int flag = 0;
                     int num = 0;
                     int num1 = 0;
                     for(int m = l;m<n;m++)
                     {
                        if(K_belong[m]==K_belong[l])
                           {
                              num1++;
                              num += B[i][m];
                              if(num>d*num1)
                              flag = 1;
                              else
                              {
                                 flag = 0;
                              }
                              
                              c++;
                           }
                     }
                     if(c+a>M||c==1||flag==1)
                        continue;                             
                     flag1 = 1;              
                     break;
                  }
               }
               if(flag1)
               continue;
               float avg_num = 0;
               int num = 0;
               for(int ll = 1;ll<=n;ll++)
               {
                  if(K_belong[ll]==K_belong[i])
                  for(int mm = 1;mm<=n;mm++)
                  {
                     if(K_belong[mm]==K_belong[j])
                     {
                        avg_num += B[ll][mm];
                        num++;
                     }
                  }
               }
               if(avg_num>float(num*d))
                  continue;
               int c = K_belong[j];
               for(int l = 1;l<=n;l++)
               {
                  if(K_belong[l]==c)
                  {
                     K_belong[l] = K_belong[i];
                  }
               }
               k = oldk - 1;
               oldk = k;
            }
         }
      }
      print(K_belong);//调用print函数，输出一次分簇的结果
}
cout<<"the cost of average connect:";
cost(K_belong);
}

void f3(float B[][9])
{
   cout<<"all connect"<<endl;
   cout<<"d  "<<"k  "<<"cluster "<<endl;
   int K_belong[n+1] = {0,1,2,3,4,5,6,7,8};//K_belong存储任务的分簇情况
   while(k!=PN)
   {
      int oldk = k;
      d = d + 1;
      for(int i = 1;i<=n;i++)
      {  
         for(int j = i+1;j<=n;j++)
         {
            int a = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[i])
                     a++;
            if(a==M)
               continue;
            if(K_belong[i] == K_belong[j])
            {
               continue;
            }
            
            if(B[i][j]<=d)
            {
               int b = 0;
               for(int l = 1;l<=n;l++)
                  if(K_belong[l]==K_belong[j])
                     b++;
               if(a+b>M)
                  continue;
               int flag1 = 0;
               if(a == 1 && b == 1)
               {
                  for(int l = j+1;l<n;l++)
                  {
                     int c = 0;
                     int flag = 1;
                     for(int m = l;m<n;m++)
                     {
                        if(K_belong[m]==K_belong[l])
                           {
                              if(B[i][m]>d)
                              flag = 0;
                              c++;
                           }
                     }
                     if(c+a>M||c==1||flag==0)
                        continue;                             
                     flag1 = 1;              
                     break;
                  }
               }
               if(flag1)
               continue;
               int flag = 0;
               for(int ll = 1;ll<=n;ll++)
               {
                  if(K_belong[ll]==K_belong[i])
                  for(int mm = 1;mm<=n;mm++)
                  {
                     if(K_belong[mm]==K_belong[j])
                     {
                        if(B[ll][mm]>d)
                        flag = 1;
                     }
                  }
               }
               if(flag)
                  break;
               int c = K_belong[j];
               for(int l = 1;l<=n;l++)
               {
                  if(K_belong[l]==c)
                  {
                     K_belong[l] = K_belong[i];
                  }
               }
               k = oldk - 1;
               oldk = k;
            }
         }
      }
      print(K_belong);//调用print函数，输出一次分簇的结果
}
cout<<"the cost of all connect:";
cost(K_belong);
}
void print(int* K_belong)//对K_belong内存储的分簇情况进行转换输出
{
         cout<<d<<"  "<<k<<"  ";
         for(int i = 1;i<=n;i++)
         {
               int flag = 0;
               for(int j = 1;j<=n;j++)
         {
               if(K_belong[j] == i)
               {
                  if(!flag)
                  cout<<"{";
                  cout<<j<<" ";
                  flag = 1;
               }
         }
               if(flag)
                  cout<<"}";
         }
         cout<<endl;
}

void cost(int* K_belong)
{
   float cost_num = 0;
   for(int i = 1;i<=n;i++)
   {
      for(int j = i+1;j<=n;j++)
      {
         if(K_belong[i]!=K_belong[j])
         cost_num += A[i][j];
      }
   }
   cout<<cost_num<<endl;
}