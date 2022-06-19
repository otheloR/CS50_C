#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// && go to first voter, first preference, put in two == alice &&
// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// GLOBAL Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // && if command line argument count is less than two, say this &&
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // && Take off the first command line argument ./runoff &&
    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // && iterate through candidates array and fill in variables with dummy input: name, votes, and eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

        //Go to the 0th voter
    // query votes for each voter
    for (int i = 0; i < voter_count; i++)
    {

        // Go to the 0th rank of the 0th voter, then the 1th rank of the 0th voter

        // && for each voter, get a name, check name, put value of name into [[#][][]], then next name put into [[][#][]] ...
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid

// is the name that is gotten on the ballot?
bool vote(int voter, int rank, string name)
{

   for (int x = 0; x < candidate_count; x++) {

        // get that index number of candidates array with matching name and put into preferences [[#][][]]
       if (strcmp(name, candidates[x].name) == 0) {

           preferences[voter][rank] = x;
           return true;

       }

   }



    return false;
}

//go to a new voter every time, tally their first preferred choice

// Tabulate votes for non-eliminated candidates
// && count all first preference votes of each voter
void tabulate(void)
{

    //go through each ballot
    for (int x = 0; x < voter_count; x++) {

        // preference counter
        int k = 0;

        // get their candidate's number
        int z = preferences[x][k];

            //if kth preference is eliminated, keep iterating through x's preferences until you find a non-eliminated candidate
            if (candidates[z].eliminated == true) {

                do {
                    z = preferences[x][k++];
                }
                while (candidates[z].eliminated == true);


            }




        // if not eliminated, add vote to their counter
        if (candidates[z].eliminated == false) {
            candidates[z].votes++;
            printf("%s %i\n", candidates[z].name, candidates[z].votes);
        }



    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int x = 0; x < candidate_count; x++) {

        if (candidates[x].votes > voter_count / 2) {

            printf("%s\n", candidates[x].name);
            return true;

        }

    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// Get minimum number candidate who is still in race

// && Set first candidate not eliminated as first minimum value, then check amount of votes of other candidates not eliminated
int find_min(void)
{

   // get first candidate value with 'false,' put into currentMin
    int z = 0;
    int currentMin = 0;

   while (true) {

       if (candidates[z].eliminated == false) {

           currentMin = candidates[z].votes;


           //print the first name that will be currentMin


           break;

       }

       else {

           z++;

       }


   }


    //check this first value against all other candidates voter amounts
   for (int x = 0; x < candidate_count; x++) {

       if(candidates[x].eliminated == false && candidates[x].votes < currentMin) {

           currentMin = candidates[x].votes;

       }

   }



    return currentMin;
    return 0;
}


// Return true if every candidate remaining in election has the same number of votes, false otherwise
bool is_tie(int min)
{
    int num_Remaining = 0;
    int nonElim_withMin = 0;

    // count every non-eliminated candidate
    for (int i = 0; i < candidate_count; i++) {

        if (candidates[i].eliminated == false) {

            num_Remaining++;
        }


    //count every non-eliminated candidate with least votes
        if (candidates[i].votes == min) {

            nonElim_withMin++;
        }


    }
    // if every non-eliminated candidate has the least amount of votes, return true
    if (nonElim_withMin == num_Remaining) {

        return true;

    }
    return false;

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int x = 0; x < candidate_count; x++) {

        if (candidates[x].votes == min) {

            candidates[x].eliminated = true;

        }

    }
    return;
}
