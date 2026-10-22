
#include <iostream>
using namespace std;

int main()
{
    int data[20], hamming[30];
    int m, r = 0;
    int i, j;

    // Enter the number of data bits
    cout << "Enter number of data bits: ";
    cin >> m;



    // Calculate the number of parity bits
    // 1 << r means 2 raised to the power r    r is number of parity bits
    while ((1 << r) < (m + r + 1))
    {
        r++;
    }

    // Calculate total number of bits
    int total = m + r;

    // Enter data bits from left to right
    // Store them starting at data[1]
    cout << "Enter data bits: ";

    for (i = 1; i <= m; i++)
    {
        cin >> data[i];

        // Check that the bit is either 0 or 1
        if (data[i] != 0 && data[i] != 1)
        {
            cout << "Enter only 0 or 1.";
            return 0;
        }
    }

    // Place data and parity bits
    // Parity positions are 1, 2, 4, 8...
    // Example for 4 data bits:
    // P1 P2 M1 P3 M2 M3 M4
    int k = 1;

    for (i = 1; i <= total; i++)
    {
        // Check whether i is a power of 2
        if ((i & (i - 1)) == 0)
        {
            hamming[i] = 0;  // Reserve parity position
        }
        else
        {
            hamming[i] = data[k];  // Place data bit
            k++;
        }
    }

    // Calculate parity bits using even parity
    for (i = 0; i < r; i++)
    {
        int p = 1 << i;
        int parity = 0;

        // Check all positions covered by this parity bit
        for (j = 1; j <= total; j++)
        {
            if (j & p)
            {
                parity = parity ^ hamming[j];
            }
        }

        // Store the calculated parity bit
        hamming[p] = parity;
    }

    // Print generated Hamming code from left to right
    cout << "\nGenerated Hamming Code: ";

    for (i = 1; i <= total; i++)
    {
        cout << hamming[i];
    }

    cout << endl;

    // Enter received Hamming code from left to right
    cout << "\nEnter received Hamming Code: ";

    for (i = 1; i <= total; i++)
    {
        cin >> hamming[i];

        if (hamming[i] != 0 && hamming[i] != 1)
        {
            cout << "Enter only 0 or 1.";
            return 0;
        }
    }

    // Detect the error using parity checks
    int errorPosition = 0;

    for (i = 0; i < r; i++)
    {
        int p = 1 << i;
        int parity = 0;

        for (j = 1; j <= total; j++)
        {
            if (j & p)
            {
                parity = parity ^ hamming[j];
            }
        }

        // Add the position if its parity check fails
        if (parity != 0)
        {
            errorPosition = errorPosition + p;
        }
    }

    // Display the result
    if (errorPosition == 0)
    {
        cout << "\nNo error detected." << endl;
    }
    else if (errorPosition > total)
    {
        cout << "\nInvalid error position." << endl;
    }
    else
    {
        // Display the error position
        cout << "\nError detected at position: "
             << errorPosition << endl;

        // Flip the incorrect bit
        hamming[errorPosition] =
            hamming[errorPosition] ^ 1;

        // Print corrected code from left to right
        cout << "Corrected Hamming Code: ";

        for (i = 1; i <= total; i++)
        {
            cout << hamming[i];
        }

        cout << endl;
    }

    return 0;
}
