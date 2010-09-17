

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <vector>
#include "PlanetWars.h"

class Simulator {
 public:
  // Constructor
  Simulator( PlanetWars &pw );
  
  // Return Planet Wars object.
  &Planetwars getPw();

  // Obtain my total ship count.
  int MyShipCount() const;
  
  // Obtain my ship count for ships on a planet.
  int MyPlanetShipCount() const;

  // Obtain my ship count in fleets.
  int MyFleetShipCount() const;
  
  // Total enemy ship count.
  int EnemyShipCount() const;
  
  // Total enemy planet ship count.
  int EnemyPlanetShipCount() const;
  
  // Total enemy fleet ship count.
  int EnemyFleetShipCount() const;

  // Total planets.
  int MyPlanetCount() const;
  
  // Total Enemy planets.
  int EnemyPlanetCount() const;

  // Total Neutral planets.
  int NeutralPlanetCount() const;

  // Value of a Planet
  int ValueOfPlanet() const;
  // distance
  // how many ships does the planet have
  // Am I winning or loosing?
  // Is it close to an enemy planet?
  // Do I have enough ships to invate it. 
  
  // Defend a planet.
  void DefendPlanet() const;

  // Create a pool of planets to send from
  void DeployPool() const;

  // SIMULATIONS
  void State(int turn);
  
 private:

#endif
