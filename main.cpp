#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h>

using namespace std;

class Baseball 
{//The public section of the baseball class contains all of the member function prototypes
public:
	void File();
	void Menu();
	void PrintAllInfo();
	void PrintOneTeam(string TeamName);
	void PrintOnePlayer(string Player);
	void UpdateStats(string PLAYER, string Team, int AB, int totalhit, int totalrun, int dingers, int runsbattedin);
	void InstertNewStat(string playername, string playerTeam, int at, int numhit, int Run, int hR, int rbi);
	void ExportData();
	int exit_program();

private://The private section of the baseball class contains vectors that represent each stat
	vector < string > name;
	vector < string > team;
	vector < int >atbats;
	vector < int >hits;
	vector < int >runs;
	vector < int >hr;
	vector < int >rbi;
	int counter = 0; //The counter variable is used to keep track of the size of the input file
};

int main()
{
	string userName;
	Baseball start; //The object start is created inorder to call the memeber functions

	cout << "Please enter you name: "; //prompts the user for his name and saves it to username
	getline(cin, userName); 
	cout << "Welcome " << userName << endl << endl;

	start.File(); //calls the file memeber fucntions which inturn opens the file
	start.Menu(); //

	cout << "Thank you " << userName << " for using the program" << endl;

	system("PAUSE");
	return 0;
}

void Baseball::File()
{
	string names;
	string tm;
	int atb, H, R, HR, runsin;
	ifstream infile; 
	infile.open("Stats.txt"); //opens the input file Stats

	if (!infile) //if there is an error opening the file the program will exit
	{
		cout << "There is an error in opening the file" << endl;
		abort();
	}

	while (!infile.eof()) //the while loop terminates at the end of the file
	{
		infile >> names >> tm >> atb >> H >> R >> HR >> runsin; //the first line is read into the tempory variables
		name.push_back(names); //then those indivuals values are all inserted into the vector and increases the vector size
		team.push_back(tm); //for example the first team name is read into tm and that value is insteted at the bottom of the vector and increases the vector size by one
		atbats.push_back(atb);
		hits.push_back(H);
		runs.push_back(R);
		hr.push_back(HR);
		rbi.push_back(runsin); 
		counter++; //after each line is read counter increase by one which keeps track of how many lines are in the input file
	}
	infile.close(); //closes the input file
}

void Baseball::Menu()
{
	int userinput;
	string teamName;
	string playername;
	int ab, hit, run, homerun, RBi;
	char choice;

	do //The do while loop will automatically output the menu at least once and will keep looping the menu until the user decides to exit
	{//The menu is outputted to the user
		cout << "1: Please enter the #1 to print out all users and statistics. " << endl << endl;
		cout << "2: Please enter the #2 to print out the statistics for a specific player. " << endl << endl;
		cout << "3: Please enter the #3 to print out all data for a specific team. " << endl << endl;
		cout << "4: Please enter the #4 to update the data for a specific player. " << endl << endl;
		cout << "5: Please enter the #5 to insert a new player and their statistics. " << endl <<endl;
		cout << "6: Please enter the #6 to export the data to an output file. " << endl << endl;
		cout << "7: Please enter the #7 to exit the program. " << endl << endl;
		
		cout << "Please enter one of the above options or -1 to exit: ";
		cin >> userinput; //the user inputs his choice
		cout << endl;

		if (userinput < 0 || userinput > 7) { //this will be outputted if the input is less then 0 or greater than 7
			cout << "Invalid selection. Try again." << endl << endl;
		}
		//based on what the user inputs it will call the corressponding function
		switch (userinput) //for example if the user inputs 1 then it will go to case 1 which calls the function then breaks out of the swithc statement
		{
		case 1:
			PrintAllInfo(); //calls the print all function which prints all the stats for each player
			break; //breaks out of the switch statement
		
		case 2:
			for (int i = 0; i < counter; i++) //This for loop lists all the names in the Stats file
			{
				cout << i << ". " << name.at(i) << endl;
			}
			cout << endl;
			cout << "Enter one of the above players that you want to search for: ";
			cin >> playername; //promts the user to enter a name that was listed above
			cout << endl;
			PrintOnePlayer(playername); //calls the function to print the stats for the player that was entered
			break;
		
		case 3:
			
			//lists all the teams that are in the input file
				
				for (int i = 0; i < counter; ++i)
				{
					cout << i << ". " << team.at(i) << endl;
				}
			
			cout << endl;
			cout << "Enter one of the above team's that you would like to search for: ";
			cin >> teamName; //promts the user to enter a team name that was listed above
			cout << endl;
			PrintOneTeam(teamName); //calls the function that prints the stats for the team that the user entered
			break;
		
		case 4:
			for (int i = 0; i < counter; i++) //lists all the names in the Stats file
			{
				cout << i << ". "<< name.at(i) << endl;
			}
			cout << endl;
			cout << "Which player would you like to update: ";
			cin >> playername; //promts the user to enter one of the players that was listed above
			cout << "The current stats for " << playername << " are listed below" << endl << endl;
			for (int j = 0; j < counter; j++) //This loop prints out the current stats for player the user entered
			{ //the loop goes through each line in the file
				if (playername == name.at(j)) //if one of those names matches up to the user input it will then print out all of his statictics
				{
					cout << left << setw(15) << "Players" << setw(12) << "Team" << setw(21) << "Total at bats" << setw(12) << "Runs" << setw(12) << "Hits" << setw(10) << "HR" << "RBI" << endl;
					cout << "-------------------------------------------------------------------------------------" << endl;
					cout << setw(15) << left << name.at(j); //the .at(j) represents the postion of the matching element
					cout << setw(18) << left << team.at(j);
					cout << setw(15) << left << atbats.at(j);
					cout << setw(12) << left << hits.at(j);
					cout << setw(12) << left << runs.at(j);
					cout << setw(10) << left << hr.at(j);
					cout << left << rbi.at(j) << endl;
				}
			}
			//the user is then promted to enter all of the players new stats
			cout << "\nEnter " << playername << "'s updated Team: ";
			cin >> teamName;
			cout << "Enter " << playername << "'s updated number of At Bats: ";
			cin >> ab;
			cout << "Enter " << playername << "'s updated number of Hits: ";
			cin >> hit;
			cout << "Enter " << playername << "'s updated number of Runs: ";
			cin >> run;
			cout << "Enter " << playername << "'s updated number of Home Runs: ";
			cin >> homerun;
			cout << "Enter " << playername << "'s updated number of Runs batted in (RBI's): ";
			cin >> RBi;
			cout << endl; //all of the new stats that the user entered is then brought to update function
			UpdateStats(playername, teamName, ab, hit, run, homerun, RBi); //the update function calls the function that updates all of the stats for the player that was seletced
			break; 
		
		case 5: //promts the user to all new stats for a player and saves them in the corressponding variables
			cout << "Please enter the player's last name: ";
			cin >> playername;
			cout << "Please enter the team name: ";
			cin >> teamName;
			cout << "Please enter the player's total at bats: ";
			cin >> ab;
			cout << "Please enter the player's total hits: ";
			cin >> hit;
			cout << "Please enter the player's total runs: ";
			cin >> run;
			cout << "Please enter the player's total home runs: ";
			cin >> homerun;
			cout << "Please enter the players total runs batted in: ";
			cin >> RBi;
			InstertNewStat(playername, teamName, ab, hit, run, homerun, RBi); //this is the function call that useses all of the user input as paramters
			cout << "\nThe new player has been successfully added" << endl;
			cout << endl;
			break;
		
		case 6:
			cout << "Would you like to export the data to a seprate output file yes or no" << endl;
			cout << "Please enter y for (yes) or n for (no): ";
			cin >> choice;
			cout << endl; //prompts the user to enter whether or not he wants to export the data to a output file
			
			if (choice == 'y'|| choice == 'Y') //if the user enters yes it will call the export function
			{
				ExportData();
			}
			else
			{//if they select no it returns them to the menu
				cout << "Returning to menu." << endl << endl;
			}
			break;

		case 7:
			exit_program(); //calls the exit program fucntion
			break;
		}
	} while (userinput != -1); //as long as the user does not enter -1 the loop will continue

}
//full function defintion for print all stats
void Baseball::PrintAllInfo()
{//prints out the label for the table in a neat manner using setw
	cout << left << setw(15) << "Players" << setw(12) << "Team" << setw(21) << "Total at bats" << setw(12) << "Runs" << setw(12) << "Hits" << setw(10) << "HR" << "RBI" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < counter; i++) //goes until the i is equal to the stats file size
	{//prints out all of the stats of each player
		cout << setw(15) << left << name.at(i);
		cout << setw(18) << left << team.at(i);
		cout << setw(15) << left << atbats.at(i);
		cout << setw(12) << left << hits.at(i);
		cout << setw(12) << left << runs.at(i);
		cout << setw(10) << left << hr.at(i);
		cout << left << rbi.at(i) << endl;
		cout << endl;
	}
}
//full function defintion for printing stats for one team
void Baseball::PrintOneTeam(string TeamName)
{
	for (int i = 0; i < counter; i++)
	{
		if (TeamName == team.at(i)) //if the user input matches one of the teams in the vector teams it prints out all the stats for that team
		{//so if there is multiple players on the same team it prints them all out 
			cout << left << setw(15) << "Players" << setw(12) << "Team" << setw(21) << "Total at bats" << setw(12) << "Runs" << setw(12) << "Hits" << setw(10) << "HR" << "RBI" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;
			cout << setw(15) << left << name.at(i);
			cout << setw(18) << left << team.at(i);
			cout << setw(15) << left << atbats.at(i);
			cout << setw(12) << left << hits.at(i);
			cout << setw(12) << left << runs.at(i);
			cout << setw(10) << left << hr.at(i);
			cout << left << rbi.at(i) << endl;
			cout << endl;
		}
	}

}
//full function defintion for printing the stats for one player
void Baseball::PrintOnePlayer(string Player)
{
	int i = 0;
	for (int j = 0; j < counter; j++) //the loop continues until i is equal to the value of counter
	{
		if (Player == name.at(j)) //if the user input is equal to name vector at that postion it prints out all of the stats including the name
		{
			cout << left << setw(15) << "Players" << setw(12) << "Team" << setw(21) << "Total at bats" << setw(12) << "Runs" << setw(12) << "Hits" << setw(10) << "HR" << "RBI" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;

			cout << setw(15) << left << name.at(j);
			cout << setw(18) << left << team.at(j);
			cout << setw(15) << left << atbats.at(j);
			cout << setw(12) << left << hits.at(j);
			cout << setw(12) << left << runs.at(j);
			cout << setw(10) << left << hr.at(j);
			cout << left << rbi.at(j) << endl << endl;

		}
		
	}
	
}
//full function defintion for update stats
void Baseball::UpdateStats(string PLAYER, string Team, int AB, int totalhit, int totalrun, int dingers, int runsbattedin)
{
	//the loop goes through the whole file and if the user enetered name matches that vector element of that postion it will replace the old element with the user input 
	for (int i = 0; i < counter; i++) 
	{
		if (PLAYER == name.at(i))
		{//replaces the old stats with the user input
			team.at(i) = Team; 
			atbats.at(i) = AB;
			hits.at(i) = totalhit;
			runs.at(i) = totalrun;
			hr.at(i) = dingers;
			rbi.at(i) = runsbattedin;
			//prints out the new stats of that player
			cout << "The new updated stats for: " << name.at(i) << endl << endl;
			cout << left << setw(15) << "Players" << setw(12) << "Team" << setw(21) << "Total at bats" << setw(12) << "Runs" << setw(12) << "Hits" << setw(10) << "HR" << "RBI" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;
			cout << setw(15) << left << name.at(i);
			cout << setw(18) << left << team.at(i);
			cout << setw(15) << left << atbats.at(i);
			cout << setw(12) << left << hits.at(i);
			cout << setw(12) << left << runs.at(i);
			cout << setw(10) << left << hr.at(i);
			cout << left << rbi.at(i) << endl << endl;
		}
	}

}
//full function defintion for insert a new player
void Baseball::InstertNewStat(string playername, string playerTeam, int at, int numhit, int Run, int hR, int Rbi) 
{//emplace back pushes the new stats to the back of the vector
	name.emplace_back(playername); 
	team.emplace_back(playerTeam);
	atbats.emplace_back(at);
	hits.emplace_back(numhit);
	runs.emplace_back(Run);
	hr.emplace_back(hR);
	rbi.emplace_back(Rbi);
	counter++; //increases the counter that keeps track of the file size
}

void Baseball::ExportData() //full function defintion for export data
{
	ofstream outfile;
	outfile.open("user.txt"); //opens the textfile user.txt

	if (!outfile)
	{
		cout << "There is an error in opening the file." << endl;
		abort(); //if there is error in opening the file the program will exit
	}

	for (int i = 0; i < counter; i++) //the for loop continues until i is equal to counter
	{//reads each element from the vector seperated by a space into a seprate output file
		outfile << name.at(i) << " " << team.at(i) << "  " << atbats.at(i) << "  " << hits.at(i) << "  " << runs.at(i) << "  " << hr.at(i) << "  " << rbi.at(i) << endl; 
	}

	cout << "The data was succefully exported!!" << endl << endl;
	outfile.close();
}

int Baseball::exit_program() //full function defintion for exit program
{
	cout << "Thank you for using the program." << endl;
	exit(0); //exits from the program
}