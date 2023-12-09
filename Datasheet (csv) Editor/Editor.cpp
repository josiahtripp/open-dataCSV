#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

string selection, dataFileName;
char dataArray[100][100];
string rowKey[100], columnKey[100];
int columnTotal = 0, rowTotal = 0, term = 0;

void loadKeys() {

	for (int i = 0; i < 100; i++) rowKey[i] = to_string(i + 1);
	for (int i = 0; i < 100; i++) {

		if (i < 26) columnKey[i] = (char(i + 65));
		else if (i < 52) columnKey[i] = "A";
		else if (i < 78) columnKey[i] = "B";
		else if (i < 100) columnKey[i] = "C";
	}
}

void printGrid(int rT, int cT) {

	cout << "    ";
	for (int i = 0; i < cT; i++) cout << " " << columnKey[i];//prints column keys
	cout << endl << "    ";
	if (cT > 27) {
		for (int i = 0; i < cT; i++) {//prints > 26 columns keys
			if (i < 26) cout << " |";
			else if (i < 52) cout << " " << char(i + 39);
			else if (i < 78) cout << " " << char(i + 13);
			else cout << " " << char(i - 13);
		}
		cout << endl << "    ";
	}

	for (int i = 0; i < cT; i++) cout << "_|";//Prints top of Grid
	cout << "_" << endl;

	for (int i = 0; i < rT; i++) {


		cout << right << setw(3) << rowKey[i] << "-|";
		for (int j = 0; j < cT; j++) {

			cout << dataArray[i][j] << "|";
		}
		cout << endl;
	}
}

void loadCharArray(string fileName) {

	columnTotal = 0, rowTotal = 0, term = 0;
	string rowRead;
	ifstream dataFile; 
	dataFile.open(fileName);

	while (getline(dataFile, rowRead) && rowRead != "") {//loads .csv datasheet into dataArray[][]
		
		for (int j = 0; j < rowRead.length(); j++) {

			if (rowRead[j] != ',') dataArray[rowTotal][term] = rowRead[j], term++;
			if (rowRead[j] == ',' && j == 0) dataArray[rowTotal][term] = ' ', term++;
			if (rowRead[j] == ',' && (rowRead[j + 1] == ',' || j + 1 == rowRead.length())) dataArray[rowTotal][term] = ' ', term++;
		}
		rowTotal++;
		columnTotal = term;
		term = 0;
	}
	dataFile.close();
}

void dataEditor() {

	string rowstring, columnstring, cell;
	int row = 404, column = 404;
	char cellFill;

	cout << "Please enter a cell (Ex: B6): ";
	cin >> cell;
	for (int i = 0; i < cell.length(); i++) {

		if (isalpha(cell[i])) columnstring += toupper(cell[i]);
		if (isdigit(cell[i])) rowstring += cell[i];
	}
	for (int i = 0; i < columnTotal; i++) if (columnKey[i] == columnstring) column = i;
	for (int i = 0; i < rowTotal; i++) if (rowKey[i] == rowstring) row = i ;

	if (column == 404 || row == 404) cout << "Specified cell is outisde of data range. Please Select again." << endl;
	else {
		cout << "You've selected row " << row + 1 << " column " << column + 1
			<< ". Please enter a data value:" << endl;
		cin >> cellFill;
		if (cellFill == '_') cellFill = ' ';
		dataArray[row][column] = cellFill;
	}
}

void dataFill() {

	string rowstring, columnstring, cell;
	char fill;
	int row = 404, column = 404, row1 = 404, column1 = 404;
	bool loop = true;

	while (loop == true) {

		loop = false;
		rowstring = "", columnstring = "";
		cout << "Please enter the cell of the first corner: ";
		cin >> cell;

		for (int i = 0; i < cell.length(); i++) {

			if (isalpha(cell[i])) columnstring += toupper(cell[i]);
			if (isdigit(cell[i])) rowstring += cell[i];
		}
		for (int i = 0; i < columnTotal; i++) if (columnKey[i] == columnstring) column = i;
		for (int i = 0; i < rowTotal; i++) if (rowKey[i] == rowstring) row = i;

		if (column == 404 || row == 404) loop = true, cout << "Specified cell is outisde of data range. Please Select again." << endl;
	}

	loop = true;
	while (loop == true) {

		loop = false;
		rowstring = "", columnstring = "";
		cout << "Please enter the cell of the second (opposite) corner: ";
		cin >> cell;

		for (int i = 0; i < cell.length(); i++) {

			if (isalpha(cell[i])) columnstring += toupper(cell[i]);
			if (isdigit(cell[i])) rowstring += cell[i];
		}
		for (int i = 0; i < columnTotal; i++) if (columnKey[i] == columnstring) column1 = i;
		for (int i = 0; i < rowTotal; i++) if (rowKey[i] == rowstring) row1 = i;

		if (column1 == 404 || row1 == 404) loop = true, cout << "Specified cell is outisde of data range. Please Select again." << endl;
	}

	cout << "selected row " << row + 1 << " column " << column + 1 << " and row " << row1 + 1 << " column " << column1 + 1
		<< endl << "Please enter a new data value: ";
	cin >> fill;
	if (fill = '_') fill = ' ';

	if (row <= row1) {

		for (int i = row; i <= row1; i++) {

			if (column <= column1) for (int j = column; j <= column1; j++) dataArray[i][j] = fill;
			if (column > column1) for (int j = column; j > column1; j--) dataArray[i][j] = fill;
		}
	}
	if (row > row1) {

		for (int i = row; i > row1; i--) {

			if (column <= column1) for (int j = column; j <= column1; j++) dataArray[i][j] = fill;
			if (column > column1) for (int j = column; j > column1; j--) dataArray[i][j] = fill;
		}
	}
}

void totals() {



}

void save() {

	fstream fileOutput;
	fileOutput.open(dataFileName);
	string rowRead;

	for (int i = 0; i < rowTotal; i++) {

		getline(fileOutput, rowRead);
		for (int j = 0; j < columnTotal; j++) {



		}

	}



}

void inputReader(string input) {

	string cmdType, target, param1, param2, data;
	int i = 0, cmdLength = input.length();

	while (input[i] != ' ' && i < cmdLength) cmdType += tolower(input[i]), i++; //Base command is loaded into cmdType

	if (i == input.length());
	else {
		while (i < cmdLength && input[i - 1] != '"') i++; //Moves forward to beginning of target
		while (i < cmdLength && input[i] != '"') target += input[i], i++; // Target name is loaded into target
		while (i < cmdLength && input[i - 1] != '[') i++; //Moves forward to beginning of first parameter
		while (i < cmdLength && input[i] != ']') target += input[i], i++; // first parameter is loaded into param1
		while (i < cmdLength && input[i - 1] != '[') i++; //Moves forward to beginning of second parameter
		while (i < cmdLength && input[i] != ']') target += input[i], i++; // second parameter is loaded into param2
		while (i < cmdLength && input[i - 1] != '{') i++; //Moves forward to data 
		while (i < cmdLength && input[i] != '}') data += input[i], i++; //loads data into data
	}

	cout << cmdType << endl << target << endl << param1 << endl << param2 << endl << data;

}

int main() {

	loadKeys();

	cout << R"(__| |______________________________________________________________________| |__
__   ______________________________________________________________________   __
  | |                                                                      | |  
  | |  ___                             _       _         ____ ______     __| |  
  | | / _ \ _ __   ___ _ __         __| | __ _| |_ __ _ / ___/ ___\ \   / /| |  
  | || | | | '_ \ / _ \ '_ \ _____ / _` |/ _` | __/ _` | |   \___ \\ \ / / | |  
  | || |_| | |_) |  __/ | | |_____| (_| | (_| | || (_| | |___ ___) |\ V /  | |  
  | | \___/| .__/ \___|_| |_|      \__,_|\__,_|\__\__,_|\____|____/  \_/   | |  
  | |      |_|                                                             | |  
__| |______________________________________________________________________| |__
__   ______________________________________________________________________   __
  | |                                                                      | |  

)";

	getline(cin, selection);
	inputReader(selection);

	if (selection == "") exit(0);
	else {
		selection += ".csv";
		dataFileName = selection;
		loadCharArray(dataFileName), printGrid(rowTotal, columnTotal);

		while (selection != "exit" || selection != "save") {

			cout << R"((Program Waiting))" << endl;

			cin >> selection;
			if (selection == "fill") dataFill();
			else if (selection == "edit") dataEditor();
			else if (selection == "totals") totals();
			printGrid(rowTotal, columnTotal);
		}
	}
}
