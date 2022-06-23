/* This program sets up an Evolved Node B operating on nonstandard LTE frequency bands using srsENB as a part of srsRAN
   This program must be ran out of the /srsRAN/build directory to execute successfully
   The syntax for execution is as follows:
   ./reconfig_enb [dl_freq] [ul_freq] [bandwidth] (all parameters are entered in Hz)
   Supported bandwidths are 1.4 MHz, 3 MHz, 5 MHz, 10 MHz, 15 MHz, and 20 MHz. Invalid bandwidths will result in using a 10 MHz band. */

#include <iostream>
#include <string>

using namespace std;

string ctos(char*); //Converts character arrays to strings
string bwton_prb(int); //Converts LTE bandwidth to n_prb parameter in srsRAN

int main(int argc, char* argv[])
{
  const char* arg;
  string ul_freq;
  string dl_freq;
  string bw;
  string arg_str;
  string n_prb;
  int uli;
  int dli;
  int bwi;

  //Check for a valid input
  if(argc != 4)
  {
    cout << "Invalid arguments." << endl;
    return(1);
  }

  //Convert const char* from input arguments to strings
  dl_freq = ctos(argv[1]);
  ul_freq = ctos(argv[2]);
  ul_freq = ctos(argv[3]);

  //Store strings as separate integers for math
  uli = stoi(ul_freq);
  dli = stoi(dl_freq);
  bwi = stoi(bw);

  //Print requested parameters
  cout << "Setting dl_freq " << double(dli)/1000000.0 << " MHz | ul_freq " << double(uli)/1000000.0 << " MHz | BW " << double(bwi) / 1000000.0 << " MHz" << endl;

  //Convert the requested bandwidth to an n_prb value for enb.conf file
  n_prb = bwton_prb(bwi);

  //Form the command to be executed
  arg_str = "sudo srsenb --rf.ul_freq " + ul_freq + " --rf.dl_freq " + dl_freq + "--enb.n_prb " + n_prb;

  //Print the command to be executed
  cout << arg_str << endl;

  //Convert the command string into a const char* so it can be executed on the command line
  arg = arg_str.c_str();

  //Execute command
  system(arg);

  return 0;
}

string ctos(char* array)
{
  string out = "";

  //concatenate each char from array to form a string
  for(int i = 0; array[i] != '\0'; i++)
    out += array[i];

  return out;
}

string bwton_prb(int bandwidth)
{
  //convert input bandwidth to n_prb parameter to control operating bandwidth
  if(bandwidth == 1400000)
    return "6";
  else if(bandwidth == 3000000)
    return "15";
  else if(bandwidth == 5000000)
    return "25";
  else if(bandwidth == 10000000)
    return "50";
  else if(bandwidth == 15000000)
    return "75";
  else if(bandwidth == 20000000)
    return "100";
  //if invalid bandwidth is entered, return default n_prb = 50
  else
    return "50";
}
  
