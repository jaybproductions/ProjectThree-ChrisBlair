#define NOMINMAX
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None 
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//display a menu to select from 
void displayMenu() {
	cout << "Welcome to the Grocery Program!" << endl;
	cout << "1. See the number of times each item appears." << endl;
	cout << "2. Search for an item." << endl;
	cout << "3. Display a histogram of the data." << endl;
	cout << "4. Exit Program" << endl;
}

// get the selection from the user
int handleSelection() {
	int num; 
	cin >> num;
	// input validation loop
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid selection...";
		cin >> num;
	}
	return num;
}

// function for creating the histogram to display
void createHistogram() {
	// initialize variables
	ifstream fileInput;
	string itemName;
	int itemCount;
	// clear the screen so the histogram shows at the top
	system("CLS");

	// use python to create the file 
	CallProcedure("CreateDatFile");

	// open the file 
	fileInput.open("frequency.dat");

	// get the first line
	fileInput >> itemName;
	fileInput >> itemCount;

	// while we haven't reached the end of the file
	while (!fileInput.fail()) {

		// display the item name 
		cout << setw(14) << left << itemName << setw(6);

		// loop through the number of items and display asterik
		for (int i = 0; i < itemCount; i++) {
			cout << right << "*";
		}

		// end line
		cout << endl;
		// get next line for next loop
		fileInput >> itemName;
		fileInput >> itemCount;
	}

	// close the file
	fileInput.close();
	// end the line
	cout << endl;


}

void handleProcessSelection(int selection) {
	string searchTerm; 
	switch (selection) {
		// option 1 is to get the item frequency for all items
		case 1:
			system("CLS");
			CallProcedure("ItemFreq");
			break;
		// option 2 is to search for an item and get the count
		case 2:
			cout << "Please enter an item to search for:" << endl;
			cin >> searchTerm;
			system("CLS");
			cout << "There are a total of " << callIntFunc("CountItemFreq", searchTerm) << " " << searchTerm << endl;
			break;
		// option 2 creates a histogram of the file data
		case 3:
			createHistogram();
			break;
		// option 4 is to exit the program
		case 4:
			cout << "Exiting Program..." << endl;
			exit(0);
			break;
		default:
			cout << "We do not recognize this command..." << endl;
	}

}



void main()
{
	bool running = true; 
	// main program loop

	while (running) {
		displayMenu();
		int selection = handleSelection();
		handleProcessSelection(selection);
	}
	
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);

}