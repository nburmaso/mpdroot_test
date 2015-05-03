//============================================================================
// Name        : function_set.h
// Author      : Konstantin Gertsenberger
// Copyright   : Konstantin Gertsenberger
// Description : set of common C++ functions
//============================================================================

// C++ includes
//#include "sys/wait.h"
//#include <pthread.h>
//#include <semaphore.h>
#include <unistd.h>
//#include "libxml/tree.h"
//#include <fstream>
#include <iostream>
//#include <vector>
#include <cstring>
#include <string>
//#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
//#include <algorithm>

using namespace std;

/*				*/
/* OS FUNCTIONS */
/*				*/

// execute system command in shell (bash)
int system_command_linux(string aCommand, string& result)
{
    FILE* f;
    if (!(f = popen(aCommand.c_str(), "r")))
    {
    	cout<<"system_command_linux error: popen failed"<<endl;
        return 1;
    }

    const int BUFSIZE = 4096;
    char buf[BUFSIZE];
    if (fgets(buf,BUFSIZE,f) != NULL)
    	result = buf;

    pclose(f);
    return 0;
}

// change tilda symbol on HOME in linux path
string replace_home_symbol_linux(string path)
{
    size_t np = path.find_first_of('~');
    if (np != string::npos)
    {
        bool isNewPath = false;
        char* pPath = getenv("HOME");
        if (pPath == NULL)
        {
            pPath = new char[2];
            pPath[0] = '/';
            pPath[1] = '\0';
            isNewPath = true;
        }

        do
        {
        	path.erase(np, 1);
        	path.insert(np, pPath);
            np = path.find_first_of('~');
        } while (np != string::npos);

        if (isNewPath)
            delete[] pPath;
    }

    return path;
}

// change $VMCWORKDIR symbol in linux path
string replace_vmc_path_linux(string path)
{
    char* pPath = getenv("VMCWORKDIR");
    bool isNewPath = false;
    if (pPath == NULL)
    {
        pPath = new char[2];
        pPath[0] = '/';
        pPath[1] = '\0';
        isNewPath = true;
    }

    size_t found;
    while ((found = path.find("$VMCWORKDIR")) != string::npos)
    {
        path.replace(found, 11, pPath);
    }

    if (isNewPath)
        delete[] pPath;

    return path;
}

// get processor core count on this machine
int get_linux_processor_count()
{
	return sysconf(_SC_NPROCESSORS_ONLN);
}

// get maximum available processor count on Sun Grid Engine system
int get_sge_processor_count()
{
	int proc_count = 0;

    const int MAX_BUFFER = 255;
    char buffer[MAX_BUFFER];

    // define count of processors for all.q queue
	string data, strDiff;
	FILE* stream = popen("export SGE_SINGLE_LINE=1; qconf -sq all.q | grep slots", "r");
    while (fgets(buffer, MAX_BUFFER, stream) != NULL)
        data.append(buffer);
	pclose(stream);

	size_t found = data.find("="), found2 = string::npos;
	while (found != string::npos)
	{
		found2 = data.find("]", found);
		strDiff = data.substr(found+1, found2 - found - 1);
		proc_count += atoi(strDiff.c_str());
		strDiff.clear();

		found = data.find("=", found2);
	}

	data.clear();

	cout<<"SGE processor count: "<<proc_count<<endl;

	return proc_count;
}

// get maximum available processor count on Torque batch system
int get_torque_processor_count()
{
	int proc_count = 0;

    const int MAX_BUFFER = 255;
    char buffer[MAX_BUFFER];

    // define count of processors for all.q queue
    string data, strDiff;
    FILE* stream = popen("qconf -sq all.q | grep slots", "r");
    while (fgets(buffer, MAX_BUFFER, stream) != NULL)
        data.append(buffer);
    pclose(stream);

    size_t found = data.find("="), found2 = string::npos;
    while (found != string::npos)
    {
        found2 = data.find("]", found);
        strDiff = data.substr(found+1, found2 - found - 1);
        proc_count += atoi(strDiff.c_str());
        strDiff.clear();

        found = data.find("=", found2);
    }

    data.clear();

    return proc_count;
}


/*								*/
/* GLOBAL APPLICATION FUNCTIONS */
/*								*/

// get application name in linux
string get_app_name_linux()
{
    pid_t procpid = getpid();
    stringstream toCom;
    toCom << "cat /proc/" << procpid << "/comm";
    string fRes="";
    system_command_linux(toCom.str(), fRes);
    size_t last_pos = fRes.find_last_not_of(" \n\r\t") + 1;
    if (last_pos != string::npos) {
        fRes.erase(last_pos);
    }
    return fRes;
}

// get aaplication directory (path without file name) in linux
string get_app_dir_linux()
{
    pid_t procpid = getpid();
    string appName = get_app_name_linux();
    stringstream command;
    command <<  "readlink /proc/" << procpid << "/exe | sed \"s/\\(\\/" << appName << "\\)$//\"";
    string fRes;
    system_command_linux(command.str(),fRes);

    // remove '\n' from end of the string and add final '/'
    fRes = fRes.erase(fRes.length()-1, 1);
    fRes.push_back('/');

    return fRes;
}


/*					*/
/* NUMBER FUNCTIONS */
/*					*/

// check bit in 'variable' at 'position'
#define CHECK_BIT(variable,position) ((variable) & (1ULL<<(position)))


/*					*/
/* STRING FUNCTIONS */
/*					*/

// convert integer number to string
string convert_integer_to_string(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}

// convert integer (hexadecimal value) to string with hexadecimal presentation without "0x"
string int_to_hex_string(int int_number)
{
  stringstream stream;
  stream << std::hex << int_number;
  return stream.str();
}

// is string a integer number?
bool is_string_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// convert array of chars to the new lowercase array
char* convert_pchar_to_lowercase_new(char* input_char_array)
{
	if (input_char_array == NULL)
		return NULL;

	const int length = strlen(input_char_array);	// get the length of the text
	char* lower = new char[length + 1];		// allocate 'length' bytes + 1 (for null terminator) and cast to char*
	lower[length] = 0;						// set the last byte to a null terminator

	// copy all character bytes to the new buffer using tolower
	for( int i = 0; i < length; i++ )
	{
	    lower[i] = tolower(input_char_array[i]);
	}

	return lower;
}

// replace string 's' by string 'd' in text
void replace_string_in_text(string &text, string s, string d)
{
	int start = -1;

	do
	{
		start = text.find(s, start + 1);
	    if(start > -1)
	    	text.replace(start, s.length(), d.c_str());
	}
	while(start > -1);
}


/*				  */
/* FILE FUNCTIONS */
/*				  */

// get file name without extension from a path
string get_file_name(string path)
{
	// Remove directory if present.
	size_t last_slash_idx = path.find_last_of("/");
	if (string::npos != last_slash_idx)
	    path.erase(0, last_slash_idx + 1);

	// Remove extension if present.
	size_t period_idx = path.rfind('.');
	if (std::string::npos != period_idx)
	    path.erase(period_idx);

	return path;
}

// get file name with extension from path
string get_file_name_with_ext(string path){
	// Remove directory if present.
	size_t last_slash_idx = path.find_last_of("/");
	if (string::npos != last_slash_idx)
	{
	    path.erase(0, last_slash_idx + 1);
	}

	return path;
}