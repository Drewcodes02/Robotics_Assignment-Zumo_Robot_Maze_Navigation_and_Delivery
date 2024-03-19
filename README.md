# Zumo Robot Maze Navigation and Delivery
This project involves programming a Zumo 32U4 robot to navigate through a maze (streets) and simulate deliveries by detecting objects (representing houses)

Project Overview: 
The Zumo uses line sensors for maze navigation and proximity sensors to detect delivery points, Its designed to perform autonomous deliveries within the maze, with wall detectiopn, obstacle avoidance and delivery confirmation mechanisms. 

Features
Maze Navigation: Utilises line sensors to navigate through the maze, simulating street navigation within a maze enviroment.
Object Detection: Procimity sensors to detect objects throughout the maze, simulating house deliveries.
Delivery Confirmation: Zumo beeps when finds a house to simlulate success delivery
Autonomous turn: 180 degree turn every few seconds to avoid zumo getting stuck as my stuck logic wwould fail time to time.

Operation Guide
1. Starting the zumo: Place the zumo at the starting point on the maze. Press the A button on thr robot to start the countdown and the navigation.
2. Maze Navigation: The zumo will navigate itself through the maze using line sensors to detect the black lines(walls) making decisions at intersections based on the programming logic
3. Delivery simulation:
- Scenario 1: On detecting an object (house) with its proximity sensors, the Zumo stops and emits a beep to simulate a delivery, then halts further navigation.
- Scenario 2: Continues navigation after making a delivery, aiming for multiple deliveries within a single journey through the maze.
4. 180 Degree Turn: To make sure the zumo doesnt get stuck it will perform a 180 degree turn every 10 seconds if no object is detected.

Scenarios
- Scenario 1: The Zumo is programmed to navigate through the maze and stopping after its first delivery is made, showcasing its ability to navigate to a specific target and comeplete the delivery task.
- Scenario 2: In this scenario, the zumo is programmed for multiple deliveries and continuing to navigate through the maze after each delivery, this shows the zumo capabilities to manage muluitple deliveries.

Acknowledgements I'd like to thank Sheffield Hallam University's Department of Computing for the opportunity to work on this project. Special thanks to my instructors and peers for their guidance and feedback throughout the development process.
