/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: NAVSEA Newport RI and MIT Cambridge MA               */
/*    FILE: main.cpp                                             */
/*    DATE: June 3rd, 2008                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s).                                      */
/*****************************************************************/

#include <string>
#include <cstdlib>
#include <iostream>
#include "MBUtils.h"
#include "GrepHandler.h"

using namespace std;

//--------------------------------------------------------
// Procedure: main

int main(int argc, char *argv[])
{
  // Look for a request for version information
  if(scanArgs(argc, argv, "-v", "--version", "-version")) {
    vector<string> svector = getReleaseInfo("aloggrep");
    for(unsigned int j=0; j<svector.size(); j++)
      cout << svector[j] << endl;    
    return(0);
  }
  
  bool verbose = true;
  if(scanArgs(argc, argv, "--verbose", "-verbose"))
    verbose = true;
  if(scanArgs(argc, argv, "--quiet", "-quiet", "-q"))
    verbose = false;
  
  bool file_overwrite = false;
  if(scanArgs(argc, argv, "-f", "--force", "-force"))
    file_overwrite = true;
  
  // Look for a request for usage information
  if(scanArgs(argc, argv, "-h", "--help", "-help")) {
    cout << "Usage: " << endl;
    cout << "  aloggrep in.alog [VAR] [SRC] [out.alog] [OPTIONS]        " << endl;
    cout << "                                                           " << endl;
    cout << "Synopsis:                                                  " << endl;
    cout << "  Create a new MOOS .alog file by retaining only the       " << endl;
    cout << "  given MOOS variables or sources from a given .alog file. " << endl;
    cout << "                                                           " << endl;
    cout << "Standard Arguments:                                        " << endl;
    cout << "  in.alog  - The input logfile.                            " << endl;
    cout << "  out.alog - The newly generated output logfile. If no     " << endl;
    cout << "             file provided, output goes to stdout.         " << endl;
    cout << "  VAR      - The name of a MOOS variable                   " << endl;
    cout << "  SRC      - The name of a MOOS process (source)           " << endl;
    cout << "                                                           " << endl;
    cout << "Options:                                                   " << endl;
    cout << "  -h,--help     Displays this help message                 " << endl;
    cout << "  -v,--version  Displays the current release version       " << endl;
    cout << "  -f,--force    Force overwrite of existing file           " << endl;
    cout << "  -q,--quiet    Verbose report suppressed at conclusion    " << endl;
    cout << "                                                           " << endl;
    cout << "Further Notes:                                             " << endl;
    cout << "  (1) The second alog is the output file. Otherwise the    " << endl;
    cout << "      order of arguments is irrelevent.                    " << endl;
    cout << "  (2) VAR* matches any MOOS variable starting with VAR     " << endl;
    cout << "  (3) See also: alogscan, alogrm, alogclip, alogview       " << endl;
    cout << endl;
    return(0);
  }

  vector<string> keys;
  string alogfile_in;
  string alogfile_out;

  for(int i=1; i<argc; i++) {
    string sarg = argv[i];
    if(strContains(sarg, ".alog")) {
      if(alogfile_in == "")
	alogfile_in = sarg;
      else 
	alogfile_out = sarg;
    }
    else
      keys.push_back(sarg);
  }
 
  if(alogfile_in == "") {
    cout << "No alog file given - exiting" << endl;
    exit(0);
  }
  else if(verbose)
    cout << "Processing on file : " << alogfile_in << endl;
  
  GrepHandler handler;
  handler.setFileOverWrite(file_overwrite);

  int ksize = keys.size();
  for(int i=0; i<ksize; i++)
    handler.addKey(keys[i]);

  bool handled = handler.handle(alogfile_in, alogfile_out);
  
  if(handled && verbose)
    handler.printReport();
}
