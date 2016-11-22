/*
Final Project for Stephanie Hart
10/20/2015

This is an auto loan calculator as I'm currently in the process of
buying a car. It calculates the total loan amount (including interest), 
the payment per month, the total interest paid, and how much of each payment
is interest and how much is principal. The user enters the loan amount,
interest rate and months to pay back the loan.

To calculate the loan payment, I used a formula found from Google on this
website: http://www.efunda.com/formulae/finance/loan_calculator.cfm

I came up with the calculation for what down payment is needed by altering
the formula for calculating a loan payment by solving for X, if the loan amount
is X and we already know what the payment amount is.
I checked the results against the loan calculator at:
https://www.bankofamerica.com/auto-loans/car-payment-calculator.go

To calculate the interest rate  per month, I used various calculators
to find the formula from this website:
http://homeguides.sfgate.com/calculate-principal-interest-mortgage-2409.html
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Function Prototypes
void Menu();
void LoanPaymentCalc(double, double, double);
void DownPaymentCalc(double, double, double, double);
void PrincipalVsInterest(double, double, double, double, double);



// Global constant
const double MPERYEAR = 12.0; // Months per year


int main()
{
	// User entered variables
	double BeginLoanAmount; // the beginning loan amount
	double InterestRate; // The interest rate
	double LoanLength; // # of months the loan is for
	int MenuChoice; // User Menu Choice to move to the next function
	char ContinueCalculations; // If the user would like to go again
	double DesiredPayment; // The desired payment per month for option 2 of the menu
	double CarPrice; // Price of the car

	cout << "\t\t\tWelcome to the loan calculator!" << endl;

	do
	{
		Menu(); // Calls the Menu function

		cin >> MenuChoice;

		if (MenuChoice != 1 && MenuChoice != 2)
			while (MenuChoice != 1 && MenuChoice != 2) // Input validation
			{
				cout << "Please enter only 1 or 2: ";
				cin >> MenuChoice;
			}

		if (MenuChoice == 1)
		{
			cout << "How much is the loan amount? : ";
			cin >> BeginLoanAmount;
			cout << "What is the interest rate? : ";
			cin >> InterestRate;
			cout << "How many months is the loan for? : ";
			cin >> LoanLength;
			LoanPaymentCalc(BeginLoanAmount, InterestRate, LoanLength);
		}
		else if (MenuChoice == 2)
		{
			cout << "How much would you like to pay per month? : ";
			cin >> DesiredPayment;
			cout << "What is the price of the car? : ";
			cin >> CarPrice;
			cout << "What is the interest rate? : ";
			cin >> InterestRate;
			cout << "How many months is the loan for? : ";
			cin >> LoanLength;
			DownPaymentCalc(CarPrice, DesiredPayment, InterestRate, LoanLength);
		}

		cout << "If you'd like to calculate another loan, press Y for Yes, or N for No: ";
		cin >> ContinueCalculations;

	} while (toupper(ContinueCalculations) == 'Y');

	return 0;
}

/*
This function prints only the beginning menu the user sees when they
first start the program, or if they've chosen to run the program again
with different loan information.
*/
void Menu()
{
	cout << "\nThe loan calculator can do one of two different options.\n"
		 << "1. Calculate your payment with the option to also show the "
		 << "amount of interest\nand principal per payment."
		 << "\n\t\t\t\tOR\n2. You enter how much you would like your payment to be "
		 << "and the calculator will tell you how much your down payment would "
		 << "need to be.\nPlease enter 1 or 2: ";
}

/*
This function calculates the payment on a car loan based on the user input
of the loan amount, interest rate and the length of the loan.
 The equation to find the monthly payment is payment = (PR(1+R)^M) / ((1+R)^M - 1)
 P = Price, R = Interest Rate (on a monthly basis), M = Months
*/
void LoanPaymentCalc(double LoanAmount, double Interest, double Months)
{
	// User entered variables
	char Continue;

	// Variables
	double TotalLoanWI; // Total loan amount with interest
	double Interest2; // After dividing interest by 100 to get a number less than 1
	double PaymentPerMonth; // Obviously how much each month's payment is

	Interest2 = Interest / 100.0; // Shows the amount of interest each payment is
	double InterestPerMonth = Interest2 / MPERYEAR; // Calculates the monthly percentage rate
	
	PaymentPerMonth = (LoanAmount * (InterestPerMonth * (pow((1.0 + InterestPerMonth), Months)))) / (pow((1.0 + InterestPerMonth), Months) -1);
	TotalLoanWI = PaymentPerMonth * Months;

	cout << setprecision(2) << fixed
		 << "The total loan, including interest will be $"
		 << TotalLoanWI << " and your monthly payment is $"
		 << PaymentPerMonth << "." << endl;
	cout << "Would you like to see how much of each payment is "
		 << "interest and how much is\nprincipal? Y for Yes, N "
		 << "for No : ";
	cin >> Continue;
	
	if (toupper(Continue) != 'Y' && toupper(Continue) != 'N') // User input checking
	{
		while (toupper(Continue) != 'Y' && toupper(Continue) != 'N')
		{
			cout << "Please enter only Y or N: ";
			cin >> Continue;
			cout << endl; // For formatting
		}
	}

	cout << endl;	// Additional formatting

	if (toupper(Continue) == 'Y')
		PrincipalVsInterest(TotalLoanWI, LoanAmount, Interest2, Months, PaymentPerMonth);
}

/*
This function dynamically creates an array to hold the values of the interest paid per
month on the loan.
Once the array has been created, it steps through the array, prints and calculates the 
amount of interest and capital per payment per month.
*/
void PrincipalVsInterest(double TotalLoan, double OrigLoan, double Interest, double Months, double Payment)
{
	// The variable OrigLoan, is the amount left on the loan after each month
	// I could not dynamically create an array with the double Months
	// So I created the int M  to turns Months into an int for the array.
	int M = Months; 
	double PrincipalPP, InterestPP; // Principal per payment and interest per payment
	double InterestPerMonth; // The percentage of interest paid per month = Interest / 12
	double *InterestArray = nullptr;
	// Creates a new array, the size of the array depends on the length of the loan
	InterestArray = new double[M];

	InterestPerMonth = Interest / MPERYEAR;

	// For loop enters the amount of interest paid per month into each
	// element of the array
	for (int count = 0; count < Months; count++)
	{
		
		InterestPP = InterestPerMonth * OrigLoan;
		InterestArray[count] = InterestPP;
		OrigLoan -= Payment;
	}

	cout << "The following chart shows how much of each monthly payment "
		 << "is interest and how\nmuch is principal. The last month is not "
		 << "shown as the last payment on a loan is\nusually slightly "
		 << "different from the other months.\n\nMonth\t\tInterest\t\t"
		 << "Principal\n_____\t\t________\t\t_________" 
		 << setprecision(2) << fixed << endl;

	// The loop runs while count < (Months - 1). I set it up as the last 
	// payment on a loan is usually a slightly different amount than the other payments.
	for (int count = 0; count < (Months - 1); count++)
	{
		PrincipalPP = Payment - InterestArray[count];
		cout << " " << (count + 1) << " \t\t$"
			 << InterestArray[count] << "\t\t\t$"
			 << PrincipalPP << endl;
	}
}

/* This function calculates how much of a down payment is needed
based on the user input of how much they'd like their car payment
to be, how much the car costs, the interest rate and the length
of the loan.

To calculate the down payment, the formula is as follows:
*** Down Payment = C - (P((1 + R)^M - 1) / ((1+ R)^M / R) ***
 C = Car Price, P = Payment, R = Interest (per month), M = Months
 */
void DownPaymentCalc(double Price, double Payment, double Interest, double Months)
{
	double DownPayment; // How much down payment is needed
	double Interest2 = Interest / 100.0; // Changes interest to a number less than 1
	double IperM = Interest2 / MPERYEAR; // Calculates the interest percentage per month

	DownPayment = Price - ((Payment * (pow((1.0 + IperM), Months) -1)) / (pow((1.0 + IperM), Months))) / IperM;


	cout << setprecision(2) << fixed << "\nWith a payment of $"
		 << Payment << " per month, a down payment of $" 
		 << DownPayment << " is needed,\nbringing the loan amount "
		 << "down to $" << (Price - DownPayment) << "." << endl;

}