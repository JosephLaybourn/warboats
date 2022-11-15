/******************************************************************************/
/*!
\file   Ocean.cpp
\author Joey Laybourn
\par    email: j.laybourn\@digipen.edu
\par    DigiPen login: j.laybourn
\par    Course: CS170
\par    Section: B
\par    Assignment #2
\date   2/15/2018
\brief  
    This file contains the implementation of the following functions for the 
    WarBoats assignment.
      
    Functions include:
    
       + DumpOcean
       + CreateOcean
       + DestroyOcean
       + PlaceBoat
       + TakeShot
       + GetShotStats
       + GetGrid
       + GetDimentions
    
  Hours spent on this assignment: 2

  Specific portions that gave you the most trouble: const function weirdness
*/
/******************************************************************************/

#include "WarBoats.h" /*   enums:        Orientation, ShotResult, 
                                         DamageType, BoatPlacement 
                                      
                           structs:      Point, Boat, ShotStats             */

#include "Ocean.h"    /*   macros:       BOAT_LENGTH, HIT_OFFSET

                           functions:    TakeShot, PlaceBoat, GetShotStats,
                                         GetGrid, GetDimensions       
                                              
                           private vars: grid_, x_quadrants_, y_quadrants_, 
                                         stats, boats, num_boats            */
                           

namespace CS170
{

  namespace WarBoats
  {
  
    /*
    * ALL STUDENT IMPLEMENTATION GOES HERE
    */
  
    /**************************************************************************/
    /*!
      \brief
        Dynamically allocates an ocean struct, a boat struct, and an int array
      
      \param num_boats_
        total number of boats being drawn to the board
      
      \param x_quadrants
        the size of the board in the x direction
      
      \param y_quadrants
        the size of the board in the y direction
    */
    /**************************************************************************/
    Ocean::Ocean(int num_boats_, int x_quadrants, int y_quadrants)
    {
      //dynamically allocates a new grid
      grid_ = new int[x_quadrants * y_quadrants](); 
      
      //dynamically allocates a new boat
      boats = new Boat[num_boats_];
      
      //resets all stats values to 0
      stats.duplicates = 0;
      stats.hits = 0;
      stats.misses = 0;
      stats.sunk = 0;
      
      //initializes ocean values
      num_boats = num_boats_;
      x_quadrants_ = x_quadrants;
      y_quadrants_ = y_quadrants;
    }
    
    /**************************************************************************/
    /*!
      \brief
        Deletes all dynamically allocated data related to the ocean
    */
    /**************************************************************************/
    Ocean::~Ocean()
    {
      delete [] boats; //deletes all the boat structs
      delete [] grid_;  //deletes the ocean's grid
    }

    /**************************************************************************/
    /*!
      \brief
        checks if the boat to be placed is at a valid location.  
        If so, place it
      
      \param boat
        the boat to attach to the ocean
      
      \return BoatPlacement
    */
    /**************************************************************************/
    BoatPlacement Ocean::PlaceBoat(const Boat& boat)
    {
      // leftmost position
      const int boatPosx = boat.position.x;
      
      // top position
      const int boatPosy = boat.position.y;
      
      //actual position relative to the grid
      const int oceanPos = boatPosx + (boatPosy * x_quadrants_);

      /* rejects if user tries to play a boat
         too far to the left or too far up    */
      if (boatPosx < 0 || boatPosy < 0)
      {
        return bpREJECTED;
      }
      
      //checks cases horizontal placement
      if (boat.orientation == oHORIZONTAL)
      {
        //checks if the boat is placed too far to the right
        if (x_quadrants_ < boatPosx + BOAT_LENGTH)
        {
          return bpREJECTED;
        }
        //checks if the boat is placed too far up
        if (y_quadrants_ < boatPosy)
        {
          return bpREJECTED;
        }
        //checks if the boat is colliding with another one
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          if (grid_[oceanPos + i] > 0)
          {
            return bpREJECTED;
          }
        }
        //places the boat if it passes all the checks
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          //changes 4 sequential values to the boat ID
          grid_[oceanPos + i] = boat.ID;
        }
        
        /* updates the boat in the ocean struct 
           to the one in the parameter          */
        boats[boat.ID - 1] = boat;
        boats[boat.ID - 1].hits = 0;
        return bpACCEPTED;
      }
      //checks cases for vertical placement
      else
      {
        //checks if the boat is placed too far up
        if (y_quadrants_ < boatPosy + BOAT_LENGTH)
        {
          return bpREJECTED;
        }
        //checks if the boat is placed too far to the right
        if(x_quadrants_ < boatPosx)
        {
          return bpREJECTED;
        }
        //checks if the boat is colliding with another one
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          if (grid_[oceanPos + (x_quadrants_ * i)] > 0)
          {
            return bpREJECTED;
          }
        }
        //places the boat if it passes all the checks
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          //changes 4 sequential y values to the boat ID
          grid_[oceanPos + (x_quadrants_ * i)] = boat.ID;
        }
        
        /* updates the boat in the ocean struct
           to the one in the parameter          */
        boats[boat.ID - 1] = boat;
        boats[boat.ID - 1].hits = 0;
        return bpACCEPTED;
      }
      return bpREJECTED;
    }

    /**************************************************************************/
    /*!
      \brief
        takes a shot
      
      \param coordinate
        x and y position of the shot
      
      \return ShotResult
    */
    /**************************************************************************/
    ShotResult Ocean::TakeShot(const Point &coordinate)
    {
      /* IF the shot is out of the ocean (grid) THEN
         Return Illegal shot result                  */
      if (coordinate.x > x_quadrants_ || coordinate.x < 0)
      {
        return srILLEGAL;
      }
      if (coordinate.y > y_quadrants_ || coordinate.y < 0)
      {
        return srILLEGAL;
      }
      
      //converts x and y coordinates to a position on the grid
      const int conversion = coordinate.x + (x_quadrants_ * coordinate.y);
      
      //the value at that grid position
      const int shotPos = grid_[conversion];

      /* IF value is OK THEN
         Increment misses
         Set position to Blownup
         Return Miss shot result */
      if (shotPos == dtOK)
      {
        stats.misses += 1;
        grid_[conversion] = dtBLOWNUP;
        return srMISS;
      }
      
      /* IF value is a Duplicate THEN
         Increment duplicates
         Return Duplicate shot result */
      if (shotPos < 0 || shotPos > 100)
      {
        stats.duplicates += 1;
        return srDUPLICATE;
      }

      /* Increment hits for this boat
         Update position to boat hit  */
      boats[shotPos - 1].hits += 1;
      stats.hits += 1;
      grid_[conversion] += HIT_OFFSET;

      if (shotPos > 0 && shotPos < HIT_OFFSET)
      {
        /* IF number of hits for this boat is >= BOAT_LENGTH THEN
           Increment sunk                                         */
        if (boats[shotPos - 1].hits >= BOAT_LENGTH)
        {
          stats.sunk += 1;
          return srSUNK;
        }
        else
        {
          return srHIT;
        }
      }
      return srILLEGAL;
    }

    /**************************************************************************/
    /*!
      \brief
        gets data on hits, misses, duplicate shots, and sunken ships
        
      \return ShotStats
    */
    /**************************************************************************/
    ShotStats Ocean::GetShotStats() const
    {
      return stats; //returns the cumulative stats of the current game
    }

    /**************************************************************************/
    /*!
      \brief
        gets data on hits, misses, duplicate shots, and sunken ships
      
      \return int
    */
    /**************************************************************************/
    const int *Ocean::GetGrid() const
    {
      return grid_; //returns the ocean's grid size
    }
    
    /**************************************************************************/
    /*!
      \brief
        gets data on hits, misses, duplicate shots, and sunken ships
      
      \return Point
    */
    /**************************************************************************/
    Point Ocean::GetDimensions() const
    {
      //creats a point from the oceans's x and y sizes
      Point pt = {x_quadrants_, y_quadrants_}; 
      
      return pt; //!<returns that point
    }

  } // namespace WarBoats

} // namespace CS170

