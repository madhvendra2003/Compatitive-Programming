#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    vector<int> bit; // Binary Indexed Tree array
    int n;

    FenwickTree(int size) {
        n = size;
        bit.resize(n + 1, 0); // 1-based indexing
    }

    // Add 'val' to index 'idx'
    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += (idx & -idx); // Move to the next index
        }
    }

    // Get the prefix sum from index 1 to idx
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx); // Move to the parent index
        }
        return sum;
    }

    // Get the sum in the range [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// Coordinate Compression function
vector<int> coordinateCompress(vector<int>& salaries) {
    vector<int> sorted_salaries = salaries;
    sort(sorted_salaries.begin(), sorted_salaries.end());
    sorted_salaries.erase(unique(sorted_salaries.begin(), sorted_salaries.end()), sorted_salaries.end());

    vector<int> compressed(salaries.size());
    for (int i = 0; i < salaries.size(); i++) {
        compressed[i] = lower_bound(sorted_salaries.begin(), sorted_salaries.end(), salaries[i]) - sorted_salaries.begin() + 1;
    }
    return compressed;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> salaries(n);
    for (int i = 0; i < n; i++) {
        cin >> salaries[i];
    }

    // Coordinate compress the salary values
    vector<int> compressed_salaries = coordinateCompress(salaries);
    FenwickTree fenwick(*max_element(compressed_salaries.begin(), compressed_salaries.end()));

    // Initialize the Fenwick Tree with the compressed salaries
    for (int i = 0; i < n; i++) {
        fenwick.update(compressed_salaries[i], 1);
    }

    while (q--) {
        char type;
        cin >> type;

        if (type == '!') {
            int k, x;
            cin >> k >> x;
             // 0-based index for the employee

            // Compress the new salary
            int compressed_new_salary = lower_bound(compressed_salaries.begin(), compressed_salaries.end(), x) - compressed_salaries.begin() + 1;

            // Update Fenwick Tree: decrement old salary and increment new salary
            fenwick.update(compressed_salaries[k], -1);
            fenwick.update(compressed_new_salary, 1);

            // Update the salary in the array
            compressed_salaries[k] = compressed_new_salary;

        } else if (type == '?') {
            int a, b;
            cin >> a >> b;

            // Compress the range values
            int compressed_a = lower_bound(compressed_salaries.begin(), compressed_salaries.end(), a) - compressed_salaries.begin() + 1;
            int compressed_b = upper_bound(compressed_salaries.begin(), compressed_salaries.end(), b) - compressed_salaries.begin();

            // Perform range query on the Fenwick Tree
            cout << fenwick.rangeQuery(compressed_a, compressed_b) << "\n";
        }
    }

    return 0;
}
