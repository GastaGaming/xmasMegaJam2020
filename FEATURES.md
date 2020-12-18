# Feature List
- [ ] Player
	- [ ] Movement with WASD
	- [ ] Shapeshift into present box (hide from enemies)
- [ ] Enemies
	- [ ] Detection meter
	- [ ] Patrol on set points
	- [ ] Detection cone 
- [ ] World
	- [ ] Load tiled map
	- [ ] Generate collision boxes from seperate layer
	- [ ] Load entities from tiled map (enemies, player...)

## Detection meter & cone
If the player is within a detection cone, an eye icon is displayed next to the patrolling enemy and starts gradually filling. Once the icon is completely filled, you are detected and the lose condition is met. If you leave the detection cone before the icon is completely filled, the icon starts to fade away. Once completely faded, the enemy will continue patrolling. The enemy will ignore you if you are hidden as a present.