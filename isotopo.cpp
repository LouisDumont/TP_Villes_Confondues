#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "point2d.h"
#include "town.h"
#include <map>


using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";


void namesRepDiag(vector<Town> towns){
    map<string,int> name_Repetitions;
    map<int,int> histo_Repetitions;
    for (vector<Town>::iterator it=towns.begin(); it != towns.end(); it++){
        Town currentTown = *it;
        map<string,int>::iterator search = name_Repetitions.find(currentTown.name());
        if (search == name_Repetitions.end()){
            name_Repetitions.insert(pair<string,int>(currentTown.name(),1));
        }
        else {
            name_Repetitions.at(currentTown.name())=(search->first,search->second +1);
        }
    }
    for (map<string,int>::iterator it=name_Repetitions.begin(); it != name_Repetitions.end(); it++){
        int nbRepet = it->second;
        map<int,int>::iterator search = histo_Repetitions.find(nbRepet);
        if (search == histo_Repetitions.end()){
            histo_Repetitions.insert(pair<int,int>(nbRepet,1));
        }
        else {
            histo_Repetitions.at(nbRepet) = (nbRepet,search->second +1);
        }
    }
    for (map<int,int>::iterator it=histo_Repetitions.begin(); it != histo_Repetitions.end(); it++){
        cout<<"Nombre de noms portés "<<it->first<<" fois:  "<<it->second<<endl;
    }
}


void posRepDiag(vector<Town> towns){
    map<pair<float,float>,int> pos_Repetitions;
    map<int,int> histo_Repetitions;
    for (vector<Town>::iterator it=towns.begin(); it != towns.end(); it++){
        Town currentPos= *it;
        float x = currentPos.x(); float y = currentPos.y();
        pair<float,float> pos(x,y);
        map<pair<float,float>,int>::iterator search = pos_Repetitions.find(pos);
        if (search == pos_Repetitions.end()){
            pos_Repetitions.insert(pair<pair<float,float>,int>(pos, 1));
        }
        else {
            pos_Repetitions.at(pos)=(search->first,search->second +1);
        }
    }
    for (map<pair<float,float>,int>::iterator it=pos_Repetitions.begin(); it != pos_Repetitions.end(); it++){
        int nbRepet = it->second;
        map<int,int>::iterator search = histo_Repetitions.find(nbRepet);
        if (search == histo_Repetitions.end()){
            histo_Repetitions.insert(pair<int,int>(nbRepet,1));
        }
        else {
            histo_Repetitions.at(nbRepet) = (nbRepet,search->second +1);
        }
    }
    for (map<int,int>::iterator it=histo_Repetitions.begin(); it != histo_Repetitions.end(); it++){
        cout<<"Nombre de positions couvrant "<<it->first<<" villes:  "<<it->second<<endl;
    }
}



/*
 * Study French isotoponyms
 */
int main()
{
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
	cout << "Error while reading file" << endl;
	return 2;
    }
    if (nb_towns == 0) {
	cout << "No town found" << endl;
	return 1;
    }
    namesRepDiag(towns);
    posRepDiag(towns);
    // Initialize random seed
    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
	 << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
	 << towns.size() /* same as nb_towns */ << endl;
    cout << "A random town, using format \"name[lat,lon](x,y)\": "
	 << towns[rand() % towns.size()] << endl;

    // That's all folks
    return 0;
}


