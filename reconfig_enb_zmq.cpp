#include<iostream>
#include<string>

using namespace std;

string arraytostring(char*);
string bwton_prb(int);

int main(int argc, char* argv[])
{
  //declare variable for string and integer values of required uplink/downlink operating frequencies and bandwidth
  const char* enb_arg;
  string enb_arg_str;
  string n_prb;
  string ul;
  string dl;
  string bw;
  int ul_freq;
  int dl_freq;
  int bwi;

  //if there are not three arguments beyond executable file, return error
  if(argc != 4)
  {
    cout << "Invalid arguments" << endl;
    return(1);
  }

  //convert const char *'s to strings and then the strings to integers and save values
  ul = arraytostring(argv[2]);
  dl = arraytostring(argv[1]);
  bw = arraytostring(argv[3]);
  ul_freq = stoi(ul);
  dl_freq = stoi(dl);
  bwi = stoi(bw);

  //convert inputted bandwidth to n_prb parameter (required resource blocks)
  n_prb = bwton_prb(bwi);

  //output requested frequencies and bandwidths in MHz
  cout << "Setting dl_freq = " << double(dl_freq)/1000000.0 << " MHz | ul_freq = " << double(ul_freq)/1000000.0 << " MHz | BW = " << double(bwi)/1000000.0 << " MHz." <<  endl;

   //concatenate all strings to form srsenb command supporting zmq and nonstandard operating conditions
  enb_arg_str = "sudo ./srsenb/src/srsenb --rf.device_name=zmq --rf.device_args=\"fail_on_disconnect=true,tx_port=tcp://*:2000,rx_port=tcp://localhost:2001,id=enb,base_srate=23.04e6\" --rf.ul_freq " + ul + " --rf.dl_freq " + dl + " --enb.n_prb " + n_prb;

  //print what would've gone into the command line
  cout << enb_arg_str << endl;

  //convert the command line argument back to a const char * so it can be executed by the system
  enb_arg = enb_arg_str.c_str();

  //execute the command as a const char *
  system(enb_arg);

  return 0;
}

string arraytostring(char* array)
{
  //variable to track the length of each array as well as concatenate each char in array
  int len = 0;
  string conv = "";

  //concatenate each char in the array to form a string
  for(int i = 0; array[i] != '\0'; i++)
    conv += array[i];

  //return string
  return conv;
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
