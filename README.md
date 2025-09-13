# Procedual Dungeon Generator in Unreal Engine

This is the procedual dungeon generator in Unreal Engine 5.5 generate the square shape of the dungon with the simple configuration and one click settings! 
Utilising a `Greedy Algorithm Approach` to create the diverse, square-shaped dungeon layouts with optimal room placement and connectivity. Thi system is designed for ARPG layout which needes for the unlimited playablity to the player. 

### Instructions 
1. Download the soruce code or clone the git repository.
2. right click the `.UProject` file and click the generate the visual studio file.
3. Open `.sln` file and build the project
4. When the project is opened generate the dungeon with dungeon number member variable in the actor setting.
5. then hit the play or simulate button and see the dungeon you generated!   

### Expected Results 

##### Low Stress Situation - 12 dungeons generated 
<img width="1702" height="1083" alt="sampleof12" src="https://github.com/user-attachments/assets/57fed672-8c4f-456a-a757-7458cb09ead5" />

##### Moderate Stress Situation - 100 dungeons generated 
<img width="1486" height="960" alt="sampleof100" src="https://github.com/user-attachments/assets/ac649292-9eac-43d9-a175-387c1808b3f5" />

##### High Stress Situation - 1000 dungeons generated 
<img width="1581" height="1110" alt="sampleof1000" src="https://github.com/user-attachments/assets/c8d7c54b-9fe3-4eb0-879b-026aea4dcaa3" />

##### In the Gameplay
<img width="1868" height="1097" alt="realgameplay" src="https://github.com/user-attachments/assets/f2b24d67-daca-48e1-afe4-a1f804760338" />

##### Usecase of the Dungeon Generator 
[![Watch the Dungeon Generator in Action](https://img.youtube.com/vi/xwpHRolSSrI/0.jpg)](https://www.youtube.com/watch?v=xwpHRolSSrI)

*Click the image above to watch the dungeon generator demo*

### Current Features 
- Configurable/adjustable Dungeon Settings in the Actor.
- Sample Dungeon block. 

### Known Problems/Bugs 
- GC may run when you generate +5k dungeons and possibly cause the bottlenecks in UE garbarge collector. 

### Requirements
- Unreal Engine above 5.4.4. or Higher. 
- C++ Compiler with Unreal Engine Support, Rider is recommanded.
