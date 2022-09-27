/**
 * @author Jane Student
 * @cwid   123 45 678
 * @class  CSci 530, Summer 2015
 * @ide    Visual Studio Express 2010
 * @date   June 8, 2015
 * @assg   prog-03
 *
 * @description This program implements a simulation of a page
 *    replacement system.  In this assignment, we simulate the
 *    implementation of the least recently used and the optimal page
 *    replacement decision policies.  The policy, and the size of
 *    memory (the number of physical frames) are provided to this
 *    simulation as command line parameters.
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// guarantee simulations have no more than this number of page references
const int MAX_PAGE_REFERENCES = 50;

/** optimal page replacement simulation
 *  Perform optimal (OPT) page replacement policy simulation.
 *
 * @arg framesize An int, the number of physical frames of memory to simulate.
 * @arg numref An int, the number of page references in the simulated page address
 *       stream.  There should be pagestream[0] to pagestream[numref-1]
 *       pages in the pagestream.
 * @arg pagestream An array of integers.  The value indicates a references
 *       page, and the index is the time when the page was referenced.
 */
void optimal(int framesize, int numref, int* pagestream) {
	// implement optimal page replacement here
	int page[framesize];
	float hit = 0;
	int filled = 0;
	int backup[numref];

	//keeping a copy of pages, for using it to check in replacement
	int i = 0;
	while (i < numref) {
		backup[i] = pagestream[i];
		i++;
	}

	//clear the page
	while (i < framesize) {
		page[i] = 0;
		i++;
	}

	//Process starts here
	i = 0;
	while (i < numref) {

		if (filled < framesize) {
			//There is still space available
			int j = 0;
			int isHit = 0;
			//first check if there is a hit
			while (j < framesize) {
				if (page[j] == pagestream[i]) {
					//Set there is a hit
					isHit = 1;
					++hit;
					break;
				}
				j++;
			}

			//If no hit replace an available slot with the current page
			if (isHit == 0) {
				j = 0;
				while (j < framesize) {
					if (page[j] == 0) {
						//Place the current page in available place
						page[j] = pagestream[i];
						++filled; //used to check if the page slots are filled, so that replacement can begin
						break;
					}
					j++;
				}
			}

		} else {

			int isHit = 0;
			//first check if there is a hit
			int j = 0;
			while (j < framesize) {
				if (page[j] == pagestream[i]) {
					//Set there is a hit
					isHit = 1;
					++hit;
					break;
				}
				j++;
			}

			//If not hit implement Optimal Policy
			if (isHit == 0) {
				//Find the least ill be used page
				int lIndex = -1;
				int pos = -1;
				j = 0;
				while (j < framesize) {
					int k = i;
					int found = 0;
					while (k < numref) {
						if (backup[k] == page[j]) {
							found = 1;
							if (pos < k) {
								lIndex = j;
								pos = k;
							}
							break;
						}

						++k;
					}

					if (found == 0) {
						lIndex = j;
						break;
					}

					++j;
				}

				page[lIndex] = pagestream[i];
			}

		}

		cout << "\n";
		cout << "Time: " << i << "\n";
		cout << "Page: " << pagestream[i] << "\n";
		int j = 0;
		while (j < framesize) {
			cout << "Frame" << (j + 1) << ":" << page[j] << "\n";
			++j;
		}
		cout << "Hit ratio: " << (int) hit << " / " << numref << " ("
				<< hit / numref << ")\n";

		++i;
	}

}

/** lru page replacement simulation
 *  Perform least recently used (LRU) page replace simulation.
 *
 * @arg framesize The number of physical frames of memory to simulate.
 * @arg numref The number of page references in the simulated page address
 *       stream.  There should be pagestream[0] to pagestream[numref-1]
 *       pages in the pagestream.
 * @arg pagestream An array of integers.  The value indicates a references
 *       page, and the index is the time when the page was referenced.
 */
void lru(int framesize, int numref, int* pagestream) {
	// implement lru (least recently used) page replacement here
	int page[framesize];
	float hit = 0;
	int filled = 0;
	int backup[numref];

	//keeping a copy of pages, for using it to check in replacement
	int i = 0;
	while (i < numref) {
		backup[i] = pagestream[i];
		i++;
	}

	//clear the page
	while (i < framesize) {
		page[i] = 0;
		i++;
	}

	//Process starts here
	i = 0;
	while (i < numref) {

		if (filled < framesize) {
			//There is still space available
			int j = 0;
			int isHit = 0;
			//first check if there is a hit
			while (j < framesize) {
				if (page[j] == pagestream[i]) {
					//Set there is a hit
					isHit = 1;
					++hit;
					break;
				}
				j++;
			}

			//If no hit replace an available slot with the current page
			if (isHit == 0) {
				j = 0;
				while (j < framesize) {
					if (page[j] == 0) {
						//Place the current page in available place
						page[j] = pagestream[i];
						++filled; //used to check if the page slots are filled, so that replacement can begin
						break;
					}
					j++;
				}
			}

		} else {

			int isHit = 0;
			//first check if there is a hit
			int j = 0;
			while (j < framesize) {
				if (page[j] == pagestream[i]) {
					//Set there is a hit
					isHit = 1;
					++hit;
					break;
				}
				j++;
			}

			//If not hit implement Optimal Policy
			if (isHit == 0) {
				//Find the least used t0 be replaced with current page
				//Find the least ill be used page
				int lIndex = numref;
				int pos = numref;
				j = 0;
				while (j < framesize) {
					int k = i-1;
					while (k > 0) {
						if (backup[k] == page[j]) {
							if (pos > k) {
								lIndex = j;
								pos = k;
							}
							break;
						}
						--k;
					}

					++j;
				}

				page[lIndex] = pagestream[i];

			}

		}

		cout << "\n";
		cout << "Time: " << i << "\n";
		cout << "Page: " << pagestream[i] << "\n";
		int j = 0;
		while (j < framesize) {
			cout << "Frame" << (j + 1) << ":" << page[j] << "\n";
			++j;
		}
		cout << "Hit ratio: " << (int) hit << " / " << numref << " ("
				<< hit / numref << ")\n";

		++i;
	}

}

/** Load page references from file
 *  Load the stream of simulated page references from the indicate file.
 *  return the references in a simple array of integers.
 *
 * @param simfilename  The name of the file to open and read page references
 *           from.
 * @param pagestream Should be a pointer to an array of integers.  The array
 *           is filled with the page references on return.  The index of each
 *           reference indicates time when the page references occurs in
 *           simulation.
 * @returns int The number of page references in the page stream.
 */
int loadPageStream(char* simfilename, int* pagestream) {
	ifstream pagestreamfile(simfilename);
	int pageref;
	int time;

	// If we can't open file, abort and let the user know problem
	if (!pagestreamfile.is_open()) {
		cout << "Error: could not open page simulation file: " << simfilename
				<< endl;
		exit(1);
	}

	// Load simulated page references into integer array
	time = 0;
	while (!pagestreamfile.eof()) {
		pagestreamfile >> pageref;
		pagestream[time] = pageref;
		time++;
		pagestreamfile >> ws;  // extract newlines from end of line
	}

	return time;
}

/** Main entry point of simulator
 *  The main entry point of the page replacement simulator.  Process 
 *  command line arguments and call appropriate simulation.  We expect
 *  three command line arguments: pageref.sim  [fifo|lru]  framesize
 *
 * @param argc The argument count
 * @param argv The command line argument values. We expect argv[1] to be the
 *              name of a file in the current directory holding page file
 *              references, argv[2] to indicate [fifo|lru] and argv[3] to be
 *              an integer indicating size of memory in frames.
 */
int main(int argc, char** argv) {
	int framesize = 0;
	int pagestream[MAX_PAGE_REFERENCES];
	int numref;
	string scheme;

	// If not all parameters not provided, abort and let user know of problem
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " pagestream.sim [lru|opt] framesize"
				<< endl;
		exit(1);
	}

	// load page stream and parse command line arguments
	numref = loadPageStream(argv[1], pagestream);
	scheme.assign(argv[2]);
	framesize = atoi(argv[3]);

	// perform simulation of indicated replacement scheme
	if (scheme == "lru") {
		lru(framesize, numref, pagestream);
	} else if (scheme == "opt") {
		optimal(framesize, numref, pagestream);
	} else {
		cout << "Error: unknown page replacement scheme: " << scheme << endl;
		exit(1);
	}
}
