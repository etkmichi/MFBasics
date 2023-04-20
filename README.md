# MFBasics
Library which provides some basic and convenient functions for developing.

To build the library (For a release build, replace "Debug" with "Release" in the last line):
```
   git clone https://github.com/etkmichi/MFBasics.git
   cd MFBasics
   chmod +x build_script.sh
   ./build_script.sh Debug
```
Library can be found in dir MFBasics/Debug or MFBasics/Release!


MFToString:

   * Different functions for converting numbers (f.e. timestamps,vectors) to formated strings

MFBasicDefines:

   * Print function for infos, errors and warnings formated like this: 


    ClassName:LineNumber function name - print string
   * Easy access to some toString functions f.e. P_NUM(x) where x can be a number or vector.

Multithreading:
   * MFAbstractTask provides different time stamps for monitoring and abstract execution function.

   * MFTaskThread class which executes tasks which need to be a subclass of MFAbstractTask. Supports some extra functionality like pause time between task execution, one-shot or repeatable tasks and some more

Data:

   *  MFDataObject provides meta configuration for data. f.e. Data can be wrapped by this class for easy monitoring with GUI

Printers:
   * MFPrintTargets can be implemented and added to the static print system to provide a custom print interface f.e. a separated GUI with file links and string filter.
   * A static object of the MFPrinterface class (MFObject::pPrinter)can be used to add other print targets or overwrite the console printer

Time:

   * MFTickCounter provides static functions for time measurement and can be instanced to get some additional time measurement functionalities
   * some helper functions to get current time and convert time to string
