#include "Processor.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Usage: " << "./simExec [config file]" << endl;
		return 0;
	}
	string configFile = argv[1];
	Processor sim(configFile);
	//cout<<"run??"<<endl;
	sim.run();

	return 0;
}
