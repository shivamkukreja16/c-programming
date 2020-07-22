#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months; // number of months
  double contribution; // amount contributed/spent from the account/month
  double rate_of_return; // rate of returns
};
typedef struct _retire_info retire_info;


void retirement(int startAge, double initial,
		retire_info working, retire_info retired) {
  /*
   * This function computes the retirement account balance each
   * month while you are working and after retirement.
   *
   * start_age -> in months
   * double_initial -> initial savings in dollars
   */

  double balance = initial;
  for (int i = 0; i < working.months; i++)
    {
      printf("Age %3d month %2d you have $%.2f\n",
	     startAge/12, startAge%12, balance);
      balance += (balance * working.rate_of_return) + working.contribution;
      startAge++;
    }

  for (int i = 0; i < retired.months; i++)
    {
      printf("Age %3d month %2d you have $%.2f\n",
	     startAge/12, startAge%12,balance);
      balance += (balance * retired.rate_of_return) + retired.contribution;
      startAge++;
    }
}

int main(void){
  retire_info working = {.months = 489, .contribution = 1000, .rate_of_return = 0.045/12};
  retire_info retired = {.months = 384, .contribution = -4000, .rate_of_return = 0.01/12};

  int initial_age = 327;
  double initial_savings = 21345;

  retirement(initial_age, initial_savings, working, retired);

  return EXIT_SUCCESS;
}

