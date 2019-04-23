# C code for calculating the density of ocean from pressure, temparature and salinity
#include<stdio.h>
#include<math.h>
void main(int argc, char *argv[])
{
  FILE *src,*trg;
  float temp,sal,dens;
  int dep;
  float getden(int,float,float);
  if(argc != 3)
    {  printf("Too few arguments");
       exit(0);
    }
  if((src=fopen(argv[1],"r"))==NULL)
    {  printf("cannot open src file");
       exit(0);
    }
  if((trg=fopen(argv[2],"w"))==NULL)
    {  printf("cannot create trg file");
       exit(0);
    }
   while(!feof(src))
    {   fscanf(src,"%d %f %f",&dep,&temp,&sal);
	dens = getden(0,temp,sal);
	fprintf(trg,"\n%5d   %6.3f   %6.3f   %f",dep,temp,sal,dens);
    }
fclose(src);
fclose(trg);
}
float getden(int d,float t,float s)
{
  float result;
  float row,k;
  float temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;

  // to calculate row(s,t,0) value

  temp1 = 0.157406 + (6.793952*pow10(-2)*t)- (9.095290*pow10(-3)*pow(t,2));
  temp2 = (1.001685*pow10(-4)*pow(t,3))-(1.120083*pow10(-6)*pow(t,4));
  temp3 = (6.536332*pow10(-9)*pow(t,5))+(8.24493*pow10(-1)*s)-(4.0899*pow10(-3)*t*s);
  temp4 = (7.6438*pow10(-5)*pow(t,2)*s)-(8.2467*pow10(-7)*pow(t,3)*s);
  temp5 = (5.3875*pow10(-9)*pow(t,4)*s)-(5.72466*pow10(-3)*pow(s,1.5));
  temp6 = (1.0227*pow10(-4)*t*pow(s,1.5))-(1.6546*pow10(-6)*pow(t,2)*pow(s,1.5))+(4.8314*pow10(-4)*pow(s,2));
  row = temp1 + temp2 + temp3 +temp4 + temp5 + temp6;

// to calculate the K(s,t,d) value

   temp1= 19652.21 + (148.4206*t)+(-2.327105*pow(t,2))+(1.360477*pow10(-2)*pow(t,3));
   temp2= (-5.155288*pow10(-5)*pow(t,4))+(3.239908*d)+(1.43713*pow10(-3)*d*t);
   temp3= (1.16092*pow10(-4)*pow(t,2)*d)+(-5.77905*pow10(-7)*pow(t,3)*d);
   temp4= (8.50935*pow10(-5)*pow(d,2))+(-6.12293*pow10(-6)*t*pow(d,2))+(54.6746*s);
   temp5= (5.2787*pow10(-8)*pow(t,2)*pow(d,2))+(-0.603459*t*s)+(1.09987*pow10(-2)*pow(t,2)*s);
   temp6= (-6.1670*pow10(-5)*pow(t,3)*s)+(7.944*pow10(-2)*pow(s,1.5))+(1.6483*pow10(-2)*t*pow(s,1.5));
   temp7= (-5.3009*pow10(-4)*pow(t,2)*pow(s,1.5))+(2.2838*pow10(-3)*d*s)+(-1.0981*pow10(-5)*t*d*s);
   temp8= (-1.6078*pow10(-6)*pow(t,2)*d*s)+(1.91075*pow10(-4)*d*pow(s,1.5))+(-9.9348*pow10(-7)*pow(d,2)*s);
   temp9= (2.0816*pow10(-8)*t*pow(d,2)*s)+(9.1697*pow10(-10)*pow(t,2)*pow(d,2)*s);
   k = temp1+temp2+temp3+temp4+temp5+temp6+temp7+temp8+temp9;

// the resultant density value to be returned

  result = (row*k)/(k-d);
  return result;
}
