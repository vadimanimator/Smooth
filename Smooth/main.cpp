#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;


string filename = "";
int smoothArgument = 0;
vector <double> sourceData;
vector <double> sortedData;

int main(int argc, char** argv) {

	if (argc != 3) {
		cout << "Example: programm file.txt 10" << endl;
		return 0;
	}
	else {
		filename = argv[1];
		smoothArgument = atoi(argv[2]);
	}
	

	//read data
	std::ifstream file(filename);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			sourceData.push_back(stof(line));
		}
		file.close();
	}
	else {
		cout << "File " << filename << " not found" << endl;
		return 0;
	}

	sortedData = sourceData;
	sort(sortedData.begin(), sortedData.end());

	//smooth
	for (int i = 0; i < sourceData.size(); i++) {
		int count = 0;
		double sum = 0;
		for (int j = 0; j < sortedData.size(); j++) {
			if (sortedData[j] >= sourceData[i] - smoothArgument && sortedData[j] <= sourceData[i] + smoothArgument) {
				count++;
				sum += sortedData[j];
			}
			if (sortedData[j] > sourceData[i] + smoothArgument) break;
		}
		if (count >= 2) sourceData[i] = sum / count;
	}

	//save new date
	ofstream fout("output.txt"); 

	for (int i = 0; i < sourceData.size(); i++) {
		if (i < sourceData.size() - 1)
			fout << sourceData[i] << endl;
		else 
			fout << sourceData[i];
	}
	
	fout.close(); 

	cout << "Smoothed data saved to \"output.txt\"" << endl;

	return 0;
}