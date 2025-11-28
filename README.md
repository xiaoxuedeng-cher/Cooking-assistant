# Cooking-assistant
# Real-Time Cooking Assistant

A C++ application that provides interactive, step-by-step cooking guidance with built-in timers.
Instead of reading long recipe blogs or watching endless cooking videos, users can follow clear, structured instructions delivered one step at a time with real-time countdowns and confirmation prompts to ensure smooth and confident cooking.
  
  # Why This Application Was Developed
Many beginners struggle with cooking because:
- Recipes online are long, cluttered, or confusing
- Timing and ordering steps correctly can feel overwhelming
- Video tutorials move too fast or too slow
- People often lose track of where they are during cooking
This app solves those problems by offering:
- A simple and guided experience
- One instruction at a time
- Automatic countdown timers
- User confirmation before advancing
- A lightweight, text-file-based recipe format
The goal is to help beginners—or anyone wanting a structured workflow-cook efficiently and confidently.

# Architecture Diagram
![image -1-](assets/image%20-1-.png)


# Project Structure
/Cooking Assistant
│
├── Step.h
├── Step.cpp
│
├── CookingAssistant.h
├── CookingAssistant.cpp
│
├── main.cpp
│
└── recipes/
    └── omelette.txt
    └── pasta.txt

# How to Compile &Run
- Compile
g++ main.cpp Step.cpp CookingAssistant.cpp -o cooking_assistant

- Run
./cooking_assistant
- Provide a recipe file
recipes/omelette.txt
[each line: seconds|description of the step]

# Key Challenges & Solutions
1. Defining the Input Recipe Data Format
   Deciding how users should provide cooking instructions in a way that is easy to write, easy to parse, and flexible enough for different types of recipes.
   Solution: The application uses a simple structured text format where each line contains:  seconds | step description
2. Real-Time Countdown Display in the Console
   Displaying a live countdown timer in a terminal window without flicker or printing hundreds of new lines.
   Solution: use"std::this_thread::sleep_for(std::chrono::seconds(1));" to create a visually clean countdown
3. Supporting a “Confirmation Buffer” After the Timer Ends
   Even after a timer reaches zero, a user may still need a few seconds to finish a physical action (e.g., plating food, stirring sauce, cleaning pan).
   Solution:
   Added a confirmation buffer prompt immediately after countdown:std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   
   

# Future Enhancements
1. Add a full Recipe class
   A more complete Recipe class can be introduced to organize recipe information more effectively. This class may include:
   ～ Title
   ～ Ingredients list
   ～ Step sequence
   ～ Difficulty level
   ～ Tags or categories

2. Add a skip-timer feature
   Some cooking steps do not require precise timing. A future improvement is to allow users to skip the countdown (for example, by typing skip) and move directly to the confirmation step. This would provide more flexibility and a smoother user experience.

3. Directory-based recipe picker
   Implement automatic scanning of the recipes/ directory and list all available recipe files for the user to choose from. This removes the need to type file paths manually and makes recipe selection more convenient.
   
# GenAI Reflection and Extension
## A) GenAI Reflection (Command-Line Implementation)
1. GenAI tools used
    I used ChatGPT as my primary AI assistant during the development of this command-line application. 

2. How I used GenAI + Example prompts

- Designing the real-time countdown timer
  I asked the AI how to implement a smooth, real-time countdown in a C++ console application using std::chrono and std::this_thread::sleep_for, and how to update the same line without printing new lines each second.
  prompt:
  “Can you help me write a C++ function that shows a real-time countdown timer in the console, updating every second on the same line?”
  
- Implementing the confirmation buffer after the timer
  I asked how to add a “buffer” after the timer reaches 0, so that the program waits for the user to confirm they have really finished the step before moving on.
  prompt:
  “Can you add a buffer between each step after the time counting down to 0 which allows the user to confirm that they have finished the previous step?”
  The AI suggested using std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); after printing a confirmation message
  
- Code optimization and debugging
  I also asked the AI to help refactor and debug my code, including splitting it into modular files (Step.h/.cpp, CookingAssistant.h/.cpp, main.cpp), improving input handling, and making the file parsing more robust.
  prompts:
  “Can you reorganize the C++ file into modular files including a header file, source files and the main file?”
  
3. How AI influenced my understanding
   AI assistance helped me:
   ~Understand how std::cin.ignore works and why input buffers behave differently after various read operations
   ~Learn best practices for modular C++ project organization
   ~Gain a clearer grasp of real-time console updates using std::chrono
   ~Identify cleaner patterns for writing reusable and readable C++ code
   ~Improve the clarity and professionalism of my overall documentation
   Instead of simply generating code, GenAI acted as a supportive coding mentor, helping me reason about the design and understand why certain solutions work.
   
4. Parts of the project that benefited most/least from AI
**Most Benefit:**
~Architecture design → clear separation of Step, Recipe, and CookingAssistant
~File parsing logic → improved robustness and whitespace trimming
~User experience design → confirmation buffer, prompts, skip timer
~Documentation → polished README and explanations

**Least Benefit:**
~Core logic that I already understood well, such as:
       Basic loops,Conditionals,Simple class structures

These parts were straightforward enough without AI assistance.

5. How I would use AI differently in future projects

In the future, I would use AI a bit differently. I would start using it earlier in the project to explore different design ideas before writing any code. I would also try AI tools that can work directly inside my code editor, so debugging and suggestions happen instantly while I write. I would ask AI to help create unit tests or think of edge cases to make my program more reliable. Most importantly, I would double-check AI’s work more carefully, because sometimes the code it generates looks correct but contains small mistakes. Overall, AI is very helpful, but it still needs human judgment and careful review.

## B) GenAI Extension (No-Code Demonstration)
For the GenAI extension, I used loveable to prototype an enhanced feature of my cooking assistant. The goal was to explore how AI tools can rapidly turn ideas into working interfaces.

**Screenshots of My Prompts**
![Prompt asking the tool to build a complete cooking assistant](assets/17642702853256.jpg)
![Prompt asking to unify timer + next-step button](assets/17642703379492.jpg)
![Prompt asking to show instruction text before starting timer](assets/17642703804583.jpg)
![Prompt asking to remove the 10-second warning](assets/17642704128640.jpg)

**Screenshots / Snippets of Generated Output**
![](assets/17642706633964.jpg)![](assets/17642710342558.jpg)

A full cooking assistant UI with: Recipe text box, “Start Cooking” button, Sample recipes (e.g., Simple Pasta, Scrambled Eggs), Clean, warm visual design with orange accents.

1. What part I tried to reproduce
I tried to recreate the core interactive workflow of my C++ application:
    ~Display a recipe step
    ~Let the user start a timer
    ~Add confirmation between steps
    ~Move step-by-step through the full recipe
The goal was to see whether a no-code AI tool could mimic the same logic visually.
2. How close the AI-generated version was to my own
Surprisingly close, the AI tool:
    ~Parsed recipe text into separate steps
    ~Built a step-by-step interface automatically
    ~Generated countdown timers
    ~Added confirmation buttons
    ~Allowed users to load sample recipes
    ~Created a clean visual UI with almost no instructions

It didn’t match every detail of my C++ implementation (especially input handling and edge-case behavior), but the overall logic and user flow were very similar.

3. What surprised me about the AI’s performance
The speed and intuition were impressive for a no-code tool：
    ～The AI created an attractive, polished UI without me describing colors or layout.
    ～It understood the idea of a step-by-step cooking flow with timers from a short prompt.
    ～It made useful assumptions (like adding progress indicators) that I hadn't requested.
    ～When I asked for design changes (“combine buttons”, “remove warning”, “change flow”), it updated the entire app instantly.
    
4. Whether such tools could be reliable in professional engineering work    
   
   AI no-code tools can be useful in real engineering work, but only for certain tasks. They work well for quickly creating prototypes, testing design ideas, and building simple interfaces or basic logic. 
   However, they are not reliable enough for complex systems, time-critical features, or anything that requires very accurate or secure behavior. These tools are great for helping engineers get ideas started, but the important parts of a real product would still need to be carefully built and checked by human engineers.
