#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// Struct to represent each entry with dimensions and price
struct Barfi_DP {  //Barfi Dimension and Price
    int dim1;
    int dim2;
    int price;
};

void readAndStoreTestCase(const string&, int& , vector<Barfi_DP>&);
int getMaxProfit_Top_Down_Memo(int , const vector<Barfi_DP>& , unordered_map<int, int>&);
int getMaxProfit_Bottom_Up_Memo(int , const vector<Barfi_DP>&);
int getMaxProfit_Top_Down_No_Memo(int, const vector<Barfi_DP>&);
int getMaxProfit_Bottom_Up_Memo_Opt(int , const vector<Barfi_DP>&);



int main() {
    // Specify the filename with the test case data
    string filename = "TestCase3.txt";

    // Variables to store burfi size and entries
    int n;
    vector<Barfi_DP> entries;

    // Call the file reading function
    readAndStoreTestCase(filename, n, entries);

    // Display the read data
    std::cout << "Burfi Size: " << n << endl;
   std:: cout << "\t\t\t\t\tDimensions\t\tPrices:" << endl;
    for (const auto& entry : entries) {
       std:: cout << "\t\t\t\t\t(" << entry.dim1 << "," << entry.dim2 << ")\t\t\t{" << entry.price << "}" << endl;
    }

    //Recursive Top Down Algorithm with Memoization
    std::cout << "\n\n\n\t\t------------Recursive Top Down Algorithm with Memoization------------\n";
    unordered_map<int, int> memo;  
    int maxProfit = getMaxProfit_Top_Down_Memo(n, entries, memo);
    std::cout << "\t\t\t\t\tMaximum Profit: " << maxProfit << endl;

    std::cout << "\n\n\n\t\t------------Iterative Buttom-Up Algorithm with Memoization------------\n";
   // unordered_map<int, int> memo;
    int result = getMaxProfit_Bottom_Up_Memo_Opt(n, entries);
    cout << "\t\t\t\t\tMaximum Profit: " << result << endl;


    std::cout << "\n\n\n\t\t------------Recursive Top-Down Algorithm without Memoization------------\n";
    
    int result1 = getMaxProfit_Top_Down_No_Memo(n, entries);

    cout << "\t\t\t\t\tMaximum Profit: " << result1 << endl;




    return 0;
}



// Function to read test case data from a file and store dimensions and prices in vectors
void readAndStoreTestCase(const string& filename, int& n, vector<Barfi_DP>& entries) {
    ifstream inputFile(filename);
    
    bool i = !inputFile;
    switch (i)
    {
        case 1:
        {
            cerr << "Error opening the file." << endl;
            exit(1);
            break;
        }

    }
        

    // Read the burfi size
    inputFile >> n;
    
    switch (n % 100 != 0)
    {
        case 1:
        {
            cerr << "Error: The burfi size must be a multiple of 100." << endl;
            exit(1);
            break;
        }

    }




    string line;
    while (getline(inputFile, line)) {

        if (line.empty()) { //to tacke '\n'
            continue;
        }

        stringstream ss(line);
        int dim1, dim2, price;

        size_t priceStart = line.find("{") + 1;
        size_t priceEnd = line.find("}");
        price = stoi(line.substr(priceStart, priceEnd - priceStart));
        int i = 0;
        int start = 0, end = 0;

        while (line[i] != '{') {


            switch(line[i]) {

                case '(':
                Barfi_DP* bf = new Barfi_DP();

                start = i + 1;
                end = line.find(',', start);
                bf->dim1 = stoi(line.substr(start, end - start));
                
                switch (bf->dim1 % 5 != 0)
                {
                    case 1:
                    cerr << "Error: The Dimension must be a multiple of 5." << endl;

                    exit(1);
                    break;
                }

                start = end + 1;
                end = line.find(')', start);
                bf->dim2 = stoi(line.substr(start, end - start));
                switch (bf->dim2 % 5 != 0)
                {
                case 1:
                    cerr << "Error: The Dimension must be a multiple of 5." << endl;

                    exit(1);
                    break;
                }

                switch ((bf->dim1 * bf->dim2) < 100 || (bf->dim1 * bf->dim2) %100 !=0)
                {
                case 1:
                    cerr << "Error: The Area of Burfi must be 100 sq cm or multiple of 100 ." << endl;

                    exit(1);

                    break;
                }
                bf->price = price;

                entries.push_back(*bf);
                break;

            }
            ++i;
        }
    }
    inputFile.close();
}

int getMaxProfit_Top_Down_Memo(int n, const vector<Barfi_DP>& entries, unordered_map<int, int>& memo) {
    // Check if the result for this burfi size has already been calculated
    switch (memo.find(n) != memo.end()) {
        case 1:
        return memo[n];
        break;
    }

    // Base case: if the burfi size is less than 100, no profit can be earned
    switch (n < 100) {
        case 1:
        return 0;
        break;
    }

    int maxProfit = 0;

    // Try different combinations of dimensions
    for (const Barfi_DP& entry : entries) {
        int remainingSize = n - entry.dim1 * entry.dim2;

        // Check if the remaining size is a multiple of 100 and does not exceed n
        switch (remainingSize >= 0 && remainingSize % 100 == 0) {
        case 1:
            int profit = entry.price + getMaxProfit_Top_Down_Memo(remainingSize, entries, memo);
            maxProfit = max(maxProfit, profit);
            break;
        }
    }

    // Memoize the result for this burfi size
    memo[n] = maxProfit;

    return maxProfit;
}
//Iterative Buttom Up

int getMaxProfit_Bottom_Up_Memo(int n, const vector<Barfi_DP>& entries) {
    unordered_map<int, int> memo;

    // Base case: if the burfi size is less than 100, no profit can be earned
    int i = 0;
    while (i < 100) {
        memo[i] = 0;
        ++i;
    }
    i = 100;
    while (i <= n) {
        int maxProfit = 0;

        // Try different combinations of dimensions
        for (const Barfi_DP& entry : entries) {
            int remainingSize = i - entry.dim1 * entry.dim2;

            // Check if the remaining size is a multiple of 100 and does not exceed i
            switch (remainingSize >= 0 && remainingSize % 100 == 0) {
            case 1:
                int profit = entry.price + memo[remainingSize];
                maxProfit = max(maxProfit, profit);
                break;
            }
        }

        // Memoize the result for this burfi size
        memo[i] = maxProfit;
        ++i;
    }

    return memo[n];
}

////Iterative Buttom Up Optimized for space
////Here i have used Vectors instead of maps. because vectors remove the overhead memory and more suitable for this scenero.

int getMaxProfit_Bottom_Up_Memo_Opt(int n, const vector<Barfi_DP>& entries) {
    // Use a vector to store the memoization table
    vector<int> memo(n + 1, 0);

    // Base case: if the burfi size is less than 100, no profit can be earned
    int i = 0;
    while (i < 100) {
        memo[i] = 0;
        ++i;
    }

    i = 100;
    while (i <= n) {
        int maxProfit = 0;

        // Try different combinations of dimensions
        for (const Barfi_DP& entry : entries) {
            int remainingSize = i - entry.dim1 * entry.dim2;

            // Check if the remaining size is a multiple of 100 and does not exceed i
            switch (remainingSize >= 0 && remainingSize % 100 == 0) {
            case 1:
                int profit = entry.price + memo[remainingSize];
                maxProfit = max(maxProfit, profit);
                break;
            }
        }

        // Memoize the result for this burfi size
        memo[i] = maxProfit;
        ++i;
    }

    return memo[n];
}


//Simple Recursive Top Down Without Memoization
int getMaxProfit_Top_Down_No_Memo(int n, const vector<Barfi_DP>& entries) {
    // Base case: if the burfi size is less than 100, no profit can be earned
    switch (n < 100) {
    case 1:
        return 0;
        break;

    }

    int maxProfit = 0;

    // Try different combinations of dimensions
    for (const Barfi_DP& entry : entries) {
        int remainingSize = n - entry.dim1 * entry.dim2;

        // Check if the remaining size is a multiple of 100 and does not exceed n
        switch (remainingSize >= 0 && remainingSize % 100 == 0) {
            case 1:
            int profit = entry.price + getMaxProfit_Top_Down_No_Memo(remainingSize, entries);
            maxProfit = max(maxProfit, profit);
            break;
        }
    }

    return maxProfit;
}
