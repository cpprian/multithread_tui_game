# Server
- thread_1: run game loop
- tread_2: run network loop 
    - run network loop (player sender)
    - run network loop (player receiver)
    - listen for new connctions
    - listen for player exit
- thread_3: run new beast
    - next beast needs to be spawned by new thread
- thread_4: keyboard handler
    - B/b - spawn new beast -> new thread
    - c/t/T - add coin/treasure/big treasure
    - Q/q - quit game


- if error has occured, restart game and player
- if player has exited, delete player, but not game


# Client
-  thread_1: run game loop
- thread_2: run network loop
    - player sender
    - player receiver


- if error has occured, player is removed from game
- if player has exited, player is removed from game

- if player collides with beast, player is removed from game
    - put player treasure in place where player was
- if player collides with player, both players respawn
    - put players treasures in place where players were in a big treasure
