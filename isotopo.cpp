#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "point2d.h"
#include "town.h"
#include <map>
#include <set>
#include <algorithm>


using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";


// Fonction renvoyant sous forme de texte l'histogramme des répétitions de noms de villes
map<int,int> namesRepDiag(vector<Town> towns){
    map<string,int> name_Repetitions; //stocke pour chaque nom de ville le nombre de répétitions
    map<int,int>   histo_Repetitions; //stocke l'histogramme
    // Un parcours de towns trouve pour chaque nom le nombre de villes le portant
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
    // Puis un parcours de name_Repetitions remplit l'histogramme
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
    // Affichage
    for (map<int,int>::iterator it=histo_Repetitions.begin(); it != histo_Repetitions.end(); it++){
        cout<<"Nombre de noms portés "<<it->first<<" fois:  "<<it->second<<endl;
    }
    return histo_Repetitions;
}

// Returns the set of all the towns which have an homonyme
set<Town> villes_homonymes(vector<Town> towns){
    map<string,int> name_Repetitions; //stocke pour chaque nom de ville le nombre de répétitions
    set<Town> homonymesSet; //stocke les villes avec homonymes
    // On génère la map des nbde répétitions de noms
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
    // Pour chaque ville on regarde si son nom est répété et on l'ajoute si oui
    for (vector<Town>::iterator it=towns.begin(); it != towns.end(); it++){
        Town current = *it;
        map<string,int>:: iterator search = name_Repetitions.find(current.name());
        if (search->second > 1){homonymesSet.insert(current);}
    }
    return homonymesSet;
}


map<int,int> posRepDiag(vector<Town> towns){
    map<pair<float,float>,int> pos_Repetitions; //stocke pour chaque position le nombre de villes
    map<int,int>             histo_Repetitions; //stocke l'histogramme
    // Un parcours de town permet de remplir pos_Repetitions
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
    // Puis un parcours de pos_Repetitions permet de remplir l'histogramme
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
    // Affichage
    for (map<int,int>::iterator it=histo_Repetitions.begin(); it != histo_Repetitions.end(); it++){
        cout<<"Nombre de positions couvrant "<<it->first<<" villes:  "<<it->second<<endl;
    }
    return histo_Repetitions;
}


// Returns the set of all the towns which have an neighbourg at the same position
set<Town> villes_MultipAtPos(vector<Town> towns){
    map<pair<float,float>,int> pos_Repetitions; //stocke pour chaque pos de villes le nombre de répétitions
    set<Town> ResultSet; //stocke les villes avec homonymes
    // On génère la map des nb de répétition de chaque pos
    for (vector<Town>::iterator it=towns.begin(); it != towns.end(); it++){
        Town currentTown = *it;
        pair<float,float> pos(currentTown.x(),currentTown.y());
        map<pair<float,float>,int>::iterator search = pos_Repetitions.find(pos);
        if (search == pos_Repetitions.end()){
            pos_Repetitions.insert(pair<pair<float,float>,int>(pos,1));
        }
        else {
            pos_Repetitions.at(pos)=(search->second +1);
        }
    }
    // On ajoute chaque ville ssi sa position est répétée
    for (vector<Town>::iterator it=towns.begin(); it != towns.end(); it++){
        Town current = *it; pair<float,float> pos(current.x(),current.y());
        map<pair<float,float>,int>:: iterator search = pos_Repetitions.find(pos);
        if (search->second > 1){ResultSet.insert(current);}
    }
    return ResultSet;
}


// Calcule toutes les situations trompeuses (Questions 4)
set<Town> getPieges(vector<Town> towns){
    // Creating all the usefull data sets
    set<Town> pieges; //Stocking the solutions
    set<Town> villesNomMulti = villes_homonymes(towns);
    set<Town> villesPosMulti = villes_MultipAtPos(towns);
    vector<Town> intersection(min(villesNomMulti.size(),villesPosMulti.size()));
    vector<Town>::iterator inter =
            set_intersection(villesNomMulti.begin(), villesNomMulti.end(),
                             villesPosMulti.begin(), villesPosMulti.end(),
                             intersection.begin());
    intersection.resize(inter - intersection.begin());
    // We have now discarded all the unusefull towns
    // We examinate all the cities of inter at same pos
    for (vector<Town>::iterator it=intersection.begin(); it!=intersection.end(); it++){
        for(vector<Town>::iterator that=it+1; that!=intersection.end(); that++){
            if (((*it).x() == (*that).x()) && ((*it).y() == (*that).y())){
                // When we find two such cities, we look for to others at same pos, with corresponding names
                for (vector<Town>::iterator s1= it+1; s1!=intersection.end(); s1++){
                    for(vector<Town>::iterator s2= that+1; s2!=intersection.end(); s2++){
                        bool cond1= (*s1).name() == (*it).name();
                        bool cond2= (*s2).name() == (*that).name();
                        bool condPos= ((*s1).x() == (*s2).x()) && ((*s1).y() == (*s2).y());
                        if((cond1 && cond2) && condPos){
                            pieges.insert(*it); pieges.insert(*that);
                            pieges.insert(*s1); pieges.insert(*s2);
                        }
                    }
                }
            }
        }
    }
    return pieges;
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

    // Test des histogrammes (questions 1 et 2)
    map<int,int> question1 = namesRepDiag(towns);
    map<int,int> question2 = posRepDiag(towns);

    // Calcul de N, C, et de leur intersection
    set<Town> homonymesSet = villes_homonymes(towns);
    set<Town> multiAtPosSet= villes_MultipAtPos(towns);
    vector<Town> intersection(min(homonymesSet.size(),multiAtPosSet.size()));
    vector<Town>::iterator inter =
            set_intersection(homonymesSet.begin(),homonymesSet.end(),
                             multiAtPosSet.begin(), multiAtPosSet.end(),
                             intersection.begin());
    intersection.resize(inter - intersection.begin());
    int interSize=0;
    for (vector<Town>::iterator it=intersection.begin(); it != intersection.end(); it++){
        interSize += 1;
        cout<<*it<<endl;
    }
    cout<<"L'intersection de N et C contient "<<interSize<<" elements"<<endl;

    // Question 4 et affichage de son résultat
    set<Town> P = getPieges(towns);
    int comptePieges=0;
    for (set<Town>::iterator it=P.begin(); it!=P.end(); it++){
        comptePieges += 1;
        cout<<*it<<endl;
    }
    cout<<"Nombre de villes dont l'association est piegeuse: "<<comptePieges<<endl;

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


