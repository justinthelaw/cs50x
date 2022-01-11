#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void merge_sort(int lowIndex, int highIndex);
void merge(int lowIndex, int midIndex, int highIndex);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
    return 0;
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    merge_sort(0, candidate_count);

    int maxVotes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (maxVotes < candidates[i].votes)
        {
            maxVotes = candidates[i].votes;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == maxVotes)
        {
            printf("%s\n", candidates[j].name);
        }
    }

    return;
}

void merge_sort(int lowIndex, int highIndex)
{
    if (lowIndex != highIndex)
    {
        int midIndex;
        midIndex = (lowIndex + highIndex) / 2; // find the middle of the current array
        merge_sort(lowIndex, midIndex);        // continue to split left side until it is a bunch of touples
        merge_sort(midIndex + 1, highIndex);   // continue to split right side until it is a bunch of touples
        merge(lowIndex, midIndex, highIndex);  // merge the sorted arrays together
    }
    return;
}

void merge(int lowIndex, int midIndex, int highIndex)
{
    candidate temp[MAX];  // array for storing candidates in order of most to least votes
    int i = lowIndex;     // first element to be compared
    int j = midIndex + 1; // second element to be compared
    int k = lowIndex;     // main index used for filling the temp array

    while ((i <= midIndex) && (j <= highIndex))
    {
        if (candidates[i].votes >=
            candidates[j].votes) // decision point for sorting of arrays, in this case the largest amount of votes wins
        {
            temp[k++] = candidates[i++];
        }
        else
        {
            temp[k++] = candidates[j++];
        }
    }

    // fill in temp array with remaining element
    while (i <= midIndex)
    {
        temp[k++] = candidates[i++];
    }

    while (j <= highIndex)
    {
        temp[k++] = candidates[j++];
    }

    // fill original array back in with ordered elements
    for (i = lowIndex; i <= highIndex; i++)
    {
        candidates[i] = temp[i];
    }
    return;
}
