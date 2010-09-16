#include <iostream>
#include "PlanetWars.h"
#include <map>
#include <algorithm>

bool cmpPlanet (Planet lhp, Planet rhp) {
  return (lhp.NumShips() < rhp.NumShips());
}


// The DoTurn function is where your code goes. The PlanetWars object contains
// the state of the game, including information about all planets and fleets
// that currently exist. Inside this function, you issue orders using the
// pw.IssueOrder() function. For example, to send 10 ships from planet 3 to
// planet 8, you would say pw.IssueOrder(3, 8, 10).
//
// There is already a basic strategy in place here. You can use it as a
// starting point, or you can throw it out entirely and replace it with your
// own. Check out the tutorials and articles on the contest website at
// http://www.ai-contest.com/resources.
void DoTurn(const PlanetWars& pw) {


  /*
  // Checks to see which player has a higher growth rate.
  // Sets the growth rate accordingly.
  int numFleets;
  if (pw.MyProduction() >= pw.EnemyProduction()) {
    numFleets = 10;
  } else {
    numFleets = 20;
  }

  // (1) If we currently have a fleet in flight, just do nothing.
  if (pw.MyFleets().size() >= numFleets) { // Changed from 2 to 20
    return;
  }

  // (2) Find my strongest planet.
  int source = -1;
  double source_score = -999999.0;
  int source_num_ships = 0;
  std::vector<Planet> my_planets = pw.MyPlanets();
  for (int i = 0; i < my_planets.size(); ++i) {
    const Planet& p = my_planets[i];
    double score = (double)p.NumShips() / (1 + p.GrowthRate());
    if (score > source_score) {
      source_score = score;
      source = p.PlanetID();
      source_num_ships = p.NumShips();
    }
  }
  // (3) Find the weakest enemy or neutral planet.
  int dest = -1;
  double dest_score = -999999.0;
  std::vector<Planet> not_my_planets = pw.NotMyPlanets();
  for (int i = 0; i < not_my_planets.size(); ++i) {
    const Planet& p = not_my_planets[i];
    double score = (double)(1 + p.GrowthRate()) / p.NumShips();
    if (score > dest_score) {
      dest_score = score;
      dest = p.PlanetID();
    }
  }
  // (4) Send half the ships from my strongest planet to the weakest
  // planet that I do not own.
  //if (source >= 0 && dest >= 0) {
  //  int num_ships = source_num_ships / 2;
  //  pw.IssueOrder(source, dest, num_ships);
  //}
  
  // (4) Half is such a crude number. Let's try sending one more than what the planet currently has.
  if (source >= 0 && dest >= 0 ) {
    int num_ships = pw.GetPlanet(dest).NumShips() + 1;
    if (source_num_ships < num_ships) {
      pw.IssueOrder(soucre, dest, num_ships);
    }
  }
  
  */

  //***********************************
  //** New Approach
  //***********************************
  

  //  bool cmpPlanet (Planet lhp, Planet rhp) {
  //  return (lhp.NumShips() < rhp.NumShips());
  //}

  // Contains fleets which have been newly created.
  // std::vector<Fleet> active_fleets;

  // Contains my planets.
  std::vector<Planet> my_planets = pw.MyPlanets();

  // Contains enemy planets.
  std::vector<Planet> not_my_planets = pw.NotMyPlanets();
  
  // Sort My Planets 
  std::sort(my_planets.begin(), my_planets.end(), cmpPlanet);
  
  // Sort unclaimed / enemy planets by number of ships.
  std::sort(not_my_planets.begin(), not_my_planets.end(), cmpPlanet);
  
  // Contains the minimum number of ships that should be on a planet.
  int minShips = 10;

  // Create a map to keep track of what fleet has been sent out.
  std::map<int,int>  active_fleets;

  // For each planet
  for (int i=0; i < my_planets.size(); i++) {
  
    int available_ships = my_planets[i].NumShips() - minShips;
    
    if (available_ships > minShips) {
      
      for (int j=0; j < not_my_planets.size(); j++) {
        
        if ( (available_ships >= not_my_planets[j].NumShips()) && ( active_fleets.find( not_my_planets[j].PlanetID() ) == active_fleets.end() )) {
          if ( pw.MyFleetByDestCount(not_my_planets[j].PlanetID()) == 0 ) {
            available_ships-= not_my_planets[j].NumShips() + 2;
          
            active_fleets[ not_my_planets[j].PlanetID() ] = not_my_planets[j].NumShips()+2;
          
            pw.IssueOrder( my_planets[i].PlanetID(), not_my_planets[j].PlanetID(), not_my_planets[j].NumShips() +2);
          }
        }
      } 
    }
  }
}



// This is just the main game loop that takes care of communicating with the
// game engine for you. You don't have to understand or change the code below.
int main(int argc, char *argv[]) {
  std::string current_line;
  std::string map_data;
  while (true) {
    int c = std::cin.get();
    current_line += (char)c;
    if (c == '\n') {
      if (current_line.length() >= 2 && current_line.substr(0, 2) == "go") {
        PlanetWars pw(map_data);
        map_data = "";
        DoTurn(pw);
	pw.FinishTurn();
      } else {
        map_data += current_line;
      }
      current_line = "";
    }
  }
  return 0;
}
