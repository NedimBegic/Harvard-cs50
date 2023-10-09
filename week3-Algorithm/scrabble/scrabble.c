#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(const char *word);

int main(void)
{
    // Get input words from both players
    char word1[50]; // Adjust the size as needed
    char word2[50]; // Adjust the size as needed

    printf("Player 1: ");
    scanf("%s", word1);
    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    printf("Score 1: %d\n", score1);
    printf("Score 2: %d\n", score2);

    // TODO: Print the winner
    int winner = score1 > score2 ? 1 : 2;
    if (score1 == score2)
    {
        printf("Tie!");
    }
    else
    {
        printf("Player %i wins!", winner);

    }
}

int compute_score(const char *word)
{
    int score = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            int index = tolower(word[i]) - 'a';
            score += POINTS[index];
        }
    }

    return score;
}
