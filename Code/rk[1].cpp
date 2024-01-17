#include<bits/stdc++.h>
#define fl double
#define vi vector<fl>
#define rep(i,j,k) for(int i = j;i<k;i++)
#define int long long int
using namespace std;

/* We have already assigned micro for vector and double,here we have used 
fl which is same as double and also used long long int so that we can large number if necessary..
*/

// We know that j = sigma*E from there we have calculated the electric field...
fl efield(fl omega,fl permfree,fl dielloss,fl excitation) 
{
    return (excitation/(omega*permfree*dielloss));
}
fl poin(fl omeg,fl permfree,fl dieloss,fl efied)
{
    return 0.5*omeg*permfree*dieloss*pow(efield(omeg,permfree,dieloss,10),2);
}
fl eval(fl t,fl T,fl alpha,fl power) // This is our f(x,y) in the diffrential eqaution..
{
    return (alpha*(T+power)); 
    /* Alpha here is the thermal diffusivity in order not to introduce too
    much variable in the eval function we have taken thermal conductivity/(density*specific heat) 
    as alpha..
    */
}
fl rk4(fl x,fl y,fl h,fl alpha,fl power) // This function is used to solve the ODE..
{ 
    fl ans =0;
    vi p(3),q(6),w(4),k(4);
    p[0] = 0.5;p[1]= 0.5;p[2]= 1;
    q[0] = 0.5;q[1] = 0;q[2] = 0.5;q[3] = 0;q[4] = 0;q[5] = 1;
    w[0] = double(0.1666666666666);w[1] = double(0.33333333333333);w[2] = double(0.33333333333333);w[3] = double(0.1666666666666);   
    k[0] = eval(x,y,alpha,power);
    k[1] = eval((x+p[1]*h),y+(q[0]*k[0]*h),alpha,power);
    k[2] = eval((x+p[2]*h),y+(q[1]*k[0]*h)+(q[2]*k[1]*h),alpha,power);
    k[3] = eval((x+p[3]*h),y+(q[3]*k[0]*h)+(q[4]*k[1]*h)+(q[5]*k[2]*h),alpha,power); 
    rep(i,0,4)
    {   
        ans+=w[i]*h*k[i];
    }
    return ans;
}
signed main() 
/* All the useful datas like density,specific heat,thermal conductivity,
electric field,permittivity,dieloss are already fed in this main function..
*/
{
    cout.precision(7);
    fl h;
    fl f = 2.45*pow(10,9); // frequency taken is of the microwave region...
    fl omega = 2*M_PI*f;
    fl permfree = 8.854*pow(10,-12);
    fl dieloss = 15;
    vi a(351),b(351);
    fl rho = 1000;
    fl cp = 3900;
    fl k  = 0.4;
    fl alpha = k/(rho*cp);
    cout<<"Enter the initial value of time:- ";cin>>a[0];
    cout<<"Enter the initial value of temperature:- ";cin>>b[0];
    cout<<"Enter the value of time step:- ";cin>>h;
    fl po = poin(omega,permfree,dieloss,efield(omega,permfree,dieloss,10));
    rep(i,1,351)
    {
        b[i] = b[i-1]+rk4(a[i-1],b[i-1],h,0.01,po);
        a[i] = a[i-1]+h;
    }
    cout<<endl<<"----------------------------------------------------------------"<<endl;
    rep(i,0,351) 
    /* rep is a micro  which is used for loop which takes three arguments(i,j,k)
    i stands for variable name,j for starting point and k for ending point.
    */
    {
        cout<<"Time(s):- "<<a[i]<<" Temperature:- "<<b[i]<<endl;
    }
}