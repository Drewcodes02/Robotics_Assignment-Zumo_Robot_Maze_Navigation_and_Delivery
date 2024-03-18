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
3. Delivery Simulation: Once the zumo detects an object(house) with its proximity sensors, the zumo will stop and emit a beep to simulate a delivery before continuing its navigation.
4. 180 Degree Turn: To make sure the zumo doesnt get stuck it will perform a 180 degree turn every 10 seconds if no object is detected.

Acknowledgements I'd like to thank Sheffield Hallam University's Department of Computing for the opportunity to work on this project. Special thanks to our instructors and peers for their guidance and feedback throughout the development process.
