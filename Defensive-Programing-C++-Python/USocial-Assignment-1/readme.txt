Social Networking Project
Introduction
This project is a simulation of a social networking platform where users can interact with each other through posts, messages, and media. 
The system supports both regular users and business users, with specialized functionality for each type.

Main Files
This project contains two main files that demonstrate different functionalities of the program.
Please find details about both main files below.

Main1 (Regular Main)
The first main file, referred to as "main1", is the regular main provided with the project.
To understand the expected output, please refer to the screenshot in the directory named main1.

Main2 (Exception Handling Main)
The second main file, referred to as "main2".
This version includes additional tests for exception handling, showcasing how the program behaves in various edge cases and when exceptions are thrown. 
A screenshot of the expected output can be found in the directory under the name main2.

Features
User Management: Register, remove, and retrieve users.
Posts: Users can create text posts or posts with media (audio, video, photo).
Friends Management: Users can add or remove friends.
Messaging: Users can send and receive messages.
Business Users: Special user type that allows messaging without friend constraints.
Media Management: Abstract media classes for handling different media types.

Classes
USocial: Main class for managing users.
User: Represents individual users, including posts and messages.
BusinessUser: Specialized user class for business accounts.
Message: Represents text messages sent between users.
Post: Represents posts that users can create.
Media: Abstract class for handling different media types.
Audio: Represents audio media.
Video: Represents video media.
Photo: Represents photo media.

Implementation Details
Static User ID Management
In this project, the static variable userId is used to generate unique identifiers for users. 
This ensures that each user is assigned a unique ID, and its encapsulated usage within the class ensures safety from unauthorized access or modification.

User ID Recycling
A queue, freeIds, is used to manage IDs that have been released when a user is removed. 
This ensures that IDs are reused efficiently, reducing the potential for ID exhaustion and ensuring that the system can handle dynamic user addition and removal.