////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

#include "WarBoats.h"

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  //!< Length of a boat
    const int HIT_OFFSET = 100; //!< Add this to the boat ID

    /*!
      This class represents the "board" in WarBoats
    */
    class Ocean
    {
      public:
        
        // Public methods...
        
        //! The Ocean Constructor
        Ocean(int num_boats_, int x_quadrants, int y_quadrants);
        
        //! function to take a shot
        ShotResult TakeShot(const Point &coordinate);
        
        //! function to place a boat
        BoatPlacement PlaceBoat(const Boat& boat);
        
        //!function to get the shot stats
        ShotStats GetShotStats() const;
        
        //! ocean destructor
        ~Ocean();

          // Provided
        const int *GetGrid(void) const;
        Point GetDimensions(void) const;
        

      private:
        int *grid_;        //!< The 2D ocean
        int x_quadrants_;  //!< Ocean size along x-axis
        int y_quadrants_;  //!< Ocean size along y-axis
        ShotStats stats;   //!< Status of the attack
        Boat *boats;       //!< The dynamic array of boats
        int num_boats;     //!< Number of boats in the ocean
        
        // Other private members...

    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
