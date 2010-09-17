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
  
  // Contains my fleets;
  std::vector<Fleet> my_fleets = pw.MyFleets();

  // Contains the minimum number of ships that should be on a planet.
  int minShips = 10;

  // Create a map to keep track of what fleet has been sent out.
  std::map<int,int>  active_fleets;

  // For each planet
  for (int i=0; i < my_planets.size(); i++) {
  
    int available_ships = my_planets[i].NumShips() - minShips;
    
    // Do I have enough ships available?
    if (available_ships > minShips) {
      
      // 
      for (int j=0; j < not_my_planets.size(); j++) {
        if ( (available_ships >= not_my_planets[j].NumShips()) ) {
          if ( active_fleets.find( not_my_planets[j].PlanetID() )  == active_fleets.end() ) {

            // is this an ememy planet?
            if ( not_my_planets[j].Owner() == 2 ) {
              int currentFleets =  pw.MyFleetByDestCount(not_my_planets[j].PlanetID());
              
              // Do I have any fleets headed there?
              if ( currentFleets > 0 ) {
                for (int k = 0; k < my_fleets.size(); ++k) {
                  if (my_fleets[k].DestinationPlanet() == not_my_planets[j].PlanetID() ) {
                    int fleet_delta = not_my_planets[j].NumShips() + (not_my_planets[j].GrowthRate() * my_fleets[k].TurnsRemaining()) + 2;
                    if ( fleet_delta > my_fleets[k].NumShips() ) {
                      int additional_fleet = (fleet_delta - my_fleets[k].NumShips()) + (not_my_planets[j].GrowthRate() * pw.Distance( my_planets[i].PlanetID(), not_my_planets[j].PlanetID() ) + 2);
                      if (available_ships > additional_fleet)
                        pw.IssueOrder( my_planets[i].PlanetID(), not_my_planets[j].PlanetID(), additional_fleet);
                      // NEW
                      my_planets[i].SetNumShips(my_planets[i].NumShips() - additional_fleet); // -= additional_fleet;
                    }
                  }
                }
              } else {
                int new_fleet_size = not_my_planets[j].GrowthRate() * pw.Distance( my_planets[i].PlanetID(), not_my_planets[j].PlanetID() ) + 2 + not_my_planets[j].NumShips();
                if (available_ships > new_fleet_size) {
                  active_fleets[ not_my_planets[j].PlanetID() ] = not_my_planets[j].NumShips()+2;
                  pw.IssueOrder( my_planets[i].PlanetID(), not_my_planets[j].PlanetID(), new_fleet_size);
                  my_planets[i].SetNumShips(my_planets[i].NumShips() - new_fleet_size);
                }
              }
            } else {
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
  }
  
  //Defense
  for (int i = my_planets.size()-1; i >= 0; --i) {
    int fleet_ship_count = pw.EnemyFleetByDestCount( my_planets[i].PlanetID() );
    if ( fleet_ship_count > 0  &&  active_fleets.find( my_planets[i].PlanetID() )  == active_fleets.end() ) {
      for (int j = 0; j < my_planets.size(); ++j) {
        if ( (my_planets[i].NumShips() - fleet_ship_count) < 1 ) {
          if ( (5 - my_planets[i].NumShips()) > my_planets[j].NumShips() ) {
            active_fleets[ my_planets[i].PlanetID() ] = my_planets[j].NumShips();
            pw.IssueOrder( my_planets[j].PlanetID(), my_planets[i].PlanetID(), (5 - my_planets[i].NumShips()) );
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
