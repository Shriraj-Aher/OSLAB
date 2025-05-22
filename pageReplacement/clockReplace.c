#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 25
void clockPageReplacement(int pages[], int numPages, int numFrames)
{
    int frames[numFrames]; // To store pages in memory
    int refBit[numFrames];
    int hand = 0;
    int pageFaults = 0;
    int i, j;
    // To keep track of reference bits
    // Points to the current page in the clock
    // Initialize memory frames and reference bits to -1 and 0 respectively
    for (i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        refBit[i] = 0;
    }
    // Iterate through the page reference string
    for (i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in one of the frames
        for (j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                refBit[j] = 1; // Set the reference bit to 1 (used recently)
                break;
            }
        }
        // If the page is not in memory (page fault)
        if (!found)
        {
            pageFaults++;
            // Find a page to replace using the clock algorithm
            while (refBit[hand] == 1)
            {
                refBit[hand] = 0;
                hand = (hand + 1) % numFrames; // Reset reference bit to 0 for pages that were used
                // Move to the next page (circular)
            }
            // Replace the page at the clock hand position
            frames[hand] = page;
            refBit[hand] = 1;              // Set the reference bit to 1 for the newly added page
            hand = (hand + 1) % numFrames; // Move the clock hand to the next position
        }
        // Display the current memory content after every page reference
        printf("Memory after %d page(s): ", i + 1);
        for (j = 0; j < numFrames; j++)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
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
    // Call the Clock page replacement function
    clockPageReplacement(pages, numPages, numFrames);
    return 0;
}