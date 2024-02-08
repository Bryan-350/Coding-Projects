/**This project that I coded in Java is essentially a calculator that can calculate the Amortization payments for a loan. 
    It can calculate loan payment amounts, the number of payments for a loan, the split between interest and principle
    for each payment, etc. Originally this was an individual semester long project but it was quite simple and I knocked it out
    in a couple of days or so. Although simple, it gave me a firm understanding of how classes, objects, and functions work while 
    also creating a tool that will be beneficial for me as a young adult. **/

import javax.swing.JOptionPane;
import java.io.*;

public class Amortization {
    /**initializing all variables needed for the Amortization class*/
    private double loanAmount; //double variable to hold loan amount
    private double interestRate; //double variable to hold annual interest rate
    private double loanBalance; //double variable to hold the loan balance
    private double term; //double variable used in the calculation of the monthly payment
    private double payment; //double variable to hold the monthly payment amount
    private int loanYears; //int variable used to hold the number of years of the loan
    private double interestMonth; //double variable that stores the interest accrued in the current month
    private double principal; //double variable that shows the principal of the payment
    private double interestPercent; //double variable that shows interestRate in a percentage
    private int paymentMonth = 1; //int variable that is used as a counter for the current month

    /**Constructor that takes in the loan, rate and years of the loan
     * and then assigns those values to variables that will be used in class
     * and then calls the calcPayment() method*/
    public Amortization(double loan, double rate, int years)
    {
        loanAmount = loan;  interestRate = rate;    loanYears = years;
        calcPayment();
    }

    /**Private method that calculates the monthly payment of the loan */
    private void calcPayment()
    {
        term = Math.pow((1 + (interestRate / 12)), (loanYears * 12));

        payment = (((loanAmount * (interestRate/12) * term) / (term - 1)));
        interestPercent = interestRate * 100;
    }

    /**Public method that calculates how many payments
     * will be need for the loan and returns that value */
    public int getNumberOfPayments()
    {
        int numberOfPayments = loanYears * 12;
        
        return numberOfPayments;
    }
    
    /**Public method that creates an Amortization report
     * and saves it to a file named Amortization.txt*/
    public void saveReport(String filename) throws FileNotFoundException 
    {
       /**Creates a new instance of an object of the PrintWriter class and is called report*/
       PrintWriter report = new PrintWriter(filename);
     
       /**Prints out the original arguments of the loan
        * to remind the user */
       report.print("Loan of $" + getLoanAmount() + " at: ");
       report.print(String.format("%,.2f", interestPercent));

       /**IF/ELSE statement that just adds the letter 's' to the word
        *  year dependning of if the loan is more than 1 year and
        * then continues to print out the orignal arguments of the loan */
       if(getLoanYears() > 1)
       {    
            report.println("% interest over the course of " + getLoanYears() + " years.");
       }
       else
            report.println("% interest over the course of " + getLoanYears() + " year.");

       /**Prints out the monthly payment for the loan and rounds to 2 decimals  */
       report.println(String.format("Monthly Payment: $" + "%,.2f", payment));

       /**Header for the Amortization report*/
       report.println("Month\t\tInterest\t\tPrincipal\t\tBalance");
       
       /**for loop that creates a dashed line to separate
        *  Amortization report header and the actual report */
       for(int i = 0; i < 62; i++)
       {
            report.print("-");
       }
       /**Prints new line */
       report.println();

       /**For loop that prints the payment month, the interest of that month,
        *  the principal of the payment, and then the balance after payment has been made.
         It iterates until all payments met and the balance is 0 */
       for(int i = 0; i < getNumberOfPayments(); i++)
       {
            /**calculates the interest accumulated in that month */
            interestMonth = (getInterestRate() * getLoanAmount()) / 12;

            /**Calcultes the principal of the payment
            *  after the interest has been subtracted */
            principal = payment - interestMonth;

            /**Sets the balance of the loan to be the
            *  amount of the loan minus the principal */
            loanBalance = loanAmount - principal;

            /**Prints out one row of the month, interest for the month,
            *  principal for the month, and the current balance of the loan */
            report.print(paymentMonth + "\t\t\t");
            report.print(String.format( "%,.2f", interestMonth));
            report.print("\t\t\t");
            report.print(String.format( "%,.2f", principal));
            report.print("\t\t\t");
            report.println(String.format( "%,.2f", loanBalance));

            /**Sets loanAmount to the current Balance so that when the loop iterates again,
            *  the interest, principal, and balance don't come out the same */
            loanAmount = loanBalance;

            /**Increments the payment month up by 1 so
            * that the next iteration of the loop displays the next month */
            paymentMonth++;        
       }
       /**Once the report is made, this closes the instance of the PrintWriter */
       report.close();     
    }

    /**Public method that returns the amount of the loan */
    public double getLoanAmount()
    {
        return loanAmount;
    }

    /**Public method that returns the interest rate of the loan */
    public double getInterestRate()
    {
        return interestRate;
    }

    /**Public method that returns the number of years of the loan */
    public int getLoanYears()
    {
        return loanYears;
    }

    public static void main(String[] args) throws FileNotFoundException 
    {   
        /**Creates a string that uses an input dialog
         *  box to enter the amount of the loan */
        String loanStr = JOptionPane.showInputDialog("Enter the loan amount.");

        /**Converts the string above into a double data type */
        double loan = Double.parseDouble(loanStr);

        /**Creates a string that uses an input dialog
         *  box to enter the interest rate of the loan  */
        String rateStr = JOptionPane.showInputDialog("Enter the annual interest rate.");

        /**Converts the string above into a double data type */
        double rate = Double.parseDouble(rateStr);

        /**Creates a string that uses an input dialog
         *  box to enter the number of years for the loan */
        String yearsStr = JOptionPane.showInputDialog("Enter the years of the loan.");
        
        /**Converts the string above into a double data type
         * 
         */
        int years = Integer.parseInt(yearsStr);

        /**Creates a new instance of the Amortization
         *  constructor and calls it calculator */
        Amortization calculator = new Amortization(loan, rate, years);
        
        /**Calls the save report method of the calculator
         *  object to create and save the report in new file */
        calculator.saveReport("AmortizationLoan.txt");

        /**After the report in the statement above has been made,
         *  this dialog box informs the user that the report was created*/
        JOptionPane.showMessageDialog(null,"Report saved to the file LoanAmortization.txt.");     
    }
}
