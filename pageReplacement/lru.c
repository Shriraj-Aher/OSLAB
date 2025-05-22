#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 25 // Define the maximum number of pages
// Function to simulate LRU page replacement
void lruPageReplacement(int pages[], int numPages, int numFrames)
{
    int memory[MAX_FRAMES]; // To store frames in memory
    int pageFaults = 0;
    int i, j, k;
    // Initialize memory with -1 (empty frames)
    for (i = 0; i < numFrames; i++)
    {
        memory[i] = -1;
    }
    // Iterate through the page reference string
    for (i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in memory (no page fault)
        for (j = 0; j < numFrames; j++)
        {
            if (memory[j] == page)
            {
                found = 1;
                break;
            }
        }
        // If page is not in memory (page fault)
        if (!found)
        {
            pageFaults++;
            // If memory is full, remove the least recently used page
            for (k = 0; k < numFrames - 1; k++)
            {
                memory[k] = memory[k + 1];
            }
            // Insert the new page at the last position in memory
            memory[numFrames - 1] = page;
        }
        // Display the current memory content after every page reference
        printf("Memory after %d page(s): ", i + 1);
        for (j = 0; j < numFrames; j++)
        {
            if (memory[j] != -1)
            {
                printf("%d ", memory[j]);
            }
        }
        printf("\n");
    }
    // Print the total page faults
    printf("Total Page Faults: %d\n", pageFaults);
}
int main()
{
    int numPages, numFrames;
    // Take input from the user for number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    if (numFrames > MAX_FRAMES)
    {
        printf("Max frames allowed are %d. Setting frames to %d.\n", MAX_FRAMES, MAX_FRAMES);
        numFrames = MAX_FRAMES;
    }
    // Take input for the page reference string
    printf("Enter the number of pages (max %d): ", MAX_PAGES);
    scanf("%d", &numPages);
    if (numPages > MAX_PAGES)
    {
        printf("Max pages allowed are %d. Setting pages to %d.\n", MAX_PAGES, MAX_PAGES);
        numPages = MAX_PAGES;
    }
    int pages[numPages];
    printf("Enter the page reference string (space-separated):\n");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }
    // Call the LRU page replacement function
    lruPageReplacement(pages, numPages, numFrames);
    return 0;
}