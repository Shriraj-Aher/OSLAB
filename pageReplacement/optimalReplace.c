#include <stdio.h>
#include <stdlib.h>
#define MAX_FRAMES 10
#define MAX_PAGES 100
// Function to find the index of the page that will not be used for the longest time in future
int findOptimal(int frames[], int n, int page[], int currPos, int totalPages)
{
    int farthest = currPos;
    int indexToReplace = -1;
    // Check all pages in memory
    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = currPos; j < totalPages; j++)
        {
            if (frames[i] == page[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        // If page is not found in future, it will be replaced
        if (j == totalPages)
        {
            return i;
        }
    }
    return indexToReplace;
}
// Function to implement Optimal page replacement
void optimalPageReplacement(int page[], int totalPages, int n)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int hit = 0;
    // Initialize frames as empty
    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
    }
    for (int i = 0; i < totalPages; i++)
    {
        int found = 0;
        // Check if page is already in frames
        for (int j = 0; j < n; j++)
        {
            if (frames[j] == page[i])
            {
                found = 1;
                hit = 1;
                break;
            }
        }
        // If page is not in frames, replace a page
        if (!found)
        {
            // Find the index to replace using the Optimal strategy
            int replaceIndex = findOptimal(frames, n, page, i + 1, totalPages);
            frames[replaceIndex] = page[i];
            pageFaults++;
        }
        printf("Frames: ");
        for (int j = 0; j < n; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        }
        if (!hit)
        {
        }
        else
        {
            printf("(Page fault!)\n");
            printf("(Page hit!)\n");
        }
        hit = 0;
    }
    printf("Total page faults: %d\n", pageFaults);
}
int main()
{
    int page[MAX_PAGES], totalPages, n;
    // Take the input from the user for page reference string and the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &n);
    printf("Enter the total number of page references: ");
    scanf("%d", &totalPages);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < totalPages; i++)
    {
        scanf("%d", &page[i]);
    }
    // Call the Optimal Page Replacement function
    optimalPageReplacement(page, totalPages, n);
    return 0;
}