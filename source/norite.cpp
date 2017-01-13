//
//  norite.cpp
//  norite
//
//  Created by Anton Segerkvist on 24/10/16.
//  Copyright © 2016 anton segerkvist. All rights reserved.
//

#include "norite.hpp"

/* static */ bool Norite::s_exit_game_flag = false;

/* static */ void Norite::HandleExitGameRequest()
{
  s_exit_game_flag = true;
}
