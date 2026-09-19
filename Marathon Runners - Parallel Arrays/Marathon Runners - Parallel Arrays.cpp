#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const int NUM_RUNNERS = 5;
const int NUM_DAYS = 7;
string runner_data[NUM_RUNNERS];
string runner_names[NUM_RUNNERS];
int runner_times[NUM_RUNNERS][NUM_DAYS];
int totals[NUM_RUNNERS];
int averages[NUM_RUNNERS];

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

static void calculateTotalsAndAverages()
{
	for (int i = 0; i < NUM_RUNNERS; ++i) {
		totals[i] = 0;
		for (int j = 0; j < NUM_DAYS; ++j) {
			totals[i] += runner_times[i][j];
		}
		averages[i] = totals[i] / NUM_DAYS;
	}
}

static void displayResults()
{
	cout << left;

	cout << setw(12) << "Name"
		<< setw(12) << "Sunday"
		<< setw(12) << "Monday"
		<< setw(12) << "Tuesday"
		<< setw(12) << "Wednesday"
		<< setw(12) << "Thursday"
		<< setw(12) << "Friday"
		<< setw(12) << "Saturday"
		<< setw(12) << "Total"
		<< setw(12) << "Average" << endl;

	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < NUM_RUNNERS; ++i) {
		cout << setw(12) << runner_names[i];
		for (int j = 0; j < NUM_DAYS; ++j) {
			cout << setw(12) << runner_times[i][j];
		}
		cout << setw(12) << totals[i]
			<< setw(12) << averages[i] << endl;
	}
}

int main()
{
	readRunnerData();
	sortRunnerData();
	calculateTotalsAndAverages();
	displayResults();
}