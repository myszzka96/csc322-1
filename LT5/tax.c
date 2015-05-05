#include <stdio.h>
#include <stdlib.h>

#define STINKING_RICH 500000
#define QUITE_RICH 200000
#define MIAMI_POOR 100000
#define AVERAGE 50000
#define REALISTIC 20000
#define MAXIMAL_TAX 50000
#define SUPER_RICH_TAXED 0.25
#define QUITE_RICH_TAXED 0.25
#define MIAMI_POOR_TAXED 0.10
#define AVERAGE_TAXED 0.03
#define REALISTIC_TAXED 0.03
#define POOR_TAXED 0.0

double computeTaxableIncome(double income, double deductions) {
  double taxableIncome;

  if (income >= deductions) {
    taxableIncome = income - deductions;
  } else {
    taxableIncome = 0.0;
  }

  return(taxableIncome);
}

char chooseTaxGroup (double taxable) {
  char taxGroup;

  if (taxable >= STINKING_RICH) {
    taxGroup = 'S';
  } else if (taxable >= QUITE_RICH) {
    taxGroup = 'Q';
  } else if (taxable >= MIAMI_POOR){
    taxGroup = 'M';
  } else if (taxable >= AVERAGE){
    taxGroup = 'A';
  } else if (taxable >= REALISTIC){
    taxGroup = 'R';
  } else {
    taxGroup = 'P';
  }

  return(taxGroup);
}

double computeTax(double tax, char taxGroupChar) {
  double taxCompute;
  switch (taxGroupChar) {
    case 'S':
      taxCompute = tax * SUPER_RICH_TAXED;
      break;
    case 'Q':
      taxCompute = tax * QUITE_RICH_TAXED;
      break;
    case 'M':
      taxCompute = tax * MIAMI_POOR_TAXED;
      break;
    case 'A':
      taxCompute = tax * AVERAGE_TAXED;
      break;
    case 'R':
      taxCompute = tax * REALISTIC_TAXED;
      break;
    case 'P':
      taxCompute = POOR_TAXED;
      break;
    default:
      taxCompute = 0.0;
      printf("Error!");
      break;
  }

  if (taxCompute < MAXIMAL_TAX) {
    return(taxCompute);
  } else {
    return(MAXIMAL_TAX);
  }
}

int main(void) {
  double income = 0.0;
  double amount;
  double deductions = 0.0;

  printf("Enter next amount: ");
  scanf("%lf", &amount);

  while (amount!=0.0) {
    if (amount >= 0.0){
      income += amount;
    } else {
      deductions -= amount;
    }

    printf("Enter next amount: ");
    scanf("%lf", &amount);
  }

  double taxable;
  char taxGroupChar;
  double tax;
  taxable = computeTaxableIncome(income, deductions);
  taxGroupChar = chooseTaxGroup(taxable);
  tax = computeTax(taxable, taxGroupChar);

  printf("\nIncome             = $%.2lf\n", income);
  printf("Deductions         = $  %.2lf\n", deductions);
  printf("Taxable income     = $%.2lf\n", taxable);
  printf("Tax group          = %c\n", taxGroupChar);
  printf("Tax owed           = $%.2lf\n", tax);

  return(EXIT_SUCCESS);
}
