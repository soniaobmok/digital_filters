#include "FormMain.h"
//#include <iostream>
//#include <ctime>

//#include "fir.h"
//#include "kalman.h"
//#include "lms.h"


using namespace System;
using namespace System::Windows::Forms;
//using namespace std;
[STAThread]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	optimalfilters::FormMain form;
	Application::Run(%form);
}