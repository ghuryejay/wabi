# wabi

It uses Networkit Library. Download it from here: https://networkit.iti.kit.edu/

Extract zip file to /usr/include. cd into NetworKit-2742bfba9724. To build the library, execute following command:

scons --optimize=Opt --target=Lib

After this is done, build using makefile.

VC_algo requires 2 parameters from command line viz., path to gml file and filtering number for centrality. 
Run it as follows:
./vc_algo path_to_gml filtering_number

Samling algo requires 3 parameters viz. path to gml, filtering number and number of sample nodes.
Run it as follows:
./sampling_algo path_to_gml filtering_nubmer no_of_samples

Output produced by both is a .repeats file. It has information in following form:

node_id, centrality_value, label_of_repeat
