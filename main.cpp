#include <stdio.h>
#include <math.h>

/*Counter var*/
int B = 0; //counter for beat freq
int R = 0; //counter for ramp
int N = 0; //counter for correlation
int i = 0; //counter for adc values
/*ADC*/
double ADC_val[1200]; //array to save I and Q
float I[600]; //ADC1 array of values[600]
float Q[600]; //ADC2 array of values [600]
/*variables*/
double correlation[599]; //correlation angle array per ramp
double suma[600]; //the sumatory of correlation angles 
double angle1;//angle n
double angle2;//angle n + 1
double fbeat; //beat frequency array
double Range[15]; //Range
double suma_range[15]; //avg range for all ramps
double avg_range = 0;
float den; //2*pi*Ts*samples
double fbeat_sum = 0.00;
double fbeat_avg =0.00;
float Range_m = 0; //range in meters
float percentage = 0;
/*constants*/
double pi = 3.14159265359; //pi number
int samples = 600; //quantity of samples per ramp
float Ts = 0.0001; //sampling period 
int BW = 200000000; //Bandwidht
int c = 300000000; // light velocity
float silo_capacity = 1447.8; //4750 foot to meters = 1447.8
float w1=1,w2=50, w3 = 25; //wairning 1, warning 2 & warning 3;


int main (){
  for (R=0; R<2; R = R + 1){ //for each ramp under study. As discussed, ramps = 15
    for (i=0; i<3; i = i + 1){ //this arrays are going to save the ADC1 and ADC2 data (i<600)
    ADC_val[i] = rand() %409;
    I[i]=ADC_val[i]; //assign rndm values to I between 0-4095
    ADC_val[3+i] = rand() %4095; //assign rndm values to Q between 0-4095
     Q[i]=ADC_val[3+i];
    printf("ADC values Q: %lf\r\n", ADC_val);
    /*used on a C compiler
   printf("Enter ADC1: \n");//used on a C compiler
   scanf("%f", &I[i]);//used on a C compiler
   printf("Enter ADC2: \n");//used on a C compiler
   scanf("%f", &Q[i]);//used on a C compiler 
   */
   
     /*while (i<600){ //In reality, this is not going to be needed
      printf("I:%f\n\n",I[i]); //used on a C compiler
      printf("Q:%f\n\n",Q[i]); //used on a C compiler 
      break; } //used on a C compiler
      */
      } //for adc 1 and adc2 values to go to I and Q arrays per ramp
        for (N=0; N<3; N++) //N<600
        { 
         if(N!=599){ //for any value other than 599
          angle1 = atan(Q[N]/I[N]); //angle 
          angle2 = atan(Q[N+1]/I[N+1]); //next angle on the I & Q arrays
          correlation[N]= angle1-angle2; //the angle of correlation <s(n+1)s*(n) = angle1-angle2
          suma[N] = suma[N-1] + correlation[N]; 
         printf("angle1 in first position:%lf\n", angle1);
         printf("angle2 in first position: %lf\n", angle2);
         printf("correlation in first position: %lf\n", correlation[N]);
         printf("primera suma is %lf\n\n", suma[N]);} //N==initial value
         if(N==2){ //for 599, the last position of the array
          printf("used I in last position:%f\n\n",I[N]);
          printf("used Q in last position:%f\n\n",Q[N]);
          angle1 = atan(Q[N]/I[N]); 
          angle2 = 0;
          correlation[N]= angle1; //
         suma[N] = correlation[N] + suma[N-1];
         printf("angle 1 in last position:%lf\n", angle1);//used on a C compiler 
         printf("angle 2 in last position:%lf\n", angle2);//used on a C compiler 
         printf("correlation in last position: %lf\n", correlation[N]);//used on a C compiler 
         printf("suma is %lf\n\n", suma[N]);} //end of if; used on a C compiler 
        } //end of correlation counter
      den= (2*pi*Ts*samples); //beat frequency estimation denominator
      printf("-denominator: %f\n", den); //used on a C compiler 
          fbeat = suma[2]/den; //beat frequency estimation. Suma[last position]/den
          fbeat_sum = fbeat_sum + fbeat;
          printf("-beat frequency = %lf\n", fbeat_sum);//used on a C compiler 
       //
          R = R +1; //Ramp position on the ramp array       
            fbeat_avg = fbeat_sum/R;
            printf("-f beat avg: %f\n", fbeat_avg);
          R = R-1; //Return to original ramp position
       Range[R] = (c*fbeat_avg*Ts)/(2*BW);
       printf("-Range per ramp: %lf\n", Range[R]);  //shows Range per ramp at 
      suma_range[R] = suma_range[R-1] + Range[R];
      avg_range = suma_range[R]/(R+1);
      printf("--avg range for all: %lf\r\n\n",avg_range);
      } //R
  Range_m = avg_range*1000000; //last element of avg_range*1000 to obtain the range in milimeters
  printf("-Range in milimeters: %f\n", Range_m);
  //percentage = 55; 
  percentage = (Range_m/silo_capacity)*100;
  printf("--Percentage:  %f\n", percentage);
  
return 0;
}
