#include <vector> 
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h>
#include <array>
#include <limits.h> 
#include <algorithm>
#include <set>
#include <utility>

using namespace std; 

		// for (std::vector<string>::const_iterator i = tokens3.begin(); i != tokens3.end(); ++i)
	 //   		cout << *i << endl;


pair<pair<vector<int>, int>, pair<vector<int>, int>> dijkstraStartKey(vector<vector<pair<int,int>>> connectionGraph,
    										vector<vector<int>> lockedRooms,
    										int roomCount,
    										int startingRoom,
    										int startingTime,
    										int startingAmmo,
    										int keyofScientistRoomNo,
    										int scientistRoomNo,
    										int chamberRoomNo,
    										int targetRoom){

	vector<vector<int>> dist(2, vector<int>(roomCount+1,1));
	vector<vector<bool>> visited(2, vector<bool>(roomCount+1));
	vector<vector<vector<int>>> parent(2, vector<vector<int>>(roomCount+1));
	for(int i=1; i<roomCount+1; i++){
		visited[0][i] = 0;
		visited[1][i] = 0;
		dist[0][i] = INT_MAX;
		dist[1][i] = INT_MAX;
	}

	dist[0][startingRoom] = 0;
	dist[1][startingRoom] = 0;
	parent[0][startingRoom].push_back(-1);
	parent[1][startingRoom].push_back(-1);
    multiset < pair < int , pair<int,bool> > > s;

    s.insert({0 , {startingRoom,startingTime}});  

    while(!s.empty()){

        pair < int , pair<int,bool> > p = *s.begin();
        s.erase(s.begin());

        int x = p.second.first;
        int wei = p.first;
        bool time = p.second.second;
        bool nexttime = !time;
        if( visited[time][x] ) continue;
        visited[time][x] = true;

        for(int i = 0; i < connectionGraph[x].size(); i++){
        	int e = connectionGraph[x][i].first;
            int w = connectionGraph[x][i].second;
            bool doorisLocked = false;

        	for(int j = 0; j < (lockedRooms[nexttime]).size(); j++){
        		if(lockedRooms[nexttime][j] == e){
        			doorisLocked = true;
        		}
        	}

        	if(e == scientistRoomNo){
        		continue;
        	}

        	if(e == chamberRoomNo){
        		continue;
        	}

        	if(doorisLocked){
        		continue;
        	}

            if((dist[time][x] + w < dist[nexttime][e]) && (startingAmmo - dist[time][x] >= w )){
                dist[nexttime][e] = dist[time][x] + w;
                s.insert({dist[nexttime][e], {e , nexttime}});
                parent[nexttime][e].push_back(x);
            }
        }
	}

	// cout << parent[0][3].size() << endl;
	// cout << parent[1][3].back() << endl;
	// cout << parent[0][5].back() << endl;
	// cout << parent[1][4].back() << endl;
	// cout << parent[0][3].back() << endl;
	// cout << parent[1][1].back() << endl;
	vector<vector<vector<int>>> parent2 = parent;

	// cout << "anan " << endl;

	int oddf = targetRoom;
	int evenf = targetRoom;
	vector<int> evenpath;
	vector<int> oddpath;
	bool evencurrent = 0;
	bool oddcurrent = 1;
	int evencost = dist[0][targetRoom];
	int oddcost = dist[1][targetRoom];
	// cout << "koylu " << endl;
	if(evencost != INT_MAX){
		while(evenf != -1){
			evenpath.push_back(evenf);
			// cout << "gecemedim " << endl;
			int newevenf = parent[evencurrent][evenf].back();
			// cout << "gectim " << endl;
			parent[evencurrent][evenf].pop_back();
			evencurrent = !evencurrent;
			evenf = newevenf;
		}
	}
	// cout << "even bitti " << endl;
	// cout << evenpath[0]<<evenpath[1] << endl;

	if(oddcost != INT_MAX){
		while(oddf != -1){
			oddpath.push_back(oddf);
			// cout << "gectim2 " << endl;
			int newoddf = parent2[oddcurrent][oddf].back();
			// cout << "gecemedim2 " << endl;
			parent2[oddcurrent][oddf].pop_back();
			oddcurrent = !oddcurrent;
			oddf = newoddf;
		}
	}

	// cout << "baban " << endl;
	// cout << evenpath.size() << endl;
	// cout << oddpath.size() << endl;

	pair<vector<int>,int> evenpair;
	pair<vector<int>,int> oddpair;
	if(evencost != INT_MAX){
		evenpair = {evenpath,evencost};
	}
	else{
		evenpair = {{},INT_MAX};
	}
	if(oddcost != INT_MAX){
		oddpair = {oddpath,oddcost};
	}
	else{
		oddpair = {{},INT_MAX};
	}

	// cout << evenpair.first.empty() << endl;
	// cout << oddpair.first.empty() << endl;
	return make_pair(evenpair,oddpair);

}


pair<pair<vector<int>, int>, pair<vector<int>, int>> dijkstraKeyScientist(vector<vector<pair<int,int>>> connectionGraph,
    										vector<vector<int>> lockedRooms,
    										int roomCount,
    										int startingRoom,
    										int startingTime,
    										int startingAmmo,
    										int keyofScientistRoomNo,
    										int scientistRoomNo,
    										int chamberRoomNo,
    										int targetRoom){

	vector<vector<int>> dist(2, vector<int>(roomCount+1,1));
	vector<vector<bool>> visited(2, vector<bool>(roomCount+1));
	vector<vector<vector<int>>> parent(2, vector<vector<int>>(roomCount+1));
	for(int i=1; i<roomCount+1; i++){
		visited[0][i] = 0;
		visited[1][i] = 0;
		dist[0][i] = INT_MAX;
		dist[1][i] = INT_MAX;
	}

	dist[0][startingRoom] = 0;
	dist[1][startingRoom] = 0;
	parent[0][startingRoom].push_back(-1);
	parent[1][startingRoom].push_back(-1);
    multiset < pair < int , pair<int,bool> > > s;

    s.insert({0 , {startingRoom,startingTime}});  

    while(!s.empty()){

        pair < int , pair<int,bool> > p = *s.begin();
        s.erase(s.begin());

        int x = p.second.first;
        int wei = p.first;
        bool time = p.second.second;
        bool nexttime = !time;
        if( visited[time][x] ) continue;
        visited[time][x] = true;

        for(int i = 0; i < connectionGraph[x].size(); i++){
        	int e = connectionGraph[x][i].first;
            int w = connectionGraph[x][i].second;
            bool doorisLocked = false;

        	for(int j = 0; j < (lockedRooms[nexttime]).size(); j++){
        		if(lockedRooms[nexttime][j] == e){
        			doorisLocked = true;
        		}
        	}

        	if(e == chamberRoomNo){
        		continue;
        	}

        	if(doorisLocked){
        		continue;
        	}

            if((dist[time][x] + w < dist[nexttime][e]) && (startingAmmo - dist[time][x] >= w )){
                dist[nexttime][e] = dist[time][x] + w;
                s.insert({dist[nexttime][e], {e , nexttime}});
                parent[nexttime][e].push_back(x);
            }
        }
	}

	// cout << parent[0][3].size() << endl;
	// cout << parent[1][3].back() << endl;
	// cout << parent[0][5].back() << endl;
	// cout << parent[1][4].back() << endl;
	// cout << parent[0][3].back() << endl;
	// cout << parent[1][1].back() << endl;
	vector<vector<vector<int>>> parent2 = parent;

	// cout << "anan " << endl;

	int oddf = targetRoom;
	int evenf = targetRoom;
	vector<int> evenpath;
	vector<int> oddpath;
	bool evencurrent = 0;
	bool oddcurrent = 1;
	int evencost = dist[0][targetRoom];
	int oddcost = dist[1][targetRoom];
	// cout << "koylu " << endl;
	if(evencost != INT_MAX){
		while(evenf != -1){
			evenpath.push_back(evenf);
			// cout << "gecemedim " << endl;
			int newevenf = parent[evencurrent][evenf].back();
			// cout << "gectim " << endl;
			parent[evencurrent][evenf].pop_back();
			evencurrent = !evencurrent;
			evenf = newevenf;
		}
	}
	// cout << "even bitti " << endl;
	// cout << evenpath[0]<<evenpath[1] << endl;

	if(oddcost != INT_MAX){
		while(oddf != -1){
			oddpath.push_back(oddf);
			// cout << "gectim2 " << endl;
			int newoddf = parent2[oddcurrent][oddf].back();
			// cout << "gecemedim2 " << endl;
			parent2[oddcurrent][oddf].pop_back();
			oddcurrent = !oddcurrent;
			oddf = newoddf;
		}
	}

	// cout << "baban " << endl;
	// cout << evenpath.size() << endl;
	// cout << oddpath.size() << endl;

	pair<vector<int>,int> evenpair;
	pair<vector<int>,int> oddpair;
	if(evencost != INT_MAX){
		evenpair = {evenpath,evencost};
	}
	else{
		evenpair = {{},INT_MAX};
	}
	if(oddcost != INT_MAX){
		oddpair = {oddpath,oddcost};
	}
	else{
		oddpair = {{},INT_MAX};
	}

	// cout << evenpair.first.empty() << endl;
	// cout << oddpair.first.empty() << endl;
	return make_pair(evenpair,oddpair);

}


pair<pair<vector<int>, int>, pair<vector<int>, int>> dijkstraScientistBoss(vector<vector<pair<int,int>>> connectionGraph,
    										vector<vector<int>> lockedRooms,
    										int roomCount,
    										int startingRoom,
    										int startingTime,
    										int startingAmmo,
    										int keyofScientistRoomNo,
    										int scientistRoomNo,
    										int chamberRoomNo,
    										int targetRoom){

	vector<vector<int>> dist(2, vector<int>(roomCount+1,1));
	vector<vector<bool>> visited(2, vector<bool>(roomCount+1));
	vector<vector<vector<int>>> parent(2, vector<vector<int>>(roomCount+1));
	for(int i=1; i<roomCount+1; i++){
		visited[0][i] = 0;
		visited[1][i] = 0;
		dist[0][i] = INT_MAX;
		dist[1][i] = INT_MAX;
	}

	dist[0][startingRoom] = 0;
	dist[1][startingRoom] = 0;
	parent[0][startingRoom].push_back(-1);
	parent[1][startingRoom].push_back(-1);
    multiset < pair < int , pair<int,bool> > > s;

    s.insert({0 , {startingRoom,startingTime}});  

    while(!s.empty()){

        pair < int , pair<int,bool> > p = *s.begin();
        s.erase(s.begin());

        int x = p.second.first;
        int wei = p.first;
        bool time = p.second.second;
        bool nexttime = !time;
        if( visited[time][x] ) continue;
        visited[time][x] = true;

        for(int i = 0; i < connectionGraph[x].size(); i++){
        	int e = connectionGraph[x][i].first;
            int w = connectionGraph[x][i].second;
            bool doorisLocked = false;

        	for(int j = 0; j < (lockedRooms[nexttime]).size(); j++){
        		if(lockedRooms[nexttime][j] == e){
        			doorisLocked = true;
        		}
        	}

        	if(doorisLocked){
        		continue;
        	}

            if((dist[time][x] + w < dist[nexttime][e]) && (startingAmmo - dist[time][x] >= w )){
                dist[nexttime][e] = dist[time][x] + w;
                s.insert({dist[nexttime][e], {e , nexttime}});
                parent[nexttime][e].push_back(x);
            }
        }
	}

	// cout << parent[0][3].size() << endl;
	// cout << parent[1][3].back() << endl;
	// cout << parent[0][5].back() << endl;
	// cout << parent[1][4].back() << endl;
	// cout << parent[0][3].back() << endl;
	// cout << parent[1][1].back() << endl;
	vector<vector<vector<int>>> parent2 = parent;

	// cout << "anan " << endl;

	int oddf = targetRoom;
	int evenf = targetRoom;
	vector<int> evenpath;
	vector<int> oddpath;
	bool evencurrent = 0;
	bool oddcurrent = 1;
	int evencost = dist[0][targetRoom];
	int oddcost = dist[1][targetRoom];
	// cout << "koylu " << endl;
	if(evencost != INT_MAX){
		while(evenf != -1){
			evenpath.push_back(evenf);
			// cout << "gecemedim " << endl;
			int newevenf = parent[evencurrent][evenf].back();
			// cout << "gectim " << endl;
			parent[evencurrent][evenf].pop_back();
			evencurrent = !evencurrent;
			evenf = newevenf;
		}
	}
	// cout << "even bitti " << endl;
	// cout << evenpath[0]<<evenpath[1] << endl;

	if(oddcost != INT_MAX){
		while(oddf != -1){
			oddpath.push_back(oddf);
			// cout << "gectim2 " << endl;
			int newoddf = parent2[oddcurrent][oddf].back();
			// cout << "gecemedim2 " << endl;
			parent2[oddcurrent][oddf].pop_back();
			oddcurrent = !oddcurrent;
			oddf = newoddf;
		}
	}

	// cout << "baban " << endl;
	// cout << evenpath.size() << endl;
	// cout << oddpath.size() << endl;

	pair<vector<int>,int> evenpair;
	pair<vector<int>,int> oddpair;
	if(evencost != INT_MAX){
		evenpair = {evenpath,evencost};
	}
	else{
		evenpair = {{},INT_MAX};
	}
	if(oddcost != INT_MAX){
		oddpair = {oddpath,oddcost};
	}
	else{
		oddpair = {{},INT_MAX};
	}

	// cout << evenpair.first.empty() << endl;
	// cout << oddpair.first.empty() << endl;
	return make_pair(evenpair,oddpair);

}





int main(){

	vector<int> bestpath;
	int bestleftammo;
	vector<pair<vector<int>,int>> bestofthebests(2);

	string::size_type sz;
	char* strval;



	string fileName = "the3.inp";
	vector<string> vecOfStr;
	vector<int> oddPeriodLocks;
	vector<int> evenPeriodLocks;
	ifstream in(fileName.c_str());
	std::string str;

	while (std::getline(in, str))
	{

		if(str.size() > 0)
			vecOfStr.push_back(str);
	}

	in.close();



	int startingAmmo = stoi (vecOfStr[0], &sz);
	int roomCount = stoi (vecOfStr[1], &sz);
	int chamberRoomNo = stoi (vecOfStr[2], &sz);
	int keyofScientistRoomNo = stoi (vecOfStr[3], &sz);
	int scientistRoomNo = stoi (vecOfStr[4], &sz);

	// cout << "basladim" << endl;
	
	istringstream split(vecOfStr[5]);
	vector<string> tokens;
	for (string each; getline(split, each, ' '); tokens.push_back(each));
	int oddPeriodLockedRoomCount = stoi (tokens[0], &sz);
	for(int i = 0; i<oddPeriodLockedRoomCount; i++){
		oddPeriodLocks.push_back(stoi(tokens[i+1], &sz));
	}

	
	// cout << "okuyorum" << endl;

	istringstream split2(vecOfStr[6]);
	vector<string> tokens2;
	for (string each; getline(split2, each, ' '); tokens2.push_back(each));
	int evenPeriodLockedRoomCount = stoi (tokens2[0], &sz);
	for(int i = 0; i<evenPeriodLockedRoomCount; i++){
		evenPeriodLocks.push_back(stoi(tokens2[i+1], &sz));
	}

	

	vector < vector< int > > lockedRooms(2);
	lockedRooms[0] = evenPeriodLocks;
	lockedRooms[1] = oddPeriodLocks;

	int corridorCount = stoi (vecOfStr[7], &sz);

	// cout << "corridorCount = " << corridorCount << endl;

	vector < vector < pair < int, int > > > connectionGraph(roomCount+1);

	// cout << roomCount << endl;

	for(int i=0; i < corridorCount; i++){
		istringstream split3(vecOfStr[8+i]);
		vector<string> tokens3;
		for (string element; getline(split3, element, ' '); tokens3.push_back(element));

		// for (std::vector<string>::const_iterator i = tokens3.begin(); i != tokens3.end(); ++i)
	 //   		cout << *i << endl;

		pair <int,int> pair1toPush = {stoi(tokens3[1], &sz), stoi(tokens3[2], &sz)};
		pair <int,int> pair2toPush = {stoi(tokens3[0], &sz), stoi(tokens3[2], &sz)};

		// cout << "pairlari olusturdum" << endl;
		// cout << stoi(tokens3[0], &sz) << endl;
		// cout << stoi(tokens3[1], &sz) << endl;
		// cout << roomCount << endl;

		connectionGraph[stoi(tokens3[0], &sz)].push_back(pair1toPush);
		connectionGraph[stoi(tokens3[1], &sz)].push_back(pair2toPush);

		// cout << i << "<- i bu"<< endl;

		//burda komsu odalari ve uzakliklari okudum
	}

	// cout << connectionGraph.size() << endl;

	// for(int k = 1; k < connectionGraph.size(); k++){
	// 	for (vector < pair < int , int > >::const_iterator i = connectionGraph[k].begin(); i != connectionGraph[k].end(); ++i){
	// 		cout << i -> first << endl;
	// 		cout << i -> second << endl;
	// 	}
	// }

	// cout << vecOfStr.size() << endl;

	int ammoRoomCount = stoi(vecOfStr[8+corridorCount], &sz);

	vector < pair < int , int > > ammoRoomsGraph;
	vector < pair < int , int > > ammoRoomsGraphStable;

	for(int i=0; i<ammoRoomCount; i++){

		istringstream split4(vecOfStr[9+corridorCount+i]);
		vector<string> tokens4;
		for (string element; getline(split4, element, ' '); tokens4.push_back(element));

		pair <int,int> pairtoPush = {stoi(tokens4[0], &sz), stoi(tokens4[1], &sz)};

		ammoRoomsGraph.push_back(pairtoPush);

		//burda ammo odalarini ve ammo miktarini okudum

	}

	for(int i=0; i<ammoRoomsGraph.size(); i++){
		ammoRoomsGraphStable.push_back(ammoRoomsGraph[i]);
	}

	// for (vector < pair < int , int > >::const_iterator i = ammoRoomsGraph.begin(); i != ammoRoomsGraph.end(); ++i){
		// 	cout << i -> first << endl;
		// 	cout << i -> second << endl;
		// }

	// cout << startingAmmo << endl;
	// cout << ammoRoomCount << endl;
	// cout << ammoRoomsGraph[0].first << endl;
	// cout << ammoRoomsGraph[0].second << endl;


	if(ammoRoomCount == 0) {
		// cout << "okudummermisizegirdim" << endl;


	pair<pair<vector<int>, int>, pair<vector<int>, int>> a = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);
	int evencost0 = a.first.second;
	int x0 = startingAmmo - evencost0;
	if(x0 < 0){
		x0 = 0;
	}
	int oddcost0 = a.second.second;
	int y0 = startingAmmo - oddcost0;
	if(y0 < 0){
		y0 = 0;
	}

	// cout << "xo " << x0 << endl;
	// cout << "yo " << y0 << endl;

	// cout << a.second.first.size() << endl;
	// cout << a.first.first[0] << endl;
	// cout << a.first.first[1] << endl;

	pair<pair<vector<int>, int>, pair<vector<int>, int>> b0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);

	pair<pair<vector<int>, int>, pair<vector<int>, int>> b1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);


	int evencost1 = b0.first.second;
	int x1 = x0 - evencost1;
	if(x1 < 0){
		x1 = 0;
	}
	int oddcost1 = b0.second.second;
	int y1 = x0 - oddcost1;
	if(y1 < 0){
		y1 = 0;
	}

	int evencost2 = b1.first.second;
	int x2 = y0 - evencost2;
	if(x2 < 0){
		x2 = 0;
	}
	int oddcost2 = b1.second.second;
	int y2 = y0 - oddcost2;
	if(y2 < 0){
		y2 = 0;
	}

	// cout << "x1 " << x1 << endl;
	// cout << "y1 " << y1 << endl;

	// cout << "x2 " << x2 << endl;
	// cout << "y2 " << y2 << endl;


	pair<pair<vector<int>, int>, pair<vector<int>, int>> c0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x1, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, chamberRoomNo);

	pair<pair<vector<int>, int>, pair<vector<int>, int>> c1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y1, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, chamberRoomNo);

	pair<pair<vector<int>, int>, pair<vector<int>, int>> c2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x2, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, chamberRoomNo);

	pair<pair<vector<int>, int>, pair<vector<int>, int>> c3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y2, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, chamberRoomNo);


	int evencost3 = c0.first.second;
	int x3 = x1 - evencost3;

	int oddcost3 = c0.second.second;
	int y3 = x1 - oddcost3;


	int evencost4 = c1.first.second;
	int x4 = y1 - evencost4;

	int oddcost4 = c1.second.second;
	int y4 = y1 - oddcost4;


	int evencost5 = c2.first.second;
	int x5 = x2 - evencost5;

	int oddcost5 = c2.second.second;
	int y5 = x2 - oddcost5;


	int evencost6 = c3.first.second;
	int x6 = y2 - evencost6;

	int oddcost6 = c3.second.second;
	int y6 = y2 - oddcost6;


	vector<int> leftammos;
	leftammos.push_back(x3);
	leftammos.push_back(y3);
	leftammos.push_back(x4);
	leftammos.push_back(y4);
	leftammos.push_back(x5);
	leftammos.push_back(y5);
	leftammos.push_back(x6);
	leftammos.push_back(y6);

	int pickedindex = 0;
	int pickedammocount = x3;
	for(int i = 0; i < 8; i++){
		if(leftammos[i] > pickedammocount && leftammos[i] >= 0){
			pickedindex = i;
			pickedammocount = leftammos[i];
		}
	}

	// cout << "path patterni " << pickedindex << endl;
	// cout << leftammos[pickedindex] << endl;

	bool thirdstep = pickedindex % 2;
	bool secondstep = int(pickedindex/2) % 2;
	bool firststep = int(pickedindex/4);

	pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);


	pair<vector<int>, int> firstpathandcost;
	int firstleftammo;
	
	if(firststep == 0){
		firstpathandcost = af.first;
		firstleftammo = startingAmmo - firstpathandcost.second;
		if(firstleftammo < 0){
			firstleftammo = 0;
		}
	}

	else{
		firstpathandcost = af.second;
		firstleftammo = startingAmmo - firstpathandcost.second;
		if(firstleftammo < 0){
			firstleftammo = 0;
		}
	}

	// cout << firstpathandcost.second << endl;
	// cout << firstleftammo << endl;

	pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);


	pair<vector<int>, int> secondpathandcost;
	int secondleftammo;
	
	if(secondstep == 0){
		secondpathandcost = bf.first;
		secondleftammo = firstleftammo - secondpathandcost.second;
		if(secondleftammo < 0){
			secondleftammo = 0;
		}
	}

	else{
		secondpathandcost = bf.second;
		secondleftammo = firstleftammo - secondpathandcost.second;
		if(secondleftammo < 0){
			secondleftammo = 0;
		}
	}

	// cout << secondleftammo << endl;


	pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, secondstep, secondleftammo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, chamberRoomNo);

	

	pair<vector<int>, int> thirdpathandcost;
	int thirdleftammo;
	
	if(thirdstep == 0){
		thirdpathandcost = cf.first;
		thirdleftammo = secondleftammo - thirdpathandcost.second;
		if(thirdleftammo < 0){
			thirdleftammo = 0;
		}
	}

	else{
		thirdpathandcost = cf.second;
		thirdleftammo = secondleftammo - thirdpathandcost.second;
		if(thirdleftammo < 0){
			thirdleftammo = 0;
		}
	}


	ofstream myfile;
  	myfile.open ("the3.out");

	cout << thirdleftammo << endl;
	myfile << thirdleftammo << endl;


	//////////////////////////////////////

	reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
	reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
	reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());

	for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
		bestpath.push_back(*t);
	}

	bestpath.pop_back();

	for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
		bestpath.push_back(*t);
	}

	bestpath.pop_back();

	for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
		bestpath.push_back(*t);
	}

	cout << bestpath.size() << endl;
	myfile << bestpath.size() << endl;

	std::vector<int>::iterator t;

	for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
		cout << *t << " ";
		myfile << *t << " ";
	}

	t = bestpath.end()-1;
	cout << *t;
	myfile << *t;

	cout << endl;
	myfile.close();


	}




	if(ammoRoomCount == 1){
		// cout << "tek mermiye girdim" << endl;

		int ammoroom = ammoRoomsGraph[0].first;
		int ammocount = ammoRoomsGraph[0].second;
		int bestindexnoammo;
		int bestindexstartkeyammo;
		int bestindexkeyscientistammo;
		int bestindexscientistbossammo;

		int bestindexnoammoleft;
		int bestindexstartkeyammoleft;
		int bestindexkeyscientistammoleft;
		int bestindexscientistbossammoleft;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> a = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);
		int evencost0 = a.first.second;
		int x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
		}
		int oddcost0 = a.second.second;
		int y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
		}

		// cout << "xo " << x0 << endl;
		// cout << "yo " << y0 << endl;

		// cout << a.second.first.size() << endl;
		// cout << a.first.first[0] << endl;
		// cout << a.first.first[1] << endl;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> b0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> b1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		int evencost1 = b0.first.second;
		int x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
		}
		int oddcost1 = b0.second.second;
		int y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
		}

		int evencost2 = b1.first.second;
		int x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
		}
		int oddcost2 = b1.second.second;
		int y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
		}

		// cout << "x1 " << x1 << endl;
		// cout << "y1 " << y1 << endl;

		// cout << "x2 " << x2 << endl;
		// cout << "y2 " << y2 << endl;


		pair<pair<vector<int>, int>, pair<vector<int>, int>> c0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);


		int evencost3 = c0.first.second;
		int x3 = x1 - evencost3;

		int oddcost3 = c0.second.second;
		int y3 = x1 - oddcost3;


		int evencost4 = c1.first.second;
		int x4 = y1 - evencost4;

		int oddcost4 = c1.second.second;
		int y4 = y1 - oddcost4;


		int evencost5 = c2.first.second;
		int x5 = x2 - evencost5;

		int oddcost5 = c2.second.second;
		int y5 = x2 - oddcost5;


		int evencost6 = c3.first.second;
		int x6 = y2 - evencost6;

		int oddcost6 = c3.second.second;
		int y6 = y2 - oddcost6;


		vector<int> leftammos;
		leftammos.push_back(x3);
		leftammos.push_back(y3);
		leftammos.push_back(x4);
		leftammos.push_back(y4);
		leftammos.push_back(x5);
		leftammos.push_back(y5);
		leftammos.push_back(x6);
		leftammos.push_back(y6);

		int pickedindex = 0;
		int pickedammocount = x3;
		for(int i = 0; i < 8; i++){
			if(leftammos[i] > pickedammocount && leftammos[i] >= 0){
				pickedindex = i;
				pickedammocount = leftammos[i];
			}
		}

		bestindexnoammo = pickedindex;
		bestindexnoammoleft = pickedammocount;



		vector<int> leftammos2(16);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos2[0] = -INT_MAX;
			leftammos2[1] = -INT_MAX;
			leftammos2[2] = -INT_MAX;
			leftammos2[3] = -INT_MAX;
			leftammos2[4] = -INT_MAX;
			leftammos2[5] = -INT_MAX;
			leftammos2[6] = -INT_MAX;
			leftammos2[7] = -INT_MAX;
		}
		x0 += ammocount;

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos2[8] = -INT_MAX;
			leftammos2[9] = -INT_MAX;
			leftammos2[10] = -INT_MAX;
			leftammos2[11] = -INT_MAX;
			leftammos2[12] = -INT_MAX;
			leftammos2[13] = -INT_MAX;
			leftammos2[14] = -INT_MAX;
			leftammos2[15] = -INT_MAX;
		}
		y0 += ammocount;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> bb0 = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> bb1 = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
		}
		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
		}

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
		}
		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
		}
    								

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc2 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc3 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
		}

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
		}


		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
		}

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
		}


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
		}

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
		}


		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
		}

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
		}


		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		int evencost7 = dd0.first.second;
		int x7 = x3- evencost7;

		int oddcost7 = dd0.second.second;
		int y7 = x3 - oddcost7;


		int evencost8 = dd1.first.second;
		int x8 = y3- evencost8;

		int oddcost8 = dd1.second.second;
		int y8 = y3 - oddcost8;


		int evencost9 = dd2.first.second;
		int x9 = x4- evencost9;

		int oddcost9 = dd2.second.second;
		int y9 = x4 - oddcost9;


		int evencost10 = dd3.first.second;
		int x10 = y4- evencost10;

		int oddcost10 = dd3.second.second;
		int y10 = y4 - oddcost10;


		int evencost11 = dd4.first.second;
		int x11 = x5- evencost11;

		int oddcost11 = dd4.second.second;
		int y11 = x5 - oddcost11;


		int evencost12 = dd5.first.second;
		int x12 = y5- evencost12;

		int oddcost12 = dd5.second.second;
		int y12 = y5 - oddcost12;


		int evencost13 = dd6.first.second;
		int x13 = x6- evencost13;

		int oddcost13 = dd6.second.second;
		int y13 = x6 - oddcost13;


		int evencost14 = dd7.first.second;
		int x14 = y6- evencost14;

		int oddcost14 = dd7.second.second;
		int y14 = y6 - oddcost14;


		//burayi -intmax degilse pushbackle seklinde yaz
		if(leftammos2[0] != -INT_MAX){
			leftammos2[0] = (x7);
		}
		if(leftammos2[1] != -INT_MAX){
			leftammos2[1] = (y7);
		}
		if(leftammos2[2] != -INT_MAX){
			leftammos2[2] = (x8);
		}
		if(leftammos2[3] != -INT_MAX){
			leftammos2[3] = (y8);
		}
		if(leftammos2[4] != -INT_MAX){
			leftammos2[4] = (x9);
		}
		if(leftammos2[5] != -INT_MAX){
			leftammos2[5] = (y9);
		}
		if(leftammos2[6] != -INT_MAX){
			leftammos2[6] = (x10);
		}
		if(leftammos2[7] != -INT_MAX){
			leftammos2[7] = (y10);
		}
		if(leftammos2[8] != -INT_MAX){
			leftammos2[8] = (x11);
		}
		if(leftammos2[9] != -INT_MAX){
			leftammos2[9] = (y11);
		}
		if(leftammos2[10] != -INT_MAX){
			leftammos2[10] = (x12);
		}
		if(leftammos2[11] != -INT_MAX){
			leftammos2[11] = (y12);
		}
		if(leftammos2[12] != -INT_MAX){
			leftammos2[12] = (x13);
		}
		if(leftammos2[13] != -INT_MAX){
			leftammos2[13] = (y13);
		}
		if(leftammos2[14] != -INT_MAX){
			leftammos2[14] = (x14);
		}
		if(leftammos2[15] != -INT_MAX){
			leftammos2[15] = (y14);
		}				

		int pickedindex2 = 0;
		int pickedammocount2 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos2[i] > pickedammocount2 && leftammos2[i] >= 0 && leftammos2[i] != -INT_MAX){
				pickedindex2 = i;
				pickedammocount2 = leftammos2[i];
			}
		}

		bestindexstartkeyammo = pickedindex2;
		bestindexstartkeyammoleft = pickedammocount2;




		vector<int> leftammos3(16);

		aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos3[0] = -INT_MAX;
			leftammos3[1] = -INT_MAX;
			leftammos3[2] = -INT_MAX;
			leftammos3[3] = -INT_MAX;
			leftammos3[4] = -INT_MAX;
			leftammos3[5] = -INT_MAX;
			leftammos3[6] = -INT_MAX;
			leftammos3[7] = -INT_MAX;
		}

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos3[8] = -INT_MAX;
			leftammos3[9] = -INT_MAX;
			leftammos3[10] = -INT_MAX;
			leftammos3[11] = -INT_MAX;
			leftammos3[12] = -INT_MAX;
			leftammos3[13] = -INT_MAX;
			leftammos3[14] = -INT_MAX;
			leftammos3[15] = -INT_MAX;
		}

		bb0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);

		bb1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
			leftammos3[0] = -INT_MAX;
			leftammos3[1] = -INT_MAX;
			leftammos3[2] = -INT_MAX;
			leftammos3[3] = -INT_MAX;
		}
		x1 += ammocount;

		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
			leftammos3[4] = -INT_MAX;
			leftammos3[5] = -INT_MAX;
			leftammos3[6] = -INT_MAX;
			leftammos3[7] = -INT_MAX;
		}
		y1 += ammocount;

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
			leftammos3[8] = -INT_MAX;
			leftammos3[9] = -INT_MAX;
			leftammos3[10] = -INT_MAX;
			leftammos3[11] = -INT_MAX;
		}
		x2 += ammocount;

		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
			leftammos3[12] = -INT_MAX;
			leftammos3[13] = -INT_MAX;
			leftammos3[14] = -INT_MAX;
			leftammos3[15] = -INT_MAX;
		}
		y2 += ammocount;
    								

		cc0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc2 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc3 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
		}

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
		}


		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
		}

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
		}


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
		}

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
		}


		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
		}

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
		}


		dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		evencost7 = dd0.first.second;
		x7 = x3- evencost7;

		oddcost7 = dd0.second.second;
		y7 = x3 - oddcost7;


		evencost8 = dd1.first.second;
		x8 = y3- evencost8;

		oddcost8 = dd1.second.second;
		y8 = y3 - oddcost8;


		evencost9 = dd2.first.second;
		x9 = x4- evencost9;

		oddcost9 = dd2.second.second;
		y9 = x4 - oddcost9;


		evencost10 = dd3.first.second;
		x10 = y4- evencost10;

		oddcost10 = dd3.second.second;
		y10 = y4 - oddcost10;


		evencost11 = dd4.first.second;
		x11 = x5- evencost11;

		oddcost11 = dd4.second.second;
		y11 = x5 - oddcost11;


		evencost12 = dd5.first.second;
		x12 = y5- evencost12;

		oddcost12 = dd5.second.second;
		y12 = y5 - oddcost12;


		evencost13 = dd6.first.second;
		x13 = x6- evencost13;

		oddcost13 = dd6.second.second;
		y13 = x6 - oddcost13;


		evencost14 = dd7.first.second;
		x14 = y6- evencost14;

		oddcost14 = dd7.second.second;
		y14 = y6 - oddcost14;


		
		if(leftammos3[0] != -INT_MAX){
			leftammos3[0] = (x7);
		}
		if(leftammos3[1] != -INT_MAX){
			leftammos3[1] = (y7);
		}
		if(leftammos3[2] != -INT_MAX){
			leftammos3[2] = (x8);
		}
		if(leftammos3[3] != -INT_MAX){
			leftammos3[3] = (y8);
		}
		if(leftammos3[4] != -INT_MAX){
			leftammos3[4] = (x9);
		}
		if(leftammos3[5] != -INT_MAX){
			leftammos3[5] = (y9);
		}
		if(leftammos3[6] != -INT_MAX){
			leftammos3[6] = (x10);
		}
		if(leftammos3[7] != -INT_MAX){
			leftammos3[7] = (y10);
		}
		if(leftammos3[8] != -INT_MAX){
			leftammos3[8] = (x11);
		}
		if(leftammos3[9] != -INT_MAX){
			leftammos3[9] = (y11);
		}
		if(leftammos3[10] != -INT_MAX){
			leftammos3[10] = (x12);
		}
		if(leftammos3[11] != -INT_MAX){
			leftammos3[11] = (y12);
		}
		if(leftammos3[12] != -INT_MAX){
			leftammos3[12] = (x13);
		}
		if(leftammos3[13] != -INT_MAX){
			leftammos3[13] = (y13);
		}
		if(leftammos3[14] != -INT_MAX){
			leftammos3[14] = (x14);
		}
		if(leftammos3[15] != -INT_MAX){
			leftammos3[15] = (y14);
		}				

		int pickedindex3 = 0;
		int pickedammocount3 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos3[i] > pickedammocount3 && leftammos3[i] >= 0 && leftammos3[i] != -INT_MAX){
				pickedindex3 = i;
				pickedammocount3 = leftammos3[i];
			}
		}

		bestindexkeyscientistammo = pickedindex3;
		bestindexkeyscientistammoleft = pickedammocount3;



		vector<int> leftammos4(16);

		aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}

		bb0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);

		bb1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
		}

		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
		}

		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}
    								

		cc0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			
		}
		x3 += ammocount;

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
			
		}
		y3 += ammocount;

		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
		}
		x4 += ammocount;

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}
		y4 += ammocount;


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
		}
		x5 += ammocount;

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
		}
		y5 += ammocount;

		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
		}
		x6 += ammocount;

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}
		y6 += ammocount;


		dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		evencost7 = dd0.first.second;
		x7 = x3- evencost7;

		oddcost7 = dd0.second.second;
		y7 = x3 - oddcost7;


		evencost8 = dd1.first.second;
		x8 = y3- evencost8;

		oddcost8 = dd1.second.second;
		y8 = y3 - oddcost8;


		evencost9 = dd2.first.second;
		x9 = x4- evencost9;

		oddcost9 = dd2.second.second;
		y9 = x4 - oddcost9;


		evencost10 = dd3.first.second;
		x10 = y4- evencost10;

		oddcost10 = dd3.second.second;
		y10 = y4 - oddcost10;


		evencost11 = dd4.first.second;
		x11 = x5- evencost11;

		oddcost11 = dd4.second.second;
		y11 = x5 - oddcost11;


		evencost12 = dd5.first.second;
		x12 = y5- evencost12;

		oddcost12 = dd5.second.second;
		y12 = y5 - oddcost12;


		evencost13 = dd6.first.second;
		x13 = x6- evencost13;

		oddcost13 = dd6.second.second;
		y13 = x6 - oddcost13;


		evencost14 = dd7.first.second;
		x14 = y6- evencost14;

		oddcost14 = dd7.second.second;
		y14 = y6 - oddcost14;


		
		if(leftammos4[0] != -INT_MAX){
			leftammos4[0] = (x7);
		}
		if(leftammos4[1] != -INT_MAX){
			leftammos4[1] = (y7);
		}
		if(leftammos4[2] != -INT_MAX){
			leftammos4[2] = (x8);
		}
		if(leftammos4[3] != -INT_MAX){
			leftammos4[3] = (y8);
		}
		if(leftammos4[4] != -INT_MAX){
			leftammos4[4] = (x9);
		}
		if(leftammos4[5] != -INT_MAX){
			leftammos4[5] = (y9);
		}
		if(leftammos4[6] != -INT_MAX){
			leftammos4[6] = (x10);
		}
		if(leftammos4[7] != -INT_MAX){
			leftammos4[7] = (y10);
		}
		if(leftammos4[8] != -INT_MAX){
			leftammos4[8] = (x11);
		}
		if(leftammos4[9] != -INT_MAX){
			leftammos4[9] = (y11);
		}
		if(leftammos4[10] != -INT_MAX){
			leftammos4[10] = (x12);
		}
		if(leftammos4[11] != -INT_MAX){
			leftammos4[11] = (y12);
		}
		if(leftammos4[12] != -INT_MAX){
			leftammos4[12] = (x13);
		}
		if(leftammos4[13] != -INT_MAX){
			leftammos4[13] = (y13);
		}
		if(leftammos4[14] != -INT_MAX){
			leftammos4[14] = (x14);
		}
		if(leftammos4[15] != -INT_MAX){
			leftammos4[15] = (y14);
		}	

		int pickedindex4 = 0;
		int pickedammocount4 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos4[i] > pickedammocount4 && leftammos4[i] >= 0 && leftammos4[i] != -INT_MAX){
				pickedindex4 = i;
				pickedammocount4 = leftammos4[i];
			}
		}

		bestindexscientistbossammo = pickedindex4;
		bestindexscientistbossammoleft = pickedammocount4;

		//ammoleftlerden en kucugunu bul her biri icin farkli bi sistem kur

		// cout << "noammo" << bestindexnoammoleft << endl;
		// cout << "startkey" << bestindexstartkeyammoleft << endl;
		// cout << "keyscientist" << bestindexkeyscientistammoleft << endl;
		// cout << "scientistboss" << bestindexscientistbossammoleft << endl;

		if(bestindexnoammoleft >= bestindexstartkeyammoleft && bestindexnoammoleft >= bestindexkeyscientistammoleft && bestindexnoammoleft >= bestindexscientistbossammoleft){//ammosuz en iyisi cikmis

			bool thirdstep = pickedindex % 2;
			bool secondstep = int(pickedindex/2) % 2;
			bool firststep = int(pickedindex/4);

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}


			ofstream myfile;
		  	myfile.open ("the3.out");

			cout << thirdleftammo << endl;
			myfile << thirdleftammo << endl;



			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			cout << bestpath.size() << endl;
			myfile << bestpath.size() << endl;

			std::vector<int>::iterator t;

			for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
				cout << *t << " ";
				myfile << *t << " ";
			}

			t = bestpath.end()-1;
			cout << *t;
			myfile << *t;

			cout << endl;
			myfile.close();

		}



		//mermi ekledigin yerleri ve fonksiyonlari degistirmeyi unutma copy paste yapabilirsin kalanini

		else if(bestindexstartkeyammoleft >= bestindexnoammoleft && bestindexstartkeyammoleft >= bestindexkeyscientistammoleft && bestindexstartkeyammoleft >= bestindexscientistbossammoleft){//ammo start key en iyisi cikmis
			
			bool fourthstep = pickedindex2 % 2;
			bool thirdstep = int(pickedindex2/2) % 2;
			bool secondstep = int(pickedindex2/4) % 2;
			bool firststep = int(pickedindex2/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second + ammocount;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second + ammocount;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			ofstream myfile;
		  	myfile.open ("the3.out");

			cout << fourthleftammo << endl;
			myfile << fourthleftammo << endl;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			cout << bestpath.size() << endl;
			myfile << bestpath.size() << endl;

			std::vector<int>::iterator t;

			for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
				cout << *t << " ";
				myfile << *t << " ";
			}

			t = bestpath.end()-1;
			cout << *t;
			myfile << *t;

			cout << endl;
			myfile.close();
		
		}





		else if(bestindexkeyscientistammoleft >= bestindexnoammoleft && bestindexkeyscientistammoleft >= bestindexstartkeyammoleft && bestindexkeyscientistammoleft >= bestindexscientistbossammoleft){//ammo key scientist en iyisi cikmis
			bool fourthstep = pickedindex3 % 2;
			bool thirdstep = int(pickedindex3/2) % 2;
			bool secondstep = int(pickedindex3/4) % 2;
			bool firststep = int(pickedindex3/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second + ammocount;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second + ammocount;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			ofstream myfile;
		  	myfile.open ("the3.out");

			cout << fourthleftammo << endl;
			myfile << fourthleftammo << endl;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			cout << bestpath.size() << endl;
			myfile << bestpath.size() << endl;

			std::vector<int>::iterator t;

			for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
				cout << *t << " ";
				myfile << *t << " ";
			}

			t = bestpath.end()-1;
			cout << *t;
			myfile << *t;

			cout << endl;
			myfile.close();
		}






		else if(bestindexscientistbossammoleft >= bestindexnoammoleft && bestindexscientistbossammoleft >= bestindexstartkeyammoleft && bestindexscientistbossammoleft >= bestindexkeyscientistammoleft){// ammo scientist boss en iyisi cikmis
			
			bool fourthstep = pickedindex4 % 2;
			bool thirdstep = int(pickedindex4/2) % 2;
			bool secondstep = int(pickedindex4/4) % 2;
			bool firststep = int(pickedindex4/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second + ammocount;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second + ammocount;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			ofstream myfile;
		  	myfile.open ("the3.out");

			cout << fourthleftammo << endl;
			myfile << fourthleftammo << endl;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			cout << bestpath.size() << endl;
			myfile << bestpath.size() << endl;

			std::vector<int>::iterator t;

			for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
				cout << *t << " ";
				myfile << *t << " ";
			}

			t = bestpath.end()-1;
			cout << *t;
			myfile << *t;

			cout << endl;
			myfile.close();
		}
	}


		else if(ammoRoomCount == 2){

			// cout << "help" << endl;
			for(int q=0; q <2; q++){

		int ammoroom = ammoRoomsGraph[q].first;
		int ammocount = ammoRoomsGraph[q].second;
		int bestindexnoammo;
		int bestindexstartkeyammo;
		int bestindexkeyscientistammo;
		int bestindexscientistbossammo;

		int bestindexnoammoleft;
		int bestindexstartkeyammoleft;
		int bestindexkeyscientistammoleft;
		int bestindexscientistbossammoleft;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> a = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);
		int evencost0 = a.first.second;
		int x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
		}
		int oddcost0 = a.second.second;
		int y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
		}

		// cout << "xo " << x0 << endl;
		// cout << "yo " << y0 << endl;

		// cout << a.second.first.size() << endl;
		// cout << a.first.first[0] << endl;
		// cout << a.first.first[1] << endl;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> b0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> b1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		int evencost1 = b0.first.second;
		int x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
		}
		int oddcost1 = b0.second.second;
		int y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
		}

		int evencost2 = b1.first.second;
		int x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
		}
		int oddcost2 = b1.second.second;
		int y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
		}

		// cout << "x1 " << x1 << endl;
		// cout << "y1 " << y1 << endl;

		// cout << "x2 " << x2 << endl;
		// cout << "y2 " << y2 << endl;


		pair<pair<vector<int>, int>, pair<vector<int>, int>> c0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> c3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);


		int evencost3 = c0.first.second;
		int x3 = x1 - evencost3;

		int oddcost3 = c0.second.second;
		int y3 = x1 - oddcost3;


		int evencost4 = c1.first.second;
		int x4 = y1 - evencost4;

		int oddcost4 = c1.second.second;
		int y4 = y1 - oddcost4;


		int evencost5 = c2.first.second;
		int x5 = x2 - evencost5;

		int oddcost5 = c2.second.second;
		int y5 = x2 - oddcost5;


		int evencost6 = c3.first.second;
		int x6 = y2 - evencost6;

		int oddcost6 = c3.second.second;
		int y6 = y2 - oddcost6;


		vector<int> leftammos;
		leftammos.push_back(x3);
		leftammos.push_back(y3);
		leftammos.push_back(x4);
		leftammos.push_back(y4);
		leftammos.push_back(x5);
		leftammos.push_back(y5);
		leftammos.push_back(x6);
		leftammos.push_back(y6);

		int pickedindex = 0;
		int pickedammocount = x3;
		for(int i = 0; i < 8; i++){
			if(leftammos[i] > pickedammocount && leftammos[i] >= 0){
				pickedindex = i;
				pickedammocount = leftammos[i];
			}
		}

		bestindexnoammo = pickedindex;
		bestindexnoammoleft = pickedammocount;



		vector<int> leftammos2(16);
		pair<pair<vector<int>, int>, pair<vector<int>, int>> aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos2[0] = -INT_MAX;
			leftammos2[1] = -INT_MAX;
			leftammos2[2] = -INT_MAX;
			leftammos2[3] = -INT_MAX;
			leftammos2[4] = -INT_MAX;
			leftammos2[5] = -INT_MAX;
			leftammos2[6] = -INT_MAX;
			leftammos2[7] = -INT_MAX;
		}
		x0 += ammocount;

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos2[8] = -INT_MAX;
			leftammos2[9] = -INT_MAX;
			leftammos2[10] = -INT_MAX;
			leftammos2[11] = -INT_MAX;
			leftammos2[12] = -INT_MAX;
			leftammos2[13] = -INT_MAX;
			leftammos2[14] = -INT_MAX;
			leftammos2[15] = -INT_MAX;
		}
		y0 += ammocount;

		pair<pair<vector<int>, int>, pair<vector<int>, int>> bb0 = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> bb1 = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
		}
		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
		}

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
		}
		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
		}
    								

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc2 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> cc3 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
		}

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
		}


		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
		}

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
		}


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
		}

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
		}


		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
		}

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
		}


		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		pair<pair<vector<int>, int>, pair<vector<int>, int>> dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		int evencost7 = dd0.first.second;
		int x7 = x3- evencost7;

		int oddcost7 = dd0.second.second;
		int y7 = x3 - oddcost7;


		int evencost8 = dd1.first.second;
		int x8 = y3- evencost8;

		int oddcost8 = dd1.second.second;
		int y8 = y3 - oddcost8;


		int evencost9 = dd2.first.second;
		int x9 = x4- evencost9;

		int oddcost9 = dd2.second.second;
		int y9 = x4 - oddcost9;


		int evencost10 = dd3.first.second;
		int x10 = y4- evencost10;

		int oddcost10 = dd3.second.second;
		int y10 = y4 - oddcost10;


		int evencost11 = dd4.first.second;
		int x11 = x5- evencost11;

		int oddcost11 = dd4.second.second;
		int y11 = x5 - oddcost11;


		int evencost12 = dd5.first.second;
		int x12 = y5- evencost12;

		int oddcost12 = dd5.second.second;
		int y12 = y5 - oddcost12;


		int evencost13 = dd6.first.second;
		int x13 = x6- evencost13;

		int oddcost13 = dd6.second.second;
		int y13 = x6 - oddcost13;


		int evencost14 = dd7.first.second;
		int x14 = y6- evencost14;

		int oddcost14 = dd7.second.second;
		int y14 = y6 - oddcost14;


		
		if(leftammos2[0] != -INT_MAX){
			leftammos2[0] = (x7);
		}
		if(leftammos2[1] != -INT_MAX){
			leftammos2[1] = (y7);
		}
		if(leftammos2[2] != -INT_MAX){
			leftammos2[2] = (x8);
		}
		if(leftammos2[3] != -INT_MAX){
			leftammos2[3] = (y8);
		}
		if(leftammos2[4] != -INT_MAX){
			leftammos2[4] = (x9);
		}
		if(leftammos2[5] != -INT_MAX){
			leftammos2[5] = (y9);
		}
		if(leftammos2[6] != -INT_MAX){
			leftammos2[6] = (x10);
		}
		if(leftammos2[7] != -INT_MAX){
			leftammos2[7] = (y10);
		}
		if(leftammos2[8] != -INT_MAX){
			leftammos2[8] = (x11);
		}
		if(leftammos2[9] != -INT_MAX){
			leftammos2[9] = (y11);
		}
		if(leftammos2[10] != -INT_MAX){
			leftammos2[10] = (x12);
		}
		if(leftammos2[11] != -INT_MAX){
			leftammos2[11] = (y12);
		}
		if(leftammos2[12] != -INT_MAX){
			leftammos2[12] = (x13);
		}
		if(leftammos2[13] != -INT_MAX){
			leftammos2[13] = (y13);
		}
		if(leftammos2[14] != -INT_MAX){
			leftammos2[14] = (x14);
		}
		if(leftammos2[15] != -INT_MAX){
			leftammos2[15] = (y14);
		}				

		int pickedindex2 = 0;
		int pickedammocount2 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos2[i] > pickedammocount2 && leftammos2[i] >= 0 && leftammos2[i] != -INT_MAX){
				pickedindex2 = i;
				pickedammocount2 = leftammos2[i];
			}
		}

		bestindexstartkeyammo = pickedindex2;
		bestindexstartkeyammoleft = pickedammocount2;



		vector<int> leftammos3(16);

		aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos3[0] = -INT_MAX;
			leftammos3[1] = -INT_MAX;
			leftammos3[2] = -INT_MAX;
			leftammos3[3] = -INT_MAX;
			leftammos3[4] = -INT_MAX;
			leftammos3[5] = -INT_MAX;
			leftammos3[6] = -INT_MAX;
			leftammos3[7] = -INT_MAX;
		}

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos3[8] = -INT_MAX;
			leftammos3[9] = -INT_MAX;
			leftammos3[10] = -INT_MAX;
			leftammos3[11] = -INT_MAX;
			leftammos3[12] = -INT_MAX;
			leftammos3[13] = -INT_MAX;
			leftammos3[14] = -INT_MAX;
			leftammos3[15] = -INT_MAX;
		}

		bb0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);

		bb1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, ammoroom);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
			leftammos3[0] = -INT_MAX;
			leftammos3[1] = -INT_MAX;
			leftammos3[2] = -INT_MAX;
			leftammos3[3] = -INT_MAX;
		}
		x1 += ammocount;

		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
			leftammos3[4] = -INT_MAX;
			leftammos3[5] = -INT_MAX;
			leftammos3[6] = -INT_MAX;
			leftammos3[7] = -INT_MAX;
		}
		y1 += ammocount;

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
			leftammos3[8] = -INT_MAX;
			leftammos3[9] = -INT_MAX;
			leftammos3[10] = -INT_MAX;
			leftammos3[11] = -INT_MAX;
		}
		x2 += ammocount;

		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
			leftammos3[12] = -INT_MAX;
			leftammos3[13] = -INT_MAX;
			leftammos3[14] = -INT_MAX;
			leftammos3[15] = -INT_MAX;
		}
		y2 += ammocount;
    								

		cc0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc2 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);

		cc3 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, scientistRoomNo);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
		}

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
		}


		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
		}

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
		}


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
		}

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
		}


		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
		}

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
		}


		dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		evencost7 = dd0.first.second;
		x7 = x3- evencost7;

		oddcost7 = dd0.second.second;
		y7 = x3 - oddcost7;


		evencost8 = dd1.first.second;
		x8 = y3- evencost8;

		oddcost8 = dd1.second.second;
		y8 = y3 - oddcost8;


		evencost9 = dd2.first.second;
		x9 = x4- evencost9;

		oddcost9 = dd2.second.second;
		y9 = x4 - oddcost9;


		evencost10 = dd3.first.second;
		x10 = y4- evencost10;

		oddcost10 = dd3.second.second;
		y10 = y4 - oddcost10;


		evencost11 = dd4.first.second;
		x11 = x5- evencost11;

		oddcost11 = dd4.second.second;
		y11 = x5 - oddcost11;


		evencost12 = dd5.first.second;
		x12 = y5- evencost12;

		oddcost12 = dd5.second.second;
		y12 = y5 - oddcost12;


		evencost13 = dd6.first.second;
		x13 = x6- evencost13;

		oddcost13 = dd6.second.second;
		y13 = x6 - oddcost13;


		evencost14 = dd7.first.second;
		x14 = y6- evencost14;

		oddcost14 = dd7.second.second;
		y14 = y6 - oddcost14;


		
		if(leftammos3[0] != -INT_MAX){
			leftammos3[0] = (x7);
		}
		if(leftammos3[1] != -INT_MAX){
			leftammos3[1] = (y7);
		}
		if(leftammos3[2] != -INT_MAX){
			leftammos3[2] = (x8);
		}
		if(leftammos3[3] != -INT_MAX){
			leftammos3[3] = (y8);
		}
		if(leftammos3[4] != -INT_MAX){
			leftammos3[4] = (x9);
		}
		if(leftammos3[5] != -INT_MAX){
			leftammos3[5] = (y9);
		}
		if(leftammos3[6] != -INT_MAX){
			leftammos3[6] = (x10);
		}
		if(leftammos3[7] != -INT_MAX){
			leftammos3[7] = (y10);
		}
		if(leftammos3[8] != -INT_MAX){
			leftammos3[8] = (x11);
		}
		if(leftammos3[9] != -INT_MAX){
			leftammos3[9] = (y11);
		}
		if(leftammos3[10] != -INT_MAX){
			leftammos3[10] = (x12);
		}
		if(leftammos3[11] != -INT_MAX){
			leftammos3[11] = (y12);
		}
		if(leftammos3[12] != -INT_MAX){
			leftammos3[12] = (x13);
		}
		if(leftammos3[13] != -INT_MAX){
			leftammos3[13] = (y13);
		}
		if(leftammos3[14] != -INT_MAX){
			leftammos3[14] = (x14);
		}
		if(leftammos3[15] != -INT_MAX){
			leftammos3[15] = (y14);
		}				

		int pickedindex3 = 0;
		int pickedammocount3 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos3[i] > pickedammocount3 && leftammos3[i] >= 0 && leftammos3[i] != -INT_MAX){
				pickedindex3 = i;
				pickedammocount3 = leftammos3[i];
			}
		}
		
		bestindexkeyscientistammo = pickedindex3;
		bestindexkeyscientistammoleft = pickedammocount3;




		vector<int> leftammos4(16);

		aa = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, keyofScientistRoomNo);

		evencost0 = aa.first.second;
		x0 = startingAmmo - evencost0;
		if(x0 < 0){
			x0 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}

		oddcost0 = aa.second.second;
		y0 = startingAmmo - oddcost0;
		if(y0 < 0){
			y0 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}

		bb0 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 0, x0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);

		bb1 = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, 1, y0, 
    										keyofScientistRoomNo, scientistRoomNo,
    										chamberRoomNo, scientistRoomNo);


		evencost1 = bb0.first.second;
		x1 = x0 - evencost1;
		if(x1 < 0){
			x1 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
		}

		oddcost1 = bb0.second.second;
		y1 = x0 - oddcost1;
		if(y1 < 0){
			y1 = 0;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}

		evencost2 = bb1.first.second;
		x2 = y0 - evencost2;
		if(x2 < 0){
			x2 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
		}

		oddcost2 = bb1.second.second;
		y2 = y0 - oddcost2;
		if(y2 < 0){
			y2 = 0;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}
    								

		cc0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y1, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 0, x2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);

		cc3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, 1, y2, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, ammoroom);


		evencost3 = cc0.first.second;
		x3 = x1 - evencost3;
		if(x3 < 0){
			x3 = 0;
			leftammos4[0] = -INT_MAX;
			leftammos4[1] = -INT_MAX;
			
		}
		x3 += ammocount;

		oddcost3 = cc0.second.second;
		y3 = x1 - oddcost3;
		if(y3 < 0){
			y3 = 0;
			leftammos4[2] = -INT_MAX;
			leftammos4[3] = -INT_MAX;
			
		}
		y3 += ammocount;

		evencost4 = cc1.first.second;
		x4 = y1 - evencost4;
		if(x4 < 0){
			x4 = 0;
			leftammos4[4] = -INT_MAX;
			leftammos4[5] = -INT_MAX;
		}
		x4 += ammocount;

		oddcost4 = cc1.second.second;
		y4 = y1 - oddcost4;
		if(y4 < 0){
			y4 = 0;
			leftammos4[6] = -INT_MAX;
			leftammos4[7] = -INT_MAX;
		}
		y4 += ammocount;


		evencost5 = cc2.first.second;
		x5 = x2 - evencost5;
		if(x5 < 0){
			x5 = 0;
			leftammos4[8] = -INT_MAX;
			leftammos4[9] = -INT_MAX;
		}
		x5 += ammocount;

		oddcost5 = cc2.second.second;
		y5 = x2 - oddcost5;
		if(y5 < 0){
			y5 = 0;
			leftammos4[10] = -INT_MAX;
			leftammos4[11] = -INT_MAX;
		}
		y5 += ammocount;

		evencost6 = cc3.first.second;
		x6 = y2 - evencost6;
		if(x6 < 0){
			x6 = 0;
			leftammos4[12] = -INT_MAX;
			leftammos4[13] = -INT_MAX;
		}
		x6 += ammocount;

		oddcost6 = cc3.second.second;
		y6 = y2 - oddcost6;
		if(y6 < 0){
			y6 = 0;
			leftammos4[14] = -INT_MAX;
			leftammos4[15] = -INT_MAX;
		}
		y6 += ammocount;


		dd0 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd1 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y3, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd2 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd3 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y4, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd4 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd5 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y5, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd6 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 0, x6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		dd7 = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, 1, y6, 
	    										keyofScientistRoomNo, scientistRoomNo,
	    										chamberRoomNo, chamberRoomNo);

		evencost7 = dd0.first.second;
		x7 = x3- evencost7;

		oddcost7 = dd0.second.second;
		y7 = x3 - oddcost7;


		evencost8 = dd1.first.second;
		x8 = y3- evencost8;

		oddcost8 = dd1.second.second;
		y8 = y3 - oddcost8;


		evencost9 = dd2.first.second;
		x9 = x4- evencost9;

		oddcost9 = dd2.second.second;
		y9 = x4 - oddcost9;


		evencost10 = dd3.first.second;
		x10 = y4- evencost10;

		oddcost10 = dd3.second.second;
		y10 = y4 - oddcost10;


		evencost11 = dd4.first.second;
		x11 = x5- evencost11;

		oddcost11 = dd4.second.second;
		y11 = x5 - oddcost11;


		evencost12 = dd5.first.second;
		x12 = y5- evencost12;

		oddcost12 = dd5.second.second;
		y12 = y5 - oddcost12;


		evencost13 = dd6.first.second;
		x13 = x6- evencost13;

		oddcost13 = dd6.second.second;
		y13 = x6 - oddcost13;


		evencost14 = dd7.first.second;
		x14 = y6- evencost14;

		oddcost14 = dd7.second.second;
		y14 = y6 - oddcost14;


		
		if(leftammos4[0] != -INT_MAX){
			leftammos4[0] = (x7);
		}
		if(leftammos4[1] != -INT_MAX){
			leftammos4[1] = (y7);
		}
		if(leftammos4[2] != -INT_MAX){
			leftammos4[2] = (x8);
		}
		if(leftammos4[3] != -INT_MAX){
			leftammos4[3] = (y8);
		}
		if(leftammos4[4] != -INT_MAX){
			leftammos4[4] = (x9);
		}
		if(leftammos4[5] != -INT_MAX){
			leftammos4[5] = (y9);
		}
		if(leftammos4[6] != -INT_MAX){
			leftammos4[6] = (x10);
		}
		if(leftammos4[7] != -INT_MAX){
			leftammos4[7] = (y10);
		}
		if(leftammos4[8] != -INT_MAX){
			leftammos4[8] = (x11);
		}
		if(leftammos4[9] != -INT_MAX){
			leftammos4[9] = (y11);
		}
		if(leftammos4[10] != -INT_MAX){
			leftammos4[10] = (x12);
		}
		if(leftammos4[11] != -INT_MAX){
			leftammos4[11] = (y12);
		}
		if(leftammos4[12] != -INT_MAX){
			leftammos4[12] = (x13);
		}
		if(leftammos4[13] != -INT_MAX){
			leftammos4[13] = (y13);
		}
		if(leftammos4[14] != -INT_MAX){
			leftammos4[14] = (x14);
		}
		if(leftammos4[15] != -INT_MAX){
			leftammos4[15] = (y14);
		}	

		int pickedindex4 = 0;
		int pickedammocount4 = x7;
		for(int i = 0; i < 16; i++){
			if(leftammos4[i] > pickedammocount4 && leftammos4[i] >= 0 && leftammos4[i] != -INT_MAX){
				pickedindex4 = i;
				pickedammocount4 = leftammos4[i];
			}
		}

		bestindexscientistbossammo = pickedindex4;
		bestindexscientistbossammoleft = pickedammocount4;

		//ammoleftlerden en kucugunu bul her biri icin farkli bi sistem kur

		// cout << bestindexnoammoleft << endl;
		// cout << bestindexstartkeyammoleft << endl;
		// cout << bestindexkeyscientistammoleft << endl;
		// cout << bestindexscientistbossammoleft << endl;

		if(bestindexnoammoleft >= bestindexstartkeyammoleft && bestindexnoammoleft >= bestindexkeyscientistammoleft && bestindexnoammoleft >= bestindexscientistbossammoleft){//ammosuz en iyisi cikmis

			bool thirdstep = pickedindex % 2;
			bool secondstep = int(pickedindex/2) % 2;
			bool firststep = int(pickedindex/4);

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}


			bestleftammo = thirdleftammo;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}


		}



		//mermi ekledigin yerleri ve fonksiyonlari degistirmeyi unutma copy paste yapabilirsin kalanini

		else if(bestindexstartkeyammoleft >= bestindexnoammoleft && bestindexstartkeyammoleft >= bestindexkeyscientistammoleft && bestindexstartkeyammoleft >= bestindexscientistbossammoleft){//ammo start key en iyisi cikmis
			
			bool fourthstep = pickedindex2 % 2;
			bool thirdstep = int(pickedindex2/2) % 2;
			bool secondstep = int(pickedindex2/4) % 2;
			bool firststep = int(pickedindex2/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second + ammocount;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second + ammocount;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, ammoroom, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			bestleftammo = fourthleftammo;



			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

		
		}





		else if(bestindexkeyscientistammoleft >= bestindexnoammoleft && bestindexkeyscientistammoleft >= bestindexstartkeyammoleft && bestindexkeyscientistammoleft >= bestindexscientistbossammoleft){//ammo key scientist en iyisi cikmis
			bool fourthstep = pickedindex3 % 2;
			bool thirdstep = int(pickedindex3/2) % 2;
			bool secondstep = int(pickedindex3/4) % 2;
			bool firststep = int(pickedindex3/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second + ammocount;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second + ammocount;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, ammoroom, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			bestleftammo = fourthleftammo;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}


		}






		else if(bestindexscientistbossammoleft >= bestindexnoammoleft && bestindexscientistbossammoleft >= bestindexstartkeyammoleft && bestindexscientistbossammoleft >= bestindexkeyscientistammoleft){// ammo scientist boss en iyisi cikmis
			
			bool fourthstep = pickedindex4 % 2;
			bool thirdstep = int(pickedindex4/2) % 2;
			bool secondstep = int(pickedindex4/4) % 2;
			bool firststep = int(pickedindex4/8);

			// cout << firststep << endl;
			// cout << secondstep << endl;
			// cout << thirdstep << endl;
			// cout << fourthstep << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> af = dijkstraStartKey(connectionGraph, lockedRooms, roomCount, 1, 1, startingAmmo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, keyofScientistRoomNo);


			pair<vector<int>, int> firstpathandcost;
			int firstleftammo;
			
			if(firststep == 0){
				firstpathandcost = af.first;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			else{
				firstpathandcost = af.second;
				firstleftammo = startingAmmo - firstpathandcost.second;
				if(firstleftammo < 0){
					firstleftammo = 0;
				}
			}

			// cout << firstpathandcost.second << endl;
			// cout << firstleftammo << endl;

			pair<pair<vector<int>, int>, pair<vector<int>, int>> bf = dijkstraKeyScientist(connectionGraph, lockedRooms, roomCount, keyofScientistRoomNo, firststep, firstleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, scientistRoomNo);


			pair<vector<int>, int> secondpathandcost;
			int secondleftammo;
			
			if(secondstep == 0){
				secondpathandcost = bf.first;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			else{
				secondpathandcost = bf.second;
				secondleftammo = firstleftammo - secondpathandcost.second;
				if(secondleftammo < 0){
					secondleftammo = 0;
				}
			}

			// cout << secondleftammo << endl;


			pair<pair<vector<int>, int>, pair<vector<int>, int>> cf = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, scientistRoomNo, secondstep, secondleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, ammoroom);

			

			pair<vector<int>, int> thirdpathandcost;
			int thirdleftammo;
			
			if(thirdstep == 0){
				thirdpathandcost = cf.first;
				thirdleftammo = secondleftammo - thirdpathandcost.second + ammocount;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			else{
				thirdpathandcost = cf.second;
				thirdleftammo = secondleftammo - thirdpathandcost.second + ammocount;
				if(thirdleftammo < 0){
					thirdleftammo = 0;
				}
			}

			pair<pair<vector<int>, int>, pair<vector<int>, int>> df = dijkstraScientistBoss(connectionGraph, lockedRooms, roomCount, ammoroom, thirdstep, thirdleftammo, 
		    										keyofScientistRoomNo, scientistRoomNo,
		    										chamberRoomNo, chamberRoomNo);


			pair<vector<int>, int> fourthpathandcost;
			int fourthleftammo;
			
			if(fourthstep == 0){
				fourthpathandcost = df.first;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}

			else{
				fourthpathandcost = df.second;
				fourthleftammo = thirdleftammo - fourthpathandcost.second;
				if(fourthleftammo < 0){
					fourthleftammo = 0;
				}
			}


			bestleftammo = fourthleftammo;


			reverse(firstpathandcost.first.begin(), firstpathandcost.first.end());
			reverse(secondpathandcost.first.begin(), secondpathandcost.first.end());
			reverse(thirdpathandcost.first.begin(), thirdpathandcost.first.end());
			reverse(fourthpathandcost.first.begin(), fourthpathandcost.first.end());

			for(std::vector<int>::iterator t=firstpathandcost.first.begin(); t !=firstpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=secondpathandcost.first.begin(); t !=secondpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=thirdpathandcost.first.begin(); t !=thirdpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}

			bestpath.pop_back();

			for(std::vector<int>::iterator t=fourthpathandcost.first.begin(); t !=fourthpathandcost.first.end(); ++t){
				bestpath.push_back(*t);
			}


		}

		bestofthebests[q] = {bestpath,bestleftammo};
		bestpath = {};

		}//for bitisi

		if(bestofthebests[0].second > bestofthebests[1].second){
			bestpath = bestofthebests[0].first;
			bestleftammo = bestofthebests[0].second;
		}

		else{
			bestpath = bestofthebests[1].first;
			bestleftammo = bestofthebests[1].second;
		}

		ofstream myfile;
  		myfile.open ("the3.out");

  		cout << bestleftammo << endl;
		myfile << bestleftammo << endl;

		cout << bestpath.size() << endl;
		myfile << bestpath.size() << endl;

		std::vector<int>::iterator t;

		for(t=bestpath.begin(); t !=bestpath.end()-1; ++t){
			cout << *t << " ";
			myfile << *t << " ";
		}

		t = bestpath.end()-1;
		cout << *t;
		myfile << *t;

		cout << endl;
		myfile.close();


	}


	// cout << keyofScientistRoomNo << endl;
	// cout << scientistRoomNo << endl;

	// cout << b0.second.first.size() << endl;//2
	// cout << b0.second.first[0] << endl;//4
	// cout << b0.second.second << endl;//1
	// cout << b0.first.first.size() << endl;//3
	// cout << b0.first.first[0] << endl;//4
	// cout << b0.first.second << endl;//5
	// cout << b1.second.first.size() << endl;//3
	// cout << b1.second.first[0] << endl;//4
	// cout << b1.second.second << endl;//5
	// cout << b1.first.first.size() << endl;//2
	// cout << b1.first.first[0] << endl;//4
	// cout << b1.first.second << endl;//1

	/*
	vector<vector<int>> dist(2, vector<int>(roomCount+1,1));
	vector<vector<bool>> visited(2, vector<bool>(roomCount+1));
	vector<vector<vector<int>>> parent(2, vector<vector<int>>(roomCount+1));
	for(int i=1; i<roomCount+1; i++){
		visited[0][i] = 0;
		visited[1][i] = 0;
		dist[0][i] = INT_MAX;
		dist[1][i] = INT_MAX;
	}

	dist[0][1] = 0;
	dist[1][1] = 0;
	parent[0][1].push_back(-1);
	parent[1][1].push_back(-1);
    multiset < pair < int , pair<int,bool> > > s;

    s.insert({0 , {1,1}});  

    while(!s.empty()){

        pair < int , pair<int,bool> > p = *s.begin();        // pop the vertex with the minimum distance
        s.erase(s.begin());

        int x = p.second.first;
        int wei = p.first;
        bool time = p.second.second;
        bool nexttime = !time;
        if( visited[time][x] ) continue;                  // check if the popped vertex is visited before
        visited[time][x] = true;

        for(int i = 0; i < connectionGraph[x].size(); i++){
        	int e = connectionGraph[x][i].first;
            int w = connectionGraph[x][i].second;
            bool doorisLocked = false;

        	for(int j = 0; j < (lockedRooms[nexttime]).size(); j++){
        		if(lockedRooms[nexttime][j] == e){
        			doorisLocked = true;
        			// cout << "oda " << e << endl;
        		}
        	}
        	
        	// if(e == scientistRoomNo){
        	// 	bool now = time;
        	// 	bool keyFound = false;
        	// 	int k = x;
        	// 	while(k != -1){
        	// 		if (k == keyofScientistRoomNo){
        	// 			keyFound = true;
        	// 			break;
        	// 		}
        	// 		if(!(parent[!now][k].empty())){
        	// 			now = !now;
        	// 			k = parent[now][k].back();
        	// 			continue;
        	// 		}
        	// 		else{
        	// 			break;
        	// 		}
        	// 	}
        	// 	if(!keyFound){
        	// 		continue;
        	// 	}
        		
        	// 	// for(int k = x; k != -1, !parent[!now][k].empty() ;now = !now, k = parent[now][k].back()){
        	// 	// 	cout << "-----" << endl;
        	// 	// 	if (k == keyofScientistRoomNo){
        	// 	// 		keyFound = true;
        	// 	// 	}
        	// 	// }
        	// 	// if(!keyFound){
        	// 	// 	continue;
        	// 	// }
        	// }
        	
        	// if(e == chamberRoomNo){
        	// 	bool now = time;
        	// 	bool keyFound = false;
        	// 	int k = x;
        	// 	while(k != -1){
        	// 		if (k == scientistRoomNo){
        	// 			keyFound = true;
        	// 			break;
        	// 		}
        	// 		if(!(parent[!now][k].empty())){
        	// 			now = !now;
        	// 			k = parent[now][k].back();
        	// 			continue;
        	// 		}
        	// 		else{
        	// 			break;
        	// 		}
        	// 	}
        	// 	if(!keyFound){
        	// 		continue;
        	// 	}
        	// }

        	if(doorisLocked){
        		// cout << "next " << nexttime << endl;
        		continue;
        	}

            if((dist[time][x] + w < dist[nexttime][e]) && (startingAmmo - dist[time][x] >= w )){            // check if the next vertex distance could be minimized
                dist[nexttime][e] = dist[time][x] + w;
                s.insert({dist[nexttime][e], {e , nexttime}});           // insert the next vertex with the updated distance
                parent[nexttime][e].push_back(x);
            }
        }
    }
    */

    // cout << parent[0][3].size() << " " << parent[0][3][0] << endl;//1
    // cout << parent[1][3].size() << " " << parent[1][3][0] << endl;//5
    // cout << parent[0][5].size() << " " << parent[0][5][0] << endl;//4
    // cout << parent[1][5].size() << " " << parent[1][5][0] << endl;//3
    // cout << parent[0][4].size() << " " << parent[0][4][0] << endl;//5
    // cout << parent[1][4].size() << " " << parent[1][4][0] << endl;//3
    // cout << parent[0][6].size() << " " << parent[0][6][0] << endl;//5
    // cout << parent[1][6].size() << " " << parent[1][6][0] << endl;//3
    // cout << parent[0][7].size() << " " << parent[0][7][0] << endl;//4
    // cout << parent[1][7].size() << " " << parent[1][7][0] << endl;//5
    // //cout << parent[5].size() << endl;
    // cout << parent[7][0] << endl;
    // cout << visited[7] << endl;
    // cout << dist[7].first << endl;
    // cout << dist[5].first << endl;




	return 0;
}

