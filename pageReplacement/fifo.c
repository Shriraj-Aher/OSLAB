#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 20
void FIFO(int pages[], int numPages, int numFrames)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int nextFrame = 0;
    // Initialize frames to -1, meaning empty
    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
    }
    // Iterate over the page reference string
    for (int i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int pageFound = 0;
        // Check if the page is already in the frame (hit)
        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                pageFound = 1;
                break;
            }
        }
        // If the page was not found in the frames, it's a page fault
        if (!pageFound)
        {
            // Replace the oldest page (FIFO)
            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % numFrames;
            pageFaults++;
            // Print the current state of the frames after replacement
            printf("Page %d inserted, Frames: ", page);
            for (int j = 0; j < numFrames; j++)
            {
                if (frames[j] == -1)
                {
                    printf("empty ");
                }
                else
                {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }
    printf("Total page faults: %d\n", pageFaults);
}
int main()
{
    int pages[MAX_PAGES];
    int numPages, numFrames;
    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter page reference string:\n");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &numFrames);
    FIFO(pages, numPages, numFrames);
    return 0;
}