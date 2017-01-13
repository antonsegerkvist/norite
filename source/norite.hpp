//
//  norite.hpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#ifndef norite_hpp
#define norite_hpp

/** Enumerator which defines the state of the game. **/
enum GameMode
{
  GM_NORMAL // Game session.
};

/** Enumerator which defines what mode we're switching to. **/
enum SwitchMode
{
  SM_NONE, // We are not switching.
};

/** Contains methods and information for the game state. **/
class Norite
{
public:
  
  /**
   * Get exit game flag.
   * @return True when event loop should exit.
   */
  static inline bool GetExitGameFlag()
  { return s_exit_game_flag; }
  
  /**
   * Handle exit game requests.
   */
  static void HandleExitGameRequest();
  
private:
  
  static bool s_exit_game_flag;
  static GameMode s_game_mode;
  static SwitchMode s_switch_mode;
  
};

#endif /* norite_hpp */
