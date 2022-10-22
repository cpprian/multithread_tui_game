// ======================= Server =======================
// thread_1: run game loop
// thread_2: run network loop
    // run network loop (player sender)
    // run network loop (player receiver)
    // listen for new connctions
    // listen for player exit
// thread_3: run new beast
    // next beast needs to be spawned by new thread


// if error has occured, restart game and player
// if player has exited, delete player, but not game


// ================= Client=============
// thread_1: run game loop
// thread_2: run network loop
    // player sender
    // player receiver


// if error has occured, player is removed from game
// if player has exited, player is removed from game

// if player collides with beast, player is removed from game
    // put player treasure in place where player was
// if player collides with player, both players respawn
    // put players treasures in place where players were in a big treasure


// ===================== MAP ============================
// the game will look like below

// ███████████████████████████████████████████████████
// █c  █*      █   #####       █         █ccccccc█   █   Server's PID: 1370
// █ █ ███ ███ ███████████ ███ █ ███████ ███ █████ t █    Campsite X/Y: 23/11
// █ █ 3 █ █ █           █ █ █   █     █     █   █   █    Round number: 32234
// █ ███ █ █ ███###█████ █ █ █████ █████████████ ███ █   
// █ █T█   █           █ █ █ ##  █      c█       █ █ █   Parameter:   Player1  Player2  Player3  Player4 
// █ █ █████ ███ ███████ █ █ █ ███ ███ ███ ███ █ █ █ █    PID         1390     1420     1900     -
// █ █   *     █ █       █ █ █     █   █   █ █ █   █ █    Type        CPU      CPU      HUMAN    -
// █ █ ███████ ███ ███████ █████ ███ ███ ███ █ ███ █ █    Curr X/Y    37/15    16/21    04/03    --/--
// █ █T█     █   █   █     █   █   █    *    █ █ █ █ █    Deaths      3        9        0        -
// █ ███ ███ ███ ███ ███ ███ █ ███ ███████████ █ █ █ █
// █ █   █       █ █  c█  A  █ █   █ █  D    █ █   █ █    Coins
// █ █ ██████#██ █ ███ ███ ███ ███ █ █ █████ █ █ ███ █        carried 30       213      0
// █ █    #█   █ █   █   █   █   █   █ █     █ █ █   █        brought 1300     33       0
// █ █ █ ##█ ███ ███ ███ ███████ ███ █ ███ ███ █ █ ███
// █ █ █## █    #  █   █ █  ###  █   █  1█     █ █ █ █
// █ █ █#  ███████ █ █ █ █ ██#████ █████ ███████ █ █ █   Legend: 
// █ █ █#      █   █ █ █   █     █   █ █       ##█   █    1234 - players
// █ █████████ █ ███ ███████ ███████ █ █████ █ ##███ █    █    - wall
// █ █#      █ █     █     █       █   █   █ █ ##  █ █    #    - bushes (slow down)
// █ █ █████ █ ███████ █ ███ █████ ███ █ █ ███#█████ █    *    - wild beast
// █###█     █     2   █  ###█## █     █ █   █###### █    c    - one coin                  D – dropped treasure 
// █c███ █████████████████████#█ ███████ ███ █#    # █    t    - treasure (10 coins)
// █ccc█      *          ######█##         █    ##   █    T    - large treasure (50 coins)
// ███████████████████████████████████████████████████    A    - campsite