# bank-management-system
A CLI-based client that emulates a bank management system and allows users to create and manage bank accounts on a local computer.

The program lets the user create a bank account and manipulate it as per the users wish. The user is first presented with a choice to either create an account or access/modify an existing account.

Creation of account involves procurement of necessary details from the user such as name, desired password, etc., after which a random account number is assigned to the account. The entered details are passed into a binary data file that functions as a database containing details of all the accounts in the bank.

Accessing an existing account requires the user to enter the username and corresponding password. If the password does not match the entered username, the user is asked to enter the username and password again. Once this is done, the user can choose to perform one of the following functions

1.	Deposit Money
2.	Withdraw Money
3.	Change Password
4.	Apply for a loan
5.	Check Balance
6.	Log Out

Deposition or withdrawal of money involves the user entering the amount he/she wants to deposit/withdraw from his/her account and doing the same.

Changing password involves verifying the old password and then asking the user to enter the password he/she desires to have for the account.

Application for loans first involves asking the user the type of loan he/she would like to apply for: Personal loan, Car loan or House loan. The appropriate details involving the application for each type of loan are obtained from the user, after which the amount is deposited to their account.

After each of the above actions are completed, the modified details of the account are passed into the bank database (binary data file).

Checking the balance in an account involves printing the balance in the account on the screen.

The log out option takes the user back to the choice between creation or modification of the account.
