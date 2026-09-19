#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int NUM_RUNNERS = 5;
const int NUM_DAYS = 7;
string runner_data[NUM_RUNNERS];
string runner_names[NUM_RUNNERS];
int runner_times[NUM_RUNNERS][NUM_DAYS];

static void readRunnerData()
{
	ifstream inputFile("runners.txt");
	if (!inputFile) {
		cerr << "Error: could not open runners.txt\n";
	}
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		if (!getline(inputFile, runner_data[i])) {
			cerr << "Error: failed to read runner at index " << i << "\n";
		}
	}
}

//example of a line of data from runner_data: Johnson 05 11 12 41 10 10 17

static void sortRunnerData()
{
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		runner_names[i] = runner_data[i].substr(0, runner_data[i].find(' '));
	}
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		std::istringstream iss(runner_data[i]);
		std::string token;

		if (!(iss >> token)) continue;

		for (int j = 0; j < NUM_DAYS; ++j) {
			if (!(iss >> token)) {
				runner_times[i][j] = 0;
			} else {
				try {
					runner_times[i][j] = std::stod(token);
				} catch (...) {
					runner_times[i][j] = 0;
				}
			}
		}
	}
}

int main()
{
	readRunnerData();
	sortRunnerData();
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		cout << runner_names[i] << endl;
	}
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		for (int j = 0; j < NUM_DAYS; ++j) {
			cout << runner_times[i][j] << endl;
		}
	}
}